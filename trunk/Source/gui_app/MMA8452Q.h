/******************************************************************************

                  版权所有 (C), 2012-2022, 浙大精益

 ******************************************************************************
  文 件 名   : MMA845x.H
  版 本 号   : 初稿
  作    者   : ganjinming
  生成日期   : 2012年10月5日
  最近修改   :
  功能描述   : MMA845x.c的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2012年10月5日
    作    者   : ganjinming
    修改内容   : 创建文件

******************************************************************************/

#ifndef _MMA845X_H_
#define _MMA845X_H_

/*----------------------------------------------*
 * 包含头文件                                   *
 *----------------------------------------------*/
#include "gui_app.h"
#ifndef WIN_SIM
#include "stm32_dsp.h"
#endif
#include "Draw.h"
#include <string.h> 

/*----------------------------------------------*
 * 宏定义                                       *
 *----------------------------------------------*/
#define BASE_SIZE    63
#define MMA845X_Z_DEFAULT   4096
#define MMA845X_XYZ_ACC_BUF 1024
#define MMA845X_Z_ACC_BUF   1024
#define MMA845X_X_ACC_BUF   1024
#define MMA845X_Y_ACC_BUF   1024

typedef enum
{
    ACK_ERROR = 0x01,
    TIME_OUT_ERROR = 0x02,
    CHECKSUM_ERROR = 0x04,
    UNIT_ERROR = 0x08
}etError;

typedef enum
{
	LOW = 0,
	HIGH = 1,
}etI2cLevel;


typedef enum
{
	ACK = 0,
	NO_ACK = 1,
}etI2cAck;


typedef enum
{
	true  = 1,
	false = 0,
}bool;


typedef  struct 
{
	unsigned int got_acc_num;
	unsigned int used_acc_num;
	signed short acc_buf[MMA845X_Z_ACC_BUF];
	signed short acc_max;
	signed short acc_ave_add;
	unsigned long acc_time;

	signed short dec_max;
	signed short dec_ave_add;
	unsigned long dec_time;

	unsigned int acc_dec_abs_max;

	unsigned int acc_x_pose;
	unsigned int acc_y_pose;

}MMA845X_struct;



extern MMA845X_struct Z_acc;
extern MMA845X_struct X_acc;
extern MMA845X_struct Y_acc;

extern 

#ifndef WIN_SIM


/*----------------------------------------------*
 * 外部变量说明                                 *
 *----------------------------------------------*/

/*----------------------------------------------*
 * 外部函数原型说明                             *
 *----------------------------------------------*/
void MMA845x_interrupt(void);
char get_from_fifo(	short* fifo_buf,short* out_buf,int lenth);
char put_head(short* in_buf, short* base_buf);
//void MMA845x_Init(void);
//void MMA845x_Standby(void);
//void MMA845x_Active(void);
void IIC_RegWrite(u8 reg,u8 val);
extern u8 IIC_RegRead(u8 reg);
void IIC_RegWriteN(u8 reg1,u8 N,u8 *array);
void IIC_RegReadN(u8 reg1, u8 N, u8 *array);
void MMA845x_Init (void);
bool IIC_RegReadXYZ_and(uint8_t *buf);
int IIC_RegReadZ(uint8_t *buf);
void resutl_caculate(signed short data,int xyz);
/*----------------------------------------------*
 * 内部函数原型说明                             *
 *----------------------------------------------*/

/*----------------------------------------------*
 * 全局变量                                     *
 *----------------------------------------------*/

/*----------------------------------------------*
 * 模块级变量                                   *
 *----------------------------------------------*/

/*----------------------------------------------*
 * 常量定义                                     *
 *----------------------------------------------*/


