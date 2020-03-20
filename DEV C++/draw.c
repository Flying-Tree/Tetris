#include <stdio.h>
#include <time.h> 
#include "data.h"
#include "draw.h" 

static int i,j;									// forѭ�����������ں������ظ����� 
static int Areaa[HEIGHT][WIDTH];				// ��ͼ�������ݣ������ݿ��и��� 
// �߶������ר�ñ��� 
static double Pen_X, Pen_Y;						// ��¼����λ�� 
static int Agl; 								// ��¼��ǰ�Ƕ�

// ���˵����淽�� 
const static int drawdown[6][10]={
	{1,0,0,0,0,0,0,0,0,0},
	{1,0,0,0,0,0,0,0,0,5},
	{1,0,0,0,0,0,0,0,0,5},
	{1,2,0,0,0,0,0,0,5,5},
	{2,2,2,0,0,0,0,4,6,6},
	{3,3,3,3,0,4,4,4,6,6},
};

// ���˵��Ϸ� Tetris ���� 
static int tetris[5][22]={
	{1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,1,0,1,0,1,1,1},
	{0,1,0,0,1,0,0,0,0,1,0,0,1,0,0,1,0,1,0,1,0,0},
	{0,1,0,0,1,1,1,0,0,1,0,0,1,1,1,0,0,1,0,1,1,1},
	{0,1,0,0,1,0,0,0,0,1,0,0,1,0,1,0,0,1,0,0,0,1},
	{0,1,0,0,1,1,1,0,0,1,0,0,1,0,0,1,0,1,0,1,1,1},
};

void Draw(void){
	static int cnt;				// �������ü����� 
	DisplayClear();             // ���� 
	
	// �γ�������Ϸ����߿� 
	SetPenColor(Choose_Color(8));
	DrawPixel(5,5,446,545);
	DrawPixel(4,4,447,546);
	DrawPixel(3,3,448,547);
	
	if ( Inf[Is_Menu]==1 ) {
		MenuInterface();
		if( Inf[Is_Quit] ) {
			ExitGraphics();      // �˳���Ϸ 
		}
	} else {
		GameInterface();		// ��Ϸ������� 
		
		// ���������ж� 
		switch(Inf[Del_Gif]){
			case 0:{ // �޶��� 
				CreateNewMap();			// �γɷ������� 
				DrawNewMap();			// ������� 
				Delete_Row();
				break;
			}
			case 14:{ // �������� 
				Now_Timer = Level; 
				startTimer(Level, (21-Level)*40 );
				Inf[Del_Gif] = 0;
				break;
			}
			case 1:{ // ������ʼ 
				cancelTimer(Now_Timer);
				Inf[Del_Gif]++;
			}
			default:{ // �������� 
				Delete_Gif();
				Inf[Del_Gif]++;
				break;
			}
		}
		
		Show_Time();			// ʱ��չʾ 
		
		// ͨ��Cnt���ƶ�ʱ������� 
		cnt++; 
		if ( Inf[Is_Tool] ){ 	// �ڹ����� 
			ToolInterface(); 
		}
		if ( Inf[In_Game] ) {	// ��Ϸ���ڽ��� 
			DrawStart();
		} else {
			if(Inf[Is_Rank]){	// ��ʾ���а� 
				DrawRank();
			} else if(Inf[Is_Help]){	// ��ʾ���� 
				DrawHelp();
			}
			if( !Inf[Read_Name] ){		// �Ƕ������ֽ������ͣ���� 
				if ( cnt<20 ){
					
				} else if(cnt < 40){
					DrawPause(); 
				} else {
					cnt = 0;
				}
			} else {
				DrawPause();
			}
		}
	}
	Interact_Window();		// �û���������
}

// �������ص㻭�߿� 
static void DrawPixel(int x1, int y1, int x2, int y2)
{
	double xx1, yy1, xx2, yy2;
	xx1=ScaleXInches(x1);     // �����ص�ת��ΪӢ�絥λ 
	yy1=ScaleYInches(y1);
	xx2=ScaleXInches(x2);
	yy2=ScaleYInches(y2);
	
	MovePen(xx1,yy1);
	DrawLine(0,yy2-yy1);
	DrawLine(xx2-xx1,0);
	DrawLine(0,yy1-yy2);
	DrawLine(xx1-xx2,0);
}

