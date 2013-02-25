
#include"MMA8452Q.h"
#include"math.h"
#include"xyz_acc_para.h"

short base_buf[BASE_SIZE];



char get_from_fifo(	short* fifo_buf,short* out_buf,int lenth)
{
// get_za_data(out_buf, lenth);
}


//	N = 9 N/2 = 4
//8
//7
//6
//5 >----|
//4		 |
//3		 |
//2		 |
//1		 |
//0 <----|

char put_head(short* in_buf, short* base_buf)
{
	memcpy(base_buf,base_buf+(BASE_SIZE/2)+1,BASE_SIZE/2);
	memcpy(base_buf+(BASE_SIZE/2),in_buf,BASE_SIZE+1);
}


/******************************************************************************

                  ��Ȩ���� (C), 2012-2022, �����

 ******************************************************************************
  �� �� ��   : MMA845x.c
  �� �� ��   : ����
  ��    ��   : ganjinming
  ��������   : 2012��10��5��
  ����޸�   :
  ��������   : MMA845x����������
  �����б�   :
              IIC_ReadByte
              IIC_RegRead
              IIC_RegReadN
              IIC_RegReadXYZ_and
              IIC_RegReadXYZ_or
              IIC_RegWrite
              IIC_RegWriteN
              IIC_Start
              IIC_Stop
              IIC_WriteByte
              MMA845x_Active
              MMA845x_Init
              MMA845x_Standby
  �޸���ʷ   :
  1.��    ��   : 2012��10��5��
    ��    ��   : ganjinming
    �޸�����   : �����ļ�

******************************************************************************/
/*----------------------------------------------*
 * �궨��                                       *
 *----------------------------------------------*/


MMA845X_struct Z_acc;
MMA845X_struct X_acc;
MMA845X_struct Y_acc;

#ifndef WIN_SIM

/*----------------------------------------------*
 * ����ͷ�ļ�                                   *
 *----------------------------------------------*/
#include "stm32f10x.h"
#include "BIT_BAND_IO.h"
#include "MMA8452Q.h"

/*----------------------------------------------*
 * �ⲿ����˵��                                 *
 *----------------------------------------------*/

/*----------------------------------------------*
 * �ⲿ����ԭ��˵��                             *
 *----------------------------------------------*/

/*----------------------------------------------*
 * �ڲ�����ԭ��˵��                             *
 *----------------------------------------------*/
__asm  void delay_asm1(int i);
void IIC_Start (void);
void IIC_Stop(void);
u8 IIC_WriteByte (u8 txByte);
u8 IIC_ReadByte (etI2cAck ack);
/*----------------------------------------------*
 * ȫ�ֱ���                                     *
 *----------------------------------------------*/
 
//unsigned int got_mma845x_num  = 0;
//unsigned int used_mma845x_num = 0;
//signed short mma845x_buf[MMA845X_PART_NUMS][MMA845X_ONE_PART];

/*----------------------------------------------*
 * ģ�鼶����                                   *
 *----------------------------------------------*/

/*----------------------------------------------*
 * ��������                                     *
 *----------------------------------------------*/
 
 
/*****************************************************************************
 �� �� ��  : MMA845x_interrupt
 ��������  : MMA845x ����һ�����ݶ�ȡ
 �������  : void  
 �������  : ��
 �� �� ֵ  : 
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2012��10��5��
    ��    ��   : ganjinming
    �޸�����   : �����ɺ���

*****************************************************************************/
void MMA845x_interrupt(void)
{   
	static short z_temp,x_temp,y_temp;
	static start_stop;
	int i;
	unsigned char z_buf[2];
	unsigned char x_buf[2];
	unsigned char y_buf[2];
	
	static int z_data_cnt =0;
	IIC_RegReadN(OUT_Z_MSB_REG, 2, z_buf);	
	IIC_RegReadN(OUT_X_MSB_REG, 2, x_buf);
	IIC_RegReadN(OUT_Y_MSB_REG, 2, y_buf);

//	temp  = ((z_buf[0]<<8) | z_buf[1]) >> 2; 
	z_temp  = ((z_buf[0]<<8) | z_buf[1]);
	x_temp  = ((x_buf[0]<<8) | x_buf[1]); 
	y_temp  = ((y_buf[0]<<8) | y_buf[1]);


	if(xyz_pars.auto_sel == 1)
	{
	 if(!start_stop)
	 {
	 if(((z_temp&0x8000)|((z_temp&0x7fff)>>2))< xyz_pars.auto_start_za*0.9);
	 start_stop = 1;
	 return;
	 }else{
	 if(((z_temp&0x8000)|((z_temp&0x7fff)>>2))< xyz_pars.auto_stop_za*0.9);
	 return;
	 }	
	}

	if(Z_acc.got_acc_num-Z_acc.used_acc_num >= MMA845X_Z_ACC_BUF)
	{
		return;
	}else{
		Z_acc.acc_buf[Z_acc.got_acc_num & (MMA845X_Z_ACC_BUF-1)] = z_temp;
		Z_acc.got_acc_num++;
	}
	resutl_caculate(z_temp,3);


	if(X_acc.got_acc_num-X_acc.used_acc_num >= MMA845X_X_ACC_BUF)
	{
		return;
	}else{
	X_acc.acc_buf[X_acc.got_acc_num & (MMA845X_X_ACC_BUF-1)] = x_temp;
	X_acc.got_acc_num++;
	}
	resutl_caculate(x_temp,1);


	if(Y_acc.got_acc_num-Y_acc.used_acc_num >= MMA845X_Y_ACC_BUF)
	{
		return;
	}else{
		Y_acc.acc_buf[Y_acc.got_acc_num & (MMA845X_Y_ACC_BUF-1)] = y_temp;
		Y_acc.got_acc_num++;
	}
	resutl_caculate(y_temp,2);
	
}

