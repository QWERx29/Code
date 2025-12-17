// 2451317 冯久恒 大数据
#pragma once

//不允许加入任何头文件，特别是<Windows.h>/<Wingdi.h>，查到就是0分甚至是倒扣-20 ！！！

//关于BMP的微软官方文档：
// https://learn.microsoft.com/zh-cn/windows/win32/api/wingdi/ns-wingdi-bitmap

//自行查阅相关资料，了解下面这几个预编译命令的作用，看能否给你的作业带来方便！！！
//#pragma pack(show) //以警告信息的形式显示当前字节对齐的值
//#pragma pack(push) //将当前字节对齐值压入编译器栈的栈顶
//#pragma pack(push, 4) //将当前字节对齐值压入编译器栈的栈顶，然后再将4设置当前值
//#pragma pack(pop)  //将编译器栈栈顶的字节对齐值弹出并设置为当前值
//#pragma pack() //不带参数是恢复默认值

//允许定义其它需要的结构体（类）、常量、常变量等
#pragma pack(push, 1)
struct BMPFileHeader {
    uint16_t signature;      // 文件标识，必须是"BM"
    uint32_t fileSize;       // 文件大小
    uint16_t reserved1;      // 保留字段1
    uint16_t reserved2;      // 保留字段2
    uint32_t dataOffset;     // 像素数据偏移量
};

// BMP信息头结构体
struct BMPInfoHeader {
    uint32_t headerSize;     // 信息头大小
    int32_t width;           // 图像宽度
    int32_t height;          // 图像高度
    uint16_t planes;         // 颜色平面数
    uint16_t bitCount;       // 每像素位数
    uint32_t compression;    // 压缩方式
    uint32_t imageSize;      // 图像数据大小
    int32_t xPixelsPerMeter; // 水平分辨率
    int32_t yPixelsPerMeter; // 垂直分辨率
    uint32_t colorsUsed;     // 使用的颜色数
    uint32_t colorsImportant;// 重要颜色数
};

// RGB颜色结构体
struct RGBQuad {
    uint8_t blue;
    uint8_t green;
    uint8_t red;
    uint8_t reserved;
};
#pragma pack(pop)



class bitmap {
private:
    const bool is_debug;
    /* 自行添加你需要的数据成员及成员函数，不限制数量 */
    BMPFileHeader fileHeader;
    BMPInfoHeader infoHeader;
    RGBQuad* colorTable;     // 颜色表
    uint8_t* pixelData;      // 像素数据
    uint32_t rowSize;        // 每行字节数

    bool readBMP(const char* filename);
    void cleanup();

public:
    /* 公有部分不允许添加任何内容 */
    bitmap(const char *const filename, const bool is_debug);
    ~bitmap();
    int show(const int top_left_x, const int top_left_y, const int angle, const bool is_mirror, 
                void (*draw_point)(const int x, const int y, const unsigned char red, const unsigned char green, const unsigned char blue)) const;
};