/*
**
**  MMA845xQ Sensor Internal Registers
*/
enum
{
  MMA845x_STATUS_00 = 0,          // 0x00
  MMA845x_OUT_X_MSB,              // 0x01
  MMA845x_OUT_X_LSB,              // 0x02
  MMA845x_OUT_Y_MSB,              // 0x03
  MMA845x_OUT_Y_LSB,              // 0x04
  MMA845x_OUT_Z_MSB,              // 0x05
  MMA845x_OUT_Z_LSB,              // 0x06
  MMA845x_F_STATUS,               // 0x08
  MMA845x_F_SETUP,                // 0x09
  MMA845x_TRIG_CFG,               // 0x0A
  MMA845x_SYSMOD,                 // 0x0B
  MMA845x_INT_SOURCE,             // 0x0C
  MMA845x_WHO_AM_I,               // 0x0D
  MMA845x_XYZ_DATA_CFG,           // 0x0E
  MMA845x_HP_FILTER_CUTOFF,       // 0x0F
  MMA845x_PL_STATUS,              // 0x10
  MMA845x_PL_CFG,                 // 0x11
  MMA845x_PL_COUNT,               // 0x12
  MMA845x_PL_BF_ZCOMP,            // 0x13
  MMA845x_PL_P_L_THS_REG,         // 0x14
  MMA845x_FF_MT_CFG,              // 0x15
  MMA845x_FF_MT_SRC,              // 0x16
  MMA845x_FF_MT_THS,              // 0x17
  MMA845x_FF_MT_COUNT,            // 0x18
  MMA845x_TRANSIENT_CFG,          // 0x1D
  MMA845x_TRANSIENT_SRC,          // 0x1E
  MMA845x_TRANSIENT_THS,          // 0x1F
  MMA845x_TRANSIENT_COUNT,        // 0x20
  MMA845x_PULSE_CFG,              // 0x21
  MMA845x_PULSE_SRC,              // 0x22
  MMA845x_PULSE_THSX,             // 0x23
  MMA845x_PULSE_THSY,             // 0x24
  MMA845x_PULSE_THSZ,             // 0x25
  MMA845x_PULSE_TMLT,             // 0x26
  MMA845x_PULSE_LTCY,             // 0x27
  MMA845x_PULSE_WIND,             // 0x28
  MMA845x_ASLP_COUNT,             // 0x29
  MMA845x_CTRL_REG1,              // 0x2A
  MMA845x_CTRL_REG2,              // 0x2B
  MMA845x_CTRL_REG3,              // 0x2C
  MMA845x_CTRL_REG4,              // 0x2D
  MMA845x_CTRL_REG5,              // 0x2E
  MMA845x_OFF_X,                  // 0x2F
  MMA845x_OFF_Y,                  // 0x30
  MMA845x_OFF_Z                   // 0x31
 
};

/*
**  STATUS Registers
*/
#define STATUS_00_REG         0x00
//
#define ZYXOW_MASK            0x80
#define ZOW_MASK              0x40
#define YOR_MASK              0x20
#define XOR_MASK              0x10
#define ZYXDR_MASK            0x08
#define ZDR_MASK              0x04
#define YDR_MASK              0x02
#define XDR_MASK              0x01

/*
**  XYZ Data Registers
*/
#define OUT_X_MSB_REG         0x01
#define OUT_X_LSB_REG         0x02
#define OUT_Y_MSB_REG         0x03
#define OUT_Y_LSB_REG         0x04
#define OUT_Z_MSB_REG         0x05
#define OUT_Z_LSB_REG         0x06


/*
**  WHO_AM_I Device ID Register
*/
#define WHO_AM_I_REG          0x0D
#define MMA8451Q_ID           0x1A
#define MMA8452Q_ID           0x2A
#define MMA8453Q_ID           0x3A

/*
**  F_STATUS FIFO Status Register
*/
#define F_STATUS_REG          0x00
//
#define F_OVF_MASK            0x80
#define F_WMRK_FLAG_MASK      0x40
#define F_CNT5_MASK           0x20
#define F_CNT4_MASK           0x10
#define F_CNT3_MASK           0x08
#define F_CNT2_MASK           0x04
#define F_CNT1_MASK           0x02
#define F_CNT0_MASK           0x01
#define F_CNT_MASK            0x3F

/*
**  F_SETUP FIFO Setup Register
*/
#define F_SETUP_REG           0x09
//
#define F_MODE1_MASK          0x80
#define F_MODE0_MASK          0x40
#define F_WMRK5_MASK          0x20
#define F_WMRK4_MASK          0x10
#define F_WMRK3_MASK          0x08
#define F_WMRK2_MASK          0x04
#define F_WMRK1_MASK          0x02
#define F_WMRK0_MASK          0x01
#define F_MODE_MASK           0xC0
#define F_WMRK_MASK           0x3F


/*
** TRIG CFG Register
*/

