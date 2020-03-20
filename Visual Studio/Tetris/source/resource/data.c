#include "data.h"
#include <stdio.h>
#include <string.h> 
#include <stdlib.h>
 
//��������ģ�ͣ������½�Ϊ�ף�һ��ʮ���ַ��� 
const Block Bck_block[BLOCK_TYPE] = {
	{	  // ���� 00 
	  {	{ 0, 0, 0, 0 },
		{ 0, 1, 1, 0 },
		{ 0, 1, 1, 0 },
		{ 0, 0, 0, 0 }, } 
	} , { // ���� 01 
	  {	{ 0, 1, 0, 0 },
		{ 0, 1, 0, 0 },
		{ 0, 1, 0, 0 },
		{ 0, 1, 0, 0 }, } 
	} , { // ���� 02 
	  {	{ 0, 0, 0, 0 },
		{ 1, 1, 1, 1 },
		{ 0, 0, 0, 0 },
		{ 0, 0, 0, 0 }, } 
	} , { // �� Z 03 
	  {	{ 0, 0, 0, 0 },
		{ 0, 0, 0, 0 },
		{ 1, 1, 0, 0 },
		{ 0, 1, 1, 0 }, } 
	} , { // �� Z 04
	  {	{ 0, 0, 0, 0 },
		{ 0, 0, 1, 0 },
		{ 0, 1, 1, 0 },
		{ 0, 1, 0, 0 }, } 
	} , { // �� Z 05 
	  {	{ 0, 0, 0, 0 },
		{ 0, 0, 0, 0 },
		{ 0, 0, 1, 1 },
		{ 0, 1, 1, 0 }, } 
	} , { // �� Z 06
	  {	{ 0, 0, 0, 0 },
		{ 0, 1, 0, 0 },
		{ 0, 1, 1, 0 },
		{ 0, 0, 1, 0 }, } 
	} , { // �� L 07
	  {	{ 0, 0, 0, 0 },
		{ 0, 1, 0, 0 },
		{ 0, 1, 0, 0 },
		{ 0, 1, 1, 0 }, } 
	} , { // �� L 08
	  {	{ 0, 0, 0, 0 },
		{ 0, 0, 0, 0 },
		{ 1, 1, 1, 0 },
		{ 1, 0, 0, 0 }, } 
	} , { // �� L 09
	  {	{ 0, 0, 0, 0 },
		{ 1, 1, 0, 0 },
		{ 0, 1, 0, 0 },
		{ 0, 1, 0, 0 }, } 
	} , { // �� L 10
	  {	{ 0, 0, 0, 0 },
		{ 0, 0, 1, 0 },
		{ 1, 1, 1, 0 },
		{ 0, 0, 0, 0 }, } 
	} , { // �� L 11
	  {	{ 0, 0, 0, 0 },
		{ 0, 1, 0, 0 },
		{ 0, 1, 0, 0 },
		{ 1, 1, 0, 0 }, } 
	} , { // �� L 12
	  {	{ 0, 0, 0, 0 },
		{ 1, 0, 0, 0 },
		{ 1, 1, 1, 0 },
		{ 0, 0, 0, 0 }, } 
	} , { // �� L 13
	  {	{ 0, 0, 0, 0 },
		{ 0, 1, 1, 0 },
		{ 0, 1, 0, 0 },
		{ 0, 1, 0, 0 }, } 
	} , { // �� L 14
	  {	{ 0, 0, 0, 0 },
		{ 0, 0, 0, 0 },
		{ 1, 1, 1, 0 },
		{ 0, 0, 1, 0 }, } 
	} , { // T �� 15
	  {	{ 0, 0, 0, 0 },
		{ 0, 1, 0, 0 },
		{ 1, 1, 1, 0 },
		{ 0, 0, 0, 0 }, } 
	} , { // T �� 16
	  {	{ 0, 0, 0, 0 },
		{ 0, 1, 0, 0 },
		{ 0, 1, 1, 0 },
		{ 0, 1, 0, 0 }, } 
	} , { // T �� 17
	  {	{ 0, 0, 0, 0 },
		{ 0, 0, 0, 0 },
		{ 1, 1, 1, 0 },
		{ 0, 1, 0, 0 }, } 
	} , { // T �� 18
	  {	{ 0, 0, 0, 0 },
		{ 0, 1, 0, 0 }, 
		{ 1, 1, 0, 0 },
		{ 0, 1, 0, 0 }, } 
	},
};

