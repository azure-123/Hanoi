#include<iostream>
#include<windows.h>
#include "cmd_console_tools.h"
#include"hanoi.h"
using namespace std;
/* -----------------------------------------

	 ���ļ����ܣ�
	1����main����
	2����ʼ����Ļ
	3�����ò˵�������hanoi_menu.cpp�У�������ѡ��
	4������ѡ����ò˵������Ӧ��ִ�к�����hanoi_multiple_solutions.cpp�У�

	 ���ļ�Ҫ��
	1����������ȫ�ֱ��������ⲿȫ�ֺ;�̬ȫ����const��#define�������Ʒ�Χ�ڣ�
	2����̬�ֲ����������������ƣ���ʹ��׼��Ҳ�ǣ����á����á��ܲ��þ�������
	3���������ϵͳͷ�ļ����Զ���ͷ�ļ��������ռ��

   ----------------------------------------- */
   /***************************************************************************
	 �������ƣ�
	 ��    �ܣ�
	 ���������
	 �� �� ֵ��
	 ˵    ����
   ***************************************************************************/
int pointer[3] = { 0 };
int capsule[3][10] = { 0 };
int step = 0;
int interval=0;
int main()
{
	int choice = 0;
	int interval = 0;
	/* demo������ִ�д˾䣬��cmd��������Ϊ40��x120�У����������120�У�����9000�У���cmd�����Ҳ���д�ֱ�����ˣ�*/
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
				cout << "�����뺺ŵ���Ĳ���(1-16)��" << endl;
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
			}//��������Դ����������
			while (1)
			{
				cout << "��������ʼ��(A-C)��" << endl;
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
				cout << "������Ŀ����(A-C)��" << endl;
				dst = getchar();
				while (getchar() != '\n')
					;
				if (dst >= 'a')
					dst -= 32;
				if (dst == src)
					cout << "Ŀ����(" << dst << ")��������ʼ��(" << src << ")��ͬ" << endl;
				else if (dst == 'A' || dst == 'B' || dst == 'C')
					break;
			}

			if ((dst == 'A' && src == 'B') || (dst == 'B' && src == 'A'))
				tmp = 'C';
			else if ((dst == 'A' && src == 'C') || (dst == 'C' && src == 'A'))
				tmp = 'B';
			else if ((dst == 'C' && src == 'B') || (dst == 'B' && src == 'C'))
				tmp = 'A';//��������

			if (order == 4||order==8)
				intervalChoice();
		}

		multiple_solutions(order, src, tmp, dst, layer);
		cct_setcolor(COLOR_BLACK, COLOR_WHITE);
		if (order == 1 || order == 2 || order == 3)
			cout << endl << endl;
		else
			cct_gotoxy(0, 36);
		cout << "���س�������..." << endl;

		for (int i = 0; i < 3; i++)
			pointer[i] = 0;
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 10; j++)
			{
				capsule[i][j] = 0;
			}
		}
		step = 0;//ÿ�β˵��ϵ�һ�������Ժ󣬽���¼�Ĳ�����ÿ�����ϵ�������������

		while (getchar() != '\n')
			;

	}
	return 0;
}