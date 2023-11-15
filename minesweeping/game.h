#pragma once//��ֹ�ظ�����
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <stdbool.h>

/*
* ���Ѷ�
*/
#define SHOW_EASY_ROW 9
#define SHOW_EASY_COL 9
#define NO_SHOW_EASY_ROW (SHOW_EASY_ROW + 2)
#define NO_SHOW_EASY_COL (SHOW_EASY_COL + 2)
#define EASY_MINE 10

/*
* ��ͨ�Ѷ�
*/
#define SHOW_NORMAL_ROW 20
#define SHOW_NORMAL_COL 20
#define NO_SHOW_NORMAL_ROW (SHOW_NORMAL_ROW + 2)
#define NO_SHOW_NORMAL_COL (SHOW_NORMAL_COL + 2)
#define NORMAL_MINE 21

/*
* �����Ѷ�
*/
#define SHOW_HARD_ROW 50
#define SHOW_HARD_COL 50
#define NO_SHOW_HARD_ROW (SHOW_HARD_ROW + 2)
#define NO_SHOW_HARD_COL (SHOW_HARD_COL + 2)
#define HARD_MINE 51

/*
* �������ߴ�
*/
#define MAX_ROW 52
#define MAX_COL 52

/*
* �����׵��ַ�
*/
#define C_MINE '1'

/*
* �����ǵ��ַ�
*/
#define MARK '!'


/*
* ����:��ʼ��ָ������(����),������ȫ��Ϊָ���ַ�
* ����:borad ����ʼ��������(����)
*	   rows ��Ϸ�Ѷ�����
*	   cols ��Ϸ�Ѷ�����
*	   c ָ�����ַ�
* ����ֵ:��
*/
void borad_init(char borad[MAX_ROW][MAX_COL], int rows, int cols, char c);

/*
* ����:��ָ��������з����׵Ĳ���,����ֻ��Ҫ�Բ���ʾ����(����)�ڷ����׾Ϳ�����
* ����:borad �������׵�����(����)
*	   rows ��Ϸ�Ѷ�����(����ʾ����)
*	   cols ��Ϸ�Ѷ�����(����ʾ����)
*	   c �׵��ַ�
* ����ֵ:��
*/
void set_mine(char borad[MAX_ROW][MAX_COL], int rows, int cols, char c, int mine_num);

/*
* ����:��ʾָ������(����)����,�����ʾ99��99��
* ����:borad Ҫ��ʾ������(����)
*	   rows ��Ϸ�Ѷ�����(����ʾ��������Ϊ׼)
*	   cols ��Ϸ�Ѷ�����(����ʾ��������Ϊ׼)
*	   result ���� �ǲ��������ڵ�����
*	   c �׵��ַ�
* ����ֵ:��
*/
void display_borad(char borad[MAX_ROW][MAX_COL], int rows, int cols, bool result, char c);

/*
* ����:������,������ʾ����ʾ���̸�������Χ���׵�����,�Լ��ж����Ƿ����ס�
* ����:show_borad Ҫ��ʾ������(����)
*	   no_show_borad ����ʾ������(����)
*	   rows ��Ϸ�Ѷ�����(����ʾ��������Ϊ׼)
*	   cols ��Ϸ�Ѷ�����(����ʾ��������Ϊ׼)
*	   c �����׵��ַ�
* ����ֵ:bool���� true����,false������
*/
bool find_mine(char show_borad[MAX_ROW][MAX_COL], char no_show_borad[MAX_ROW][MAX_COL], int rows, int cols, char c);

/*
* ����:���
* ����:borad Ҫ��ǵ�����(����)
*	   rows ��Ϸ�Ѷ�����(����ʾ��������Ϊ׼)
*	   cols ��Ϸ�Ѷ�����(����ʾ��������Ϊ׼)
*	   c ��ǵ��ַ�
* ����ֵ:��
*/
void mark(char borad[MAX_ROW][MAX_COL], int rows, int cols, char c);

/*
* ����:ȡ�����
* ����:borad Ҫ��ǵ�����(����)
*	   rows ��Ϸ�Ѷ�����(����ʾ��������Ϊ׼)
*	   cols ��Ϸ�Ѷ�����(����ʾ��������Ϊ׼)
*	   c ��ǵ��ַ�
* ����ֵ:��
*/
void unmark(char borad[MAX_ROW][MAX_COL], int rows, int cols, char c);

/*
* ����:�ж��Ƿ�ʤ��
* ����:show_borad Ҫ��ʾ������(����)
*	   no_show_borad ����ʾ������(����)
*	   rows ��Ϸ�Ѷ�����(����ʾ��������Ϊ׼)
*	   cols ��Ϸ�Ѷ�����(����ʾ��������Ϊ׼)
*	   mine_num �׵ĸ���
* ����ֵ:bool���� trueʤ��,false������Ϸ
*/
bool is_win(char show_borad[MAX_ROW][MAX_COL], char no_show_borad[MAX_ROW][MAX_COL], int rows, int cols, int mine_num);