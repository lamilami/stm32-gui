#ifndef __AD54XX_H
#define __AD54XX_H


#define RXEN    1
#define OUTEN   1

#define SREN    0
#define DCEN    0

#define ADDR_NOP  0
#define ADDR_DATA 1
#define ADDR_READ_BACK_REG 2
#define ADDR_CONTROL_REG 0x55
#define ADDR_RES  0x56

#define READ_ADD_DEC_STATUS 0
#define READ_ADD_DEC_DATA_REG 1
#define READ_ADD_DEC_CONTROL_REG 2

#define OUT_PUT_4_20MA 5
#define OUT_PUT_0_20MA 6
#define OUT_PUT_0_24MA 7

#define R1R2R3_4_20MA 5
#define R1R2R3_0_20MA 6
#define R1R2R3_0_24MA 7


typedef enum {
	 SR_257730 = 0 ,
	 SR_198410 = 1,
	 SR_152440 = 2,
	 SR_131580 = 3,
	 SR_116740 = 4,
	 SR_69440 = 5,
	 SR_37590 = 6,
	 SR_25770 = 7,
	 SR_20160 = 8,
	 SR_16030 = 9,
	 SR_10290 = 10,
	 SR_8280 = 11,
	 SR_6900 = 12,
	 SR_5530 = 13,
	 SR_4240 = 14,
	 SR_3300 = 15

}ESR_CLK;

typedef enum{
	 AD5410_SR_STEP_1_16_AD5420_1 = 0,
	 AD5410_SR_STEP_1_8_AD5420_2 = 1,
	 AD5410_SR_STEP_1_4_AD5420_4 = 2,
	 AD5410_SR_STEP_1_2_AD5420_8 = 3,
	 AD5410_SR_STEP_1_AD5420_16 = 4,
	 AD5410_SR_STEP_2_AD5420_32 = 5,
	 AD5410_SR_STEP_4_AD5420_64 = 6,
	 AD5410_SR_STEP_8_AD5420_128  = 7

}ESR_STEP;


typedef enum{

 READ_STA_REG =0,
 READ_DATA_REG=1,
 READ_CONT_REG=2

}EREAD_KIND;

#define AD5410    12
#define AD5420    16
#define AD54XX    AD5410
#define OUT_MA	  R1R2R3_0_20MA


void AD54XX_init(void);

void set_contol(ESR_CLK sr_clk,ESR_STEP sr_step);

void set_data(float ma);

void reset(void);

unsigned int read(EREAD_KIND read_kind);
 
#endif