/*****************************************************************************
 �� �� ��  : delay_asm
 ��������  : ���ʵ�־�ȷ��ʱ��һ��ѭ����Ҫ6��ʱ������, ��һ��12-24����
                ϵͳʱ��72MHz--- 0.5us	----> i = 6
 �������  : int i  --> ��ʱѭ������
 �������  : ��
 �� �� ֵ  : 
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2012��10��5��
    ��    ��   : ganjinming 
    �޸�����   : �����ɺ���

*****************************************************************************/
__asm void  delay_asm1(int i)
{
	subs    r0, #1   
    bne     delay_asm1
    bx      lr
} 

/*****************************************************************************
 �� �� ��  : IIC_Start
 ��������  : IIC�����ź�
 �������  : void  
 �������  : ��
 �� �� ֵ  : 
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2012��10��5��
    ��    ��   : ganjinming
    �޸�����   : �����ɺ���

*****************************************************************************/
void IIC_Start (void)
{
	IIC_SDA=HIGH;
	IIC_SCL=HIGH;
	delay_asm1(6*2);
	IIC_SDA=LOW;
	delay_asm1(6*2);
	IIC_SCL=LOW;
	delay_asm1(6);
	
}
/*****************************************************************************
 �� �� ��  : IIC_Stop
 ��������  : IIC�����ź�
 �������  : void  
 �������  : ��
 �� �� ֵ  : 
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2012��10��5��
    ��    ��   : ganjinming
    �޸�����   : �����ɺ���

*****************************************************************************/
void IIC_Stop (void)
{
	IIC_SDA=LOW;
	IIC_SCL=LOW;
	delay_asm1(6*2);
	IIC_SCL=HIGH;
	delay_asm1(6*2);
	IIC_SDA=HIGH;
	delay_asm1(6*4);
}

/*****************************************************************************
 �� �� ��  : IIC_WriteByte
 ��������  : IICд��һ���ֽ�
 �������  : u8 txByte--> ��д����ֽ�
 �������  : ��
 �� �� ֵ  : 
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2012��10��5��
    ��    ��   : ganjinming
    �޸�����   : �����ɺ���

*****************************************************************************/
u8 IIC_WriteByte (u8 txByte)
{
    u8 mask,erro=0;
    for (mask=0x80; mask>0; mask>>=1) 
    { 
	    if ((mask & txByte) == 0) IIC_SDA=LOW;
		else IIC_SDA=HIGH;
		delay_asm1(6);
		IIC_SCL=HIGH; 
		delay_asm1(6*3);
		IIC_SCL=LOW;
		delay_asm1(6*3);
    }
    IIC_SDA=HIGH; //release SDA-line
    IIC_SCL=HIGH; //clk #9 for ack
    delay_asm1(6*3);
	if(READ_SDA==HIGH) erro=ACK_ERROR;
    IIC_SCL=LOW;
	delay_asm1(6*3);
    return erro; //return error code
}

