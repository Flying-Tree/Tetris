#include "data.h"
#include "ctrl.h"
#include "model.h"
#include <stdio.h>

static int Name_cnt = 0;	// ��¼�û������ַ����� 

// ���ص����� 
void MouseCtrl(int x, int y, int button, int event)
{
//	printf("x=%d,y=%d,button=%d,event=%d\n",x,y,button,event);
	if( Inf[Is_Menu] == 1 ){	 				// �˵��ص����� 
		MenuMouseCtrl(x,y,button,event);
	} else if ( Inf[Is_Menu] == 0 && !Inf[Is_Gif] ) {			// ��Ϸ���� 
		if ( Inf[Read_Name] ) {					// �û������룬�Ѷ�ѡ��� 
			NameMouseCtrl(x,y,button,event);
		} else{
			HotMouseCtrl(x,y,button,event);		// ��Ϸ�еĿ�ݼ� 
		} 
		if ( Inf[Is_Tool] ) {					// �������Ŀ�ݼ� 
			ToolMouseCtrl(x,y,button,event);
		}
	}
}

// ���̻ص� 
void KeyBoardCtrl(int key, int event)
{
//	printf("key=%d, event=%d\n", key, event);
	if ( Inf[Is_Menu] == 1) { 			// ���˵� 
		MenuKeyCtrl(key, event);
	} else if ( Inf[Is_Menu] == 0 && !Inf[Is_Gif] ){	// ��Ϸ���� 
		if( Inf[Read_Name] ){			// �û�������̻ص� 
			NameKeyCtrl(key, event);
		} else {						// ��Ϸ����
			HotKeyCtrl(key, event);		// ��ݼ��ص� 
			if( Inf[In_Game] ){ 		// ��Ϸ�еļ��̻ص� 
				GameKeyCtrl(key, event); 
			} else {					// ��ͣ 
				if(Inf[Is_Tool]){		// �������ص� 
					ToolKeyCtrl(key,event);
				}
			}	
		}
	}
}

// �˵����̻ص� 
static void MenuKeyCtrl(int key, int event)
{
	 
	if (!event) {	// ��ס���� 
		switch(key){	// �û������źű��� 
			case Key_S:	Inf[Menu_Ret1] = 1; break;
			case Key_C:	Inf[Menu_Ret2] = 1; break;
			case Key_R:	Inf[Menu_Ret3] = 1; break;
			case Key_H:	Inf[Menu_Ret4] = 1; break;
			case Key_Q:	Inf[Menu_Ret5] = 1; break;
		}
	} else {
		// �������� 
		Inf[Menu_Ret1] = 0;
		Inf[Menu_Ret2] = 0;
		Inf[Menu_Ret3] = 0;
		Inf[Menu_Ret4] = 0;
		Inf[Menu_Ret5] = 0;
		// �����б� 
		switch(key){
			case Key_S:
				if ( !Inf[Is_Rank] && !Inf[Is_Help] ){ // �������а�Ͱ����˵��� ��ͬ 
					Inf[Is_Menu] = 0;		// ������Ϸ 
					Init_Game();			// ��ʼ�����û��޸�����	
				}
				break;
			case Key_C:
				if ( !Inf[Is_Rank] && !Inf[Is_Help] ){
					if(Inf[Is_Save]){  		// ����д浵 
						Con_Continue(); 	// ��ȡ�浵 
						Con_DestorySave();	// ���ٴ浵 
						Inf[Is_Save] = Con_Is_Save(); 	// �浵�����ж�
						// ��ת����Ϸ���� 
						Inf[In_Game] = 0;
						Inf[Is_Menu] = 0;
						Inf[Read_Name] = 0; 
					} else {
						printf("û�д浵\n");
					}	
				}
				break;
			case Key_R: // ���а�չʾ 
				if(Inf[Is_Rank]){
					Inf[Is_Rank] = 0;
				} else {
					if( !Inf[Is_Help] ){
						Con_Print(Head);
						Inf[Is_Rank] = 1;	
					}
				}
				break;
			case Key_H:	// ����չʾ 
				if(Inf[Is_Help]){
					Inf[Is_Help] = 0;
				} else {
					if( !Inf[Is_Rank] ) {
						Inf[Is_Help] = 1;
					}
				} 
				break;
			case Key_B:	// �˳����а�Ͳ˵� 
				Inf[Is_Rank] = 0;
				Inf[Is_Help] = 0;
				break; 
			case Key_Q:	// �˳���Ϸ 
				if( !Inf[Is_Rank] && !Inf[Is_Help] ){
					Inf[Is_Quit] = 1;
					break; 	
				} 
		}
	}
} 

