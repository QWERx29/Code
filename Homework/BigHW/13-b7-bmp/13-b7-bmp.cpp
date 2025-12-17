//2451317 冯久恒 大数据
#include <iostream>
#include <iomanip>  //用于debug信息打印时的格式
#include <fstream>
//不再允许加入任何头文件，特别是<Windows.h>/<Wingdi.h>，查到就是0分甚至是倒扣-20 ！！！
using namespace std;

#include "13-b7-bmp.h"

// 读取16位小端序
static uint16_t readU16(ifstream& file) 
{
    uint16_t value;
    file.read(reinterpret_cast<char*>(&value), sizeof(value));
    return value;
}

// 读取32位小端序
static uint32_t readU32(ifstream& file) 
{
    uint32_t value;
    file.read(reinterpret_cast<char*>(&value), sizeof(value));
    return value;
}

// 读取有符号32位小端序
static int32_t readS32(ifstream& file)
{
    int32_t value;
    file.read(reinterpret_cast<char*>(&value), sizeof(value));
    return value;
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：is_debug，用于查看调试信息，不需要实现（或者按自己的方式实现，对debug的输出不做要求）
            其余内容按需补充
***************************************************************************/
bitmap::bitmap(const char* const filename, const bool is_debug) : is_debug(is_debug), colorTable(nullptr), pixelData(nullptr)
{
    if (!readBMP(filename))
        cleanup();
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：按需补充
***************************************************************************/
bitmap::~bitmap()
{
    cleanup();
}

//按需增加内容

bool bitmap::readBMP(const char* filename) 
{
    ifstream file(filename, ios::binary);
    if (!file.is_open()) 
    {
        cerr << "打开文件[" << filename << "]失败." << endl;
        return false;
    }

    // 读取文件头 & 检查文件标识
    file.read(reinterpret_cast<char*>(&fileHeader), sizeof(fileHeader));
    if (fileHeader.signature != 0x4D42) // "BM"
    {
        cerr << "文件头读取错误." << endl;
        return false;
    }
    // 读取信息头 检查支持的格式
    file.read(reinterpret_cast<char*>(&infoHeader), sizeof(infoHeader));
    if (infoHeader.bitCount != 1 && infoHeader.bitCount != 4 && infoHeader.bitCount != 8 && infoHeader.bitCount != 24 && infoHeader.bitCount != 32)
    {
        cerr << "不支持的BMP格式: " << infoHeader.bitCount << " bits" << endl;
        return false;
    }
    // 读取颜色表（对于1,4,8位图像）
    if (infoHeader.bitCount <= 8) 
    {
        int colorCount = (infoHeader.colorsUsed == 0) ? (1 << infoHeader.bitCount) : infoHeader.colorsUsed;
        colorTable = new RGBQuad[colorCount];
        file.read(reinterpret_cast<char*>(colorTable), colorCount * sizeof(RGBQuad));
        cout << "Color table entries: " << colorCount << endl;
    }
    // 计算每行字节数（4字节对齐）
    rowSize = ((infoHeader.width * infoHeader.bitCount + 31) / 32) * 4;
    // 移动到像素数据位置
    file.seekg(fileHeader.dataOffset, ios::beg);
    // 分配内存并读取像素数据
    uint32_t dataSize = rowSize * abs(infoHeader.height);
    pixelData = new uint8_t[dataSize];
    file.read(reinterpret_cast<char*>(pixelData), dataSize);
    if (file.fail()) 
    {
        cerr << "读取像素数据失败. " << endl;
        return false;
    }
    file.close();
    return true;
}

void bitmap::cleanup() 
{
    if (colorTable != nullptr) 
    {
        delete[] colorTable;
        colorTable = nullptr;
    }
    if (pixelData != nullptr) 
    {
        delete[] pixelData;
        pixelData = nullptr;
    }
}

int bitmap::show(const int top_left_x, const int top_left_y, const int angle, const bool is_mirror, void (*draw_point)(const int x, const int y, const unsigned char red, const unsigned char green, const unsigned char blue)) const
{

    if (pixelData == nullptr)
    {
        return -1;
    }

    int width = infoHeader.width;
    int height = abs(infoHeader.height);
    bool topDown = (infoHeader.height < 0);
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            int srcX = x;
            int srcY = topDown ? y : (height - 1 - y);

            unsigned char red = 0, green = 0, blue = 0;
            uint32_t pixelIndex = srcY * rowSize;

            switch (infoHeader.bitCount)
            {
            case 1:
            { // 单色
                uint8_t byte = pixelData[pixelIndex + srcX / 8];
                uint8_t bit = 7 - (srcX % 8);
                uint8_t colorIndex = (byte >> bit) & 0x01;
                if (colorTable)
                {
                    red = colorTable[colorIndex].red;
                    green = colorTable[colorIndex].green;
                    blue = colorTable[colorIndex].blue;
                }
                else
                    red = green = blue = colorIndex * 255;
                break;
            }
            case 4:
            { // 16色
                uint8_t byte = pixelData[pixelIndex + srcX / 2];
                uint8_t colorIndex = (srcX % 2 == 0) ? (byte >> 4) : (byte & 0x0F);
                if (colorTable)
                {
                    red = colorTable[colorIndex].red;
                    green = colorTable[colorIndex].green;
                    blue = colorTable[colorIndex].blue;
                }
                break;
            }
            case 8:
            { // 256色
                uint8_t colorIndex = pixelData[pixelIndex + srcX];
                if (colorTable) 
                {
                    red = colorTable[colorIndex].red;
                    green = colorTable[colorIndex].green;
                    blue = colorTable[colorIndex].blue;
                }
                break;
            }
            case 24:
            { // 24位真彩色
                uint32_t offset = pixelIndex + srcX * 3;
                blue = pixelData[offset];
                green = pixelData[offset + 1];
                red = pixelData[offset + 2];
                break;
            }
            case 32:
            { // 32位真彩色
                uint32_t offset = pixelIndex + srcX * 4;
                blue = pixelData[offset];
                green = pixelData[offset + 1];
                red = pixelData[offset + 2];
                break;
            }
            }
            if (!is_mirror)
                srcX = width - 1 - srcX;
            int dstX, dstY;
            switch (angle) 
            {
            case 0:
                dstX = top_left_x + width - 1 - srcX;
                dstY = top_left_y + height - 1 - srcY;
                break;
            case 90:
                dstX = top_left_x + height - 1 - srcY;
                dstY = top_left_y + srcX;
                break;
            case 180:
                 dstX = top_left_x + srcX;
                dstY = top_left_y + srcY;
                break;
            case 270:
                dstX = top_left_x + srcY;
                dstY = top_left_y + width - 1 - srcX;
                break;
            default:
                dstX = top_left_x + srcX;
                dstY = top_left_y + srcY;
                break;
            }
            // 绘制像素
            draw_point(dstX, dstY, red, green, blue);
        }
    }
    return 0;
}