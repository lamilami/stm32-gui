
#include"fifo.h"

void fifo_open(EBufKind buf_kind, TFIFO* tfifo)
{
  int base_size;
  switch(buf_kind)
  {
   case CHAR:
   case UCHAR:
   base_size = sizeof(char);
   break;

   case INT:
   case UINT:
   base_size = sizeof(int);

   break;

   case FLOAT:
   base_size = sizeof(float);
   break;

   case LONG:
   case ULONG:
   base_size = sizeof(float);
   break;

   case DOUBLE:
   base_size = sizeof(double);
   break;

   default:
   base_size = sizeof(double);
   break;
  
  }
  tfifo->buf_size = BUF_SIZE;

   tfifo->pfifo_buf =  malloc(base_size*tfifo->buf_size);

}

void fifo_close(TFIFO* tfifo)
{
   free(tfifo->pfifo_buf);

}

int put_into_fifo(TFIFO* tfifo, void* data)
{
	unsigned int addr;

	addr = (tfifo->in_lenth&tfifo->buf_size);
	tfifo->pfifo_buf[addr] = data[0];

	tfifo->in_lenth++;
	tfifo->left_size++;
	
	if(tfifo->left_size-1> tfifo->buf_size)
		return -1;
	else 
		return 0;
}

int out_fifo(TFIFO* tfifo,void* data)
{
	unsigned int addr;
	
	addr = (tfifo->out_lenth&tfifo->buf_size);
	
	data[0] = tfifo->pfifo_buf[tfifo->out_lenth];

	tfifo->out_lenth--;
	tfifo->left_size--;
	if(tfifo->left_size < 0)
		return -1;
	else 
		return 0;
}