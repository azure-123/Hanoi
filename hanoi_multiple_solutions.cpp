#include<iostream>
#include<iomanip>
#include<conio.h>
#include <windows.h>
#include"hanoi.h"
#include"cmd_console_tools.h"
using namespace std;
/* -----------------------------------------

	 本文件功能：
	1、放被 hanoi_main.cpp/hanoi_menu.cpp 中的各函数调用的菜单各项对应的执行函数

	 本文件要求：
	1、不允许定义外部全局变量（const及#define不在限制范围内）
	2、允许定义静态全局变量（具体需要的数量不要超过文档显示，全局变量的使用准则是：少用、慎用、能不用尽量不用）
	3、静态局部变量的数量不限制，但使用准则也是：少用、慎用、能不用尽量不用
	4、按需加入系统头文件、自定义头文件、命名空间等

   ----------------------------------------- */

extern int pointer[3];
extern int capsule[3][10];
extern int step;
extern int interval;

void intervalChoice()
{
	while (1)
	{
		cout << "请输入移动速度(0-5：0-按回车单步演示 1-延时最长 5-延时最短)：" << endl;
		cin >> interval;
		cin.clear();
		if (interval >= 0 && interval <= 5)
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
	}
}


void move(char src, char dst)
{
	
	capsule[dst - 'A'][pointer[dst - 'A']] = capsule[src - 'A'][pointer[src - 'A']-1];
	pointer[src - 'A']--;
	capsule[src - 'A'][pointer[src - 'A']] = 0;
	pointer[dst - 'A']++;//用数组模拟栈的操作，pointer指针指向最后一个元素的后一个位置。若有移动操作，则模拟出栈入栈
}

void print()
{
	for (int i = 0; i < 3; i++)
	{
		cout << setw(2) << char('A' + i) << ':';
		for (int j = 0; j < 10; j++)
		{
			if (j < pointer[i])
				cout << setw(2) << capsule[i][j];
			else
				cout << "  ";
		}
	}
	cout << endl;//横向打印数组内容
}

void printSteps(int n, char src, char dst,int order)
{
	if (order == 4)
	{
		if (!interval)
		{
			while (_getch() != '\r')
				;//等待输入回车
		}//等待回车
		else
			Sleep(1000 - interval * 150);
		cct_gotoxy(0, 17);
	}
	else if (order == 8||order==9)
		cct_gotoxy(0, 32);
	if (order == 9)
		n = capsule[dst-'A'][pointer[dst-'A']-1];
	cout << "第" << setw(4) << step << "步(" << n << "#: " << src << "-->" << dst << ") ";
	print();//若选择了显示数组内部，则横向输出
}
/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/

void printVer( int n, char src, char dst,int order)
{
	cct_setcolor(COLOR_BLACK, COLOR_WHITE);
	for (int i = 0; i < 3; i++)
	{
		int y=0;
		if (order == 4)
			y = 12;
		else if (order == 8||order==9)
			y = 29;
		for (int j = 0; j < 10; j++)
		{
			cct_gotoxy(10 + 10 * i, --y);
			if (j < pointer[i])
				cout << setw(2) << capsule[i][j];
		
			 else if(j==pointer[i])
				cout << "  ";//纵向打印
		}
	}
}

void hanoiSolutions(int n, char src, char tmp, char dst, int order)
{
	if (order == 1)
		cout << setw(2) << n << "# " << src << "-->" << dst << endl;
	if (order == 2)
		cout << setw(5) << step << ":" << setw(3) << n << "# " << src << "-->" << dst << endl;
	if (order == 3)
	{
		cout << "第" << setw(4) << step << "步(" << n << "#: " << src << "-->" << dst << ") ";
		move(src, dst);
		print();
	}
	if (order == 4)
	{
		move(src, dst);
		printSteps(n, src, dst, order);
		printVer(n, src, dst, order);
	}
	if (order == 8)
	{
		if (!interval)
		{
			while (getchar() != '\n')
				;
		}
		movePlate(12 + 32 * (src - 'A'), 14 - pointer[src - 'A'], src, dst, order);
		move(src, dst);
		printVer(n, src, dst, order);
		printSteps(n, src, dst, order);
	}
}


void hanoi(int n, char src, char tmp, char dst, int order)
{
	if (n == 1)
	{
		step++;
		hanoiSolutions(n, src, tmp, dst, order);
		return;
	}
	else
	{
		hanoi(n - 1, src, dst, tmp, order);//移到tmp,dst作辅助塔
		step++;
		hanoiSolutions(n, src, tmp, dst, order);
		hanoi(n - 1, tmp, src, dst, order);//移到dst,src作辅助塔
	}
}

