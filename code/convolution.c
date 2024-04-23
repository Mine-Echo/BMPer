#include "convolution.h"

unsigned char* fill()//边缘填充 
{
	int new_width=base->info.biWidth+2;
	int new_height=base->info.biHeight+2;
	int con=255;//所要填充的像素值（三色道全255） 
	char *image=(char *)malloc(sizeof(char)*(new_width*new_height*3));
	int i,j;
	//填充第一行 
	for(i=0;i<new_width;i++)
	{
		image[3*i]=con;
		image[3*i+1]=con;
		image[3*i+2]=con;
	}
	for(i=0;i<new_height-2;i++)
	{
		image[3*new_width*(i+1)]=con;
		image[3*new_width*(i+1)+1]=con;
		image[3*new_width*(i+1)+2]=con;//第一个像素
		memcpy(image+3*new_width*(i+1)+3,base->bmp_data+3*i*base->info.biWidth,3*base->info.biWidth); 
		image[3*new_width*(i+1)+3+3*base->info.biWidth]=con;
		image[3*new_width*(i+1)+3+3*base->info.biWidth+1]=con;
		image[3*new_width*(i+1)+3+3*base->info.biWidth+2]=con;//第一个像素
	} 
	for(i=0;i<new_width;i++)
	{
		image[3*new_width*(new_height-1)+3*i]=con;
		image[3*new_width*(new_height-1)+3*i+1]=con;
		image[3*new_width*(new_height-1)+3*i+2]=con;
	}
	return image;
}

void convolution(double core[3][3])
{
    int width=base->info.biWidth;
	int height=base->info.biHeight;
	unsigned char *image=(unsigned char *)fill();
	BMP_node* new_node=(BMP_node*)CopyNode(base);

	 int i,j,k;
	 
	 for(i=0;i<height;i++)
	 {
	    for(j=0;j<width;j++)
	    {
	    	for(k=0;k<3;k++) 
	    	//进行卷积计算 
	    	new_node->bmp_data[3*i*width+j*3+k]=image[3*(i*(width+2)+j)+k]*core[2][0]+image[3*(i*(width+2)+j+1)+k]*core[2][1]+image[3*(i*(width+2)+j+2)+k]*core[2][2]
	    	                           +image[3*((i+1)*(width+2)+j)+k]*core[1][0]+image[3*((i+1)*(width+2)+j+1)+k]*core[1][1]+image[3*((i+1)*(width+2)+j+2)+k]*core[1][2]
	    	                           +image[3*((i+2)*(width+2)+j)+k]*core[0][0]+image[3*((i+2)*(width+2)+j+1)+k]*core[0][1]+image[3*((i+2)*(width+2)+j+2)+k]*core[0][2];
	        
			new_node->bmp_data[3*i*width+j*3+k]=max_num(new_node->bmp_data[3*i*width+j*3+k],0);
			new_node->bmp_data[3*i*width+j*3+k]=min_num(new_node->bmp_data[3*i*width+j*3+k],255);//处理小于0或大于255的点 
		}
	}

	base=(BMP_node*)PushStack(base,new_node);//压栈 
	Reshape(top->info.biWidth,top->info.biHeight);
	top->changebase=TRUE;
}

void Gray()
{
	int width=base->info.biWidth;
	int height=base->info.biHeight;
	BMP_node* new_node=(BMP_node*)CopyNode(base);
	int i,j,gray;
	for(i=0;i<height;i++)
	 {
	    for(j=0;j<width;j++)
	    {
	    	//灰度转换公式 
	        gray=new_node->bmp_data[3*i*width+j*3]*0.114+new_node->bmp_data[3*i*width+j*3+1]*0.587+new_node->bmp_data[3*i*width+j*3+2]*0.299;
		    new_node->bmp_data[3*i*width+j*3]=gray;
		    new_node->bmp_data[3*i*width+j*3+1]=gray;
		    new_node->bmp_data[3*i*width+j*3+2]=gray;
	    }
	 }
	base=(BMP_node*)PushStack(base,new_node);//压栈 
	Reshape(top->info.biWidth,top->info.biHeight);
	top->changebase=TRUE;//标志基准改变 
}

void Binarization(int n)
{
	int width=base->info.biWidth;
	int height=base->info.biHeight;
	BMP_node* new_node=(BMP_node*)CopyNode(base);
	int i,j,gray;//循环变量 
	for(i=0;i<height;i++)
	 {
	    for(j=0;j<width;j++)
	    {
	    	//灰度转换公式 
	        gray=new_node->bmp_data[3*i*width+j*3]*0.114+new_node->bmp_data[3*i*width+j*3+1]*0.587+new_node->bmp_data[3*i*width+j*3+2]*0.299;
		    if(gray<n)gray=0;
		    else gray=255;//将图片依据阈值二值化 
		    new_node->bmp_data[3*i*width+j*3]=gray;
		    new_node->bmp_data[3*i*width+j*3+1]=gray;
		    new_node->bmp_data[3*i*width+j*3+2]=gray;
	    }
	 }
	base=(BMP_node*)PushStack(base,new_node);//压栈 
	Reshape(top->info.biWidth,top->info.biHeight);
	top->changebase=TRUE;
}
int max_num(int a,int b)//返回最大值 
{
	if(a>=b)
	return a;
	else
	return b;
} 

int min_num(int a,int b)//返回最小值 
{
	if(a<=b)
	return a;
	else
	return b;
} 