// �������߶� 
static void DrawPixelLine(int x1, int y1, int x2, int y2){
	double xx1, yy1, xx2, yy2;
	xx1=ScaleXInches(x1);
	yy1=ScaleYInches(y1);
	xx2=ScaleXInches(x2);
	yy2=ScaleYInches(y2);
	
	DrawLine(xx2-xx1,yy2-yy1);
}

// Ϳɫ 
static string Choose_Color(int x){
	char *color;
	switch(x){
		case 1: color= "red"; break;
		case 2: color= "Orange"; break;
		case 3: color= "yellow"; break;
		case 4: color= "green"; break;
		case 5: color= "Cyan"; break;
		case 6: color= "blue"; break;
		case 7: color= "Magenta"; break;
		
		// �Զ�����һЩ��ɫ���ڿ����Ѿ��޸� 
		case 8: color= "Tomato"; break;
		case 9: color= "Goldenrod1"; break;
		case 10: color= "Moccasin"; break;
		case 11: color= "Khaki1"; break;
		default: color= "black"; break;
	}
	return color;
}

// �ض���������� 
static void ClearScreen(int x1, int y1, int x2, int y2){
	StartFilledRegion(0.01);
	DrawPixel(x1,y1,x2,y2);
	EndFilledRegion();
}
 
// �γ����˵�����
static void MenuInterface(void){
	
	DrawTet();				// ���Ʊ���ͼƬ  
	
	// �˵����ܵ�ѡ�� 
	if(Inf[Is_Rank]==0&&Inf[Is_Help]==0){
		DrawMenuChoice();
	} else if(Inf[Is_Help]){
		DrawHelp();
	} else if (Inf[Is_Rank]){
		DrawRank();
	} 
} 

// �����˵� 
static void DrawMenuChoice(void)
{
	SetPenColor(Choose_Color(8));
	
	DrawPixel(80,160,370,405);
	DrawPixel(175,190,275,220);		// ��ʼ��Ϸ 
	DrawPixel(175,230,275,260);		// ��Ϸ���� 
	DrawPixel(175,270,275,300);		// ���а� 
	DrawPixel(175,310,275,340);		// ����
	DrawPixel(175,350,275,380);     // �˳���Ϸ 
	
	// ��ʾ���幦�� 
	ShowStr(184, 210, "��ʼ��Ϸ [S]");
	ShowStr(184, 250, "����浵 [C]");
	ShowStr(192, 290, "���а� [R]");
	ShowStr(200, 330, "���� [H]");
	ShowStr(184, 370, "�˳���Ϸ [Q]");
} 

// �������û������� 
static void NameFace(void){
	SetPenColor(Choose_Color(2));
	
	DrawPixel(6,120,274,440);
	ShowStr(30,144,"�����û��� (������ĸ ֱ�Ӱ���)");
	DrawPixel(68,160,220,190);
	ShowStr(73,180,Con_Name);
	
	// ��ʾ�趨�Ѷȹ���ѡ�� 
	ShowStr(40,240,"�趨�Ѷ� [����]");
	SetPenSize(3);
	DrawPixel(175,235,185,235);  // ������ 
	DrawPixel(180,230,180,240);
	DrawPixel(219,235,229,235);  // ������ 
	SetPenSize(1);
	DrawPixel(170,225,234,245);  // ��� 
	DrawPixel(190,225,214,245);	 // С�� 
	ShowStr(195,240,IntegerToString(Level));
	
	// ��ʾ�趨��ʼ����ѡ�� 
	ShowStr(40,280,"��ʼ���� [����]");
	SetPenSize(3);
	DrawPixel(175,275,185,275);  // ������ 
	DrawPixel(180,270,180,280);
	DrawPixel(219,275,229,275);  // ������ 
	SetPenSize(1);
	DrawPixel(170,265,234,285);  // ��� 
	DrawPixel(190,265,214,285);	 // С�� 
	ShowStr(195,280,IntegerToString(S_Line));
	
	Draw_Go();
}

