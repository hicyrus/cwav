#include <stdio.h>

int main(int argc,char *argv[])
{
	char ch;
	unsigned char hch[100];//头部信息数组
	FILE *fp;

	char hbuf[28];//输出文件
	char dbuf[28];//输出文件	

	sprintf(hbuf,"%s-head.wav",argv[1]);
	sprintf(dbuf,"%s-data.wav",argv[1]);
	
	int data_flag = 0; 
		
	if((fp=fopen(argv[1],"r"))==NULL)
	{
		printf("not open");
		exit(0);
	}

	//查找data_flag 位置
	for(int i=0;i<100;i++)
	{
		hch[i]=fgetc(fp);
		if(i%16==0)
			printf("\n");
		if(hch[i]<16)
			printf("0%x",hch[i]);
		else
			printf("%x",hch[i]);
	}	
 	
	for(int i=32;i<100;i++)
	{
		if(hch[i]=='t'&&hch[i-1]=='a'&&hch[i-2]=='d'&&hch[i+1]=='a')
		{
			data_flag=i-2;
			break;
		}
	}	
	
	printf("\ndata_flag:%d\n",data_flag);
	int a = 0;
	
	//每秒byte
	int bytepers = *((int*)&hch[28]);
	printf("\nbytepers:%d\n",bytepers);

	//重置fseek(fp,0,SEEK_SET);
	//rewind()
	//重置到开头
	rewind(fp);	
	int startdata = data_flag + 8;	

	FILE *hfp;
	if((hfp=fopen(hbuf,"wb"))==NULL){
	
		printf("not open %s \n",hbuf);	
		exit(0);

	}
	for(int i=0;i<data_flag;i++)
	{
		fputc(hch[i],hfp);
	}
	fflush(hfp);
	fclose(hfp);
			
	FILE *hp;
	if((hp=fopen(dbuf,"wb"))==NULL){
		printf("not open %s",dbuf);
		exit(0);	
	}

	//fseek(fp,data_flag,SEEK_SET);
	fseek(fp,startdata,SEEK_SET);
	while(!feof(fp))
	{
		fputc(fgetc(fp),hp);				
	}
	fflush(hp);
	fclose(hp);
		
	//while((ch=fgetc(fp))!=EOF)
	/*
	*/
	printf("\n");
	printf("\nnum:%d\n",a);
	fclose(fp);
	exit(1);
}