// ���������̻ص� 
static void ToolKeyCtrl(int key, int event)
{
	if (Inf[Is_Tool] && !event) {
		switch(key){
			case Key_N: // ����Ϸ 
				if( !Inf[Is_Rank] && !Inf[Is_Help] ){
					Inf[Is_Menu] = 0;
					cancelTimer(Now_Timer); // ������ǰ��ϷTimer 
					Init_Game();
				}
				break;
			case Key_C:	// ������Ϸ 
				if( !Inf[Is_Rank] && !Inf[Is_Help] ){
					Inf[Is_Tool] = 0;
					Inf[In_Game] = 1;
				}
				break;
			case Key_R:	// ���а� 
				if( Inf[Is_Rank] ){
					Inf[Is_Rank] = 0;
				} else {
					if( !Inf[Is_Help] ){
						Inf[Is_Rank] = 1;
					}
				}
				break;
			case Key_H:	// ���� 
				if( Inf[Is_Help] ){
					Inf[Is_Help] = 0;
				} else {
					if( !Inf[Is_Rank] ){
						Inf[Is_Help] = 1;
					}
				}
				break;
			case Key_B: // ���� 
				if( !Inf[Is_Rank] && !Inf[Is_Help] ){
					Con_Save();
					Inf[Is_Tool] = 0; 
					Inf[Is_Menu] = 1;
					Inf[Is_Save] = Con_Is_Save(); 
				}
				Inf[Is_Rank] = 0;
				Inf[Is_Help] = 0;
				break;
		}
	}
}

// ��ʼ������Ϸ���ݣ��û����ȳ�ʼ�� 
void Init_Data(void)
{
	// ��Ҫ�û�����֮���ʼ�� 
	int i,j; 
	Now_Timer = Level; 
	startTimer(Now_Timer, (21-Now_Timer)*40); 
	
	for(i=0; i<HEIGHT-S_Line; i++){		// ��ʼ�����ʼ��Ϊ�� 
		for(j=0; j<WIDTH; j++){
			Area[i][j] = 0; 
		}
	}
	srand(time(NULL));
	for(i=HEIGHT-S_Line; i<HEIGHT; i++){	// �û�ָ��������ʼ��Ϊ����ո� 
		for(j=0; j<WIDTH; j++){
			Area[i][j] = !(rand()%4)*(rand()%7+1);
		}
	} 
	Inf[In_Game] = 1;	// ��Ϸ���� 
} 

// ��ʼ����Ϸ�� ���û�ָ�����ݳ�ʼ�� 
void Init_Game(void)  
{
	int i,j;
	// ��Ҫ������Ϸ�ͳ�ʼ�� 
	Level = 1;		// ��ʼ����Ϸ�Ѷ�Ϊ 1 
	G_Score = 0; 	// ��ʼ�������� ��ʼ������ �������� 
	S_Line = 0;
	C_Line = 0;
	// ��ʼ����Ϸ���� 
	for(i=0; i<HEIGHT; i++){
		for(j=0; j<WIDTH; j++){
			Area[i][j] = 0; 
		}
	}
	// ��ʼ���������ɫ 
	Now_Color = 1; 
	Next_Color = 2; 
	srand(time(NULL));
	Next_Block = rand()%BLOCK_TYPE;
	// ��ʼ��������ʼλ������
	X = -1;	 
	Y = WIDTH/2-2;	
	// ��ʼ���û���
	for(i=0; i<NUB; i++){ 
		Con_Name[i] = 0;
	} 
	// ��ʼ����Ϸ�ڲ��źű��� 
	Inf[In_Game] = 0; 
	Inf[Is_Tool] = 0; 
	Inf[Read_Name] = 1;
	Inf[Name_Remand] = 0; 
	Inf[Is_End] = 0;
	Inf[Is_Help] = 0;
	Inf[Is_Rank] = 0;
	Inf[Del_Gif] = 0; 
}