// ����GO��ʽ 
static void Draw_Go(void)
{
	int go[5][9]={
		{1,2,3,4,0,6,7,1,2},
		{2,0,0,0,0,7,0,0,3},
		{3,0,5,6,0,1,0,0,4},
		{4,0,0,7,0,2,0,0,5},
		{5,6,7,1,0,3,4,5,6},
	};
	
	int i,j;
	
	// ����������з���Ϳɫ 
	for(i=0;i<5;i++){
		for(j=0;j<9;j++){
			if(go[i][j]){
				if( Inf[Name_Ret] ){
					SetPenColor(Choose_Color(go[i][j]));
				} else {
					SetPenColor(Choose_Color(12));
				}
				StartFilledRegion(0.9);
				DrawPixel(50+j*20,315+i*20,50+j*20+16,315+i*20+16);
				EndFilledRegion();
			}
		} 
	}
	
	// δ�����û�����ʾ��ʾ 
	if (Inf[Name_Remand] ){
		SetPenColor("red");
		ShowStr(96, 210, "�������û���"); 
	}
} 

// �����а�
static void DrawRank(void){
	SetPenSize(1);
	SetPenColor(Choose_Color(8));
	ClearScreen(80,160,370,405); 
	DrawPixel(80,160,370,405);
	ShowStr(170,190,"���а�(ֻȡǰ5��)");
	ShowStr(100,220,"����");
	ShowStr(200,220,"���");
	ShowStr(300,220,"�÷�");
	
	// ��ʾ���а� 
	int i;
	Con* tem = NULL;
	tem=Head;
	for(i=0;i<5;i++){
		if(tem){
			ShowStr(110,240+i*25,IntegerToString(tem->num));
			ShowStr(190,240+i*25,tem->name);
			ShowStr(300,240+i*25,IntegerToString(tem->score));
			tem=tem->next;
		} 
	}
	
	DrawPixel(180,370,255,400);
	ShowStr(190,390,"���� [B]");
} 

// �������˵� 
static void DrawHelp(void){
	SetPenSize(1);
	SetPenColor(Choose_Color(8));
	ClearScreen(80,160,370,405);
	DrawPixel(80,160,370,405);
	
	// ��ʾ����������� 
	ShowStr(207,185,"����");
	ShowStr(127,205,"���鿪����д����������Ϸ");
	ShowStr(104,225,"��Ϸ֧��������Լ���ݼ�����");
	ShowStr(167,255,"��Ϸ�����ݼ�");
	ShowStr(125,275,"���Ҽ����ƶ�����");
	ShowStr(125,295,"�ϼ�����ת����");
	ShowStr(125,315,"�¼������ٷ�������");
	ShowStr(125,335,"�ո�������������ײ�");
	ShowStr(125,355,"P����ͣ��Ϸ      T ��������");
	
	DrawPixel(180,370,255,400);
	ShowStr(190,390,"���� [B]");
}

// �γ���Ϸ���� 
static void GameInterface(void)
{
	int i, j;
	if (Inf[Read_Name]==1) {
		NameFace();
	} else {
		SetPenColor(Choose_Color(10));
		StartFilledRegion(0.2);
		DrawPixel(6,6,445,544);
		EndFilledRegion();	
		
		// ��䱳���뻮�� 
		for(i=0;i<19;i++){
			DrawPixel(5,5+i*27+27,446,5+i*27+27);
		}
		
		for(i=0;i<9;i++){
			DrawPixel(5+i*27+27,5,5+i*27+27,545);
		}

		SetPenColor(Choose_Color(11));
		StartFilledRegion(0.4);
		DrawPixel(276,6,445,544);
		EndFilledRegion();	
	}
	
	// �γ���Ϸ�߿� 
	SetPenColor(Choose_Color(8));
	DrawPixel(275,5,275,545);
	DrawPixel(275,175,446,175);
	DrawPixel(275,290,446,290);
	DrawPixel(275,400,446,400);
	DrawPixel(275,510,446,510);
	DrawPixel(335,510,335,545);
	DrawPixel(375,510,375,545);
	
	SetPenColor(Choose_Color(8));
	// ��ʾ�Ҳ����
	ShowStr(280, 25, "��һ������");
	// ��ʾ��������������
	ShowStr(280, 195, "����������");
	// ��ʾ�÷ֽ���
	ShowStr(280, 310, "��ǰ�÷�");
	// ��ʾ��ǰ�Ѷȵȼ�
	ShowStr(280, 420, "��ǰ�Ѷȵȼ�");
	// ��ʾ������
	ShowStr(280, 533, "���� [T]");
	
	DrawPixel(310,68-25,385+25,145+25-25);
	DrawPixel(310+25,68-25,385+25,145+25-25);
	DrawPixel(335+25,68-25,385+25,145+25-25);
	DrawPixel(360+25,68-25,385+25,145+25-25);
	
	DrawPixel(310,68-25,385+25,70+25-25);
	DrawPixel(310,70+25-25,385+25,95+25-25);
	DrawPixel(310,95+25-25,385+25,120+25-25);
	DrawPixel(310,120+25-25,385+25,145+25-25);
	  
	// ��ʾ Level��G_Score��C_Line 
	int size = 15;
	int Pen_Size = 2;
	int Space = 2; 
	Draw_Nub(410, 240, C_Line, size, Space, Pen_Size);
	Draw_Nub(410, 350, G_Score, size, Space, Pen_Size);
	Draw_Nub(410, 460, Level, size, Space, Pen_Size); 
}

