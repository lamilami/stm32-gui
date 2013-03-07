#ifndef __RDPRINT_H
#define __RDPRINT_H


typedef enum{
	 CH1616=0,
	 CH816,
	 CH168,
	 CH88,
	 CH1212,
	 CH612,
	 ASCII816,
	 ASCII812
}EChar;

typedef enum{
	 d0= 0,
	 d90 = 1,
	 d180 = 2,
	 d270 = 3
}ECharRt;


void rdprint(char data);

#define PRINT_BUSY     0x13
#define PRINT_FREE	   0x11

//n -- 	0  16*16
//  --  1  8*16
//  --  2  16*8
//	--  3  8*8
//  --  4  12*12
//  --  5  6*12
//  --  6  8*16
//  --  7  8*12
#define COMM_CHINESE(n)   rdprint(0x1B);rdprint(0x38);rdprint(n);

//换行
#define COMM_LF			rdprint(0x0A);
//执行n点行走纸
#define COMM_J(n)       rdprint(0x1B);rdprint(0x4A);rdprint(n);
//设置n点行间距	 
#define COMM_1(n)		rdprint(0x1B);rdprint(0x31);rdprint(n);

//设置字间距
#define COMM_SP(n)		rdprint(0x1B);rdprint(0x20);rdprint(n);	 // n 0-128 default 0

//垂直造表
#define COMM_Bs      rdprint(0x1B);rdprint(0x42);
#define COMM_Bm(n)      rdprint(n)
#define COMM_Be			rdpirnt(0x00);

//执行垂直造表
#define COMM_VT			rdprint(0x0B);

//水平造表
#define COMM_Ds		rdprint(0x1B);rdprint(0x44);
#define COMM_Dm(n)			rdprint(n);
#define COMM_De			rdprint(0x00);

//
#define COMM_HT			rdprint(0x09);

//打印空格或空行
#define COMM_F(M,n)		rdprint(0x1B); rdprint(0x66);rdprint(M);rdprint(n);

//设置右限
#define COMM_Q(n)		rdprint(0x1B); rdprint(0x51);rdprint(n);

//设置左限
#define COMM_L(n)       rdprint(0x1B); rdprint(0x6c);rdprint(n);

//选择字符集1
#define COMM_6			rdprint(0x1B); rdprint(0x36);

//选择字符集2
#define COMM_7			rdprint(0x1B); rdprint(0x37);

//横向放大
#define COMM_U(n)		rdprint(0x1B); rdprint(0x55);rdprint(n);

//纵向放大
#define COMM_V(n)       rdprint(0x1B); rdprint(0x56);rdprint(n);

//横纵向放大
#define COMM_W(n)       rdprint(0x1B); rdprint(0x57);rdprint(n);

//横纵向放大不同倍数
#define COMM_X(m,n)     rdprint(0x1B); rdprint(0x58);rdprint(m);rdprint(n);

//热敏打印机打印深度调整 越打越深
#define COMM_2B_R(n)    rdprint(0x1B); rdprint(0x72);rdprint(0x2B);rdprint(n);
//热敏打印机打印深度调整 越打越浅
#define COMM_2D_R(n)    rdprint(0x1B); rdprint(0x72);rdprint(0x2D);rdprint(n);

//一行内双宽度打印
#define COMM_SO	  		rdprint(0x0E);

//撤销一行内双宽度打印
#define COMM_DC4        rdprint(0x14);

//允许撤销下划线打印   1-- 允许
#define COMM__(n)			rdprint(0x1B);rdprint(0x2D);rdprint(n);

//允许撤销上划线打印 
#define COMM_A(n)	   rdprint(0x1B);rdprint(0x2B);rdprint(n);
//选择上下标 n = 0 对应上标
#define COMM_r(n)	   	 rdprint(0x1C);rdprint(0x72);rdprint(n);

//禁止允许反白打印
#define COMM_i(n)		rdprint(0x1B);rdprint(0x69);rdprint(n);

//禁止允许反向打印
#define COMM_C(n)		rdprint(0x1B);rdprint(0x63);rdprint(n);

//设置纵向打印
#define COMM_J   	rdprint(0x1C);rdprint(0x4A);

//设置横向打印
#define COMM_K	    rdprint(0x1C);rdprint(0x4B);

//设置字符旋转打印
#define COMM_2(n)    rdprint(0x1C);rdprint(0x49);rdprint(n);

//用户自定义字符
//图形打印命令
//打印曲线Ⅰ
//打印曲线Ⅱ
//打印条型码

//初始化命令
#define COMM_INIT	rdprint(0x1B);rdprint(0x40);

//数据控制命令
#define COMM_CR 	 rdprint(0x0D);


void print_ch(int loc, char* str_ch);

		











		


#endif