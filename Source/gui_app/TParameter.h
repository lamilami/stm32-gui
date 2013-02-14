#ifndef __TPARE_H
#define __TPARE_H


typedef struct{
	
	float enc_r;
	float enc_n;
    float r_mm;
	float R_mm;

	float Ve;

	float start_speed;
	unsigned int t0;
	
	float V1;
	float V2;
	float a1;
	float a2;
	float a3;

	unsigned int t1;
	unsigned int t2;
	unsigned int t3;
	float dV;
	
	float HZ;
	float Vp;
	float res1;
	float res2;
	float res3;

	char dir;

}TTPars;


extern TTPars ttpars;


void save_parameters(void);
void read_parameters(void);


#endif