/*****************************************************************************
 �� �� ��  : IIC_ReadByte
 ��������  : IIC��ȡһ���ֽ�
 �������  : etI2cAck ack  ACK������Ӧ�ӻ� NO_ACK ��������Ӧ�ӻ�
 �������  : ��
 �� �� ֵ  : 
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2012��10��5��
    ��    ��   : ganjinming
    �޸�����   : �����ɺ���

*****************************************************************************/
u8 IIC_ReadByte (etI2cAck ack)
{
	u8 mask,rxByte=0;
	IIC_SDA=HIGH; 
	delay_asm1(6);
	for (mask=0x80; mask>0; mask>>=1) 
	{ 
	    IIC_SCL=HIGH; //start clock on SCL-line
		delay_asm1(6*3);
		if(READ_SDA==1) rxByte=(rxByte | mask); 
		IIC_SCL=LOW;
		delay_asm1(6*3);
	}
	IIC_SDA=ack; 
	delay_asm1(6);
	IIC_SCL=HIGH; //clk #9 for ack
	delay_asm1(6*3);
	IIC_SCL=LOW;
	IIC_SDA=HIGH;
	delay_asm1(6*3);
	return rxByte; 
}

/*****************************************************************************
 �� �� ��  : IIC_RegWrite
 ��������  : ����MM845x��һ���Ĵ���
 �������  : u8 device_add  -->MMA845x�ĵ�ַ
             u8 reg         --> MMA8445x�ļĴ�����ַ
             u8 val         --> д����Ӧ�Ĵ�����ֵ
 �������  : ��
 �� �� ֵ  : 
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2012��10��5��
    ��    ��   : ganjinming
    �޸�����   : �����ɺ���

*****************************************************************************/
void IIC_RegWrite(u8 reg,u8 val)
{
  IIC_Start();                                  
  IIC_WriteByte(MMA845X_ADD);                      
  IIC_WriteByte(reg);                         
  IIC_WriteByte(val);                         
  IIC_Stop();                               
}

/*****************************************************************************
 �� �� ��  : IIC_RegRead
 ��������  : ��ȡMMA845x��һ���Ĵ�����ֵ
 �������  : u8 reg         -->MMA8445x�ļĴ�����ַ
 �������  : ��
 �� �� ֵ  : ��ȡ�ļĴ�����ֵ
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2012��10��5��
    ��    ��   : ganjinming
    �޸�����   : �����ɺ���

*****************************************************************************/
u8 IIC_RegRead(u8 reg)
{
  u8 b;
  IIC_Start();                                  
  IIC_WriteByte(MMA845X_ADD);                 
  IIC_WriteByte(reg);                        
  IIC_Start();                           
  IIC_WriteByte(MMA845X_ADD+1);                    
  b = IIC_ReadByte(NO_ACK);                                                
  IIC_Stop();                                 
  return b;
}


/*****************************************************************************
 �� �� ��  : IIC_RegWriteN
 ��������  : ����д��MMA845x�Ķ���Ĵ���
 �������  : u8 reg1        -->Ҫд�����ʼ�ļĴ�����ַ
             u8 N           -->Ҫд��ļĴ�������
             u8 *array      -->д��Ĵ���ֵ�洢λ��
 �������  : ��
 �� �� ֵ  : 
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2012��10��5��
    ��    ��   : ganjinming
    �޸�����   : �����ɺ���

*****************************************************************************/
void IIC_RegWriteN(u8 reg1,u8 N,u8 *array)
{                              
  IIC_Start();                                 
  IIC_WriteByte(MMA845X_ADD);                      
  IIC_WriteByte(reg1);                     
  while (N>0)                               
  {
    IIC_WriteByte(*array);
    array++;
    N--;
  }
  IIC_Stop();                                
}


/*****************************************************************************
 �� �� ��  : IIC_RegReadN
 ��������  : ������ȡMMA845x�Ķ���Ĵ�����ֵ
 �������  : u8 reg1        -->Ҫ����ʼ�ļĴ�����ַ
             u8 N           -->Ҫ����ʼ�ļĴ�������
             u8 *array      -->��ȡ�ļĴ���ֵ�洢λ��
 �������  : ��
 �� �� ֵ  : 
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2012��10��5��
    ��    ��   : ganjinming
    �޸�����   : �����ɺ���

*****************************************************************************/
void IIC_RegReadN(u8 reg1, u8 N, u8 *array)
{
  u8 b;
  IIC_Start();                                  
  IIC_WriteByte(MMA845X_ADD);                      
  IIC_WriteByte(reg1);                        
  IIC_Start();                           
  IIC_WriteByte(MMA845X_ADD+1);                    
  //b = IIC_ReadByte(ACK);                        
  while (N>1)                                   
  {
    b = IIC_ReadByte(ACK);
    *array = b;
    array++;
    N--;
  }
  b = IIC_ReadByte(NO_ACK);
  *array = b;                                   
  IIC_Stop();                                
}


