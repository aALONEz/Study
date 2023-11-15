#define _CRT_SECURE_NO_WARNINGS 1

#include "game.h"


/*
* 功能:游戏中功能选择
* 参数:无
* 返回值:无
*/
void game_function_selection(char show_borad[MAX_ROW][MAX_COL], char no_show_borad[MAX_ROW][MAX_COL], int rows, int cols, int mines)
{
	int gfs_input = 0;
	while (1)
	{
		printf("选择要进行的动作:\n1.排查雷    2.标记    3.取消标记\n");
		scanf("%d", &gfs_input);//接收用户输入坐标
		switch (gfs_input)
		{
			case 1:
				{
					//排查雷
					bool result = find_mine(show_borad, no_show_borad, rows, cols, C_MINE);
					if (result)//为真是雷
					{
						printf("你输了!\n");
						//输了使用输了显示函数
						display_borad(no_show_borad, rows, cols, result, C_MINE);//输了就展示一下所有雷的位置
						return;//是雷就游戏结束返回菜单页面
					}
					if (is_win(show_borad, no_show_borad, rows, cols, mines))
					{
						printf("恭喜你胜利了!\n");
						return;
					}
					break;
				}
			case 2:
				{
					//标记
					mark(show_borad, rows, cols, MARK);
					if (is_win(show_borad, no_show_borad, rows, cols, mines))
					{
						printf("恭喜你胜利了!\n");
						return;
					}
					break;
				}
			case 3:
				{
					//取消标记
					unmark(show_borad, rows, cols, MARK);
					/*if (is_win(show_borad, no_show_borad, rows, cols, mines))//取消标记不需要判断,因为既然取消标记能判断胜利,那么前面标记的时候一定可以判断胜利了
					{
						printf("恭喜你胜利了!\n");
						return;
					}*/
					break;
				}
		}
	}
}

/*
* 功能:用于输出显示菜单
* 参数:无
* 返回值:无
*/
void menu(void)
{
	printf("******************\n");
	printf("*** 1.开始游戏 ***\n");
	printf("*** 0.退出游戏 ***\n");
	printf("******************\n");
}

/*
* 功能:用于输出显示难度菜单
* 参数:无
* 返回值:无
*/
void difficulty_menu(void)
{
	printf("******************\n");
	printf("*** 1.简单难度 ***\n");
	printf("*** 2.普通难度 ***\n");
	printf("*** 3.困难难度 ***\n");
	printf("***   0.返回   ***\n");
	printf("******************\n");
}

/*
* 功能:游戏主体函数
* 参数:无
* 返回值:无
*/
void game(void)
{
	srand((unsigned int)time(NULL));
	int rows, cols, mines;//创建变量用来存储难度
	char show_borad[52][52] = {0};//展示棋盘
	char no_show_borad[52][52] = {0};//不展示棋盘
	int difficulty = 0;//难度选择存储变量
	difficulty_selection:
	difficulty_menu();//难度菜单函数
	scanf("%d", &difficulty);
	switch (difficulty)//多种选择,使用switch语句
	{
		case 0:
			{
				return;//选择0直接返回菜单
			}
		case 1:
			{
				//简单难度
				rows = NO_SHOW_EASY_ROW;
				cols = NO_SHOW_EASY_COL;
				mines = EASY_MINE;
				break;
			}
		case 2:
			{
				//普通难度
				rows = NO_SHOW_NORMAL_ROW;
				cols = NO_SHOW_NORMAL_COL;
				mines = NORMAL_MINE;
				break;
			}
		case 3:
			{
				//困难难度
				rows = NO_SHOW_HARD_ROW;
				cols = NO_SHOW_HARD_COL;
				mines = HARD_MINE;
				break;
			}
		default:
			{
				printf("选择错误请重新选择!\n");
				goto difficulty_selection;//使用goto语句回到难度菜单函数
			}
	}
	//上面难度选择完之后就应该紧接着初始化数组,让显示棋盘初始化为全部'*',不显示数组全部初始化为'0',之后再放雷
	//初始化显示棋盘(数组)
	borad_init(show_borad, rows, cols, '*');
	//初始化不显示棋盘(数组)
	borad_init(no_show_borad, rows, cols, '0');
	//放置雷
	set_mine(no_show_borad, rows, cols, C_MINE, mines);
	//显示棋盘
	display_borad(show_borad, rows, cols, false, C_MINE);
	//显示 不显示棋盘,查看雷是否是随机放置,后面会屏蔽
	//display_borad(no_show_borad, rows, cols, true, C_MINE);
	//游戏中功能选择
	game_function_selection(show_borad, no_show_borad, rows, cols, mines);
}

int main()
{
	//下面代码只是为了设置Windows环境下命令行窗口尺寸的代码,暂时不需要搞懂照抄即可.更改窗口大小是为了方便各个难度的窗口调整,以方便显示全部棋盘
	HWND console = GetConsoleWindow();
	RECT r;
	GetWindowRect(console, &r); // 获取当前窗口尺寸
	MoveWindow(console, r.left, r.top, 1495, 970,TRUE); // 设置新的窗口尺寸


	int select;//接收用户选择的变量
	do
	{
		//1.首先应该打印一下菜单,展示一下才可以进行选择:
		menu();//菜单函数
		scanf("%d", &select);
		switch (select)//由于有多种判断,且后面有难度选择,所以这里使用switch
		{
			case 0:
				{
					printf("感谢游玩!\n");
					break;
				}
			case 1:
				{
					game();//游戏正式开始函数

					break;
				}
			default:
				{
					printf("输入错误,请重新选择!\n");
					break;
				}
		}
	} while (select);
	return 0;
}
