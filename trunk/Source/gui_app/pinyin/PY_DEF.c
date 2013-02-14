#define PY_DEF_GLOBALS
#include "PY_DEF.h"
#include "PY_TAB.c"
#include "string.h"

/*******************************************************************************
* �ļ���	  	 : PYSearch
* ����	         : ����ƴ���ĺ���
* ����           : ����ƴ��������
* ���           : ��
* ����           : ������ƴ�����ں��������Ӧ�����ؼ������ĺ��ֵ�ָ�룬
				   ���û�У����ؿ�ָ��
*******************************************************************************/	
char *PYSearch(unsigned char *msg ,int *num)
{
	unsigned char count=0;
	unsigned char i=0;
	struct PinYinPCB const *headpcb; 					//���确b'���Զ���Ϊ��b'��ͷ�����к���
	struct PinYinPCB const *tailpcb;					//��b'����һ����c'���Զ���Ϊ��c'��ͷ�����к���
												//ͨ����Ƚ��������ݵĴ�С���Եõ���b'�����е�Ԫ��+����
	while(msg[count]!=0)count++;				//���������ƴ�����ֽ���		
	for(i=0;i<count;i++)						//��������ƴ���Ƿ���Ϲ淶
	{
		if((msg[i]>='a')&&(msg[i]<='z')) 		//����������������Ч
		{
			continue;
		}
		else if((msg[i]>='A')&&(msg[i]<='Z'))	//����Ǵ�д��ͳһ���Сд
		{
		    msg[i]+=0x20;						
			continue;
		}									   	//��������ݷǷ�������
		else
		{
		    return '\0';
		}
	}
	if((*msg=='i')||(*msg=='u')||(*msg=='v')||(*msg=='\0'))	//��������ݷǷ�������
	{
	    return '\0';
	}
	tailpcb=PYRankThreeList[*msg-'a'];	 		//�Զ���Ϊ*msg��ͷ������ƴ������
	headpcb=PYRankThreeList[*msg-'a'+1];		//�Զ���Ϊ*msg+1��ͷ������ƴ������
	for(;tailpcb<headpcb;tailpcb++)
	{
	    for(i=0;i<count-1;i++)				    //��������ƴ��������ṹ���е�ƴ���Ƿ�һ��
		{	
			if(*((*tailpcb).PYSerList+i)!=msg[i+1])
			{
			    break;
			}
		}
		if(i==(count-1))	 					//һ�£����ָ��
		{
			*num = strlen((*tailpcb).PYRankOneList)/2;
		    return (char *)(*tailpcb).PYRankOneList;
		}
		
	}
	return '\0';								//���߷��ؿյ�ָ��
}

