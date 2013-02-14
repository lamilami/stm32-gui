
#include"gui_app.h"

#define DEVICE_ADD	  0x70
#define IIC_CTPM_SDA  PCout(4) 	
#define IIC_CTPM_SCL  PAout(5)
#define READ_CTPM_SDA PCin(4)


void IIC_CTPM_Start (void);
void IIC_CTPM_Stop(void);
unsigned char IIC_CTPM_WriteByte (unsigned char txByte);









