#ifndef _linklist_h
#define _linklist_h

#include"bmpdef.h"

#define INIT_X_POS 5.11 //ͼƬ��ʼX���� 
#define INIT_Y_POS 0.36 //ͼƬ��ʼY����

//�½��ڵ㲢��̬�����ڴ� 
BMP_node * CreateNode();

//��ʼ������ 
BMP_node * InitList();

//ѹջ 
BMP_node * PushStack(BMP_node *old_top,BMP_node *new_top);

//����ջ���ڵ� 
BMP_node * PopStack(BMP_node *top);

//����ڵ� 
BMP_node * CopyNode(BMP_node *old);

//������� 
void ClearList();

#endif
