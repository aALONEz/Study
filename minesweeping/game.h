#pragma once//防止重复定义
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <stdbool.h>

/*
* 简单难度
*/
#define SHOW_EASY_ROW 9
#define SHOW_EASY_COL 9
#define NO_SHOW_EASY_ROW (SHOW_EASY_ROW + 2)
#define NO_SHOW_EASY_COL (SHOW_EASY_COL + 2)
#define EASY_MINE 10

/*
* 普通难度
*/
#define SHOW_NORMAL_ROW 20
#define SHOW_NORMAL_COL 20
#define NO_SHOW_NORMAL_ROW (SHOW_NORMAL_ROW + 2)
#define NO_SHOW_NORMAL_COL (SHOW_NORMAL_COL + 2)
#define NORMAL_MINE 21

/*
* 困难难度
*/
#define SHOW_HARD_ROW 50
#define SHOW_HARD_COL 50
#define NO_SHOW_HARD_ROW (SHOW_HARD_ROW + 2)
#define NO_SHOW_HARD_COL (SHOW_HARD_COL + 2)
#define HARD_MINE 51

/*
* 最大数组尺寸
*/
#define MAX_ROW 52
#define MAX_COL 52

/*
* 代表雷的字符
*/
#define C_MINE '1'

/*
* 代表标记的字符
*/
#define MARK '!'


/*
* 功能:初始化指定数组(棋盘),的内容全部为指定字符
* 参数:borad 被初始化的数组(棋盘)
*	   rows 游戏难度行数
*	   cols 游戏难度列数
*	   c 指定的字符
* 返回值:空
*/
void borad_init(char borad[MAX_ROW][MAX_COL], int rows, int cols, char c);

/*
* 功能:对指定数组进行放置雷的操作,这里只需要对不显示棋盘(数组)内放置雷就可以了
* 参数:borad 被放置雷的数组(棋盘)
*	   rows 游戏难度行数(不显示棋盘)
*	   cols 游戏难度列数(不显示棋盘)
*	   c 雷的字符
* 返回值:空
*/
void set_mine(char borad[MAX_ROW][MAX_COL], int rows, int cols, char c, int mine_num);

/*
* 功能:显示指定棋盘(数组)内容,最多显示99行99列
* 参数:borad 要显示的棋盘(数组)
*	   rows 游戏难度行数(不显示棋盘行数为准)
*	   cols 游戏难度列数(不显示棋盘列数为准)
*	   result 数组 是不是雷所在的数组
*	   c 雷的字符
* 返回值:空
*/
void display_borad(char borad[MAX_ROW][MAX_COL], int rows, int cols, bool result, char c);

/*
* 功能:查找雷,并且显示在显示棋盘该坐标周围的雷的数量,以及判断是是否是雷。
* 参数:show_borad 要显示的棋盘(数组)
*	   no_show_borad 不显示的棋盘(数组)
*	   rows 游戏难度行数(不显示棋盘行数为准)
*	   cols 游戏难度列数(不显示棋盘列数为准)
*	   c 代表雷的字符
* 返回值:bool类型 true是雷,false不是雷
*/
bool find_mine(char show_borad[MAX_ROW][MAX_COL], char no_show_borad[MAX_ROW][MAX_COL], int rows, int cols, char c);

/*
* 功能:标记
* 参数:borad 要标记的棋盘(数组)
*	   rows 游戏难度行数(不显示棋盘行数为准)
*	   cols 游戏难度列数(不显示棋盘列数为准)
*	   c 标记的字符
* 返回值:空
*/
void mark(char borad[MAX_ROW][MAX_COL], int rows, int cols, char c);

/*
* 功能:取消标记
* 参数:borad 要标记的棋盘(数组)
*	   rows 游戏难度行数(不显示棋盘行数为准)
*	   cols 游戏难度列数(不显示棋盘列数为准)
*	   c 标记的字符
* 返回值:空
*/
void unmark(char borad[MAX_ROW][MAX_COL], int rows, int cols, char c);

/*
* 功能:判断是否胜利
* 参数:show_borad 要显示的棋盘(数组)
*	   no_show_borad 不显示的棋盘(数组)
*	   rows 游戏难度行数(不显示棋盘行数为准)
*	   cols 游戏难度列数(不显示棋盘列数为准)
*	   mine_num 雷的个数
* 返回值:bool类型 true胜利,false继续游戏
*/
bool is_win(char show_borad[MAX_ROW][MAX_COL], char no_show_borad[MAX_ROW][MAX_COL], int rows, int cols, int mine_num);