void printPillar(int layer, char src)
{
	const int WIDTH = 23;
	const int HEIGHT = 12;
	for (int i = 0; i < WIDTH; i++)
	{
		Sleep(10);
		cct_showch(i + 1, 15, ' ', COLOR_HYELLOW, COLOR_HYELLOW, 1);
		cct_showch(i + 33, 15, ' ', COLOR_HYELLOW, COLOR_HYELLOW, 1);
		cct_showch(i + 65, 15, ' ', COLOR_HYELLOW, COLOR_HYELLOW, 1);
	}

	for (int i = 0; i < HEIGHT; i++)
	{
		Sleep(10);
		cct_showch(12, 14 - i, ' ', COLOR_HYELLOW, COLOR_HYELLOW, 1);
		cct_showch(44, 14 - i, ' ', COLOR_HYELLOW, COLOR_HYELLOW, 1);
		cct_showch(76, 14 - i, ' ', COLOR_HYELLOW, COLOR_HYELLOW, 1);
	}
}

void printPlate(int x, int y, int half_length,int color) 
{
	cct_showch(x - half_length, y, ' ', color, color, half_length * 2 + 1);
}

void movePlate(int x, int y, char src, char dst,int order)
{
	cct_setcursor(CURSOR_INVISIBLE);
	int color = capsule[src - 'A'][pointer[src - 'A']-1];
	cct_gotoxy(x, y - pointer[src - 'A']);
	while (y > 0)
	{
		if (order != 9)
		{
			if (interval)
				Sleep(1000 - interval * 190);
			else
			{
				Sleep(100);
			}
		}
		printPlate(x, y, capsule[src - 'A'][pointer[src - 'A']-1],color);
		printPlate(x, y+1, capsule[src - 'A'][pointer[src - 'A']-1], COLOR_BLACK);
		if(y!=1)
			cct_showch(x, y+1, ' ', COLOR_HYELLOW, COLOR_HYELLOW, 1);
		y--;
	}
	y++;
	if (src < dst)
	{
		while (x < 12 + 32 * (dst - 'A'))
		{
			if (order != 9)
			{
				if (interval)
					Sleep(1000 - interval * 190);
				else
				{
					Sleep(100);
				}
			}
			cct_showch(x - capsule[src - 'A'][pointer[src - 'A'] - 1], y, ' ', COLOR_BLACK, COLOR_BLACK, 1);
			x++;
			printPlate(x, y, capsule[src - 'A'][pointer[src - 'A']-1], color);
		}
	}
	else
	{
		while (x > 12 + 32 * (dst - 'A'))
		{
			if (order != 9)
			{
				if (interval)
					Sleep(1000 - interval * 190);
				else
				{
					Sleep(100);
				}
			}
			cct_showch(x + capsule[src - 'A'][pointer[src - 'A'] - 1], y, ' ', COLOR_BLACK, COLOR_BLACK, 1);
			x--;
			printPlate(x, y, capsule[src - 'A'][pointer[src - 'A']-1], color);
		}
	}
	while (y<15-pointer[dst-'A'])
	{
		if (order != 9)
		{
			if (interval)
				Sleep(1000 - interval * 190);
			else
			{
				Sleep(100);
			}
		}
		printPlate(x, y, capsule[src - 'A'][pointer[src - 'A'] - 1], color);
		if (y != 1)
			printPlate(x, y - 1, capsule[src - 'A'][pointer[src - 'A'] - 1], COLOR_BLACK);
		if (y != 1&&y!=2&&y!=3)
			cct_showch(x, y - 1, ' ', COLOR_HYELLOW, COLOR_HYELLOW, 1);
		y++;
	}
}

void multiple_solutions(int order, char src, char tmp, char dst, int layer)
{
	cct_setcursor(CURSOR_INVISIBLE);
	if (order == 1 || order == 2)
		cout << "移动步骤为: " << endl;

	if (order == 3)
	{
		initial(src, layer, order);
	}

	if (order == 4||order==8||order==9)
	{
		cct_cls();
		if(order!=9)
			cout << "从 " << src << " 移动到 " << dst << "，共 " << layer << " 层，延时设置为 " << interval << endl;
		initial(src, layer, order);
		if (order == 4)
			cct_gotoxy(9, 12);
		else if (order == 8||order==9)
			cct_gotoxy(9, 29);
		cout << "=========================" << endl;
		cout << "           A         B         C" << endl;
		for (int i = 0; i < 3; i++)
		{
			int y;
			if (order == 4)
				y = 12;
			else if (order == 8||order==9)
				y = 29;
			for (int j = 0; j < 10; j++)
			{
				cct_gotoxy(10 + 10 * i, --y);
				if (j < pointer[i])
					cout << setw(2) << capsule[i][j];
				else
					cout << "  ";//纵向打印
			}
		}

	}
	if (order == 5||order==6||order==7||order==8||order==9)
	{
		const int WIDTH = 23;
		const int HEIGHT = 12;
		if(order!=8&&order!=9)
			cct_cls();
		initial(src, layer, order);
		if (order == 7)
			cout << "从 " << src << " 移动到 " << dst << "，共 " << layer << " 层";
		printPillar(layer, src);
		if (order == 6||order==7||order==8||order==9)
		{
			int color = pointer[src-'A'];
			int x = 12 + 32 * (src - 'A');
			int y = 14;
			for (int i = layer; i >0; i--,color--,y--)
			{
				cct_gotoxy(x, y);
				printPlate(x, y, i,color);
			}
			if (order == 7)
			{
				if (layer % 2 != 0)
					movePlate(x, y, src, dst, order);
				else
					movePlate(x, y, src, tmp, order);
			}
		}
		cct_setcolor(0, 7);
	}
	cct_gotoxy(0, 20);
	cout << endl;
	if (order != 9&&order!=7)
		hanoi(layer, src, tmp, dst, order);
	else if(order==9)
		gameVer(layer, src, dst,order);
}