// ȫ�ֱ��� 
int Now_Timer;				// ��¼��ǰ��ϷTimer
int Area[HEIGHT][WIDTH];	// ��Ϸ�� 
int X, Y;					// ��������ķ���λ������ 
int Next_Block;				// ��һ���������� 
int Next_Color;				// ��һ��������ɫ 
int Now_Block;				// ��ǰ�������� 
int Now_Color;				// ��ǰ������ɫ 
int S_Line;					// ��ʼ����	 
int G_Score;				// �÷� 
int Level;					// �Ѷȵȼ� 
int C_Line; 				// �������� 
int Del_Line[HEIGHT];		// ��ǰ�����������У�����Ϸ�������¼��� 
int Num;					// ���а����� 
char Con_Name[NUB];			// ��ǰ��Ϸ�û��� 
Con* Head = NULL;			// ��ǰ��Ϸ���а��û�ͷָ�� 

// �ۺ��źű�������ʹ�÷������data.h�ļ��궨�岿�� 
int Inf[NUMBER];

// �û���ʵ�ֺ��� 

//�½� ������ÿһ����Ϸ����ʱ����ȫ�ֱ��������½ڵ� 
Con* Con_Create(void)
{
	Con *p;
	p = (Con*)malloc( sizeof (Con) );			
	p->num = 0; 
	p->score = G_Score;
	strcpy(p->name, Con_Name);
	p->level = Level;
	p->c_line = C_Line;
	p->next = NULL;		
	return p;
}


//�������û��������а� 
Con* Con_Input(Con *head, Con *consumer)
{
	Con *ptr, *ptr1, *ptr2;
	
	ptr2 = head;			 
	ptr  = consumer;			//ptrָ���������µ�ѧ����¼��� 
	//ԭ����Ϊ�յĲ��� 
	if (head == NULL){
		head = ptr;				//�²���Ľ���Ϊͷ��� 
		head->next = NULL;	
	} 
	//ԭ����Ϊ�յĲ��� 
	else {
		while( (ptr->num > ptr2->num) && (ptr2->next != NULL) ){
			//ptr1��ptr2������һ����� 
			ptr1 = ptr2;
			ptr2 = ptr2->next;
		}
		if ( ptr->num <= ptr2->num ) {
			if ( head == ptr2 )  head = ptr;
			else   ptr1->next = ptr;
			ptr->next = ptr2;
		} else {				//�²���Ľ���Ϊβ��� 
			ptr2->next = ptr;
			ptr->next  = NULL;
		}
	}
	return head;
}

//�����������������Ϣ�������ã� 
void Con_Print ( Con *head )
{
	Con *ptr;
	if ( head == NULL ) {
		printf("No records found\n");
	} else {
		printf("����\t�û���\t�÷�\t�Ѷ�\t��������\n");
		for( ptr = head; ptr != NULL; ptr = ptr->next){
			printf("%d\t%s\t%d\t%d\t%d\n", ptr->num, ptr->name, ptr->score, ptr->level, ptr->c_line);
		}	
	}
}

//�����а��������� 
void Con_Sort(Con *head)
{
    Con *ptr1, *ptr2;
    int temp;
    char exname[NUB];
	for (ptr1 = head; ptr1 != NULL; ptr1 = ptr1->next){
		for (ptr2 = ptr1; ptr2 != NULL; ptr2 = ptr2->next){
			//��λ�ں���Ľ���score�ϴ�ʱ����������ǰһ������num�������ֵ 
			if (ptr1->score < ptr2->score){
				temp = ptr1->score;
				ptr1->score = ptr2->score;
				ptr2->score = temp;
				temp = ptr1->c_line;
				ptr1->c_line = ptr2->c_line;
				ptr2->c_line = temp;
				
				temp = ptr1->level;
				ptr1->level = ptr2->level;
				ptr2->level = temp;
				
				strcpy(exname, ptr1->name);
				strcpy(ptr1->name, ptr2->name);
				strcpy(ptr2->name, exname);
			}
		}
	}
	// �ٴα�������д�������
	int cnt = 1;
	for (ptr1 = head; ptr1 != NULL; ptr1 = ptr1->next){
		ptr1->num = cnt++;
	}
}

//�������а��ļ����γ�����ṹ 
Con* Con_Fileopen(void){
	Con *head = NULL, *p;
	int num, score, level, c_line;
	char name[NUB];
	int i;
	int size = sizeof (Con);
	FILE *fp = fopen ("Rank.txt","r");
	
	if (fp==NULL){
		printf("No File!\n");
		return NULL; 
	} else {
		fscanf(fp,"%d",&Num);
		for (i=0; i<Num; i++){
			fscanf(fp,"%d%s%d%d%d", &num, name, &score, &level, &c_line);
			p = (Con*)malloc(size);			
			p->num = num; 
			p->score = score;
			strcpy(p->name, name);
			p->level = level;
			p->c_line = c_line;
			head = Con_Input(head, p);
			p = p->next;
		
		}
		if(fclose(fp)){
			printf("Can not close the file!\n");
			exit(0);
		}
	}
	return head;
}

