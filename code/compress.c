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
		if(i==0)          //��һ�����ݵ��ж� 
		{
			if(copy[i]!=copy[i+1])   //��һ����������һ�� 
			{
				source[j++]=copy[i]; 
				if(copy[i]==0)          //������������0��Ϊ00 
					source[j++]=copy[i]; 
			}
		}
		else
		{
			if(copy[i]==copy[i-1])
			{
				count++;
				if(copy[i]!=copy[i+1]||count==255)  //��������һ�����߼�����255ʱѹ����unsigned char ��Χ0-255�� 
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
				if(copy[i]!=copy[i+1])    //�Ȳ�����ǰһ��Ҳ��������һ�� 
				{
					source[j++]=copy[i];
					if(copy[i]==0)
						source[j++]=copy[i];
				}
				else ;       //������ǰһ����������һ������������ 
			}	
		}
	}
	free(copy);
	return j;		//����ѹ��������ĳ��� 
}
	
void SaveCompress(const unsigned char *source,const char *bmp_path)
{
	//��� 	
	unsigned int n=top->info.biWidth*top->info.biHeight;
	unsigned char *b=(unsigned char *)malloc(2*n*sizeof(source[0]));       //����2*n���ֽڶ�����n���ֽڣ���ֹѹ��ѹ�����ڴ治�� 
	unsigned char *g=(unsigned char *)malloc(2*n*sizeof(source[0]));
	unsigned char *r=(unsigned char *)malloc(2*n*sizeof(source[0]));
	
	if(r==NULL||g==NULL||b==NULL)
		exit(1);
	
	unsigned int i=0,l=0,m=0,o=0;
	//��RGB����ɫ�������ݷ��� 
	for(i=0;i<3*n;i+=3)
	{
		b[l++]=source[i];
		g[m++]=source[i+1];
		r[o++]=source[i+2];
	} 
	
	//ѹ�� 
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
	
	//�����ѹ������ļ� 
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
	base=(BMP_node *)InitList();//��ʼ��ջ 
	
 	//��ȡԭ��Ƭ��ͷ��Ϣ
 	unsigned int l,m,o;
 	fread(&l,sizeof(unsigned int),1,fpr);
 	fread(&m,sizeof(unsigned int),1,fpr);
 	fread(&o,sizeof(unsigned int),1,fpr);
 	fread(&base->head,sizeof(BITMAPFILEHEADER),1,fpr);
 	fread(&base->info,sizeof(BITMAPINFOHEADER),1,fpr);

 	int old_width=base->info.biWidth;//��ȡԭͼƬ�Ŀ�
 	int old_height=base->info.biHeight;//��ȡԭͼƬ�ĸ�
	//�����ڴ�ռ� 
	unsigned char* compress1=(unsigned char*)malloc(l*sizeof(unsigned char));
	unsigned char* compress2=(unsigned char*)malloc(m*sizeof(unsigned char));
	unsigned char* compress3=(unsigned char*)malloc(o*sizeof(unsigned char));
	//��ȡѹ�����ͼƬ���� 
	fseek(fpr,54+12,SEEK_SET);
	fread(compress1,l,1,fpr);
	fread(compress2,m,1,fpr);
	fread(compress3,o,1,fpr);
	int n=old_width*old_height;
	
	unsigned char *b=(unsigned char*)malloc(n*sizeof(unsigned char));
	unsigned char *g=(unsigned char*)malloc(n*sizeof(unsigned char));
	unsigned char *r=(unsigned char*)malloc(n*sizeof(unsigned char));
	
	//��ѹ�� 
	Unzip(compress1,l,b);
	Unzip(compress2,m,g);
	Unzip(compress3,o,r);
	//�ͷ��ڴ�ռ� 
	free(compress1);	
	free(compress2);	
	free(compress3);	
	
	base->bmp_data=(char*)malloc(3*n);
	int i;
	//����ѹ�������ͨ����ͼ�����ݺ���һ�� 
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
		if(compress[i]==0)//����0��ʱ������ж� 
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
		else	//����0ֱ�Ӹ������� 
			unzip[j++]=compress[i];
	}
}	
	
	
	

