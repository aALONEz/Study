#define _CRT_SECURE_NO_WARNINGS 1

#include "game.h"


/*
* ����:��Ϸ�й���ѡ��
* ����:��
* ����ֵ:��
*/
void game_function_selection(char show_borad[MAX_ROW][MAX_COL], char no_show_borad[MAX_ROW][MAX_COL], int rows, int cols, int mines)
{
	int gfs_input = 0;
	while (1)
	{
		printf("ѡ��Ҫ���еĶ���:\n1.�Ų���    2.���    3.ȡ�����\n");
		scanf("%d", &gfs_input);//�����û���������
		switch (gfs_input)
		{
			case 1:
				{
					//�Ų���
					bool result = find_mine(show_borad, no_show_borad, rows, cols, C_MINE);
					if (result)//Ϊ������
					{
						printf("������!\n");
						//����ʹ��������ʾ����
						display_borad(no_show_borad, rows, cols, result, C_MINE);//���˾�չʾһ�������׵�λ��
						return;//���׾���Ϸ�������ز˵�ҳ��
					}
					if (is_win(show_borad, no_show_borad, rows, cols, mines))
					{
						printf("��ϲ��ʤ����!\n");
						return;
					}
					break;
				}
			case 2:
				{
					//���
					mark(show_borad, rows, cols, MARK);
					if (is_win(show_borad, no_show_borad, rows, cols, mines))
					{
						printf("��ϲ��ʤ����!\n");
						return;
					}
					break;
				}
			case 3:
				{
					//ȡ�����
					unmark(show_borad, rows, cols, MARK);
					/*if (is_win(show_borad, no_show_borad, rows, cols, mines))//ȡ����ǲ���Ҫ�ж�,��Ϊ��Ȼȡ��������ж�ʤ��,��ôǰ���ǵ�ʱ��һ�������ж�ʤ����
					{
						printf("��ϲ��ʤ����!\n");
						return;
					}*/
					break;
				}
		}
	}
}

/*
* ����:���������ʾ�˵�
* ����:��
* ����ֵ:��
*/
void menu(void)
{
	printf("******************\n");
	printf("*** 1.��ʼ��Ϸ ***\n");
	printf("*** 0.�˳���Ϸ ***\n");
	printf("******************\n");
}

/*
* ����:���������ʾ�ѶȲ˵�
* ����:��
* ����ֵ:��
*/
void difficulty_menu(void)
{
	printf("******************\n");
	printf("*** 1.���Ѷ� ***\n");
	printf("*** 2.��ͨ�Ѷ� ***\n");
	printf("*** 3.�����Ѷ� ***\n");
	printf("***   0.����   ***\n");
	printf("******************\n");
}

/*
* ����:��Ϸ���庯��
* ����:��
* ����ֵ:��
*/
void game(void)
{
	srand((unsigned int)time(NULL));
	int rows, cols, mines;//�������������洢�Ѷ�
	char show_borad[52][52] = {0};//չʾ����
	char no_show_borad[52][52] = {0};//��չʾ����
	int difficulty = 0;//�Ѷ�ѡ��洢����
	difficulty_selection:
	difficulty_menu();//�ѶȲ˵�����
	scanf("%d", &difficulty);
	switch (difficulty)//����ѡ��,ʹ��switch���
	{
		case 0:
			{
				return;//ѡ��0ֱ�ӷ��ز˵�
			}
		case 1:
			{
				//���Ѷ�
				rows = NO_SHOW_EASY_ROW;
				cols = NO_SHOW_EASY_COL;
				mines = EASY_MINE;
				break;
			}
		case 2:
			{
				//��ͨ�Ѷ�
				rows = NO_SHOW_NORMAL_ROW;
				cols = NO_SHOW_NORMAL_COL;
				mines = NORMAL_MINE;
				break;
			}
		case 3:
			{
				//�����Ѷ�
				rows = NO_SHOW_HARD_ROW;
				cols = NO_SHOW_HARD_COL;
				mines = HARD_MINE;
				break;
			}
		default:
			{
				printf("ѡ�����������ѡ��!\n");
				goto difficulty_selection;//ʹ��goto���ص��ѶȲ˵�����
			}
	}
	//�����Ѷ�ѡ����֮���Ӧ�ý����ų�ʼ������,����ʾ���̳�ʼ��Ϊȫ��'*',����ʾ����ȫ����ʼ��Ϊ'0',֮���ٷ���
	//��ʼ����ʾ����(����)
	borad_init(show_borad, rows, cols, '*');
	//��ʼ������ʾ����(����)
	borad_init(no_show_borad, rows, cols, '0');
	//������
	set_mine(no_show_borad, rows, cols, C_MINE, mines);
	//��ʾ����
	display_borad(show_borad, rows, cols, false, C_MINE);
	//��ʾ ����ʾ����,�鿴���Ƿ����������,���������
	//display_borad(no_show_borad, rows, cols, true, C_MINE);
	//��Ϸ�й���ѡ��
	game_function_selection(show_borad, no_show_borad, rows, cols, mines);
}

int main()
{
	//�������ֻ��Ϊ������Windows�����������д��ڳߴ�Ĵ���,��ʱ����Ҫ�㶮�ճ�����.���Ĵ��ڴ�С��Ϊ�˷�������ѶȵĴ��ڵ���,�Է�����ʾȫ������
	HWND console = GetConsoleWindow();
	RECT r;
	GetWindowRect(console, &r); // ��ȡ��ǰ���ڳߴ�
	MoveWindow(console, r.left, r.top, 1495, 970,TRUE); // �����µĴ��ڳߴ�


	int select;//�����û�ѡ��ı���
	do
	{
		//1.����Ӧ�ô�ӡһ�²˵�,չʾһ�²ſ��Խ���ѡ��:
		menu();//�˵�����
		scanf("%d", &select);
		switch (select)//�����ж����ж�,�Һ������Ѷ�ѡ��,��������ʹ��switch
		{
			case 0:
				{
					printf("��л����!\n");
					break;
				}
			case 1:
				{
					game();//��Ϸ��ʽ��ʼ����

					break;
				}
			default:
				{
					printf("�������,������ѡ��!\n");
					break;
				}
		}
	} while (select);
	return 0;
}
