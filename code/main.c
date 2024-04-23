#include"bmpdef.h"
#include"bmp.h"
#include"linklist.h"
#include"callback.h"
#include"gui.h" 
#include "convolution.h"
#include"compress.h"
 //定义原照片信息结构体

 BMP_node *top=NULL;
 BMP_node *base=NULL;
 
 //需要打开或保存的文件名 
char FileName[50];
char name[50];
//文件指针
FILE *fp;

 //布尔变量 
bool OPEN=FALSE;     //文件是否打开 
bool SAVE=TRUE;      //文件是否保存 
bool IS_TAILOR=FALSE;  //裁剪模式或选择模式 
bool IS_PLAY=FALSE; //音乐是否打开 

HWND window;   //窗口句柄 

void Main()
{ 
    //设置窗口大小 
	SetWindowSize(WindowW,WindowH);
	//设置窗口标题 
	SetWindowTitle("BMP图片编辑器");
	InitGraphics();
    registerKeyboardEvent(KeyboardEventProcess);
    registerMouseEvent(MouseEventProcess);
    
    //SaveCompress(top->bmp_data,"com.a");
}
 
