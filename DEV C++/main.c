#include "graphics.h"
#include "extgraph.h"
#include "genlib.h"
#include "simpio.h"
#include "random.h"
#include "strlib.h"
#include "conio.h"
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <windows.h>
#include <olectl.h>
#include <mmsystem.h>
#include <wingdi.h>
#include <ole2.h>
#include <ocidl.h>
#include <winuser.h>
 
#include "main.h"		// ������ͷ�ļ� 
#include "data.h"		// ���ݿ�ͷ�ļ� 
#include "model.h" 		// ģ�Ϳ�ͷ�ļ� 
#include "ctrl.h"		// ���ƿ�ͷ�ļ� 

void Main()
{
	//��Ϸ���ݳ�ʼ��
	InitGame();
	// ͼ�δ��ڳ�ʼ������ 
	SetWindowTitle("Tetris"); 
	SetWindowSize( (double)451/GetXResolution(),(double)550/GetYResolution() );  
	InitGraphics();
	// �ص����� 
	registerMouseEvent(MouseCtrl);
	registerTimerEvent(TimeListener);
	registerKeyboardEvent(KeyBoardCtrl); 
	startTimer(0, 20);	// ��ͼTimer ���� 
}

void TimeListener(int id)
{
	if ( id == 0 ) { 
		Draw(); 
	} else {
		Model_Flow();
	}  
}

//��ʼ����Ϸ���� 
void InitGame(void)
{
	// ȫ����Ϸ�źű�����ʼ�� 
	Inf[Is_Menu]   = 1;	// ������ʾ��Ϸ���� 
	Inf[In_Game]   = 0;	// ��Ϸδ���� 
	Inf[Name_Ret]  = 0; // �������û��� 
	Inf[Is_Help]   = 0;	// ����ʾ���� 
	Inf[Is_Rank]   = 0; // ����ʾ���а� 
	Inf[Is_Quit]   = 0; // ���˳���Ϸ 
	
	// ͼ�ν���������ʼ�� 
	Inf[Menu_Ret1] = 0; // ��ʼ��Ϸ 
	Inf[Menu_Ret2] = 0; // ����浵 
	Inf[Menu_Ret3] = 0; // ���а� 
	Inf[Menu_Ret4] = 0; // ���� 
	Inf[Menu_Ret5] = 0; // �˳���Ϸ 
	Inf[Tool_Ret1] = 0;	// ����Ϸ
	Inf[Tool_Ret2] = 0;	// ������Ϸ
	Inf[Tool_Ret3] = 0;	// ���а�
	Inf[Tool_Ret4] = 0;	// ����
	Inf[Tool_Ret5] = 0;	// ���沢�˳�
	
	Head = Con_Fileopen();		// �������а� 
	Inf[Is_Save] = Con_Is_Save();  	// �ж��Ƿ��д浵 
}