//��ȡ����д�뵽�ļ���
void Con_Fileprint(Con *head, int n)
{
	Con *ptr;
	int size = sizeof (Con);
	FILE *fp = fopen("Rank.txt","w");
	fprintf(fp,"%d\n",n);
	for(ptr = head; ptr != NULL; ptr = ptr->next){
		fprintf(fp, "%d\t%s\t%d\t%d\t%d\n", ptr->num, ptr->name, ptr->score, ptr->level, ptr->c_line);
	}
	fclose(fp);
} 
		
//������Ϸ���ݲ���д���ļ��� 
void Con_Save(void)
{
	int i, j; 
	//�ֱ��¼Ҫ��������� 
	int SArea[HEIGHT][WIDTH];
	int SNow_Block, SNow_Color; 
	int SNext_Block, SNext_Color;
	int SX, SY; 
	char SCon_Name[NUB];
	int SG_Score, SLevel, SC_Line; 
	
	//��Ҫ��������ݴ洢�����Ӧ��S�� 
	for(i=0; i<HEIGHT; i++){
		for(j=0; j<WIDTH; j++){
			SArea[i][j] = Area[i][j];
		}
	}
	SNow_Block = Now_Block;
	SNow_Color = Now_Color;
	SNext_Block = Next_Block;
	SNext_Color = Next_Color;
	SX = X;
	SY = Y;
	strcpy(SCon_Name, Con_Name);
	SG_Score = G_Score;
	SLevel = Level;
	SC_Line = C_Line;
	
	//����������������Con_Save.txt��	 
	FILE *fp;
	fp = fopen("Con_Save.txt","w");

	for(i=0; i<HEIGHT; i++){
		for(j=0; j<WIDTH; j++){
			fprintf(fp, "%d\t", SArea[i][j]);
		}
		fprintf(fp, "\n");
	}
	fprintf(fp, "%s\n", SCon_Name);
	fprintf(fp, "%d\t%d\n", SNow_Block, SNow_Color);	
	fprintf(fp, "%d\t%d\n", SNext_Block, SNext_Color);
	fprintf(fp, "%d\t%d\n", SX, SY);
	fprintf(fp, "%d\t%d\t%d\n", SG_Score, SLevel, SC_Line);
	
	//�ر��ļ� 
	fclose(fp);
} 

//��ȡ�ļ�������Ϸ 	,ֱ�����벢���޸�ȫ�ֱ��� 
void Con_Continue(void)
{
	int i, j; 
	//��Con_Save.txt ��ȡ���� 
	FILE *fp;
	fp = fopen("Con_Save.txt","r");
	
	for(i=0; i<20; i++){
		for(j=0; j<10; j++){
			fscanf(fp, "%d", &Area[i][j]);
		}
	}
	
	fscanf(fp, "%s", Con_Name);
	fscanf(fp, "%d%d", &Now_Block, &Now_Color);
	fscanf(fp, "%d%d", &Next_Block, &Next_Color);
	fscanf(fp, "%d%d", &X, &Y);
	fscanf(fp, "%d%d%d", &G_Score, &Level, &C_Line);
	fclose(fp);
	
	Now_Timer = Level;
	
	startTimer(Now_Timer, (21-Level)*40); //������ǰTimer 
} 

// ɾ����֮ǰ�Ĵ浵������д��һ��  '#' �����ĵ���Ч 
void Con_DestorySave(void)
{
	FILE *fp = fopen("Con_Save.txt","w");
	fprintf(fp,"%c",'#');
	fclose(fp);
} 

// �ж��Ƿ���ڴ浵�ļ� 
int Con_Is_Save(void)
{
	FILE *fp = NULL;
	fp = fopen("Con_Save.txt","r");
	char ret;
	if( fp ){ // ��ȡ�ļ�ָ�� 
		fscanf(fp, "%c", &ret);
		if( ret == '#'){ // �ļ���һ���ַ�Ϊ # ��û�д浵 
			printf("û�д浵��\n"); 
			return 0;
		} else { // �����д浵 
			fclose(fp);
			return 1;
		}	
	} else { // �ļ�ָ��Ϊ�գ� û�д浵 
		printf("û�д浵��\n");
		return 0;
	}
} 
