#define _CRT_SECURE_NO_WARNINGS 1

#include "game.h"//包含game.h

static int get_around_mine(char show_borad[MAX_ROW][MAX_COL], char no_show_borad[MAX_ROW][MAX_COL], int x, int y);

static void expand_find_mine(char show_borad[MAX_ROW][MAX_COL], char no_show_borad[MAX_ROW][MAX_COL], int rows, int cols, int x, int y);

/*
* 功能:初始化指定数组(棋盘),的内容全部为指定字符
* 参数:borad 被初始化的数组(棋盘)
*	   rows 游戏难度行数
*	   cols 游戏难度列数
*	   c 指定的字符
* 返回值:空
*/
void borad_init(char borad[MAX_ROW][MAX_COL], int rows, int cols, char c)
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			borad[i][j] = c;
		}
	}
}

/*
* 功能:对指定数组进行放置雷的操作,这里只需要对不显示棋盘(数组)内放置雷就可以了
* 参数:borad 被放置雷的数组(棋盘)
*	   rows 游戏难度行数(不显示棋盘)
*	   cols 游戏难度列数(不显示棋盘)
*	   c 雷的字符
* 返回值:空
*/
void set_mine(char borad[MAX_ROW][MAX_COL], int rows, int cols, char c, int mine_num)
{
	//使用随机数,rand函数,在使用rand函数之前要调用srand函数设置种子,这里使用时间戳作为种子,srand设置种子只需要设置一次,所以放在程序主函数不放在这里
	int x, y;
	while (mine_num)
	{
		x = rand() % (rows - 2) + 1;
		y = rand() % (cols - 2) + 1;
		if (borad[x][y] != c)//当随机位置不等于雷的字符之后就让这个位置等于雷的字符,且雷的数量--
		{
			borad[x][y] = c;
			mine_num--;//这里形参减减不会影响实参,所以外面还可以使用实参判断胜利。
		}
	}
}

/*
* 功能:显示指定棋盘(数组)内容,最多显示99行99列
* 参数:borad 要显示的棋盘(数组)
*	   rows 游戏难度行数(不显示棋盘行数为准)
*	   cols 游戏难度列数(不显示棋盘列数为准)
*	   result 数组 是不是雷所在的数组
*	   c 雷的字符
* 返回值:空
*/
void display_borad(char borad[MAX_ROW][MAX_COL], int rows, int cols, bool result, char c)
{
	int i = 0, j = 0;
	//打印游戏标题
	for (i = 0; i < cols - 5; i++)
	{
		if (((cols - 5) / 2) == i)
		{
			printf("-扫雷游戏-");
		}
		printf("---");
	}
	printf("\n");
	//显示列号
	for (i = 0; i < cols - 1; i++)
	{
		if (i == 0)
		{
			printf("   ");
			continue;
		}
		if (i < 9)
		{
			printf("%d  ", i);

		}
		if (i >= 9)
		{
			printf("%d ", i);
		}
	}
	printf("\n");//第一行显示列号之后进行换行
	for (i = 1; i < rows - 1; i++)
	{
		if (i < 10)//加入行号判断,当行号小于10的时候输出下面内容,让棋盘看着更舒服,以及解决两位数会导致棋盘显示偏移的问题
		{
			printf(" %d ", i);//行号
		}
		if (i >= 10)
		{
			printf("%d ", i);//行号大于9时
		}
		for (j = 1; j < cols - 1; j++)
		{
			if (result && borad[i][j] == c)//添加判断如果是要显示雷所在棋盘,且对应坐标上面是雷的话就让雷显示红色,方便观看
			{
				printf("\033[1;31m%c\033[0m  ", borad[i][j]);
			}
			else if (borad[i][j] == '*')//如果是*就显示红色的*,方便观看
			{
				printf("\033[1;31m%c\033[0m  ", borad[i][j]);
			}
			else
			{
				printf("%c  ", borad[i][j]);
			}
		}
		printf("\n");
	}
	//打印游戏页尾
	for (i = 0; i < cols - 5; i++)
	{
		if (((cols - 5) / 2) == i)
		{
			printf("-扫雷游戏-");
		}
		printf("---");
	}
	printf("\n");
}

