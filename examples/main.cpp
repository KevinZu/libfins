#include <stdio.h>
extern "C" {
#include "fins.h"
}
#include <string.h>

/*
*function：ftoc(float fvalue,unsigned char*arr)
*decription:  浮点数转化成四个字节
*input: 浮点数 
*output: 4个字节的字节数组
*/ //例如12.5--0x41 48 00 00;转换完之后，arr[0]-00，arr[1]-00，arr[2]-48，arr[3]-41 
void ftoc(float fvalue,unsigned char*arr) 
{ 
	unsigned char *pf; 
	unsigned char *px; 
	unsigned char i; //计数器 
	pf =(unsigned char *)&fvalue; /*unsigned char型指针取得浮点数的首地址*/ 
	px = arr; /*字符数组arr准备存储浮点数的四个字节,px指针指向字节数组arr*/ 
	for(i=0;i<4;i++) { 
		*(px+i)=*(pf+i); /*使用unsigned char型指针从低地址一个字节一个字节取出*/ 
	} 
} 


/* 
*function：float ByteToFloat(unsigned char* byteArray) 
*decription:  将字节型转化成32bits浮点型 
*input:       长度为4的字节数组 
*output: 
*/ 

float ByteToFloat(unsigned char* byteArray) 
{ 
	return *((float*)byteArray); 
} 




void fins_test()
{
	int i;
	unsigned char byteArray[4];
    ftoc(-12.12345,byteArray);


	struct fins_sys_tp *sys;
	int ret;

	//sys.address = "192.168.1.1";
	//sys.port = 9600;
	int error_val;
	
	sys = finslib_tcp_connect(NULL, "172.17.208.152", 9600, 0, 10, 0, 0, 1,0,&error_val, 6);
	printf("0x%x   error_val: %d\n",sys,error_val);
	if(sys == NULL || error_val != 0) {
		return;
	}



	int a;
	float f1 = 12.2312;
	printf("f1: %f\n",f1);
	int *b = (int *)byteArray;
	printf("f1 : 0x%x   b: 0x%x\n",f1,b);

	sys->plc_mode = FINS_MODE_CS;
	//struct fins_cpudata_tp *cpudata = new(struct fins_cpudata_tp);

	//ret = finslib_cpu_unit_data_read(sys,cpudata);

	//printf("cpudata read ret:%d\n",ret);

	unsigned char data[] = {0x30,0x39,0x01,0x02};
	unsigned char rddata[10];
	memset(rddata,0,10);
	char start[] = "DM15000";
 
	//ret = finslib_memory_area_read_word(sys,start,rddata,2);
	ret = finslib_memory_area_read_int32( sys, start, &a, 1 );
	printf("ret:%d\n",ret);
	printf("=== 0x%x\n",a);


	//for(int i = 0; i < 8; i ++ ) {
	//	printf("rddata[%d]: 0x%x \n",i,rddata[i]);
	//} 
	//printf("rddata[0]:  %d   rddata[1]: %d\n",rddata[0],rddata[1] );

	if(ret != FINS_RETVAL_SUCCESS)
		return;

	ret = finslib_memory_area_write_int32( sys, start,b, 1 ) ;
	//ret = finslib_memory_area_write_word(sys,start,byteArray,2);
	printf("ret:%d\n",ret);

	if(ret != FINS_RETVAL_SUCCESS)return;

	printf("==========");

	//unsigned char read_data[2];

	//ret = finslib_memory_area_read_word(sys,start, read_data, 2);

	//printf("ret:%d    read_data0:0x%x   read_data1:0x%x\n",ret,read_data[0],read_data[1]);

	finslib_disconnect(sys);
}



int main()
{

	fins_test();

}
