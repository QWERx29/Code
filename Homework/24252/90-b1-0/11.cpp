# include<iostream>
# include<conio.h>
# include "cmd_console_tools.h"
# include "cmd_hdc_tools.h"


#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

using namespace std;

int main() 
{
    // 初始化画布：背景黑色，前景白色，分辨率800x600

	char addr[500];
	cout << "请输入图片路径：" << endl;
	cin >> addr;
	cout << "请确认当前cmd窗口的大小为40行*120列以上，字体为新宋体/16，按C继续，Q退出" << endl;
	cout << "请检查图像分辨率不超过2500*1400" << endl;
	while (1) {
		char ch = _getch();
		if (ch == 'C' || ch == 'c')
			break;
		if (ch == 'Q' || ch == 'q')
			return 0;
	}
	cct_cls();
	const int   win_width = 2500, win_high = 1400;	//设定屏幕宽度
	const int   win_bgcolor = 7, win_fgcolor = 0;
	const int   color[] = { 0x00FF0000, 0x0000FF00, 0x000000FF }; //R G B
	hdc_init(win_bgcolor, win_fgcolor, win_width, win_high);		//用(背景色，前景色，宽度，高度）初始化窗口
	hdc_cls();
	
    // 在坐标(50, 50)处绘制图片
    hdc_draw_image(50, 25, addr);

    // 释放资源
    hdc_release();
	Sleep(1000);
    return 0;
}