// ��Ϸ��ݼ��ص� 
static void HotKeyCtrl(int key, int event)
{
	static int ret = 1;
	if(!event){
		switch(key){
			case Key_P:	// ��ͣ 
				// ȷ���������ᷴ������ͣ�ͼ���֮��ת��
				if(ret){ 
					ret = 0;
					if( Inf[In_Game] ){
						Inf[In_Game] = 0;
					} else {
						Inf[In_Game] = 1;
						Inf[Is_Tool] = 0;
					}
				}
			case Key_T:	// ������ 
				if(ret){ 
					ret = 0;
					if( Inf[In_Game] ){
						Inf[In_Game] = 0;
					}
					if( Inf[Is_Tool] == 0 ){
						Inf[Is_Tool] = 1;
					} else if(Inf[Is_Tool] == 1){
						Inf[Is_Tool] = 0;
						Inf[In_Game] = 1;
					}
				}
		}
	} else {
		ret = 1;
	}
}

// ��Ϸ���̿��ƺ��� 
static void GameKeyCtrl(int key, int event)
{
	static int ret; 
	// רΪ�����������壬��Ӧʵ��һֱ����ֻ��Ҫһ�β����ĺ��� 
	if(!event){
		switch(key){
			case Key_Up: 	//��ת���� 
				if(ret){
					Turn_Block();
					ret = 0;	
				}
				break;
			case Key_Down:	//�½� 
			// ����������ʱ�������ģ�ͺ���
				if( !Inf[Del_Gif] ){ 
					TimeListener(1); 	
				}
				break;  
			case Key_Left:
				Left_Move();
				break;
			case Key_Right:
				Right_Move();
				break; 
			case Space:
				Go_Button();
				break;
		} 
	} else {
		ret = 1;
	}
} 

// �û�������ص����� 
static void NameKeyCtrl(int key, int event)
{
	if(!event){
		if ( key != Key_Enter ) { // �û������� 
			if ( key >= Key_A && key <= Key_Z  && Name_cnt < NUB-1 ) {
				Con_Name[Name_cnt++] = key;
			} else if( key == Key_Backspace && Name_cnt > 0 ){ // ɾ�� 
				Con_Name[--Name_cnt] = 0;
			}
			switch(key){ // �ѶȺͿ�ʼ�����ص� 
				case Key_Up:
					if(S_Line < 10){
						S_Line++;
					}
					break;
				case Key_Down:
					if(S_Line > 0){
						S_Line--;
					}
					break;
				case Key_Left:
					if(Level < 20){
						Level++;
					}
					break;
				case Key_Right:
					if(Level > 1){
						Level--;
					}
					break; 
				default:break;
			}
		} else { // �����û�����֮��Ĳ��� 
			if(Name_cnt > 0){
				Inf[Read_Name] = 0; 	// �����û����� 
				Init_Data();
				Name_cnt = 0; 
			} else {
				Inf[Name_Remand] = 1;	// �û���Ϊ�գ� ��ʾ�����û��� 
			}
		}
	}
} 

// �˵����ص� 
static void MenuMouseCtrl(int x, int y, int button, int event)
{
	if( In(175,190,275,220) ){ 	// ����ƶ������ͼ���� 
		Inf[Menu_Ret1] = 1;		// ��ͼ�����޸�Ϊ1 
		if ( button==1 && event==0 && !Inf[Is_Rank] && !Inf[Is_Help] ){
			Inf[Is_Menu] = 0;		// ������Ϸ 
			Init_Game();			// ��ʼ�����û��޸�����	
		}
	} else {
		Inf[Menu_Ret1] = 0;		// ����Ƴ���ǰͼ�� ��ͼ�����޸�Ϊ0 
	}
	// ��ͬ
	if( In(175,230,275,260) ){
		Inf[Menu_Ret2] = 1;
		
		if ( !Inf[Is_Rank] && !Inf[Is_Help] && button==1 && event==0 ){
			if(Inf[Is_Save]){
				Inf[Is_Menu] = 0;
				Inf[Read_Name] = 0;
				Con_Continue();
				Inf[In_Game] = 0; 
				Con_DestorySave();
				Inf[Is_Save] = Con_Is_Save(); 
			} else {
				printf("û�д浵\n");
			}	
		}
	} else {
		Inf[Menu_Ret2] = 0;
	}
	
	if( In(175,270,275,300) ){
		printf("���а�\n"); 
		Inf[Menu_Ret3] = 1;
		if( button==1 && event==0){
			if( !Inf[Is_Rank]) {
				if( !Inf[Is_Help] ){
					Inf[Is_Rank] = 1;	
				}
			}
		}
	} else {
		Inf[Menu_Ret3] = 0;
	}
	
	if( In(175,310,275,340) ){ // ���а� 
		Inf[Menu_Ret4] = 1;
		if( button==1 && event==0){
			if(!Inf[Is_Help]){
				if( !Inf[Is_Rank] ) {
					Inf[Is_Help] = 1;
				}
			}
		}
	} else {
		Inf[Menu_Ret4] = 0;
	}

	if( In(175,350,275,380) ){	// ���� 
		Inf[Menu_Ret5] = 1;
		if( button==1 && event==0){
			if( !Inf[Is_Rank] && !Inf[Is_Help] ){
				Inf[Is_Quit] = 1;
			} 
		}
	} else {
		Inf[Menu_Ret5] = 0;
	}
	
	if( In(180,370,255,400) ){	// �˳���Ϸ 
		Inf[Is_Back] = 1;
		if( button==1 && event==0 && Inf[Is_Help]==0){
			Inf[Is_Rank] = 0;
		}
		if( button==1 && event==0 && Inf[Is_Rank]==0){
			Inf[Is_Help] = 0;
		}
	}else{
		Inf[Is_Back] = 0;
	}
}

