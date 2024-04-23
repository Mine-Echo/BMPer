#ifndef _callback_h
#define _callback_h

#include "bmpdef.h"
#include "bmp.h"
#include "gui.h" 

//键盘回调函数 
void KeyboardEventProcess(int key,int event);

//鼠标回调函数 
void MouseEventProcess(int x, int y, int button, int event);

#endif
