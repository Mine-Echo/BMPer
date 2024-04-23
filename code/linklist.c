#include"linklist.h"

BMP_node * CreateNode()
{
	BMP_node* p = (BMP_node*)malloc(sizeof(BMP_node));
	p->next=NULL;
	p->changebase=FALSE;
	return p;
}

BMP_node * InitList()
{
	BMP_node* p = CreateNode();
	p->InitX=ScaleX(INIT_X_POS);
	p->InitY=ScaleY(INIT_Y_POS);//起始画图点 
	return p;
}

BMP_node * PushStack(BMP_node *old_top,BMP_node *new_top)
{
	new_top->next = old_top;
	return new_top;
}

BMP_node * PopStack(BMP_node *head)
{   
    if(head->next==NULL)return head;
    else
    {
	BMP_node *p=head->next;
	free(head->bmp_data);
	free(head);
	return p;
    }
}

BMP_node * CopyNode(BMP_node * old)
{
	BMP_node* p=(BMP_node *)CreateNode();
	p->head=old->head;
	p->info=old->info;
    p->InitX=old->InitX;
    p->InitY=old->InitY;
    p->bmp_data=(char*)malloc(old->info.biWidth*old->info.biHeight*3);
    memcpy(p->bmp_data,old->bmp_data,old->info.biWidth*old->info.biHeight*3);//对节点的成员变量进行深拷贝 
    return p;
}

void ClearList()
{
	while(top!=NULL&&top->next!=NULL)
	{
	 top=(BMP_node *)PopStack(top);
	}
	if(top!=NULL)
	{
		free(top->bmp_data);
		free(top);
		top=NULL;
	}
	
	while(base!=NULL&&base->next!=NULL)
	{
	 base=(BMP_node *)PopStack(base);
	}
	if(base!=NULL)
	{
		free(base->bmp_data);
		free(base);
		base=NULL;
	}
} 