// �������ص� 
static void ToolMouseCtrl(int x, int y, int button, int event)
{
	if( In(175,190,275,220) ){ 	// ����ƶ������ͼ���� 
		Inf[Tool_Ret1] = 1;		// ��ͼ�����޸�Ϊ1 
		if( button==1 && event==0){	// ������ 
			if( !Inf[Is_Rank] && !Inf[Is_Help] ){
				printf("����Ϸ\n"); 
				Inf[Is_Menu] = 0;
				cancelTimer(Now_Timer);
				Init_Game();
			}
		}
	} else {
		Inf[Tool_Ret1] = 0;		// ����Ƴ���ǰͼ�� ��ͼ�����޸�Ϊ0 
	}
	// ��ͬ
	if( In(175,230,275,260) ){
		Inf[Tool_Ret2] = 1;
		if( button==1 && event==0){
			if( !Inf[Is_Rank] && !Inf[Is_Help] ){
				printf("������Ϸ\n");
				Inf[Is_Tool] = 0;
				Inf[In_Game] = 1;
			}
		}
	} else {
		Inf[Tool_Ret2] = 0;
	}
	
	if( In(175,270,275,300) ){	// ���а� 
		Inf[Tool_Ret3] = 1;
		if( button==1 && event==0){
			if ( !Inf[Is_Rank] ) {
				if( !Inf[Is_Help] ){
					printf("���а�\n"); 
					Inf[Is_Rank] = 1;
					Con_Print(Head);
				}
			}
		}
	} else {
		Inf[Tool_Ret3] = 0;
	}
	
	if( In(175,310,275,340) ){	// ���� 
		Inf[Tool_Ret4] = 1;
		if( button==1 && event==0){
			if ( !Inf[Is_Help] ) {
				if( !Inf[Is_Rank] ){
					printf("����\n");
					Inf[Is_Help] = 1;
				}
			}
		}
	} else {
		Inf[Tool_Ret4] = 0;
	}
	
	if( In(175,350,275,380) ){	// ���沢�˳� 
		Inf[Tool_Ret5] = 1;
		if( button==1 && event==0){
			if( !Inf[Is_Rank] && !Inf[Is_Help] ){
				printf("���沢�˳�\n");
				Con_Save();
				Inf[Is_Tool] = 0; 
				Inf[Is_Menu] = 1;
				Inf[Is_Save] = Con_Is_Save();
				Inf[Is_Rank] = 0;
				Inf[Is_Help] = 0; 
			}
		}
	} else {
		Inf[Tool_Ret5] = 0;
	}
	
	if( In(180,370,255,400) ){	// ���а�Ͱ����ص� 
		printf("f����\n");
		Inf[Is_Back] = 1;
		if( button==1 && event==0 && Inf[Is_Help]==0){
			Inf[Is_Rank] = 0;
		}
		if( button==1 && event==0 && Inf[Is_Rank]==0){
			Inf[Is_Help] = 0;
		}
	}else{
		Inf[Is_Back] = 0;
	}
}

// ͼ���ݼ��ص����� 
static void HotMouseCtrl(int x, int y, int button, int event)
{
	if( In(275,510,335,540) ){ 	// ����ƶ������ͼ���� 
		if( button==1 && event==0){	// ������ 
			printf("������\n"); 
			if( Inf[In_Game] ){
				Inf[In_Game] = 0;
			}
			if( Inf[Is_Tool] == 0 ){
				Inf[Is_Tool] = 1;
			} else if(Inf[Is_Tool] == 1){
				Inf[Is_Tool] = 0;
				Inf[In_Game] = 1;
			}
		}
	}
	// ��ͬ
	if( In(335,510,375,545) ){	// ��ͣ 
		if( button==1 && event==0){
			printf("��ͣ\n");
				// ȷ���������ᷴ������ͣ�ͼ���֮��ת��
			if( Inf[In_Game] ){
				Inf[In_Game] = 0;
			} else {
				Inf[In_Game] = 1;
				Inf[Is_Tool] = 0;
			}
		}
	}
}

