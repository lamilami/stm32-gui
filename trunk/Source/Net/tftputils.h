
#ifndef __TFTP_UTILS_H_
#define __TFTP_UTILS_H_

typedef unsigned   char    u8_t;
typedef signed     char    s8_t;
typedef unsigned   short   u16_t;
typedef signed     short   s16_t;
typedef unsigned   long    u32_t;
typedef signed     long    s32_t;


//tftp_opcode tftp_decode_op(char *buf);
void tftp_extract_filename(char *fname, char *buf);
//u16_t tftp_extract_block(char *buf);
//void tftp_set_opcode(char *buffer, tftp_opcode opcode);
//void tftp_set_errorcode(char *buffer, tftp_errorcode errCode);
//void tftp_set_errormsg(char * buffer, char* errormsg);
//u32_t tftp_is_correct_ack(char *buf, int block);
void tftp_set_data_message(char* packet, char* buf, int buflen);
//void tftp_set_block(char* packet, u16_t block);

#endif