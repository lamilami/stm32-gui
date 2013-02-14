#ifndef __MOT_T_H
#define __MOT_T_H

// 多少个编码器脉冲计算一次数据
#define CACU_SPEED_PER_ENCORD_N 1



void caculate_parameters(void);



void mot_t_init(void);
void counter_interrupt();

void caculate_speed();




#endif


