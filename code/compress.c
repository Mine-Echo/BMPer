#include"compress.h" 

int Compress(unsigned char *source,unsigned int n)
{
	unsigned char *copy=(unsigned char *)malloc(n*sizeof(source[0]));
	if(copy==NULL)
		exit(1);
		 
	memcpy(copy,source,n);
	unsigned int i=0,j=0,count=1;
	for(i=0;i<n;i++)
	{
		if(i==0)          //第一个数据的判定 
		{
			if(copy[i]!=copy[i+1])   //第一个不等于下一个 
			{
				source[j++]=copy[i]; 
				if(copy[i]==0)          //单个不连续的0记为00 
					source[j++]=copy[i]; 
			}
		}
		else
		{
			if(copy[i]==copy[i-1])
			{
				count++;
				if(copy[i]!=copy[i+1]||count==255)  //不等于下一个或者计数到255时压缩（unsigned char 范围0-255） 
				{
					source[j++]=0;
					source[j++]=count;
					source[j++]=copy[i];
					if(count==255&&copy[i]==copy[i+1])count=0;
					else					
					count=1;
				}
			}
			else
			{
				if(copy[i]!=copy[i+1])    //既不等于前一个也不等于下一个 
				{
					source[j++]=copy[i];
					if(copy[i]==0)
						source[j++]=copy[i];
				}
				else ;       //不等于前一个但等于下一个，不做处理 
			}	
		}
	}
	free(copy);
	return j;		//返回压缩后数组的长度 
}
	
void SaveCompress(const unsigned char *source,const char *bmp_path)
{
	//输出 	
	unsigned int n=top->info.biWidth*top->info.biHeight;
	unsigned char *b=(unsigned char *)malloc(2*n*sizeof(source[0]));       //申请2*n个字节而不是n个字节，防止压缩压大导致内存不够 
	unsigned char *g=(unsigned char *)malloc(2*n*sizeof(source[0]));
	unsigned char *r=(unsigned char *)malloc(2*n*sizeof(source[0]));
	
	if(r==NULL||g==NULL||b==NULL)
		exit(1);
	
	unsigned int i=0,l=0,m=0,o=0;
	//将RGB单个色道的数据分离 
	for(i=0;i<3*n;i+=3)
	{
		b[l++]=source[i];
		g[m++]=source[i+1];
		r[o++]=source[i+2];
	} 
	
	//压缩 
	l=Compress(b,n);
	m=Compress(g,n);
	o=Compress(r,n);
	
	unsigned char *compress=(unsigned char*)malloc((l+m+o)*sizeof(source[0]));
	
	for(i=0;i<l;i++)
		compress[i]=b[i];
	for(i=0;i<m;i++)
		compress[i+l]=g[i];
	for(i=0;i<o;i++)
		compress[i+l+m]=r[i];
	free(b);
	free(g);
	free(r);
	
	//输出到压缩后的文件 
	FILE *fpw=fopen(bmp_path,"wb+");
	fwrite(&l,sizeof(unsigned int),1,fpw);
	fwrite(&m,sizeof(unsigned int),1,fpw);
	fwrite(&o,sizeof(unsigned int),1,fpw);
	fwrite(&top->head,sizeof(BITMAPFILEHEADER),1,fpw);
 	fwrite(&top->info,sizeof(BITMAPINFOHEADER),1,fpw);
 	fseek(fpw,54+12,SEEK_SET);
 	fwrite(compress,(l+m+o),1,fpw);
 	free(compress);
 	fclose(fpw);
}
 	
void ReadCompressImage(const char* path)
{
	FILE *fpr=fopen(path,"rb");
	base=(BMP_node *)InitList();//初始化栈 
	
 	//读取原照片的头信息
 	unsigned int l,m,o;
 	fread(&l,sizeof(unsigned int),1,fpr);
 	fread(&m,sizeof(unsigned int),1,fpr);
 	fread(&o,sizeof(unsigned int),1,fpr);
 	fread(&base->head,sizeof(BITMAPFILEHEADER),1,fpr);
 	fread(&base->info,sizeof(BITMAPINFOHEADER),1,fpr);

 	int old_width=base->info.biWidth;//获取原图片的宽
 	int old_height=base->info.biHeight;//获取原图片的高
	//申请内存空间 
	unsigned char* compress1=(unsigned char*)malloc(l*sizeof(unsigned char));
	unsigned char* compress2=(unsigned char*)malloc(m*sizeof(unsigned char));
	unsigned char* compress3=(unsigned char*)malloc(o*sizeof(unsigned char));
	//读取压缩后的图片数据 
	fseek(fpr,54+12,SEEK_SET);
	fread(compress1,l,1,fpr);
	fread(compress2,m,1,fpr);
	fread(compress3,o,1,fpr);
	int n=old_width*old_height;
	
	unsigned char *b=(unsigned char*)malloc(n*sizeof(unsigned char));
	unsigned char *g=(unsigned char*)malloc(n*sizeof(unsigned char));
	unsigned char *r=(unsigned char*)malloc(n*sizeof(unsigned char));
	
	//解压缩 
	Unzip(compress1,l,b);
	Unzip(compress2,m,g);
	Unzip(compress3,o,r);
	//释放内存空间 
	free(compress1);	
	free(compress2);	
	free(compress3);	
	
	base->bmp_data=(char*)malloc(3*n);
	int i;
	//将解压后的三个通道的图像数据合在一起 
	for(i=0;i<n;i++)
	{
		base->bmp_data[3*i]=b[i];
		base->bmp_data[3*i+1]=g[i];
		base->bmp_data[3*i+2]=r[i];
	} 
	free(b);
	free(g);
	free(r);
	
	int width=(int)(old_width)/4*4;
    int height=(int)(old_height)/4*4;
    Reshape(width,height);
    Display();
    ShowImage();

} 

void Unzip(const unsigned char*compress,int n,unsigned char *unzip)
{
	int i=0,j=0,k=0;
	for(i=0;i<n;i++)
	{
		if(compress[i]==0)//读到0的时候进行判断 
		{
			if(compress[i+1]==0)
			{
				unzip[j++]=compress[i];
				i++;
			}
			else
			{
				for(k=0;k<compress[i+1];k++)
					unzip[j++]=compress[i+2];
					i+=2;
			}
		}
		else	//不是0直接复制数据 
			unzip[j++]=compress[i];
	}
}	
	
	
	

