#include "data.h"
#include "model.h"
#include "ctrl.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// M ��ָ�� Model �еĺ��� ����Ctrl�еĺ������ֿ� 
void Go_Button_M(void)
{
	while ( !Fall_Block() );
	Timer_Model();
	if ( Is_End_Game() ){ 
		End_Game();
	} else {
		Creat_Block();
	}
}

// ���̺��� 
void Model_Flow(void)
{
	if ( Inf[In_Game] ) {
		if ( Fall_Block() ) {
			Timer_Model();
			if ( Is_End_Game() ){
				End_Game();
			} else {
				Creat_Block();
			}
		}
	} 
}
 
// �������һ���µķ��飬������� 0-18����ɫ����Ϊ 1-7 
static void Creat_Block(void)
{
	srand(time(NULL));
	Now_Block = Next_Block;
	Next_Block = rand()%BLOCK_TYPE;
	Now_Color = Next_Color;
	Next_Color = ( (Next_Color+1)%7 ) ? (Next_Color+1)%7 : 7; 
	// �����ʼ���� 
	X = 0;
	Y = WIDTH/2-2; 
}

//���䣬����ֹͣ 
static int Fall_Block(void)
{
	int ret = 0; 
	if ( Is_Touch() ){
		Change_Score(0); 
		Fixed_Block();
		ret = 1; 
	} else {
		X++;
	} 
	return ret;
}

// ��������Ϣд�� Area�����У� ʵ���ƶ�������̶������ת�� 
static void Fixed_Block(void)
{
	int i,j;
	for(i=0; i<SIZE; i++){
		for(j=0; j<SIZE; j++){
			if ( Bck_block[Now_Block].a[i][j] ) {
				Area[X-SIZE+1+i][Y+j] = Now_Color;
			}
		}
	}
}

//�жϷ����Ƿ񵽵� 
static int Is_Touch(void)
{
	int i, j;
	int ret = 0;
	for(j=0; j<SIZE; j++){
		for(i=SIZE-1; i>=0; i--){
			if( Bck_block[Now_Block].a[i][j] ){ // �Է���ģ�����ݵ����� 
				if( X-SIZE+1+i+1 >=0 ){//��֤�������ò�Խ�� 
					if( (X-SIZE+1+i+1)==(HEIGHT) || Area[X-SIZE+1+i+1][Y+j] ){
						// �����ǰ�����»��з�������Ѿ������߽� 
						ret = 1;
						return ret; 
					} else {
						break;
					}
				}
			}
		}
	}
	return ret;
}

static int Is_End_Game(void)
{
	int ret = 0,i;
	//��Ϸ����������һ������ 
	for(i=0; i<WIDTH; i++){
		if ( Area[0][i] ) {  // ����������з��鼴������Ϸ 
			ret = 1;
			break;
		}
	}
	return ret;
} 

// �ж��Ƿ����У�����ɾ����ͬʱ�޸�Inf[Del_Gif]����ʾ���� 
void Delete_Row(void)
{
	int cnt = 0, ret, i, j, k;
	for ( i=0; i<HEIGHT; i++ ) {
		ret = 1;
		Del_Line[i] = 0; 
		for ( j=0; j<WIDTH; j++ ) {
			if ( !Area[i][j] ) {
				ret = 0;
				break;
			}
		}
		if ( ret ) {
			Del_Line[i] = 1;	// ��¼��Ҫ�������� 
			Move_Area(i);		// ��Ϸ������������ 
			C_Line++;			// �������м�һ 
			cnt++;
		}
	}
	if ( cnt ) {
		Change_Score(cnt);		// �޸ķ��� 
		Inf[Del_Gif] = 1;		// ���ƶ��� 
	}
} 

// ����Ϸ�� 0 ~ (row-1) ����������ƽ��һ�� 
static void Move_Area(int row)
{
	int i,j;
	for(i=row-1; i>=0; i--){
		for(j=0; j<WIDTH; j++){
			Area[i+1][j] = Area[i][j];
		}
	}
}

// �ı���� 
static void Change_Score(int ret)
{
	switch(ret){
		case 0:G_Score +=   7 + Level *  3 + S_Line;	break;	// ���䷽�� 
		case 1:G_Score +=  90 + Level * 10 + S_Line;	break;	// ����һ�� 
		case 2:G_Score += 280 + Level * 20 + S_Line;	break;	// �������� 
		case 3:G_Score += 570 + Level * 30 + S_Line;	break;	// �������� 
		case 4:G_Score += 960 + Level * 40 + S_Line;	break;	// �������� 
	}
} 

// �޸�Timer�� ������Ϸ�Ѷ� 
static void Timer_Model(void)
{
	static int ret = 0; 
	if( (C_Line-2)/6 != ret ){
		ret++;
		if(ret > (C_Line-2)/6 ){
			ret = (C_Line-2)/6;
		} 	
		if(Level != 20){
			Level++;
		}
	}
	
	if(Now_Timer != Level){ 
		cancelTimer(Now_Timer);
		startTimer(Level, (21-Level)*40);
		Now_Timer = Level;
	}
}

// ������Ϸ�ж� 
static void End_Game(void)
{
	printf("��Ϸ������\n"); 
	cancelTimer(Now_Timer);
	// �������а����� 
	Head = Con_Input( Head, Con_Create() );
	Num++;
	// ���а��������� 
	Con_Sort(Head); 
	// �������
	Con_Fileprint(Head, Num); 
	printf("Num = %d", Num);
	// �ٴγ�ʼ����Ϸ 
//	Init_Game(); 
	Inf[In_Game] = 0;
	Inf[Is_Gif]  = 1;
} 

// �������� �������ͼ�̶����飬�������������䷽�� 
static void Print_Area(void)
{
	int i, j;
	for(i=0; i<HEIGHT; i++){
		for(j=0; j<WIDTH; j++){
			printf("%3d ",Area[i][j]); 
		}
		printf("\n");
	}
	printf("\n");
} 
