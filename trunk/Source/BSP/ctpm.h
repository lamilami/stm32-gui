
#include"gui_app.h"

#define DEVICE_ADD	  0x70
#define IIC_CTPM_SDA  PBout(7)  	
#define IIC_CTPM_SCL  PBout(6) 
#define READ_CTPM_SDA PBin(7)


void IIC_CTPM_Start (void);
void IIC_CTPM_Stop(void);
unsigned char IIC_CTPM_WriteByte (unsigned char txByte);