// �γ��µ����� 
static void CreateNewMap(void)
{
	// ˢ��������
	for(i=0; i<HEIGHT; i++)
       for(j=0; j<WIDTH; j++)
   	       Areaa[i][j] = Area[i][j];
	
	// ��¼�������䷽�� 
	for(i=0; i<SIZE; i++){
		for(j=0; j<SIZE; j++){
			if ( Bck_block[Now_Block].a[i][j] && (X-SIZE+1+i) >= 0 ) {
				Areaa[X-SIZE+1+i][Y+j] = Now_Color;
			}
		} 
    }
}

// ���������� 
static void DrawNewMap(void)
{
	int xxx1, yyy1, xxx2, yyy2;
	
	// �����ڵ���ķ��� 
	for(i=0;i<HEIGHT;i++){
		for(j=0;j<WIDTH;j++){
			if( Areaa[i][j] ){
				SetPenColor(Choose_Color(Areaa[i][j]));
				StartFilledRegion(0.9);
				xxx1=7+j*27;
				yyy1=7+i*27;
				xxx2=7+j*27+23;
				yyy2=7+i*27+23;
				DrawPixel(xxx1,yyy1,xxx2,yyy2);
				EndFilledRegion();
			}
		}
   }
	
    // ����һ������ 
	SetPenColor(Choose_Color(Next_Color));
	for(i=0;i<SIZE;i++){
		for(j=0;j<SIZE;j++){
			if(Bck_block[Next_Block].a[i][j]){
				StartFilledRegion(0.9);
				DrawPixel(312+j*25,72+i*25-25,312+j*25+21,72+i*25+21-25);
				EndFilledRegion();
			}
		} 
	}
}

// �γɹ���������
static void ToolInterface(void)
{
	SetPenColor(Choose_Color(8));
	ClearScreen(80,160,370,405);
	
	DrawPixel(175,190,275,220);		
	DrawPixel(175,230,275,260);		
	DrawPixel(175,270,275,300);		 
	DrawPixel(175,310,275,340);	
	DrawPixel(175,350,275,380);	
	
	ShowStr(192, 210, "����Ϸ [N]");
	ShowStr(184, 250, "������Ϸ [C]");
	ShowStr(192, 290, "���а� [R]");
	ShowStr(200, 330, "���� [H]");
	ShowStr(175, 370, "���沢�˳� [B]");
} 

// ��(x,y)����ʾ�ַ���str 
static void ShowStr(int x, int y, char *str)
{
	MovePen(ScaleXInches(x),ScaleYInches(y));
	DrawTextString(str);
}

// ��Ӧ�˵����Ľ���
static void Interact_Window(void)  
{
	// ���а�Ͱ����ķ��ؿ�ͼ 
	if ( Inf[Is_Rank] || Inf[Is_Help] ){
		
		// ���������а�ķ��ء�B�����û��������� 
		if ( Inf[Is_Back] ){		
			printf("In Interact  Is_Rank\n");
			DrawPixel(177,367,258,403);
		}
	} else if ( Inf[Is_Menu] ){ // ����ڲ˵����� 
		if ( Inf[Menu_Ret1] ) {
			DrawPixel(172,187,278,223);
		}
		if ( Inf[Menu_Ret2] ) {
			DrawPixel(172,227,278,263);
		}
		if ( Inf[Menu_Ret3] ) {
			DrawPixel(172,267,278,303);
		}
		if ( Inf[Menu_Ret4] ) {
			DrawPixel(172,307,278,343);
		}	
		if ( Inf[Menu_Ret5] ) {
			DrawPixel(172,347,278,383);
		}	
	} 
	else { // ��Ϸ���� 
		if ( Inf[Is_Tool] ) {
			// �������û����� 
			if ( Inf[Tool_Ret1] ) {
				DrawPixel(172,187,278,223);
			}
			if ( Inf[Tool_Ret2] ) {
				DrawPixel(172,227,278,263);
			}
			if ( Inf[Tool_Ret3] ) {
				DrawPixel(172,267,278,303);
			}
			if ( Inf[Tool_Ret4] ) {
				DrawPixel(172,307,278,343);
			}
			if ( Inf[Tool_Ret5] ) {
				DrawPixel(172,347,278,383);
			}		
		}  
	} 
}