void gameVer(int layer, char src, char dst,int order)
{
	while (1)
	{
		cct_gotoxy(0, 34);
		cct_setcolor(COLOR_BLACK, COLOR_WHITE);
		cout << "请输入移动的柱号(命令形式：AC=A顶端的盘子移动到C，Q=退出) ：  \b\b";
		char temp_src, temp_dst,temp;
		temp_src = _getche();
		temp_dst = _getche();
		
		if ((temp_src == 'q' || temp_src == 'Q') && temp_dst == '\r')
		{
			cout <<endl<< "游戏结束！" << endl;
			break;
		}
		temp = _getch();
		if (temp != '\r')
		{
			cct_setcolor(COLOR_BLACK, COLOR_WHITE);
			cout << "\b\b  \b\b";
			continue;
		}
		else
			cout << endl;
		if (temp_src >= 'a')
			temp_src -= 32;
		if (temp_dst >= 'a')
			temp_dst -= 32;
		if (pointer[temp_src-'A'] == 0)
		{
			cout << "源柱为空,请重新输入";
			Sleep(1000);
			int x = 19, y = 35;
			while (x >= 0)
			{
				cct_gotoxy(x, y);
				cout << ' ';
				x--;
			}
			continue;
		}
		else if (capsule[temp_src - 'A'][pointer[temp_src - 'A'] - 1] > capsule[temp_dst - 'A'][pointer[temp_dst - 'A'] - 1]&&pointer[temp_dst-'A']!=0)
		{
			cout << "大盘压小盘,非法移动!";
			Sleep(1000);
			int x=21,y=35;
			while (x >= 0)
			{
				cct_gotoxy(x, y);
				cout << ' ';
				x--;
			}
			continue;
		}
		else
		{
			step++;
			movePlate(12 + 32 * (temp_src - 'A'), 14 - pointer[temp_src - 'A'], temp_src, temp_dst,order);
			move(temp_src, temp_dst);
			printVer(layer, temp_src, temp_dst, order);
			printSteps(layer, temp_src, temp_dst, order);
		}
		if (pointer[src-'A'] == 0 && pointer[dst-'A'] == layer)
		{
			cct_gotoxy(0, 35);
			cout << "游戏结束！" << endl;
			break;
		}
	}
}

void initial(char src, int layer,int order)
{
	if (order==4||order==9)
		cct_gotoxy(0, 17);
	if (order != 5 && order != 6 && order != 7)
	{
		if (order == 8||order==9)
			cct_gotoxy(0, 32);
		cout << "初始:  ";
	}
	if (src == 'A')
	{
		capsule[0][0] = layer;
		pointer[0] = layer;
		if (order==4||order==8||order==9)
			cout << " A:" << setw(2) << capsule[0][0];
		for (int i = 1; i < layer; i++)
		{
			capsule[0][i] = capsule[0][i - 1] - 1;
			if (order==4||order==8||order==9)
				cout << setw(2) << capsule[0][i];
		}
		for (int i = layer; i < 10; i++)
			if (order==4||order==8||order==9)
				cout << "  ";
		if (order==4 || order == 8||order==9)
		{
			cout << " B:                    ";
			cout << " C:" << endl;
		}
	}//分别进行初始化操作，若选择了显示内部数组，则输出各个盘子内部的数字
	else if (src == 'B')
	{
		capsule[1][0] = layer;
		pointer[1] = layer;
		if (order==4 || order == 8||order==9)
		{
			cout << " A:                    ";
			cout << " B:" << setw(2) << capsule[1][0];
		}
		for (int i = 1; i < layer; i++)
		{
			capsule[1][i] = capsule[1][i - 1] - 1;
			if (order==4)
				cout << setw(2) << capsule[1][i];
		}
		if (order==4 || order == 8||order==9)
		{
			for (int i = layer; i < 10; i++)
				cout << "  ";
			cout << " C:" << endl;
		}
	}
	else if (src == 'C')
	{
		capsule[2][0] = layer;
		pointer[2] = layer;
		if (order==4 || order == 8||order==9)
		{
			cout << " A:                    ";
			cout << " B:                    ";
			cout << " C:" << setw(2) << capsule[2][0];
		}
		for (int i = 1; i < layer; i++)
		{
			capsule[2][i] = capsule[2][i - 1] - 1;
			if (order==4 || order == 8||order==9)
				cout << setw(2) << capsule[2][i];
		}
		if (order==4 || order == 8||order==9)
		{
			for (int i = layer; i < 10; i++)
				cout << "  ";
		}
	}//初始化操作
}