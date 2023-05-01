#include<iostream>
#include<iomanip>
#include<conio.h>
#include <windows.h>
#include"hanoi.h"
#include"cmd_console_tools.h"
using namespace std;
/* -----------------------------------------

	 ���ļ����ܣ�
	1���ű� hanoi_main.cpp/hanoi_menu.cpp �еĸ��������õĲ˵������Ӧ��ִ�к���

	 ���ļ�Ҫ��
	1�����������ⲿȫ�ֱ�����const��#define�������Ʒ�Χ�ڣ�
	2�������徲̬ȫ�ֱ�����������Ҫ��������Ҫ�����ĵ���ʾ��ȫ�ֱ�����ʹ��׼���ǣ����á����á��ܲ��þ������ã�
	3����̬�ֲ����������������ƣ���ʹ��׼��Ҳ�ǣ����á����á��ܲ��þ�������
	4���������ϵͳͷ�ļ����Զ���ͷ�ļ��������ռ��

   ----------------------------------------- */

extern int pointer[3];
extern int capsule[3][10];
extern int step;
extern int interval;

void intervalChoice()
{
	while (1)
	{
		cout << "�������ƶ��ٶ�(0-5��0-���س�������ʾ 1-��ʱ� 5-��ʱ���)��" << endl;
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
	pointer[dst - 'A']++;//������ģ��ջ�Ĳ�����pointerָ��ָ�����һ��Ԫ�صĺ�һ��λ�á������ƶ���������ģ���ջ��ջ
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
	cout << endl;//�����ӡ��������
}

void printSteps(int n, char src, char dst,int order)
{
	if (order == 4)
	{
		if (!interval)
		{
			while (_getch() != '\r')
				;//�ȴ�����س�
		}//�ȴ��س�
		else
			Sleep(1000 - interval * 150);
		cct_gotoxy(0, 17);
	}
	else if (order == 8||order==9)
		cct_gotoxy(0, 32);
	if (order == 9)
		n = capsule[dst-'A'][pointer[dst-'A']-1];
	cout << "��" << setw(4) << step << "��(" << n << "#: " << src << "-->" << dst << ") ";
	print();//��ѡ������ʾ�����ڲ�����������
}
/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����
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
				cout << "  ";//�����ӡ
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
		cout << "��" << setw(4) << step << "��(" << n << "#: " << src << "-->" << dst << ") ";
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
		hanoi(n - 1, src, dst, tmp, order);//�Ƶ�tmp,dst��������
		step++;
		hanoiSolutions(n, src, tmp, dst, order);
		hanoi(n - 1, tmp, src, dst, order);//�Ƶ�dst,src��������
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
		cout << "�ƶ�����Ϊ: " << endl;

	if (order == 3)
	{
		initial(src, layer, order);
	}

	if (order == 4||order==8||order==9)
	{
		cct_cls();
		if(order!=9)
			cout << "�� " << src << " �ƶ��� " << dst << "���� " << layer << " �㣬��ʱ����Ϊ " << interval << endl;
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
					cout << "  ";//�����ӡ
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
			cout << "�� " << src << " �ƶ��� " << dst << "���� " << layer << " ��";
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
		cout << "�������ƶ�������(������ʽ��AC=A���˵������ƶ���C��Q=�˳�) ��  \b\b";
		char temp_src, temp_dst,temp;
		temp_src = _getche();
		temp_dst = _getche();
		
		if ((temp_src == 'q' || temp_src == 'Q') && temp_dst == '\r')
		{
			cout <<endl<< "��Ϸ������" << endl;
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
			cout << "Դ��Ϊ��,����������";
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
			cout << "����ѹС��,�Ƿ��ƶ�!";
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
			cout << "��Ϸ������" << endl;
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
		cout << "��ʼ:  ";
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
	}//�ֱ���г�ʼ����������ѡ������ʾ�ڲ����飬��������������ڲ�������
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
	}//��ʼ������
}