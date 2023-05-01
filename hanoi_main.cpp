#include<iostream>
#include<windows.h>
#include "cmd_console_tools.h"
#include"hanoi.h"
using namespace std;
/* -----------------------------------------

	 本文件功能：
	1、放main函数
	2、初始化屏幕
	3、调用菜单函数（hanoi_menu.cpp中）并返回选项
	4、根据选项调用菜单各项对应的执行函数（hanoi_multiple_solutions.cpp中）

	 本文件要求：
	1、不允许定义全局变量（含外部全局和静态全集，const及#define不在限制范围内）
	2、静态局部变量的数量不限制，但使用准则也是：少用、慎用、能不用尽量不用
	3、按需加入系统头文件、自定义头文件、命名空间等

   ----------------------------------------- */
   /***************************************************************************
	 函数名称：
	 功    能：
	 输入参数：
	 返 回 值：
	 说    明：
   ***************************************************************************/
int pointer[3] = { 0 };
int capsule[3][10] = { 0 };
int step = 0;
int interval=0;
int main()
{
	int choice = 0;
	int interval = 0;
	/* demo中首先执行此句，将cmd窗口设置为40行x120列（缓冲区宽度120列，行数9000行，即cmd窗口右侧带有垂直滚动杆）*/
	cct_setconsoleborder(120, 40, 120, 9000);
	while (1)
	{
		cct_cls();
		int order = show_menu();
		if (order == 0)
			return 0;
		int layer=1;
		char src='a', dst='b', tmp='c';
		if (order != 5)
		{
			while (1)
			{
				cout << "请输入汉诺塔的层数(1-16)：" << endl;
				cin >> layer;
				cin.clear();
				if (layer >= 1 && layer <= 16)
				{
					cin.clear();
					cin.ignore(65535, '\n');
					break;
				}
				else
				{
					cin.clear();
					cin.ignore(65535, '\n');
				}
			}//无论输入对错都清除缓存区
			while (1)
			{
				cout << "请输入起始柱(A-C)：" << endl;
				src = getchar();
				while (getchar() != '\n')
					;
				if (src >= 'a')
					src -= 32;
				if (src == 'A' || src == 'B' || src == 'C')
					break;
			}

			while (1)
			{
				cout << "请输入目标柱(A-C)：" << endl;
				dst = getchar();
				while (getchar() != '\n')
					;
				if (dst >= 'a')
					dst -= 32;
				if (dst == src)
					cout << "目标柱(" << dst << ")不能与起始柱(" << src << ")相同" << endl;
				else if (dst == 'A' || dst == 'B' || dst == 'C')
					break;
			}

			if ((dst == 'A' && src == 'B') || (dst == 'B' && src == 'A'))
				tmp = 'C';
			else if ((dst == 'A' && src == 'C') || (dst == 'C' && src == 'A'))
				tmp = 'B';
			else if ((dst == 'C' && src == 'B') || (dst == 'B' && src == 'C'))
				tmp = 'A';//错误处理部分

			if (order == 4||order==8)
				intervalChoice();
		}

		multiple_solutions(order, src, tmp, dst, layer);
		cct_setcolor(COLOR_BLACK, COLOR_WHITE);
		if (order == 1 || order == 2 || order == 3)
			cout << endl << endl;
		else
			cct_gotoxy(0, 36);
		cout << "按回车键继续..." << endl;

		for (int i = 0; i < 3; i++)
			pointer[i] = 0;
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 10; j++)
			{
				capsule[i][j] = 0;
			}
		}
		step = 0;//每次菜单上的一条结束以后，将记录的步数、每个柱上的盘子数都清零

		while (getchar() != '\n')
			;

	}
	return 0;
}