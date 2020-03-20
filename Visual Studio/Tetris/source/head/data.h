#ifndef _DATA_H_
#define _DATA_H_

#define HEIGHT 20		// ��Ϸ���߶� 
#define WIDTH 10		// ��Ϸ����� 
#define BLOCK_TYPE 19	// ������������ 
#define SIZE 4			// ÿ������洢�����С 
#define NUB 9			// �û��������С 

// ���º�Ϊ�źű������巽ʽ
// ������ӻ�ͼ���� In_Draw
// ������궨������Ӻ꣺#define In_Draw Nub
// ���� Nub Ϊ��ǰ ��NUMBER+1 �Ľ��
// ���ҰѺ� NUMBER ֵҲ��һ
// ���Բ��� Inf[In_Draw] �ķ�ʽ���� 
#define NUMBER 24		// �ź�ָʾ���������� 
#define Is_Menu 0 		// ͼ�ν���ָʾ������0 ��ʾ��Ϸ���� ��1 ��ʾ�˵�����
#define In_Game 1 		// ��Ϸ�źű����� 1 ��ʾ���ڽ�����Ϸ��0 ��ʾ��Ϸδ���� 
// �˵�����������ͼ���� , ��Ӧ�˵������ĸ�ѡ��� 
#define Menu_Ret1 2		// ��ʼ��Ϸ 
#define Menu_Ret2 3		// ������Ϸ 
#define Menu_Ret3 4		// ���а� 
#define Menu_Ret4 5		// ���� 
#define Menu_Ret5 6	// �˳���Ϸ 
#define Read_Name 7 	// �Ƿ�����û��� 
#define Del_Gif 8		// �Ƿ�չʾ��������
#define Name_Ret 9		// ���뽻���źű��� 
#define Name_Remand 10	// ��ʾ�û������û��� 
#define Is_Tool 11		// �Ƿ��ڹ��������� 
#define Is_End 12		// ��Ϸ�Ƿ���� 
#define Is_Save 13		// �Ƿ��д浵 
#define Is_Rank 14		// �Ƿ���ʾ���а� 
#define Is_Help	15		// �Ƿ���ʾ���� 
#define Is_Quit	16		// �Ƿ��˳���Ϸ 
#define Tool_Ret1 17	// ����Ϸ
#define Tool_Ret2 18	// ������Ϸ
#define Tool_Ret3 19	// ���а�
#define Tool_Ret4 20	// ����
#define Tool_Ret5 21	// ���沢�˳� 
#define Is_Back 22		// ���� 
#define Is_Gif 23 
 
extern int Now_Timer;	// ��¼��ǰ��ϷTimer 

// ����ṹ�� 
typedef struct Block_{
	int a[SIZE][SIZE]; 	// ��ŷ�����״ 
}Block;

extern const Block Bck_block[BLOCK_TYPE]; // ��������ģ�� 

extern int Now_Block;	// ��ǰ���� 
extern int Next_Block;	// ��һ������ 
// ������ɫ����Ϊ 1-7 
extern int Now_Color;	// ��ǰ������ɫ 
extern int Next_Color;	// ��һ��������ɫ 

extern int X,Y;			// ��ǰ�������� 

extern int Area[HEIGHT][WIDTH];		// ��Ϸ���� 
extern int Del_Line[HEIGHT];		// ��ǰ�����������У����������� 
 
// ��Ϸ��ʾ��Ϣ	
extern char Con_Name[NUB];	// ��ǰ��Ϸ�û��� 
extern int G_Score;			// ��ǰ�÷� 
extern int Level;			// ��ǰ�Ѷȼ��� 
extern int C_Line; 			// �Ѿ����������� 
extern int S_Line; 			// ��ʼ��Ϸ����
extern int Inf[NUMBER];		// �����źű�������

 // �û��ṹ�� 
typedef struct Con_node{
	int num;					// ����      
	char name[NUB];				// �û��� 
	int score;					// ���� 
	int level;					// �Ѷ� 
	int c_line;					// �������� 
	struct Con_node * next;
} Con;

extern int Num;		// ���а��û����� 
extern Con* Head;	// ��Ϸ�û���������ͷָ�� 

Con* Con_Create(void);						// �½� 
Con* Con_Input(Con *head, Con *consumer);	// ���� 
void Con_Print(Con *head);					// ��ʽ��Console���� 
void Con_Sort(Con *head);					// ���� 
Con* Con_Fileopen(void);					// ���ļ���ȡ���а� 
void Con_Fileprint(Con *head, int n);		// �γ��ļ��������а� 
void Con_Save(void);						// �洢�û����� 
void Con_Continue(void);					// ����浵���� 
int Con_Is_Save(void);						// �ж��Ƿ��д浵 
void Con_DestorySave(void);					// ʹ�浵ʧЧ���ĵ������Զ�λָ� 
 
#endif