#define TRIG_CFG_REG        0x0A
//
#define TRIG_TRANS_MASK     0x20
#define TRIG_LNDPRT_MASK    0x10
#define TRIG_PULSE_MASK     0x08
#define TRIG_FF_MT_MASK     0x04

/*
**  SYSMOD System Mode Register
*/
#define SYSMOD_REG            0x0B
//
#define FGERR_MASK            0x80
#define FGT_4MASK             0x40
#define FGT_3MASK             0x20
#define FGT_2MASK             0x10
#define FGT_1MASK             0x08
#define FGT_0MASK             0x04
#define FGT_MASK              0x7C
#define SYSMOD1_MASK          0x02
#define SYSMOD0_MASK          0x01
#define SYSMOD_MASK           0x03

/*
**  INT_SOURCE System Interrupt Status Register
*/
#define INT_SOURCE_REG        0x0C
//
#define SRC_ASLP_MASK         0x80
#define SRC_FIFO_MASK         0x40
#define SRC_TRANS_MASK        0x20
#define SRC_LNDPRT_MASK       0x10
#define SRC_PULSE_MASK        0x08
#define SRC_FF_MT_1_MASK      0x04
#define SRC_FF_MT_2_MASK      0x02
#define SRC_DRDY_MASK         0x01

/*
**  XYZ_DATA_CFG Sensor Data Configuration Register
*/
#define XYZ_DATA_CFG_REG      0x0E
//
#define HPF_OUT_MASK          0x10
#define FS1_MASK              0x02
#define FS0_MASK              0x01
#define FS_MASK               0x03

#define FULL_SCALE_8G         FS1_MASK
#define FULL_SCALE_4G         FS0_MASK
#define FULL_SCALE_2G         0x00

/*
**  HP_FILTER_CUTOFF High Pass Filter Register
*/
#define HP_FILTER_CUTOFF_REG  0x0F
//
#define PULSE_HPF_BYP_MASK    0x20
#define PULSE_LPF_EN_MASK     0x10
#define SEL1_MASK             0x02
#define SEL0_MASK             0x01
#define SEL_MASK              0x03

/*
**  PL_STATUS Portrait/Landscape Status Register
**  PL_PRE_STATUS Portrait/Landscape Previous Data Status Register
*/
#define PL_STATUS_REG         0x10
//
#define NEWLP_MASK            0x80
#define LO_MASK               0x40
#define LAPO1_MASK            0x04
#define LAPO0_MASK            0x02
#define LAPO_MASK             0x06
#define BAFRO_MASK            0x01


/*
**  PL_CFG Portrait/Landscape Configuration Register
*/
#define PL_CFG_REG            0x11
//
#define DBCNTM_MASK           0x80
#define PL_EN_MASK            0x40

/*
**  PL_COUNT Portrait/Landscape Debounce Register
*/
#define PL_COUNT_REG          0x12

/*
**  PL_BF_ZCOMP Back/Front and Z Compensation Register
*/
#define PL_BF_ZCOMP_REG       0x13
//
#define BKFR1_MASK            0x80
#define BKFR0_MASK            0x40
#define ZLOCK2_MASK           0x04
#define ZLOCK1_MASK           0x02
#define ZLOCK0_MASK           0x01
#define BKFR_MASK             0xC0
#define ZLOCK_MASK            0x07

/*
**  PL_P_L_THS Portrait to Landscape Threshold Registers
*/
#define PL_P_L_THS_REG        0x14
//
#define P_L_THS4_MASK         0x80
#define P_L_THS3_MASK         0x40
#define P_L_THS2_MASK         0x20
#define P_L_THS1_MASK         0x10
#define P_L_THS0_MASK         0x08
#define P_L_THS_MASK          0xF8
#define HYS2_MASK             0x04
#define HYS1_MASK             0x02
#define HYS0_MASK             0x01
#define HYS_MASK              0x07

  
/*
**  FF_MT_CFG Freefall and Motion Configuration Registers
*/
#define FF_MT_CFG_1_REG       0x15
#define FF_MT_CFG_2_REG       0x19
//
#define ELE_MASK              0x80
#define OAE_MASK              0x40
#define ZEFE_MASK             0x20
#define YEFE_MASK             0x10
#define XEFE_MASK             0x08

