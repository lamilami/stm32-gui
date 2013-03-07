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

//����
#define COMM_LF			rdprint(0x0A);
//ִ��n������ֽ
#define COMM_J(n)       rdprint(0x1B);rdprint(0x4A);rdprint(n);
//����n���м��	 
#define COMM_1(n)		rdprint(0x1B);rdprint(0x31);rdprint(n);

//�����ּ��
#define COMM_SP(n)		rdprint(0x1B);rdprint(0x20);rdprint(n);	 // n 0-128 default 0

//��ֱ���
#define COMM_Bs      rdprint(0x1B);rdprint(0x42);
#define COMM_Bm(n)      rdprint(n)
#define COMM_Be			rdpirnt(0x00);

//ִ�д�ֱ���
#define COMM_VT			rdprint(0x0B);

//ˮƽ���
#define COMM_Ds		rdprint(0x1B);rdprint(0x44);
#define COMM_Dm(n)			rdprint(n);
#define COMM_De			rdprint(0x00);

//
#define COMM_HT			rdprint(0x09);

//��ӡ�ո�����
#define COMM_F(M,n)		rdprint(0x1B); rdprint(0x66);rdprint(M);rdprint(n);

//��������
#define COMM_Q(n)		rdprint(0x1B); rdprint(0x51);rdprint(n);

//��������
#define COMM_L(n)       rdprint(0x1B); rdprint(0x6c);rdprint(n);

//ѡ���ַ���1
#define COMM_6			rdprint(0x1B); rdprint(0x36);

//ѡ���ַ���2
#define COMM_7			rdprint(0x1B); rdprint(0x37);

//����Ŵ�
#define COMM_U(n)		rdprint(0x1B); rdprint(0x55);rdprint(n);

//����Ŵ�
#define COMM_V(n)       rdprint(0x1B); rdprint(0x56);rdprint(n);

//������Ŵ�
#define COMM_W(n)       rdprint(0x1B); rdprint(0x57);rdprint(n);

//������Ŵ�ͬ����
#define COMM_X(m,n)     rdprint(0x1B); rdprint(0x58);rdprint(m);rdprint(n);

//������ӡ����ӡ��ȵ��� Խ��Խ��
#define COMM_2B_R(n)    rdprint(0x1B); rdprint(0x72);rdprint(0x2B);rdprint(n);
//������ӡ����ӡ��ȵ��� Խ��Խǳ
#define COMM_2D_R(n)    rdprint(0x1B); rdprint(0x72);rdprint(0x2D);rdprint(n);

//һ����˫��ȴ�ӡ
#define COMM_SO	  		rdprint(0x0E);

//����һ����˫��ȴ�ӡ
#define COMM_DC4        rdprint(0x14);

//�������»��ߴ�ӡ   1-- ����
#define COMM__(n)			rdprint(0x1B);rdprint(0x2D);rdprint(n);

//�������ϻ��ߴ�ӡ 
#define COMM_A(n)	   rdprint(0x1B);rdprint(0x2B);rdprint(n);
//ѡ�����±� n = 0 ��Ӧ�ϱ�
#define COMM_r(n)	   	 rdprint(0x1C);rdprint(0x72);rdprint(n);

//��ֹ�����״�ӡ
#define COMM_i(n)		rdprint(0x1B);rdprint(0x69);rdprint(n);

//��ֹ�������ӡ
#define COMM_C(n)		rdprint(0x1B);rdprint(0x63);rdprint(n);

//���������ӡ
#define COMM_J   	rdprint(0x1C);rdprint(0x4A);

//���ú����ӡ
#define COMM_K	    rdprint(0x1C);rdprint(0x4B);

//�����ַ���ת��ӡ
#define COMM_2(n)    rdprint(0x1C);rdprint(0x49);rdprint(n);

//�û��Զ����ַ�
//ͼ�δ�ӡ����
//��ӡ���ߢ�
//��ӡ���ߢ�
//��ӡ������

//��ʼ������
#define COMM_INIT	rdprint(0x1B);rdprint(0x40);

//���ݿ�������
#define COMM_CR 	 rdprint(0x0D);


void print_ch(int loc, char* str_ch);

		











		


#endif