// nubΪ�������֣� len Ϊ���ִ�С��������Ϊ��λ 
static void Draw_Nub(int x, int y, int nub, int len, int space, int size)
{
	SetPenColor(Choose_Color(8));
	Pen_X = x/GetXResolution();
	Pen_Y = (GetWindowHeight()*GetYResolution()-y)/GetYResolution();
	
	int Sgl_Nub;	// �������� 
	int o_pensize = GetPenSize();	// ��¼֮ǰ���ʿ�� 
	SetPenSize(size);			// �����µĻ��ʿ�� 
	if(nub){						// ���������֣��������� 
		while(nub){
			Sgl_Nub = nub % 10;
			nub /= 10;
			SignalDigitalNub(len, Sgl_Nub, space);
			Pen_X -= ScaleXInches(2*len+7*space);
		}
	} else {
		SignalDigitalNub(len, 0, space);		 
	}
	SetPenSize(o_pensize);			// �����ʿ���޸Ļ��� 
}

// ������������ 
static void SignalDigitalNub(int len, int nub, int space)
{
	SetPenColor(Choose_Color(8));
	int i, ret[7];
	
	switch (nub) {		// 0-9���ֶ�Ӧ��������� 
		case 0:ret[0]=0;ret[1]=1;ret[2]=1;ret[3]=1;ret[4]=1;ret[5]=1;ret[6]=1;break;  
		case 1:ret[0]=0;ret[1]=1;ret[2]=0;ret[3]=0;ret[4]=0;ret[5]=0;ret[6]=1;break;
		case 2:ret[0]=1;ret[1]=0;ret[2]=1;ret[3]=1;ret[4]=0;ret[5]=1;ret[6]=1;break;
		case 3:ret[0]=1;ret[1]=1;ret[2]=1;ret[3]=0;ret[4]=0;ret[5]=1;ret[6]=1;break;
		case 4:ret[0]=1;ret[1]=1;ret[2]=0;ret[3]=0;ret[4]=1;ret[5]=0;ret[6]=1;break;
		case 5:ret[0]=1;ret[1]=1;ret[2]=1;ret[3]=0;ret[4]=1;ret[5]=1;ret[6]=0;break;
		case 6:ret[0]=1;ret[1]=1;ret[2]=1;ret[3]=1;ret[4]=1;ret[5]=1;ret[6]=0;break;
		case 7:ret[0]=0;ret[1]=1;ret[2]=0;ret[3]=0;ret[4]=0;ret[5]=1;ret[6]=1;break;
		case 8:ret[0]=1;ret[1]=1;ret[2]=1;ret[3]=1;ret[4]=1;ret[5]=1;ret[6]=1;break;
		case 9:ret[0]=1;ret[1]=1;ret[2]=1;ret[3]=0;ret[4]=1;ret[5]=1;ret[6]=1;break;	
	}
	// ������ܵ����ʻ� 
	for(i=0; i<4; i++){		
		Draw_Space(space);		// ��ʼ�ո� 
		Draw_Line(len, ret[i]);	// ���� 
		Draw_Space(space);		// �����ո� 
		Agl += 90;				// ����ת�� 
	}
	Agl-= 90;
	for(i=4; i<7; i++){
		Draw_Space(space);
		Draw_Line(len, ret[i]);
		Draw_Space(space);
		Agl += 90;
	}
	Agl -= 180; 
}

// �������ּ��϶ 
static void Draw_Space(int len)
{
	double Len_X = ScaleXInches(len);
	double Len_Y = GetWindowHeight() - ScaleYInches(len);
	switch ( Agl % 360 ) {
		case 0: 	Pen_X += Len_X; break;
		case 90:	Pen_Y -= Len_Y; break;
		case 180:	Pen_X -= Len_X; break;
		case 270:	Pen_Y += Len_Y; break;
	}
} 

