#ifndef	_PY_DEF_H_
#define _PY_DEF_H_

#ifdef 	PY_DEF_GLOBALS
#define	PY_DEF_EXT
#else
#define  PY_DEF_EXT  extern
#endif


typedef struct{
	const unsigned char *PYList;  	//拼音检索字符串
	int			num;		//总汉字数
	const unsigned char *HZGB;		//以所定义的拼音组合的汉字GB码的指针
}PinYinDef;


//拼音组合的汉字字库
//拼音检索的结构体
struct PinYinPCB{
const  unsigned char *PYSerList;  		//拼音检索字符
const unsigned char *PYRankOneList;  	//以所定义的拼音组合的汉字字库的指针
};

/******************************************************************************
**	函数:	_py_init();
**	功能:	输入法初始化
**	参数:	无
**	返回:	无
**	说明:	无
******************************************************************************/
PY_DEF_EXT void _py_init(void);

char *PYSearch(unsigned char *msg ,int *num);
#endif   /* end */
