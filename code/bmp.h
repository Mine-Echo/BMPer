#ifndef _bmp_h
#define _bmp_h

#include"bmpdef.h"

#define UI_X 2.8       //������UI����ʼX����
#define UI_Y 2.0       //������UI����ʼY����
#define UILenth 2      //�������ĳ���
#define UIInterval 0.5   //������������UI�ļ��
#define UI_Button_X 0.1 //�϶���ť�Ŀ��
#define UI_Button_Y 0.4 //�϶���ť�ĸ߶�
#define ScreenY 10     //���ڵĸ߶�

extern int dx1,dx2,dy1,dy2;//�ü�ƫ���� 

//��ͼƬ�������Ų��� 
void Reshape(int new_width,int new_height);

//��ͼƬ������ת�Լ�����ת���� 
void Rotate(int mode);

//��ͼƬ���вü� 
void CutImage(int InitX,int InitY,int width,int height);

//ͼƬ���� 
int ReadImage(const char* old_bmp_path);

//ͼƬ���� 
int PutImage(const char *new_bmp_path);

//���ü�ģʽ�µ�UI�밴�� 
void DrawCutUI(int dx1,int dx2,int dy1,int dy2);

//��ͼƬ��ʾ�ڴ��� 
int ShowImage();

//ˢ�´��ڣ����²˵�������������·���Ϣ����״̬ 
void Display();

//��ָ��������� 
void ClearSpace(double x,double y,double width,double height);

//�����·���Ϣ����λ����Ϣ 
void UpdateLocation(int X,int Y);

//�����·���Ϣ���ĳ����������Ϣ 
void UpdateSize(double width,double height);
#endif