/*
* 功能:查找雷,并且显示在显示棋盘该坐标周围的雷的数量,以及判断是是否是雷。
* 参数:show_borad 要显示的棋盘(数组)
*	   no_show_borad 不显示的棋盘(数组)
*	   rows 游戏难度行数(不显示棋盘行数为准)
*	   cols 游戏难度列数(不显示棋盘列数为准)
*	   c 代表雷的字符
* 返回值:bool类型 true是雷,false不是雷
*/
bool find_mine(char show_borad[MAX_ROW][MAX_COL], char no_show_borad[MAX_ROW][MAX_COL], int rows, int cols, char c)
{
	int x = 1, y = 1;
	printf("请输入要排查的坐标,示例输入:5 6,输入0 0返回上一级。\n");
	while (!((x == 0) && (y == 0)))
	{
		scanf("%d %d", &x, &y);
		if ((x >= 1) && (y >= 1) && (x < (rows - 1)) && (y < (cols - 1)) && (show_borad[x][y] == '*'))
		{
			if (no_show_borad[x][y] == c)
			{
				return true;
			}
			else//不是雷
			{
				//如果不是雷就向周围递归查找雷
				expand_find_mine(show_borad, no_show_borad, rows, cols, x, y);
				
				display_borad(show_borad, rows, cols, false, C_MINE);
				return false;
			}
		}
		else if ((x == 0) && (y == 0))
		{
			continue;//如果用户输入0 0就让他跳过本次循环然后直接进入下次循环判断,然后也就跳出循环回到上级菜单了
		}
		else
		{
			printf("输入坐标不合法,请重新输入:\n");
		}
	}
	return false;
}

/*
* 功能:检查周围雷的个数
* 参数:no_show_borad 不显示的棋盘,存放雷的棋盘
*		show_borad 显示棋盘,主要是用于将标记判断为雷的
*	   x 检查的坐标x轴
*	   y 检查的坐标y轴
* 返回值:雷的数量
*/
static int get_around_mine(char show_borad[MAX_ROW][MAX_COL], char no_show_borad[MAX_ROW][MAX_COL], int x, int y)
{
	int count = 0;
	for (int i = x - 1; i <= x + 1; i++)
	{
		for (int j = y - 1; j <= y + 1; j++)
		{
			if (no_show_borad[i][j] == C_MINE || show_borad[i][j] == '!')
			{
				count++;
			}
		}
	}
	//如果对应坐标不是雷那么就只需要将对应坐标周围8个坐标的值相加,由于是字符所以要对字符'0'(因为字符0不是雷)取模然后得到的余数(此时的余数是周围有多少个雷(阿拉伯数字))再加上'0'就是要显示的数字(字符数字)了
	return count;
}

/*
* 功能:扩散检查周围雷,直到遇到x y坐标上周围有雷停止
* 参数:show_borad 要显示的棋盘
*	   no_show_borad 不显示的棋盘
*	   rows 游戏难度行数
*	   cols 游戏难度列数
*	   x 检查的坐标x轴
*	   y 检查的坐标y轴
* 返回值:空
*/
static void expand_find_mine(char show_borad[MAX_ROW][MAX_COL], char no_show_borad[MAX_ROW][MAX_COL], int rows, int cols, int x, int y)
{
	int i = 0;
	int j = 0;
	//停止递归的条件:
	//1.坐标超出限制
	//2.该坐标是雷
	//3.该坐标已经被查找,准备将已经被查找的坐标设置为'2'
	//4.该坐标已经被标记
	/*if (show_borad[x][y] == MARK)
	{
		return;
	}*/
	if (get_around_mine(show_borad, no_show_borad, x, y))//如果这个坐标周围有雷就将该坐标显示周围雷的数量
	{
		show_borad[x][y] = get_around_mine(show_borad, no_show_borad, x, y) + '0';
		return;
	}
	else//如果周围没有雷就显示'0',周围没有雷就不需要返回,继续执行下面的代码,对这个坐标的周围坐标进行排查
	{
		show_borad[x][y] = '0';
	}
	for (i = x - 1; i <= x + 1; i++)
	{
		for (j = y - 1; j <= y + 1; j++)
		{
			if ((show_borad[i][j] == '*') && (no_show_borad[i][j] == '0') && (i >= 1) && (j >= 1) && (i <= (rows - 2)) && j <= (cols - 2))//这里一定要判断坐标合法性,虽然上面输入已经判断了,但是这里是有递归的,递归之后合不合法要判断
			{
				expand_find_mine(show_borad, no_show_borad, rows, cols, i, j);
			}
		}
	}
}