/*
**  FF_MT_SRC Freefall and Motion Source Registers
*/
#define FF_MT_SRC_1_REG       0x16
#define FF_MT_SRC_2_REG       0x1A

//
#define EA_MASK               0x80
#define ZHE_MASK              0x20
#define ZHP_MASK              0x10
#define YHE_MASK              0x08
#define YHP_MASK              0x04
#define XHE_MASK              0x02
#define XHP_MASK              0x01

/*
**  FF_MT_THS Freefall and Motion Threshold Registers
**  TRANSIENT_THS Transient Threshold Register
*/
#define FT_MT_THS_1_REG       0x17
#define FT_MT_THS_2_REG       0x1B
#define TRANSIENT_THS_REG     0x1F

//
#define DBCNTM_MASK           0x80
#define THS6_MASK             0x40
#define THS5_MASK             0x20
#define THS4_MASK             0x10
#define THS3_MASK             0x08
#define THS2_MASK             0x04
#define TXS1_MASK             0x02
#define THS0_MASK             0x01
#define THS_MASK              0x7F

/*
**  FF_MT_COUNT Freefall Motion Count Registers
*/
#define FF_MT_COUNT_1_REG     0x18
#define FF_MT_COUNT_2_REG     0x1C

/*
**  TRANSIENT_CFG Transient Configuration Register
*/
#define TRANSIENT_CFG_REG     0x1D
//
#define TELE_MASK             0x10
#define ZTEFE_MASK            0x08
#define YTEFE_MASK            0x04
#define XTEFE_MASK            0x02
#define HPF_BYP_MASK          0x01

/*
**  TRANSIENT_SRC Transient Source Register
*/
#define TRANSIENT_SRC_REG     0x1E


//
#define TEA_MASK              0x40
#define ZTRANSE_MASK          0x20
#define ZTRANSEPOL_MASK       0x10
#define YTRANSE_MASK          0x08
#define YTRANSEPOL_MASK       0x04
#define XTRANSE_MASK          0x02
#define XTRANSEPOL_MASK       0x01

/*
**  TRANSIENT_COUNT Transient Debounce Register
*/
#define TRANSIENT_COUNT_REG   0x20

/*
**  PULSE_CFG Pulse Configuration Register
*/
#define PULSE_CFG_REG         0x21

//
#define DPA_MASK              0x80
#define PELE_MASK             0x40
#define ZDPEFE_MASK           0x20
#define ZSPEFE_MASK           0x10
#define YDPEFE_MASK           0x08
#define YSPEFE_MASK           0x04
#define XDPEFE_MASK           0x02
#define XSPEFE_MASK           0x01

/*
**  PULSE_SRC Pulse Source Register
*/
#define PULSE_SRC_REG         0x22

//
#define PEA_MASK              0x80
#define PAXZ_MASK             0x40
#define PAXY_MASK             0x20
#define PAXX_MASK             0x10
#define PDPE_MASK             0x08
#define POLZ_MASK             0x04
#define POLY_MASK             0x02
#define POLX_MASK             0x01

/*
**  PULSE_THS XYZ Pulse Threshold Registers
*/
#define PULSE_THSX_REG        0x23
#define PULSE_THSY_REG        0x24
#define PULSE_THSZ_REG        0x25
//
#define PTHS_MASK             0x7F

/*
**  PULSE_TMLT Pulse Time Window Register
*/
#define PULSE_TMLT_REG        0x26

/*
**  PULSE_LTCY Pulse Latency Timer Register
*/
#define PULSE_LTCY_REG        0x27

/*
**  PULSE_WIND Second Pulse Time Window Register
*/
#define PULSE_WIND_REG        0x28

/*
**  ASLP_COUNT Auto Sleep Inactivity Timer Register
*/
#define ASLP_COUNT_REG        0x29

