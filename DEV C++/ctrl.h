#ifndef _CTRL_H_
#define _CTRL_H_

#define In(x1,y1,x2,y2) ( x>=(x1) && x<=(x2) && y>=(y1) && y<=(y2) )  

// ����keyֵ 
#define Key_Up 38
#define Key_Down 40
#define Key_Left 37
#define Key_Right 39
#define Space 32 
#define Key_Enter 13
#define Key_A 65
#define Key_B 66
#define Key_C 67
#define Key_H 72
#define Key_N 78
#define Key_P 80
#define Key_R 82
#define Key_S 83
#define Key_T 84
#define Key_Z 90 
#define Key_Q 81
#define Key_Backspace 8

// ģ�����Ӻ��� 
void MouseCtrl(int x, int y, int button, int event);// �� Main�е��ã����ص�  
void KeyBoardCtrl(int key, int event);				// �� Main�е��ã����̻ص� 
void Init_Data(void);								// �û���ѡ��Ϸ���ݳ�ʼ��
void Init_Game(void); 								// ���û����ݳ�ʼ��

// ģ���ں��� 
static void Go_Button(void);					// ���� Modle������ʵ�ֿո���ʵ���� 
static void MenuKeyCtrl(int key, int event);	// �˵���ݼ��ص����� 
static void GameKeyCtrl(int key, int event);	// ��Ϸ���̿��ƺ��� 
static void NameKeyCtrl(int key, int event);	// ��Ϸ�û�������ƺ��� 
static void HotKeyCtrl(int key, int event);		// ��ݼ����ƺ��� 
static void ToolKeyCtrl(int key, int event);	// �������ص����� 

static void MenuMouseCtrl(int x, int y, int button, int event); // �˵������ƽ�������
static void HotMouseCtrl(int x, int y, int button, int event);	// ��ݼ������ƽ������� 
static void ToolMouseCtrl(int x, int y, int button, int event);	// �����������ƽ������� 
static void NameMouseCtrl(int x, int y, int button, int event);	// �û������������ص����� 

static void Turn_Block(void);				// �ı䷽������ 
static int Is_Touch(void);					// �жϷ����Ƿ�����з����ص����߳����߽� 
static void Left_Move(void);				// �����ƶ����� 
static void Right_Move(void);				// �����ƶ����� 

#endif 