/*****************************************************************************
 �� �� ��  : MMA845x_Active
 ��������  : ����MMA845x
 �������  : ��
 �������  : ��
 �� �� ֵ  : 
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2012��10��5��
    ��    ��   : ganjinming
    �޸�����   : �����ɺ���

*****************************************************************************/
void MMA845x_Active ()
{
  IIC_RegWrite(CTRL_REG1, (IIC_RegRead(CTRL_REG1) | ACTIVE_MASK));
}


/*****************************************************************************
 �� �� ��  : MMA845x_Standby
 ��������  : ʹMMA845x���ڴ���״̬
 �������  : void  
 �������  : ��
 �� �� ֵ  : 
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2012��10��5��
    ��    ��   : ganjinming
    �޸�����   : �����ɺ���

*****************************************************************************/
void MMA845x_Standby (void)
{
	uint32_t n;
	n= IIC_RegRead(WHO_AM_I_REG);
	n = IIC_RegRead(CTRL_REG1);
 	IIC_RegWrite(CTRL_REG1, n & ~ACTIVE_MASK);
    
}


/*****************************************************************************
 �� �� ��  : MMA845x_Init
 ��������  : MMA845x��ʼ��
 �������  : void  
 �������  : ��
 �� �� ֵ  : 
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2012��10��5��
    ��    ��   : ganjinming
    �޸�����   : �����ɺ���

*****************************************************************************/
void MMA845x_Init (void)
{

	MMA845x_Standby();
	 /*
	**  Configure sensor for:
	**    - Sleep Mode Poll Rate of 50Hz (20ms)
	**    - System Output Data Rate of 200Hz (5ms)
	**    - Full Scale of +/-2g
	*/
	IIC_RegWrite(CTRL_REG1, ASLP_RATE_20MS+DATA_RATE);
	IIC_RegWrite(XYZ_DATA_CFG_REG, FULL_SCALE);

	MMA845x_Active ();  
}


int IIC_RegReadZ(uint8_t *buf)
{
    int xyz_status;
	xyz_status = IIC_RegRead(STATUS_00_REG);

    if(xyz_status & ZDR_MASK)
	{
		IIC_RegReadN(OUT_Z_MSB_REG, 2, buf);
		return true;
	}
/*	else if	 (xyz_status & ZOW_MASK)
	{
	    
		return false;
	} */
	else 
	{
		return false;
	}
}
/*****************************************************************************
 �� �� ��  : IIC_RegReadXYZ_or
 ��������  : ��ȡxyz����һ���������
 �������  : uint32_t Out_xyz_msb_Reg   x-y-z���Ӧ�ļĴ���
             uint8_t *buf               --��ȡ���ݴ��λ��
 �������  : ��
 �� �� ֵ  : 
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2012��10��5��
    ��    ��   : ganjinming
    �޸�����   : �����ɺ���

*****************************************************************************/
int IIC_RegReadXYZ_or(uint32_t Out_xyz_msb_Reg,uint8_t *buf)
{
    int xyz_status;
	xyz_status = IIC_RegRead(STATUS_00_REG);

	if(Out_xyz_msb_Reg == OUT_Z_MSB_REG)
	{
		xyz_status &= ZDR_MASK;	
	}
	else if (Out_xyz_msb_Reg == OUT_Y_MSB_REG)
	{
		xyz_status &= YDR_MASK;
	}
	else if (Out_xyz_msb_Reg == OUT_X_MSB_REG)
	{
		xyz_status &= XDR_MASK;
	}
	else
	{
		  return false;
	}

    if(xyz_status)
	{
		IIC_RegReadN(Out_xyz_msb_Reg, 2, buf);
		return true;
	}
	else
	{
		return false;
	}

}
/*****************************************************************************
 �� �� ��  : IIC_RegReadXYZ_and
 ��������  : ��ȡXYZ���������
 �������  : uint8_t *buf  --����ȡ���ݴ��λ��
 �������  : ��
 �� �� ֵ  : true :��ȡ���ݳɹ�
             false:��ȡ����ʧ��(û������������)
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2012��10��5��
    ��    ��   : ganjinming
    �޸�����   : �����ɺ���

*****************************************************************************/
bool IIC_RegReadXYZ_and(uint8_t *buf)
{
	unsigned int xyz_status;
	xyz_status = IIC_RegRead(STATUS_00_REG);

    if(xyz_status & ZYXDR_MASK)
	{
		IIC_RegReadN(OUT_X_MSB_REG,6, buf);
		return true;
	}
	else
	{
		return false;	
	}
}