// ������һ���ߣ������黭 
static void Draw_Line(int len, int ret)
{
	SetPenColor(Choose_Color(8));
	double Len_X = ScaleXInches(len);
	double Len_Y = GetWindowHeight() - ScaleYInches(len); 
	MovePen(Pen_X,Pen_Y);
	// ��Ӧ��ͬ�Ƕȣ����ʳ��ȿ�ȿ��ܲ�ͬ 
	switch ( Agl % 360 ) {
		case 0:
			if(ret){
				DrawLine(Len_X, 0);
			} 
			Pen_X += Len_X;
			break;
		case 90:
			if(ret){
				DrawLine(0, -Len_Y); 
			} 
			Pen_Y -= Len_Y;
			break;
		case 180:
			if(ret){
				DrawLine(-Len_X, 0);
			}
			Pen_X -= Len_X;
			break;
		case 270:
			if(ret){
				DrawLine(0, Len_Y);
			}
			Pen_Y += Len_Y;
			break;
	}
}

// ��õ�ǰϵͳʱ�䣬��ָ����ʽ���� 
static void GetTime(int *hour, int *min, int *sec)
{
	time_t timep;
	struct tm *p;
	time(&timep);
	p = localtime(&timep);
	*hour = p->tm_hour;
	*min = p->tm_min;
	*sec = p->tm_sec;
} 

// ��Ϸ����ʱ����ʾ 
static void Show_Time(void)
{
	int hour, min, sec;
	string o_color = GetPenColor();
	GetTime(&hour, &min, &sec);
	if(hour<10){
		Draw_Nub(380,528,0,6,2,3);
	} 
	Draw_Nub(395,528,hour,6,2,3);
	if(min<10){
		Draw_Nub(415,528,0,6,2,3);
	}
	Draw_Nub(430,528,min, 6,2,3); 
	if(sec%2){
		Draw_Point(410,523,4);
		Draw_Point(410,533,4);
	}
	SetPenColor(o_color);
}

// ���Ƶ㣨ʱ����ʾר�ã�
static void Draw_Point( int x, int y, int size)
{
	double X = ScaleXInches(x);
	double Y = ScaleYInches(y);
	int o_size = GetPenSize();
	SetPenColor(Choose_Color(8));
	SetPenSize(size);
	MovePen(X,Y);
	DrawLine(0.0001,0.0001);
	SetPenSize(o_size);
}

// ����ͣ��ť 
static void DrawPause(void){
	SetPenColor(Choose_Color(8));
	StartFilledRegion(0.9);
	MovePen(ScaleXInches(345),ScaleYInches(518));
	DrawPixelLine(365,515,385,525);
	DrawPixelLine(385,525,365,535);
	DrawPixelLine(365,535,365,515);
	EndFilledRegion();
}

// ����ʼ��ť
static void DrawStart(void){
	SetPenColor(Choose_Color(8));
	StartFilledRegion(0.9);
	DrawPixel(345,518,350,538);
	EndFilledRegion();
	StartFilledRegion(0.9);
	DrawPixel(360,518,365,538);
	EndFilledRegion();
} 

// ���˵�ͼ���������� 
static void DrawTet(void)
{
	static int cnt;
	int i,j;
	
	// ͼ���ĸ�ֵ 
	for(i=0;i<5;i++){
		for(j=0;j<22;j++){
			if(tetris[i][j]){
				if( !(cnt%10) ){
					tetris[i][j] = rand()%7+1;
				}
				SetPenColor(Choose_Color(tetris[i][j]));
				StartFilledRegion(0.9);
				DrawPixel(20+j*19,20+i*19,20+j*19+17,20+i*19+17);
				EndFilledRegion();
			}
		} 
	}
	
	// ����ͼ��	
	for(i=0;i<6;i++){
		for(j=0;j<10;j++){
			if(drawdown[i][j]){
				SetPenColor(Choose_Color(drawdown[i][j]));
				StartFilledRegion(0.9);
				DrawPixel(20+j*42,290+i*42,20+j*42+39,290+i*42+39);
				EndFilledRegion();
			}
		} 
	}
	cnt++;
}

// �������� 
static void Delete_Gif(void)
{
	DisplayClear();
	DrawPixel(5,5,446,545);
	DrawPixel(4,4,447,546);
	DrawPixel(3,3,448,547);
	GameInterface();
	Show_Time();
	
	for(i=0; i<HEIGHT; i++){
		if( Del_Line[i] ){
			Areaa[i][Inf[Del_Gif]-2] = 0; 
		}
	}
	DrawNewMap();
}
