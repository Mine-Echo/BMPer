#include"bmpdef.h"
#include"bmp.h"
#include"linklist.h"
#include"callback.h"
#include"gui.h" 
#include "convolution.h"
#include"compress.h"
 //����ԭ��Ƭ��Ϣ�ṹ��

 BMP_node *top=NULL;
 BMP_node *base=NULL;
 
 //��Ҫ�򿪻򱣴���ļ��� 
char FileName[50];
char name[50];
//�ļ�ָ��
FILE *fp;

 //�������� 
bool OPEN=FALSE;     //�ļ��Ƿ�� 
bool SAVE=TRUE;      //�ļ��Ƿ񱣴� 
bool IS_TAILOR=FALSE;  //�ü�ģʽ��ѡ��ģʽ 
bool IS_PLAY=FALSE; //�����Ƿ�� 

HWND window;   //���ھ�� 

void Main()
{ 
    //���ô��ڴ�С 
	SetWindowSize(WindowW,WindowH);
	//���ô��ڱ��� 
	SetWindowTitle("BMPͼƬ�༭��");
	InitGraphics();
    registerKeyboardEvent(KeyboardEventProcess);
    registerMouseEvent(MouseEventProcess);
    
    //SaveCompress(top->bmp_data,"com.a");
}
 
