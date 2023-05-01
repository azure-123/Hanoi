/* 1953463 ����Ƚ ��Ϣ��ȫ */
#pragma once

/* -----------------------------------------

	 ���ļ����ܣ�
	1��Ϊ�˱�֤ hanoi_main.cpp/hanoi_menu.cpp/hanoi_multiple_solutions.cpp ���໥���ʺ����ĺ�������
	2��һ�����ϵ�cpp���õ��ĺ궨�壨#define����ȫ��ֻ����const����������������
	3�����Բο� cmd_console_tools.h ��д���������Ķ�����ᣩ
   ----------------------------------------- */
int show_menu();//��ʾ�˵�ѡ�������main����
void initial(char src,int layer,int order);//�Գ�����г�ʼ������Դ�������������䣬�����ݲ˵�ѡ�ͬ���г�ʼ��

void multiple_solutions(int order,char src, char tmp,char dst ,int layer);//�Բ�ͬѡ����д�������ѡ��Ĳ�ͬ���ø��ֺ����Ϳ������
void hanoi(int n, char src, char tmp, char dst,int order);//��ŵ���ݹ�ʵ�ֹ���

//��ŵ��������ʽ�Ĵ�ӡ
void printVer(int n, char src, char dst,int order);//������ŵ���Ĵ�ӡ
void print();//�Ժ���ŵ���Ĵ�ӡ

//��ŵ��αͼ�ν���Ĵ�ӡ
void printPillar(int layer, char src);//�����ӵĴ�ӡ
void printPlate(int x, int y, int half_length,int color);//�����ӵĴ�ӡ

//�������
void movePlate(int x, int y, char src, char dst,int order);//�����������ӵ��ƶ�
void intervalChoice();//����ʱ������ѡ��
void gameVer(int layer,char src, char dst,int order);//orderΪ9����Ϸģʽ
void hanoiSolutions(int n, char src, char tmp, char dst, int order);//����ָ��Ĳ�ͬ���жԺ�ŵ��������ѡ��
