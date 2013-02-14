
#ifndef _FIFO_H_
#define _FIFO_H_

#define BUF_SIZE 1024

typedef enum
{
   CHAR = 1,
   UCHAR = 2,
   INT = 3,
   UINT = 4,
   FLOAT = 5,
   LONG = 6,
   ULONG = 7,
   DOUBLE = 8

}EBufKind;

typedef struct
{
	unsigned int in_lenth;
	unsigned int out_lenth;
	unsigned int buf_size;
	long left_size;
	void* pfifo_buf;

}TFIFO;



void fifo_open(EBufKind buf_kind, TFIFO* tfifo);

void fifo_close(TFIFO* tfifo);

int put_into_fifo(TFIFO* tfifo, void* data);

int out_fifo(TFIFO* tfifo,void* data);



#endif
