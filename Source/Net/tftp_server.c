
#include"tftp_server.h"
#include"ip_arp_udp_tcp.h"
#include "bsp.h"
#include "ff.h"	
#include "stm32f10x.h"
#include "sdcard.h"
#include "diskio.h"
#include <string.h>

 S_TFTP_PACK tftp_pack;

 S_TIMER tftp_timer;


extern FATFS fs;
extern FIL fsrc;



void tftp_timer_refush(void)
{
	tftp_timer.data = 0;
}

void tftp_timer_run(unsigned char* buf)
{
   if(tftp_timer.enable)
   {  
   	if(tftp_timer.data++ >= tftp_timer.over)
	{
	  tftp_timer_over(buf);
	}
   }
}

void tftp_timer_enable(void)
{
	tftp_timer.enable = 1;
}


void tftp_timer_disable(void)
{
	tftp_timer.enable = 0;
}



char error_exc(unsigned char* buf,S_ERROR err_code)
{

	char sbuf[30];
	sbuf[0] = 0;
	sbuf[1] = ERR;
	sbuf[2] = 0;
	sbuf[3] = err_code;
    
    sbuf[4] =0; 

	sbuf[5] = 0;

	f_close(&fsrc);
	f_mount(0, NULL);

	make_udp_reply_from_request(buf,sbuf,20,TFTP_PORT);	
	return 0;
}

void tftp_timer_over(unsigned char* buf)
{
	error_exc(buf,TIMER_OUT_ERR);
	tftp_timer.enable = 0;
	tftp_timer.data = 0;	
}




char rrq_wrq_exc(unsigned char* buf)
{
	int i,j,r_res;
	int br;
	unsigned char res;
	tftp_pack.op_code = *(buf+OP_CODE_LOC);

	//strcpy(tftp_pack.file_name, buf + NAME_LOC);
	for(i=0;*(buf+NAME_LOC+i)!='\0';i++)
	 tftp_pack.file_name[i] = *(buf+NAME_LOC+i);

	if(tftp_pack.op_code == RRQ)
   {
	res = f_open(&fsrc,tftp_pack.file_name,FA_READ) ;
	if(res)
	{
		error_exc(buf,FILE_NOT_FOUND);
		return -1;	
	}else{
		f_lseek(&fsrc, 0);
		r_res = f_read (&fsrc,tftp_pack.file_content,512,&br);
		if(r_res)
		{
		error_exc(buf,FILE_READ_ERR);
		return -1;
		}
		tftp_pack.current_file_size = br;
	}
		
	for(j=0; (*(buf+NAME_LOC+1+i+j)!='\0')&&(j<10);j++)
	tftp_pack.mode[j] =	*(buf+NAME_LOC+i+1+j);

	tftp_pack.block_No = 1;

	data_exc(buf);
	
   }
	return 0;
}

char data_exc(unsigned char* buf)
{
	int i;
	char packet[516];
	packet[0] = 0;
	packet[1] = DATA;
	packet[2] = 0;
	packet[3] = tftp_pack.block_No ;
	
	tftp_set_data_message(packet,tftp_pack.file_content, tftp_pack.current_file_size);
	
	make_udp_reply_from_request(buf,packet,tftp_pack.current_file_size+4,TFTP_PORT);

	tftp_timer_enable();

	return 0;
}

char ack_exc(unsigned char* buf)
{
	unsigned int k,n,l,r_res,br;

	k =   *(buf+BLOCK_LOC_H);
	n =   *(buf+BLOCK_LOC_L);
	l = (k<<8)+n;
	
//	if(tftp_pack.trans_end !=0)
	if(tftp_pack.current_file_size == 512)
	{
	tftp_pack.block_No = l+1;
	tftp_timer_refush();
	f_lseek(&fsrc, l*512);
	r_res = f_read (&fsrc,tftp_pack.file_content,512,&br);
	if(r_res)
	{
		error_exc(buf,FILE_READ_ERR);
	    return -1;
	}
		tftp_pack.current_file_size = br;	
	
	data_exc(buf);
	return 0;
	}else{
	
	f_close(&fsrc);
	//f_mount(0, NULL);

	}

	return 0;
}

char  tftp_exc(unsigned char* buf)
{
	int op_code ;
	op_code = *(buf+OP_CODE_LOC);

	if((op_code == RRQ)||(op_code == WRQ))
	{
	rrq_wrq_exc(buf);

	}else if(op_code == DATA){

	data_exc(buf);

	}else if(op_code == ACK){

	ack_exc(buf);

	} 

	return OP_ERR;
}

void tftp_init(void)
{
   f_mount(0, &fs);
}









