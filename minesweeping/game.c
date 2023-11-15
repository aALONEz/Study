#define _CRT_SECURE_NO_WARNINGS 1

#include "game.h"//����game.h

static int get_around_mine(char show_borad[MAX_ROW][MAX_COL], char no_show_borad[MAX_ROW][MAX_COL], int x, int y);

static void expand_find_mine(char show_borad[MAX_ROW][MAX_COL], char no_show_borad[MAX_ROW][MAX_COL], int rows, int cols, int x, int y);

/*
* ����:��ʼ��ָ������(����),������ȫ��Ϊָ���ַ�
* ����:borad ����ʼ��������(����)
*	   rows ��Ϸ�Ѷ�����
*	   cols ��Ϸ�Ѷ�����
*	   c ָ�����ַ�
* ����ֵ:��
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
* ����:��ָ��������з����׵Ĳ���,����ֻ��Ҫ�Բ���ʾ����(����)�ڷ����׾Ϳ�����
* ����:borad �������׵�����(����)
*	   rows ��Ϸ�Ѷ�����(����ʾ����)
*	   cols ��Ϸ�Ѷ�����(����ʾ����)
*	   c �׵��ַ�
* ����ֵ:��
*/
void set_mine(char borad[MAX_ROW][MAX_COL], int rows, int cols, char c, int mine_num)
{
	//ʹ�������,rand����,��ʹ��rand����֮ǰҪ����srand������������,����ʹ��ʱ�����Ϊ����,srand��������ֻ��Ҫ����һ��,���Է��ڳ�������������������
	int x, y;
	while (mine_num)
	{
		x = rand() % (rows - 2) + 1;
		y = rand() % (cols - 2) + 1;
		if (borad[x][y] != c)//�����λ�ò������׵��ַ�֮��������λ�õ����׵��ַ�,���׵�����--
		{
			borad[x][y] = c;
			mine_num--;//�����βμ�������Ӱ��ʵ��,�������滹����ʹ��ʵ���ж�ʤ����
		}
	}
}

