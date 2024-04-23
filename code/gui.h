#ifndef _menu_h
#define _menu_h
 
#include"bmpdef.h"
#include"bmp.h"
#include"callback.h"

#include<mmsystem.h>
#pragma comment(lib,"winmm.lib")

#define WindowH 10  //���ڸ߶� 
#define WindowW 16  //���ڿ�� 
#define INTERVAL 1  

//��Ҫ�򿪻򱣴���ļ��� 
extern char FileName[50];
extern char name[50];
//�ļ�ָ�� 
extern FILE *fp;

//�������� 
extern bool OPEN;     //�ļ��Ƿ�� 
extern bool SAVE;      //�ļ��Ƿ񱣴� 
extern bool IS_TAILOR;  //�ü�ģʽ��ѡ��ģʽ 
extern bool IS_PLAY;   //���������Ƿ�� 
extern HWND window;   //���ھ�� 

//��ͼƬ���˵�����ť��չʾ��ͼ�ν����� 
//void display();

//��ͼ�ν��滭���˵� 
void DrawMenu();

//�����ļ��˵�����ѡ�� 
void SelectFile(int selection);

//ѡ��ر�ʱ����һЩ�ж�
void ChoiceOfClose(int choice);

//ѡ���˳�ʱ����һЩ�ж� 
void ChoiceOfExit(int choice);

//���ļ�ʱ��ʼ��һЩ����
void Init(); 

//����������ܲ˵���ѡ�� 
void SelectFunction(int selection);

//�����������ܵ�ѡ�� 
void SelectFunction2(int selection); 

//������ڲ˵���ѡ�� 
void SelectAbout(int selection);

//��ͼ�ν��滭��״̬��Ϣ�� 
void DrawInformationBar(double x,double y,double w,double h,double w_rate,double h_rate);

//���ܣ���ͼ�λ����滭����ťһ�� 
void DrawButton();

#endif
