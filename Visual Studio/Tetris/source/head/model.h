#ifndef _MODEL_H_
#define _MODEL_H_

// ģ������Ӻ��� 
void Go_Button_M(void); 				// �� Ctrl�е��ã�ʵ�ֿո�ʹ����ֱ����ʵ 
void Model_Flow(void);					// �� Main�е��ã�Timer�ص�������ɲ��֣�������Ϸ���� 
void Delete_Row(void);					// �� Draw�е��ã�����ʵ���������� 

// ģ���ڲ����� 
static void Creat_Block(void);			// �����¸����� 
static int Fall_Block(void);			// �������䣬�Ƿ��Ѿ���أ���1��0 
static void Fixed_Block(void);			// ���Ѿ��̶��ķ��������Ϸ�����̶����� 
static int Is_Touch(void);				// �Ƿ�Ӵ����ײ� ����1��0 
static int Is_End_Game(void);			// ������Ϸ ��1��0 
static void Move_Area(int row);			// ��1-row-1�������ƶ�һ�У����������� 
static void Change_Score(int ret);		// �����ı䣬ret Ϊ��������  
static void Timer_Model(void); 			// �Ѷȿ��ƺ�����ͨ������Timer�����ٶ� 
static void End_Game(void);				// ��Ϸ������Ĵ������ص���ʼ�˵� 
static void Print_Area(void); 			// �� Consule��������ͼ������ 

#endif
