#define PY_DEF_GLOBALS
#include "PY_DEF.h"
#include "PY_TAB.c"
#include "string.h"

/*******************************************************************************
* 文件名	  	 : PYSearch
* 描述	         : 检索拼音的函数
* 输入           : 检索拼音的数组
* 输出           : 无
* 返回           : 如果这个拼音存在汉字与其对应，返回检索到的汉字的指针，
				   如果没有，返回空指针
*******************************************************************************/	
char *PYSearch(unsigned char *msg ,int *num)
{
	unsigned char count=0;
	unsigned char i=0;
	struct PinYinPCB const *headpcb; 					//例如‘b'，以读音为’b'开头的所有汉字
	struct PinYinPCB const *tailpcb;					//‘b'的下一个‘c'，以读音为’c'开头的所有汉字
												//通过这比较两个数据的大小可以得到’b'的所有的元音+辅音
	while(msg[count]!=0)count++;				//计算检索的拼音的字节数		
	for(i=0;i<count;i++)						//检查检索的拼音是否符合规范
	{
		if((msg[i]>='a')&&(msg[i]<='z')) 		//在这个区间的数据有效
		{
			continue;
		}
		else if((msg[i]>='A')&&(msg[i]<='Z'))	//如果是大写，统一变成小写
		{
		    msg[i]+=0x20;						
			continue;
		}									   	//输入的数据非法，返回
		else
		{
		    return '\0';
		}
	}
	if((*msg=='i')||(*msg=='u')||(*msg=='v')||(*msg=='\0'))	//输入的数据非法，返回
	{
	    return '\0';
	}
	tailpcb=PYRankThreeList[*msg-'a'];	 		//以读音为*msg开头的所有拼音检索
	headpcb=PYRankThreeList[*msg-'a'+1];		//以读音为*msg+1开头的所有拼音检索
	for(;tailpcb<headpcb;tailpcb++)
	{
	    for(i=0;i<count-1;i++)				    //检查输入的拼音与检索结构体中的拼音是否一致
		{	
			if(*((*tailpcb).PYSerList+i)!=msg[i+1])
			{
			    break;
			}
		}
		if(i==(count-1))	 					//一致，输出指针
		{
			*num = strlen((*tailpcb).PYRankOneList)/2;
		    return (char *)(*tailpcb).PYRankOneList;
		}
		
	}
	return '\0';								//否者返回空的指针
}

