#include <stdio.h>
extern "C" {
#include "fins.h"
}
#include <string.h>


void fins_test()
{
	struct fins_sys_tp *sys;
	int ret;

	//sys.address = "192.168.1.1";
	//sys.port = 9600;
	int error_val;
	
	sys = finslib_tcp_connect(NULL, "192.168.1.1", 9600, 0, 10, 0, 0, 1,0,&error_val, 6);
	printf("0x%x   error_val: %d\n",sys,error_val);
	if(sys == NULL || error_val != 0) {
		return;
	}

	sys->plc_mode = FINS_MODE_CS;
	//struct fins_cpudata_tp *cpudata = new(struct fins_cpudata_tp);

	//ret = finslib_cpu_unit_data_read(sys,cpudata);

	//printf("cpudata read ret:%d\n",ret);

	unsigned char data[] = {0x55,0x55};
	unsigned char rddata[10];
	memset(rddata,0,10);
	char start[] = "DM100";
 
	ret = finslib_memory_area_read_word(sys,start,rddata,1);
	printf("ret:%d\n",ret);

	if(ret != FINS_RETVAL_SUCCESS)return;

	//ret = finslib_memory_area_write_word(sys,start,data,2);
	//printf("ret:%d\n",ret);

	//if(ret != FINS_RETVAL_SUCCESS)return;

	//unsigned char read_data[2];

	//ret = finslib_memory_area_read_word(sys,start, read_data, 2);

	//printf("ret:%d    read_data0:0x%x   read_data1:0x%x\n",ret,read_data[0],read_data[1]);

	finslib_disconnect(sys);
}



int main()
{

	fins_test();

}