// �û������ص� 
static void NameMouseCtrl(int x, int y, int button, int event)
{
	if ( In(170,225,190,245) ) {	// �Ѷ����� 
		if ( !event && Level < 20 ) {
			Level++;
		}
	}
	if ( In(215,225,235,245) ) {	// �Ѷȼ��� 
		if ( !event && Level > 1 ) {
			Level--;
		}
	}
	if ( In(170,265,190,285) ) {	// ��ʼ��������
		if ( !event && S_Line < 10 ) {
			S_Line++;
		}
	}
	if ( In(215,265,235,285) ) {	// ��ʼ�������� 
		if ( !event && S_Line > 0 ) {
			S_Line--;
		}
	}
	if ( In(49, 315, 225, 413) ) {	// ��ʼ��Ϸ 
		Inf[Name_Ret] = 1;
		if( !event ){
			if( Name_cnt > 0 ) {
				Inf[Read_Name] = 0; // �����û����� 
				Init_Data();
				Name_cnt = 0;
			} else {
				Inf[Name_Remand] = 1;	
			} 
		} 
	} else {
		Inf[Name_Ret] = 0;
	} 
} 

//������ת 
static void Turn_Block(void)
{
	int Old_Block = Now_Block; 
	switch( Now_Block ) {	// �ı䷽�����༴��ʵ����ת 
		case 0 : Now_Block = 0;	break;
		case 1 : Now_Block++;	break;
		case 2 : Now_Block = 1;	break;
		case 3 : Now_Block++;	break;
		case 4 : Now_Block = 3;	break;
		case 5 : Now_Block++;	break;
		case 6 : Now_Block = 5;	break;
		case 7 : Now_Block++;	break;
		case 8 : Now_Block++;	break;
		case 9 : Now_Block++;	break;
		case 10: Now_Block = 7;	break;
		case 11: Now_Block++;	break;
		case 12: Now_Block++;	break;
		case 13: Now_Block++;	break;
		case 14: Now_Block = 11;	break;
		case 15: Now_Block++;	break;
		case 16: Now_Block++;	break;
		case 17: Now_Block++;	break;
		case 18: Now_Block = 15;	break;
	}
	//�ж���ת��ķ����Ƿ���������з����ص� 
	if ( Is_Touch() ) {
		//����ص��ͽ��������͸Ļ������൱�ڲ���ת 
		Now_Block = Old_Block;
	}
}

// �жϷ����Ƿ����Ϸ�����з����ص�
// ���߷����Ƿ��Ѿ�������Ϸ�߽� 
static int Is_Touch()
{
	int i,j;
	int ret = 0;
	for(i=0; i<SIZE; i++){
		for(j=0; j<SIZE; j++){
			if( Bck_block[Now_Block].a[i][j] ) { //�������ģ�͵ĸ�λ���з��� 
				if( Y+j < 0 || Y+j >= WIDTH ) {
					//���鳬�����ұ߽���߷�������������ص� 
					ret = 1;
					return ret;
				}
				//������黹�����棬�������ÿ���Խ�磬�����ж� 
				if ( X-SIZE+i+1 >= 0 && X-SIZE+i+1 < HEIGHT && Area[X-SIZE+1+i][Y+j] ){
					ret = 1;
					return ret;
				}//��ͱ߽��ж� 
				if ( X-SIZE+i+1 >= HEIGHT ){
					ret = 1;
					return ret;
				}
			}
		}
	}
	return ret; 
}

// ���� 
static void Left_Move(void)
{
	if(!Inf[Del_Gif]){
		Y--;
		if( Is_Touch() ) {
			Y++;
		}	
	}
} 

// ���� 
static void Right_Move(void)
{
	if(!Inf[Del_Gif]){
		Y++;
		if( Is_Touch() ) {
			Y--;
		}	
	}
} 

// �ո��亯�� 
static void Go_Button(void)
{
// ��Ϊ��غ���������Model��
// Ϊ����ģ������϶�
// ���˺�������������Model.c��ʵ�� 
	Go_Button_M();
}