/*
**  CTRL_REG1 System Control 1 Register
*/
#define CTRL_REG1             0x2A
//
#define ASLP_RATE1_MASK       0x80
#define ASLP_RATE0_MASK       0x40
#define DR2_MASK              0x20
#define DR1_MASK              0x10
#define DR0_MASK              0x08
#define LNOISE_MASK           0x04
#define FREAD_MASK            0x02
#define ACTIVE_MASK           0x01
#define ASLP_RATE_MASK        0xC0
#define DR_MASK               0x38
//                      
#define ASLP_RATE_20MS        0x00
#define ASLP_RATE_80MS        ASLP_RATE0_MASK
#define ASLP_RATE_160MS       ASLP_RATE1_MASK
#define ASLP_RATE_640MS       ASLP_RATE1_MASK+ASLP_RATE0_MASK
//
#define DATA_RATE_1250US      0x00
#define DATA_RATE_2500US      DR0_MASK
#define DATA_RATE_5MS         DR1_MASK
#define DATA_RATE_10MS        DR1_MASK+DR0_MASK
#define DATA_RATE_20MS        DR2_MASK
#define DATA_RATE_80MS        DR2_MASK+DR0_MASK
#define DATA_RATE_160MS       DR2_MASK+DR1_MASK
#define DATA_RATE_640MS       DR2_MASK+DR1_MASK+DR0_MASK

/*
**  CTRL_REG2 System Control 2 Register
*/
#define CTRL_REG2             0x2B
//
#define ST_MASK               0x80
#define BOOT_MASK             0x40
#define SMODS1_MASK           0x20
#define SMODS0_MASK           0x10
#define SLPE_MASK             0x04
#define MODS1_MASK            0x02
#define MODS0_MASK            0x01
#define SMODS_MASK            0x18
#define MODS_MASK             0x03

/*
**  CTRL_REG3 Interrupt Control Register
*/
#define CTRL_REG3             0x2C
//
#define FIFO_GATE_MASK        0x80
#define WAKE_TRANS_MASK       0x40
#define WAKE_LNDPRT_MASK      0x20
#define WAKE_PULSE_MASK       0x10
#define WAKE_FF_MT_1_MASK     0x08
#define WAKE_FF_MT_2_MASK     0x04
#define IPOL_MASK             0x02
#define PP_OD_MASK            0x01

/*
**  CTRL_REG4 Interrupt Enable Register
*/
#define CTRL_REG4             0x2D
//
#define INT_EN_ASLP_MASK      0x80
#define INT_EN_FIFO_MASK      0x40
#define INT_EN_TRANS_MASK     0x20
#define INT_EN_LNDPRT_MASK    0x10
#define INT_EN_PULSE_MASK     0x08
#define INT_EN_FF_MT_1_MASK   0x04
#define INT_EN_FF_MT_2_MASK   0x02
#define INT_EN_DRDY_MASK      0x01

/*
**  CTRL_REG5 Interrupt Configuration Register
*/
#define CTRL_REG5             0x2E
//
#define INT_CFG_ASLP_MASK     0x80
#define INT_CFG_FIFO_MASK     0x40
#define INT_CFG_TRANS_MASK    0x20
#define INT_CFG_LNDPRT_MASK   0x10
#define INT_CFG_PULSE_MASK    0x08
#define INT_CFG_FF_MT_1_MASK  0x04
#define INT_CFG_FF_MT_2_MASK  0x02
#define INT_CFG_DRDY_MASK     0x01

/*
**  XYZ Offset Correction Registers
*/
#define OFF_X_REG             0x2F
#define OFF_Y_REG             0x30
#define OFF_Z_REG             0x31


#define FRAC_2d1 5000
#define FRAC_2d2 2500
#define FRAC_2d3 1250
#define FRAC_2d4 625
#define FRAC_2d5 313
#define FRAC_2d6 156
#define FRAC_2d7 78
#define FRAC_2d8 39
#define FRAC_2d9 20
#define FRAC_2d10 10
#define FRAC_2d11 5
#define FRAC_2d12 2

/**************
*根据系统需要配置
**/

#define SA0   0		   //MMA845x地址

#if  (SA0 == 0)
#define MMA845X_ADD   0x38
#else
#define MMA845X_ADD   0x3a
#endif

#define FULL_SCALE			      FULL_SCALE_2G	    //测量范围 2G(+-2g) 4G(+-4g) 8G(+-8g)
#define DATA_RATE				  DATA_RATE_1250US     //测量数据生成速率 200Hz--(5ms)可选项 1250US  2500US 5MS 10MS 20MS 40MS 80MS 160MS 640MS

#define IIC_SDA         PBout(7) 
#define READ_SDA 		PBin(7) 
#define IIC_SCL 		PBout(6)


#endif  /* _MMA845X_H_ */

void Data_Sim(unsigned lenth);

#endif