#endif

// x - 1 y - 2 z - 3
void resutl_caculate(signed short data,int xyz)
{
	unsigned short abs_data;
	float get_acc;
	float v_z;

	unsigned short in;

	WM_MESSAGE * pMsg;

	static long current_count;

	abs_data = abs(data);

	if(xyz == 3)
	{
	   if(data >= 0)
	   {
			if(data > Z_acc.acc_max)
			{
		    Z_acc.acc_max = data;
	        Z_acc.acc_ave_add += data;
		    Z_acc.acc_time++;
			}
	   }else{
			if(data < Z_acc.dec_max)
			{
			Z_acc.dec_max = data;
			Z_acc.dec_ave_add += data;
			Z_acc.dec_time++;
			}
	   }
	   if(abs_data > Z_acc.acc_dec_abs_max)
	   {
			Z_acc.acc_dec_abs_max = abs_data;
	   }

	if(xyz_pars.auto_sel)
	{
	   get_acc = GET_ACC(Z_acc.acc_ave_add + Z_acc.dec_ave_add);

	   v_z = get_acc*(Z_acc.acc_time + Z_acc.dec_time -1);// >>2 

	   if(v_z > Z_acc.v_max)
	   {
		   Z_acc.v_max = v_z;
	   }else{
		   if(v_z <= (Z_acc.v_max/2)&&(( Z_acc.dec_time + Z_acc.acc_time)> 50))
		   {
				if(v_z <= STOP_START_SPEED_END)
				{
					if(current_count == 0)
					{
						current_count = Z_acc.acc_time + Z_acc.dec_time - 1;
					}
					if((Z_acc.acc_time + Z_acc.dec_time - 1 - current_count)>= STOP_GET_TIMES)
					{
						OnButtonStopClicked(pMsg);
					}
				}
		   }
	   }
	}

	}else if(xyz == 2){
	   if(abs_data > Y_acc.acc_dec_abs_max)
	   {
			Y_acc.acc_dec_abs_max = abs_data;
	   }
	}else if(xyz == 1){
	   if(abs_data > X_acc.acc_dec_abs_max)
	   {
			X_acc.acc_dec_abs_max = abs_data;
	   }
	}


}




void Data_Sim(unsigned lenth)
 {
	static short temp;
	int i;
	char z_buf[2];
	char x_buf[2];
	char y_buf[2];
	static int z_data_cnt =0;

	for(i=0;i<lenth;i++)
	{
		z_buf[0] = rand();
		z_buf[1] = rand();
		z_buf[1] = z_buf[1]&0x0fc;

		temp  = ((z_buf[0]<<8) | z_buf[1]) ;

		resutl_caculate(temp,3);

		if(Z_acc.got_acc_num-Z_acc.used_acc_num >= MMA845X_Z_ACC_BUF)
		{
		break;
		}
		Z_acc.acc_buf[Z_acc.got_acc_num & (MMA845X_Z_ACC_BUF-1)] =  temp;	
	
		Z_acc.got_acc_num++;
	}
	

	for(i=0;i<lenth;i++)
	{
	x_buf[0] = rand();
	x_buf[1] = rand();
	x_buf[1] = x_buf[1]&0x0fc;

	temp  = ((x_buf[0]<<8) | x_buf[1]) ;

	resutl_caculate(temp,1);

	if(X_acc.got_acc_num-X_acc.used_acc_num >= MMA845X_X_ACC_BUF)
	{
		break;
	}
	X_acc.acc_buf[X_acc.got_acc_num & (MMA845X_X_ACC_BUF-1)] =  temp;	
	
	X_acc.got_acc_num++;
	}

	for(i=0;i<lenth;i++)
	{
	y_buf[0] = rand();
	y_buf[1] = rand();
	y_buf[1] = y_buf[1]&0x0fc;


	temp  = ((y_buf[0]<<8) | y_buf[1]); 

	resutl_caculate(temp,2);

	if(Y_acc.got_acc_num-Y_acc.used_acc_num >= MMA845X_Y_ACC_BUF)
	{
		break;
	}
	Y_acc.acc_buf[Y_acc.got_acc_num & (MMA845X_Y_ACC_BUF-1)] =  temp;	
	
	Y_acc.got_acc_num++;
	}

}


void test_resutl_caculate()
{
	static signed short i;

	i++;
	if(i == 5000)
	i = 0;

	resutl_caculate(i,3);

}



