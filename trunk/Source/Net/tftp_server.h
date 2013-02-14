#ifndef __TFTP_H
#define __TFTP_H

#define OP_CODE_LOC 0x2B

#define NAME_LOC (OP_CODE_LOC+1)

#define TFTP_PORT 69

#define BLOCK_LOC_H  (OP_CODE_LOC+1)

#define BLOCK_LOC_L  (OP_CODE_LOC+2)



typedef  enum OP
{
	RRQ = 1,
	WRQ = 2,
	DATA = 3,
	ACK = 4,
	ERR = 5
}EOP;

typedef enum ERR
{
  OP_ERR = 0,
  TIMER_OUT_ERR = 1,
  FILE_NOT_FOUND = 2,
  FILE_READ_ERR = 3

}S_ERROR;

typedef enum MODE
{
   NETASCII = 1,
   OCTET = 2
}EMODE;


typedef struct TFTP_PACK
{
	unsigned int op_code;
	char file_name[20];
	char mode[10];
	int  block_No;
	char file_content[516];
	int  current_file_size;
//	int  trans_end;	

}S_TFTP_PACK;


typedef struct TIMER
{
  int enable;
  int data;
  int data_end;

  long over;

}S_TIMER;

void tftp_timer_refush(void);
void tftp_timer_enable(void);
void tftp_timer_disable(void);

void tftp_timer_over(unsigned char* buf);
void init_tftp(void);
char rrq_wrq_exc(unsigned char* buf);
char data_exc(unsigned char* buf);
char ack_exc(unsigned char* buf);
char error_exc(unsigned char* buf,S_ERROR err_code);
char  tftp_exc(unsigned char* buf);
void tftp_timer_run(unsigned char* buf);
void tftp_init(void);










#endif  
