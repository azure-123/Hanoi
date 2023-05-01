/* 1953463 郭卫冉 信息安全 */
#pragma once

/* -----------------------------------------

	 本文件功能：
	1、为了保证 hanoi_main.cpp/hanoi_menu.cpp/hanoi_multiple_solutions.cpp 能相互访问函数的函数声明
	2、一个以上的cpp中用到的宏定义（#define）或全局只读（const）变量，个数不限
	3、可以参考 cmd_console_tools.h 的写法（认真阅读并体会）
   ----------------------------------------- */
int show_menu();//显示菜单选项，返回至main函数
void initial(char src,int layer,int order);//对程序进行初始化，将源柱的数组进行填充，并根据菜单选项不同进行初始化

void multiple_solutions(int order,char src, char tmp,char dst ,int layer);//对不同选项进行处理，根据选项的不同调用各种函数和控制输出
void hanoi(int n, char src, char tmp, char dst,int order);//汉诺塔递归实现过程

//汉诺塔数字形式的打印
void printVer(int n, char src, char dst,int order);//对纵向汉诺塔的打印
void print();//对横向汉诺塔的打印

//汉诺塔伪图形界面的打印
void printPillar(int layer, char src);//对柱子的打印
void printPlate(int x, int y, int half_length,int color);//对盘子的打印

//数组操作
void movePlate(int x, int y, char src, char dst,int order);//对柱子上盘子的移动
void intervalChoice();//对延时操作的选择
void gameVer(int layer,char src, char dst,int order);//order为9的游戏模式
void hanoiSolutions(int n, char src, char tmp, char dst, int order);//根据指令的不同进行对汉诺塔操作的选择