/*
* 功能:标记
* 参数:borad 要标记的棋盘(数组)
*	   rows 游戏难度行数(不显示棋盘行数为准)
*	   cols 游戏难度列数(不显示棋盘列数为准)
*	   c 标记的字符
* 返回值:空
*/
void mark(char borad[MAX_ROW][MAX_COL], int rows, int cols, char c)
{
	int x = 1, y = 1;
	printf("请输入要标记的坐标,标记也会被视为雷,请谨慎标记。示例输入:5 6,输入0 0返回上一级。\n");
	while (!((x == 0) && (y == 0)))
	{
		scanf("%d %d", &x, &y);
		if ((x >= 1) && (y >= 1) && (x < (rows - 1)) && (y < (cols - 1)) && borad[x][y] == '*')//满足这些条件就标记这个位置,然后重新显示这个棋盘
		{
			borad[x][y] = c;//标记这个位置
			//显示棋盘
			display_borad(borad, rows, cols, false, C_MINE);
			return;
		}
		else if ((x == 0) && (y == 0))
		{
			continue;//如果用户输入0 0就让他跳过本次循环然后直接进入下次循环判断,然后也就跳出循环回到上级菜单了
		}
		else
		{
			printf("输入坐标不合法,请重新输入:\n");
		}
	}
}

/*
* 功能:取消标记
* 参数:borad 要标记的棋盘(数组)
*	   rows 游戏难度行数(不显示棋盘行数为准)
*	   cols 游戏难度列数(不显示棋盘列数为准)
*	   c 标记的字符
* 返回值:空
*/
void unmark(char borad[MAX_ROW][MAX_COL], int rows, int cols, char c)
{
	int x = 1, y = 1;
	printf("请输入要取消标记的坐标,标记也会被视为雷,取消标记之后就不会被视为雷。示例输入:5 6,输入0 0返回上一级。\n");
	while (!((x == 0) && (y == 0)))
	{
		scanf("%d %d", &x, &y);
		if ((x >= 1) && (y >= 1) && (x < (rows - 1)) && (y < (cols - 1)) && borad[x][y] == c)//满足这些条件就取消标记这个位置,然后重新显示这个棋盘
		{
			borad[x][y] = '*';
			//显示棋盘
			display_borad(borad, rows, cols, false, C_MINE);
			return;
		}
		else if ((x == 0) && (y == 0))
		{
			continue;//如果用户输入0 0就让他跳过本次循环然后直接进入下次循环判断,然后也就跳出循环回到上级菜单了
		}
		else
		{
			printf("输入坐标不合法,请重新输入:\n");
		}
	}
}

/*
* 功能:判断是否胜利
* 参数:show_borad 要显示的棋盘(数组)
*	   no_show_borad 不显示的棋盘(数组)
*	   rows 游戏难度行数(不显示棋盘行数为准)
*	   cols 游戏难度列数(不显示棋盘列数为准)
*	   mine_num 雷的个数
* 返回值:bool类型 true胜利,false继续游戏
*/
bool is_win(char show_borad[MAX_ROW][MAX_COL], char no_show_borad[MAX_ROW][MAX_COL], int rows, int cols, int mine_num)
{
	int count = 0;
	int mark_correct = 0;//标记正确,当可以不扫雷,直接标记所有雷的位置也算胜利
	for (int i = 1; i < rows - 1; i++)
	{
		for (int j = 1; j < cols - 1; j++)
		{
			if (show_borad[i][j] == '*')
			{
				count++;
			}
			if (show_borad[i][j] == '!')
			{
				if ((show_borad[i][j] == '!') && no_show_borad[i][j] == '1')
				{
					mark_correct++;
				}
				count++;
			}
			
		}
	}
	if (mark_correct == mine_num || count == mine_num)
	{
		return true;
	}
	return false;
}