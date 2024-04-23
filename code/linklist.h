#ifndef _linklist_h
#define _linklist_h

#include"bmpdef.h"

#define INIT_X_POS 5.11 //图片起始X坐标 
#define INIT_Y_POS 0.36 //图片起始Y坐标

//新建节点并动态申请内存 
BMP_node * CreateNode();

//初始化链表 
BMP_node * InitList();

//压栈 
BMP_node * PushStack(BMP_node *old_top,BMP_node *new_top);

//弹出栈顶节点 
BMP_node * PopStack(BMP_node *top);

//深拷贝节点 
BMP_node * CopyNode(BMP_node *old);

//清空链表 
void ClearList();

#endif
