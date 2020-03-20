#include "graphics.h"
#include "extgraph.h"
#include "genlib.h"
#include "simpio.h"
#include "random.h"
#include "strlib.h"
#include "conio.h"

#ifndef _DRAW_H_
#define _DRAW_H_

// ģ������Ӻ���
void Draw(void);				// ��Timer���� 

// ģ���ڲ����� 
// �������� 
static void DrawPixel(int x1, int y1, int x2, int y2);		// ���Ƴ����� 
static string Choose_Color(int x);							// ѡ����ɫ 
static void ClearScreen(int x1, int y1, int x2, int y2);	// �ֲ����� 
static void ShowStr(int x, int y, char *str);				// ��ͼ�δ���������ֺ���
static void Single_Pen(int ret);							// ���λ��� 
static void DrawPixelLine(int x1, int y1, int x2, int y2);	// ����һ����

// ����Ϊ���Ϲ��ܺ��� 
static void ToolInterface(void);				// ���߽��� 
static void GameInterface(void);				// ��Ϸ���� 
static void MenuInterface(void); 				// �˵����� 
static void CreateNewMap(void);					// �γ��µ�ͼ������ 
static void DrawNewMap(void);					// �����γɵ������ݻ�ͼ  
static void Interact_Window(void);				// �û���꽻��ͼ�Σ�����ƶ�ָʾ�� 
static void DrawPause(void);					// ������ͣ���� 
static void DrawStart(void);					// ���ƿ�ʼ���� 
static void NameFace(void);						// �û����ݶ��봰�� 
static void Draw_Go(void);						// ��Go 
static void DrawTet(void);						// ��Tetris 
static void DrawRank(void);                     // �����а�
static void DrawHelp(void);                     // ������ 
static void DrawMenuChoice(void);				// ����ʼ����ѡ�� 
static void Delete_Gif(void);					// �������� 
static void End_Gif(void);						// ������Ϸ���� 
 
// �߶������ר�ñ���������  
static void Draw_Line(int len, int ret);									// ������һ���ߣ������黭 
static void SignalDigitalNub(int len, int nub, int space);					// ������������ 
static void Draw_Space(int len);											// �������ּ��϶ 
static void Draw_Nub(int x, int y, int nub, int len, int space, int size);	// �����������ִ�

// ��ʾʱ�� 
static void Show_Time(void);							// ��Ϸ����ʱ����ʾ 
static void GetTime(int *hour, int *min, int *sec);		// ��õ�ǰϵͳʱ�䣬��ָ����ʽ���� 
static void Draw_Point(int x, int y, int size); 		// ���Ƶ㣨ʱ����ʾר�ã� 

#endif