/*
* ����:��ʾָ������(����)����,�����ʾ99��99��
* ����:borad Ҫ��ʾ������(����)
*	   rows ��Ϸ�Ѷ�����(����ʾ��������Ϊ׼)
*	   cols ��Ϸ�Ѷ�����(����ʾ��������Ϊ׼)
*	   result ���� �ǲ��������ڵ�����
*	   c �׵��ַ�
* ����ֵ:��
*/
void display_borad(char borad[MAX_ROW][MAX_COL], int rows, int cols, bool result, char c)
{
	int i = 0, j = 0;
	//��ӡ��Ϸ����
	for (i = 0; i < cols - 5; i++)
	{
		if (((cols - 5) / 2) == i)
		{
			printf("-ɨ����Ϸ-");
		}
		printf("---");
	}
	printf("\n");
	//��ʾ�к�
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
	printf("\n");//��һ����ʾ�к�֮����л���
	for (i = 1; i < rows - 1; i++)
	{
		if (i < 10)//�����к��ж�,���к�С��10��ʱ�������������,�����̿��Ÿ����,�Լ������λ���ᵼ��������ʾƫ�Ƶ�����
		{
			printf(" %d ", i);//�к�
		}
		if (i >= 10)
		{
			printf("%d ", i);//�кŴ���9ʱ
		}
		for (j = 1; j < cols - 1; j++)
		{
			if (result && borad[i][j] == c)//����ж������Ҫ��ʾ����������,�Ҷ�Ӧ�����������׵Ļ���������ʾ��ɫ,����ۿ�
			{
				printf("\033[1;31m%c\033[0m  ", borad[i][j]);
			}
			else if (borad[i][j] == '*')//�����*����ʾ��ɫ��*,����ۿ�
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
	//��ӡ��Ϸҳβ
	for (i = 0; i < cols - 5; i++)
	{
		if (((cols - 5) / 2) == i)
		{
			printf("-ɨ����Ϸ-");
		}
		printf("---");
	}
	printf("\n");
}

/*
* ����:������,������ʾ����ʾ���̸�������Χ���׵�����,�Լ��ж����Ƿ����ס�
* ����:show_borad Ҫ��ʾ������(����)
*	   no_show_borad ����ʾ������(����)
*	   rows ��Ϸ�Ѷ�����(����ʾ��������Ϊ׼)
*	   cols ��Ϸ�Ѷ�����(����ʾ��������Ϊ׼)
*	   c �����׵��ַ�
* ����ֵ:bool���� true����,false������
*/
bool find_mine(char show_borad[MAX_ROW][MAX_COL], char no_show_borad[MAX_ROW][MAX_COL], int rows, int cols, char c)
{
	int x = 1, y = 1;
	printf("������Ҫ�Ų������,ʾ������:5 6,����0 0������һ����\n");
	while (!((x == 0) && (y == 0)))
	{
		scanf("%d %d", &x, &y);
		if ((x >= 1) && (y >= 1) && (x < (rows - 1)) && (y < (cols - 1)) && (show_borad[x][y] == '*'))
		{
			if (no_show_borad[x][y] == c)
			{
				return true;
			}
			else//������
			{
				//��������׾�����Χ�ݹ������
				expand_find_mine(show_borad, no_show_borad, rows, cols, x, y);
				
				display_borad(show_borad, rows, cols, false, C_MINE);
				return false;
			}
		}
		else if ((x == 0) && (y == 0))
		{
			continue;//����û�����0 0��������������ѭ��Ȼ��ֱ�ӽ����´�ѭ���ж�,Ȼ��Ҳ������ѭ���ص��ϼ��˵���
		}
		else
		{
			printf("�������겻�Ϸ�,����������:\n");
		}
	}
	return false;
}

/*
* ����:�����Χ�׵ĸ���
* ����:no_show_borad ����ʾ������,����׵�����
*		show_borad ��ʾ����,��Ҫ�����ڽ�����ж�Ϊ�׵�
*	   x ��������x��
*	   y ��������y��
* ����ֵ:�׵�����
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
	//�����Ӧ���겻������ô��ֻ��Ҫ����Ӧ������Χ8�������ֵ���,�������ַ�����Ҫ���ַ�'0'(��Ϊ�ַ�0������)ȡģȻ��õ�������(��ʱ����������Χ�ж��ٸ���(����������))�ټ���'0'����Ҫ��ʾ������(�ַ�����)��
	return count;
}

/*
* ����:��ɢ�����Χ��,ֱ������x y��������Χ����ֹͣ
* ����:show_borad Ҫ��ʾ������
*	   no_show_borad ����ʾ������
*	   rows ��Ϸ�Ѷ�����
*	   cols ��Ϸ�Ѷ�����
*	   x ��������x��
*	   y ��������y��
* ����ֵ:��
*/
static void expand_find_mine(char show_borad[MAX_ROW][MAX_COL], char no_show_borad[MAX_ROW][MAX_COL], int rows, int cols, int x, int y)
{
	int i = 0;
	int j = 0;
	//ֹͣ�ݹ������:
	//1.���곬������
	//2.����������
	//3.�������Ѿ�������,׼�����Ѿ������ҵ���������Ϊ'2'
	//4.�������Ѿ������
	/*if (show_borad[x][y] == MARK)
	{
		return;
	}*/
	if (get_around_mine(show_borad, no_show_borad, x, y))//������������Χ���׾ͽ���������ʾ��Χ�׵�����
	{
		show_borad[x][y] = get_around_mine(show_borad, no_show_borad, x, y) + '0';
		return;
	}
	else//�����Χû���׾���ʾ'0',��Χû���׾Ͳ���Ҫ����,����ִ������Ĵ���,������������Χ��������Ų�
	{
		show_borad[x][y] = '0';
	}
	for (i = x - 1; i <= x + 1; i++)
	{
		for (j = y - 1; j <= y + 1; j++)
		{
			if ((show_borad[i][j] == '*') && (no_show_borad[i][j] == '0') && (i >= 1) && (j >= 1) && (i <= (rows - 2)) && j <= (cols - 2))//����һ��Ҫ�ж�����Ϸ���,��Ȼ���������Ѿ��ж���,�����������еݹ��,�ݹ�֮��ϲ��Ϸ�Ҫ�ж�
			{
				expand_find_mine(show_borad, no_show_borad, rows, cols, i, j);
			}
		}
	}
}

/*
* ����:���
* ����:borad Ҫ��ǵ�����(����)
*	   rows ��Ϸ�Ѷ�����(����ʾ��������Ϊ׼)
*	   cols ��Ϸ�Ѷ�����(����ʾ��������Ϊ׼)
*	   c ��ǵ��ַ�
* ����ֵ:��
*/
void mark(char borad[MAX_ROW][MAX_COL], int rows, int cols, char c)
{
	int x = 1, y = 1;
	printf("������Ҫ��ǵ�����,���Ҳ�ᱻ��Ϊ��,�������ǡ�ʾ������:5 6,����0 0������һ����\n");
	while (!((x == 0) && (y == 0)))
	{
		scanf("%d %d", &x, &y);
		if ((x >= 1) && (y >= 1) && (x < (rows - 1)) && (y < (cols - 1)) && borad[x][y] == '*')//������Щ�����ͱ�����λ��,Ȼ��������ʾ�������
		{
			borad[x][y] = c;//������λ��
			//��ʾ����
			display_borad(borad, rows, cols, false, C_MINE);
			return;
		}
		else if ((x == 0) && (y == 0))
		{
			continue;//����û�����0 0��������������ѭ��Ȼ��ֱ�ӽ����´�ѭ���ж�,Ȼ��Ҳ������ѭ���ص��ϼ��˵���
		}
		else
		{
			printf("�������겻�Ϸ�,����������:\n");
		}
	}
}

/*
* ����:ȡ�����
* ����:borad Ҫ��ǵ�����(����)
*	   rows ��Ϸ�Ѷ�����(����ʾ��������Ϊ׼)
*	   cols ��Ϸ�Ѷ�����(����ʾ��������Ϊ׼)
*	   c ��ǵ��ַ�
* ����ֵ:��
*/
void unmark(char borad[MAX_ROW][MAX_COL], int rows, int cols, char c)
{
	int x = 1, y = 1;
	printf("������Ҫȡ����ǵ�����,���Ҳ�ᱻ��Ϊ��,ȡ�����֮��Ͳ��ᱻ��Ϊ�ס�ʾ������:5 6,����0 0������һ����\n");
	while (!((x == 0) && (y == 0)))
	{
		scanf("%d %d", &x, &y);
		if ((x >= 1) && (y >= 1) && (x < (rows - 1)) && (y < (cols - 1)) && borad[x][y] == c)//������Щ������ȡ��������λ��,Ȼ��������ʾ�������
		{
			borad[x][y] = '*';
			//��ʾ����
			display_borad(borad, rows, cols, false, C_MINE);
			return;
		}
		else if ((x == 0) && (y == 0))
		{
			continue;//����û�����0 0��������������ѭ��Ȼ��ֱ�ӽ����´�ѭ���ж�,Ȼ��Ҳ������ѭ���ص��ϼ��˵���
		}
		else
		{
			printf("�������겻�Ϸ�,����������:\n");
		}
	}
}

/*
* ����:�ж��Ƿ�ʤ��
* ����:show_borad Ҫ��ʾ������(����)
*	   no_show_borad ����ʾ������(����)
*	   rows ��Ϸ�Ѷ�����(����ʾ��������Ϊ׼)
*	   cols ��Ϸ�Ѷ�����(����ʾ��������Ϊ׼)
*	   mine_num �׵ĸ���
* ����ֵ:bool���� trueʤ��,false������Ϸ
*/
bool is_win(char show_borad[MAX_ROW][MAX_COL], char no_show_borad[MAX_ROW][MAX_COL], int rows, int cols, int mine_num)
{
	int count = 0;
	int mark_correct = 0;//�����ȷ,�����Բ�ɨ��,ֱ�ӱ�������׵�λ��Ҳ��ʤ��
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