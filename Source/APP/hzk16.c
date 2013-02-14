/*
****************************************************** 


		 File Name   : hzk16.C
		 Compiler    : 
		 Author      : Liu_xf
		 Version     : V1.0
		 Date        : 2011-3-28 11:25:54
		 Description : 
		    ucguiµÄÖÐÎÄ×Ö¿â£¬Óëuc¹¤¾ßÉú³ÉµÄ×Ö¿âÎÄ¼þ²»Í¬µÄÊÇ£¬¿ÉÒÔ½«
		    ´óÈÝÁ¿µÄºº×ÖÊý×é´æÈëµ½Íâ²¿µÄFALSHÀï
		    µ±È»Õâ¸öÒ²ÊÇÓÉuc¹¤¾ßÉú³ÉµÄÎÄ¼þÐÞ¸Ä¶øÀ´µÄ¡£
*******************************************************
		 Structure : 
		 
		 History:

*******************************************************
*/

#include "GUI.H"
#ifndef GUI_FLASH
   #define GUI_FLASH
#endif
extern GUI_FLASH const GUI_FONT GUI_FontHZ16;

/*
GUI_FLASH const GUI_CHARINFO GUI_FontHZ16_CharInfo[] = {
{ 10, 10, 1, (void GUI_FLASH *)0},  // ×Ö·ûÔÚFLASHÖÐµÄÆ«ÒÆÁ¿
{ 16, 16, 2, (void GUI_FLASH *)3840}, //ºº×ÖÔÚFLASHÖÐµÄÆ«ÒÆÁ¿
};
*/
 
GUI_FLASH const GUI_CHARINFO GUI_FontHZ16_CharInfo[] = {
{ 8, 8, 1, (void GUI_FLASH *)(512*512)}, //×Ö·ûÔÚFLASHÖÐµÄÆ«ÒÆÁ¿£¬´Ó512page¿ªÊ¼ µØÖ·Îª512*512 
{ 16, 16, 2, (void GUI_FLASH *)GUI_FontHZ16_Flash_BaseAddr}, //GUI_FontHZ16_Flash_BaseAddrÔÚGUI.hÖÐ¶¨Òå
};

//ºº×ÖºÍ×Ö·ûË÷Òý±í//////////////////////////////////

/*÷¡--÷þ*/

GUI_FLASH const GUI_FONT_PROP GUI_FontHZ16_Propf7a1= {
      0xf7a1,
      0xf7fe,
      &GUI_FontHZ16_CharInfo[1],
      (void *)0 
};
/*ö¡--öþ*/
GUI_FLASH  const GUI_FONT_PROP GUI_FontHZ16_Propf6a1= {
      0xf6a1,
      0xf6fe,
      &GUI_FontHZ16_CharInfo[1],
      (void *)&GUI_FontHZ16_Propf7a1 
};
/*õ¡--õþ*/
GUI_FLASH  const GUI_FONT_PROP GUI_FontHZ16_Propf5a1= {
      0xf5a1,
      0xf5fe,
      &GUI_FontHZ16_CharInfo[1],
      (void *)&GUI_FontHZ16_Propf6a1 
};
/*ô¡--ôþ*/
GUI_FLASH  const GUI_FONT_PROP GUI_FontHZ16_Propf4a1= {
      0xf4a1,
      0xf4fe,
      &GUI_FontHZ16_CharInfo[1],
      (void *)&GUI_FontHZ16_Propf5a1 
};
/*ó¡--óþ*/
GUI_FLASH  const GUI_FONT_PROP GUI_FontHZ16_Propf3a1= {
      0xf3a1,
      0xf3fe,
      &GUI_FontHZ16_CharInfo[1],
      (void *)&GUI_FontHZ16_Propf4a1 
};
/*ò¡--òþ*/
GUI_FLASH  const GUI_FONT_PROP GUI_FontHZ16_Propf2a1= {
      0xf2a1,
      0xf2fe,
      &GUI_FontHZ16_CharInfo[1],
      (void *)&GUI_FontHZ16_Propf3a1 
};
/*ñ¡--ñþ*/
GUI_FLASH  const GUI_FONT_PROP GUI_FontHZ16_Propf1a1= {
      0xf1a1,
      0xf1fe,
      &GUI_FontHZ16_CharInfo[1],
      (void *)&GUI_FontHZ16_Propf2a1 
};
/*ð¡--ðþ*/
GUI_FLASH  const GUI_FONT_PROP GUI_FontHZ16_Propf0a1= {
      0xf0a1,
      0xf0fe,
      &GUI_FontHZ16_CharInfo[1],
      (void *)&GUI_FontHZ16_Propf1a1 
};
/*ï¡--ïþ*/
GUI_FLASH  const GUI_FONT_PROP GUI_FontHZ16_Propefa1= {
      0xefa1,
      0xeffe,
      &GUI_FontHZ16_CharInfo[1],
      (void *)&GUI_FontHZ16_Propf0a1 
};
/*î¡--îþ*/
GUI_FLASH  const GUI_FONT_PROP GUI_FontHZ16_Propeea1= {
      0xeea1,
      0xeefe,
      &GUI_FontHZ16_CharInfo[1],
      (void *)&GUI_FontHZ16_Propefa1 
};
/*í¡--íþ*/
GUI_FLASH  const GUI_FONT_PROP GUI_FontHZ16_Propeda1= {
      0xeda1,
      0xedfe,
      &GUI_FontHZ16_CharInfo[1],
      (void *)&GUI_FontHZ16_Propeea1 
};
/*ì¡--ìþ*/
GUI_FLASH  const GUI_FONT_PROP GUI_FontHZ16_Propeca1= {
      0xeca1,
      0xecfe,
      &GUI_FontHZ16_CharInfo[1],
      (void *)&GUI_FontHZ16_Propeda1 
};
/*ë¡--ëþ*/
GUI_FLASH  const GUI_FONT_PROP GUI_FontHZ16_Propeba1= {
      0xeba1,
      0xebfe,
      &GUI_FontHZ16_CharInfo[1],
      (void *)&GUI_FontHZ16_Propeca1 
};
/*ê¡--êþ*/
GUI_FLASH  const GUI_FONT_PROP GUI_FontHZ16_Propeaa1= {
      0xeaa1,
      0xeafe,
      &GUI_FontHZ16_CharInfo[1],
      (void *)&GUI_FontHZ16_Propeba1 
};
/*é¡--éþ*/
GUI_FLASH  const GUI_FONT_PROP GUI_FontHZ16_Prope9a1= {
      0xe9a1,
      0xe9fe,
      &GUI_FontHZ16_CharInfo[1],
      (void *)&GUI_FontHZ16_Propeaa1 
};
/*è¡--èþ*/
GUI_FLASH  const GUI_FONT_PROP GUI_FontHZ16_Prope8a1= {
      0xe8a1,
      0xe8fe,
      &GUI_FontHZ16_CharInfo[1],
      (void *)&GUI_FontHZ16_Prope9a1 
};
/*ç¡--çþ*/
GUI_FLASH  const GUI_FONT_PROP GUI_FontHZ16_Prope7a1= {
      0xe7a1,
      0xe7fe,
      &GUI_FontHZ16_CharInfo[1],
      (void *)&GUI_FontHZ16_Prope8a1 
};
/*æ¡--æþ*/
GUI_FLASH  const GUI_FONT_PROP GUI_FontHZ16_Prope6a1= {
      0xe6a1,
      0xe6fe,
      &GUI_FontHZ16_CharInfo[1],
      (void *)&GUI_FontHZ16_Prope7a1 
};
/*å¡--åþ*/
GUI_FLASH  const GUI_FONT_PROP GUI_FontHZ16_Prope5a1= {
      0xe5a1,
      0xe5fe,
      &GUI_FontHZ16_CharInfo[1],
      (void *)&GUI_FontHZ16_Prope6a1 
};
/*ä¡--äþ*/
GUI_FLASH  const GUI_FONT_PROP GUI_FontHZ16_Prope4a1= {
      0xe4a1,
      0xe4fe,
      &GUI_FontHZ16_CharInfo[1],
      (void *)&GUI_FontHZ16_Prope5a1 
};
/*ã¡--ãþ*/
GUI_FLASH  const GUI_FONT_PROP GUI_FontHZ16_Prope3a1= {
      0xe3a1,
      0xe3fe,
      &GUI_FontHZ16_CharInfo[1],
      (void *)&GUI_FontHZ16_Prope4a1 
};
/*â¡--âþ*/
GUI_FLASH  const GUI_FONT_PROP GUI_FontHZ16_Prope2a1= {
      0xe2a1,
      0xe2fe,
      &GUI_FontHZ16_CharInfo[1],
      (void *)&GUI_FontHZ16_Prope3a1 
};
/*á¡--áþ*/
GUI_FLASH  const GUI_FONT_PROP GUI_FontHZ16_Prope1a1= {
      0xe1a1,
      0xe1fe,
      &GUI_FontHZ16_CharInfo[1],
      (void *)&GUI_FontHZ16_Prope2a1 
};
/*à¡--àþ*/
GUI_FLASH  const GUI_FONT_PROP GUI_FontHZ16_Prope0a1= {
      0xe0a1,
      0xe0fe,
      &GUI_FontHZ16_CharInfo[1],
      (void *)&GUI_FontHZ16_Prope1a1 
};
/*ß¡--ßþ*/
GUI_FLASH  const GUI_FONT_PROP GUI_FontHZ16_Propdfa1= {
      0xdfa1,
      0xdffe,
      &GUI_FontHZ16_CharInfo[1],
      (void *)&GUI_FontHZ16_Prope0a1 
};
/*Þ¡--Þþ*/
GUI_FLASH  const GUI_FONT_PROP GUI_FontHZ16_Propdea1= {
      0xdea1,
      0xdefe,
      &GUI_FontHZ16_CharInfo[1],
      (void *)&GUI_FontHZ16_Propdfa1 
};
/*Ý¡--Ýþ*/
GUI_FLASH  const GUI_FONT_PROP GUI_FontHZ16_Propdda1= {
      0xdda1,
      0xddfe,
      &GUI_FontHZ16_CharInfo[1],
      (void *)&GUI_FontHZ16_Propdea1 
};
/*Ü¡--Üþ*/
GUI_FLASH  const GUI_FONT_PROP GUI_FontHZ16_Propdca1= {
      0xdca1,
      0xdcfe,
      &GUI_FontHZ16_CharInfo[1],
      (void *)&GUI_FontHZ16_Propdda1 
};
/*Û¡--Ûþ*/
GUI_FLASH  const GUI_FONT_PROP GUI_FontHZ16_Propdba1= {
      0xdba1,
      0xdbfe,
      &GUI_FontHZ16_CharInfo[1],
      (void *)&GUI_FontHZ16_Propdca1 
};
/*Ú¡--Úþ*/
GUI_FLASH  const GUI_FONT_PROP GUI_FontHZ16_Propdaa1= {
      0xdaa1,
      0xdafe,
      &GUI_FontHZ16_CharInfo[1],
      (void *)&GUI_FontHZ16_Propdba1 
};
/*Ù¡--Ùþ*/
GUI_FLASH  const GUI_FONT_PROP GUI_FontHZ16_Propd9a1= {
      0xd9a1,
      0xd9fe,
      &GUI_FontHZ16_CharInfo[1],
      (void *)&GUI_FontHZ16_Propdaa1 
};
/*Ø¡--Øþ*/
GUI_FLASH  const GUI_FONT_PROP GUI_FontHZ16_Propd8a1= {
      0xd8a1,
      0xd8fe,
      &GUI_FontHZ16_CharInfo[1],
      (void *)&GUI_FontHZ16_Propd9a1 
};
/*×¡--×þ*/
GUI_FLASH  const GUI_FONT_PROP GUI_FontHZ16_Propd7a1= {
      0xd7a1,
      0xd7fe,
      &GUI_FontHZ16_CharInfo[1],
      (void *)&GUI_FontHZ16_Propd8a1 
};
/*Ö¡--Öþ*/
GUI_FLASH  const GUI_FONT_PROP GUI_FontHZ16_Propd6a1= {
      0xd6a1,
      0xd6fe,
      &GUI_FontHZ16_CharInfo[1],
      (void *)&GUI_FontHZ16_Propd7a1 
};
/*Õ¡--Õþ*/
GUI_FLASH  const GUI_FONT_PROP GUI_FontHZ16_Propd5a1= {
      0xd5a1,
      0xd5fe,
      &GUI_FontHZ16_CharInfo[1],
      (void *)&GUI_FontHZ16_Propd6a1 
};
/*Ô¡--Ôþ*/
GUI_FLASH  const GUI_FONT_PROP GUI_FontHZ16_Propd4a1= {
      0xd4a1,
      0xd4fe,
      &GUI_FontHZ16_CharInfo[1],
      (void *)&GUI_FontHZ16_Propd5a1 
};
/*Ó¡--Óþ*/
GUI_FLASH  const GUI_FONT_PROP GUI_FontHZ16_Propd3a1= {
      0xd3a1,
      0xd3fe,
      &GUI_FontHZ16_CharInfo[1],
      (void *)&GUI_FontHZ16_Propd4a1 
};
/*Ò¡--Òþ*/
GUI_FLASH  const GUI_FONT_PROP GUI_FontHZ16_Propd2a1= {
      0xd2a1,
      0xd2fe,
      &GUI_FontHZ16_CharInfo[1],
      (void *)&GUI_FontHZ16_Propd3a1 
};
/*Ñ¡--Ñþ*/
GUI_FLASH  const GUI_FONT_PROP GUI_FontHZ16_Propd1a1= {
      0xd1a1,
      0xd1fe,
      &GUI_FontHZ16_CharInfo[1],
      (void *)&GUI_FontHZ16_Propd2a1 
};
/*Ð¡--Ðþ*/
GUI_FLASH  const GUI_FONT_PROP GUI_FontHZ16_Propd0a1= {
      0xd0a1,
      0xd0fe,
      &GUI_FontHZ16_CharInfo[1],
      (void *)&GUI_FontHZ16_Propd1a1 
};
/*Ï¡--Ïþ*/
GUI_FLASH  const GUI_FONT_PROP GUI_FontHZ16_Propcfa1= {
      0xcfa1,
      0xcffe,
      &GUI_FontHZ16_CharInfo[1],
      (void *)&GUI_FontHZ16_Propd0a1 
};
/*Î¡--Îþ*/
GUI_FLASH  const GUI_FONT_PROP GUI_FontHZ16_Propcea1= {
      0xcea1,
      0xcefe,
      &GUI_FontHZ16_CharInfo[1],
      (void *)&GUI_FontHZ16_Propcfa1 
};
/*Í¡--Íþ*/
GUI_FLASH  const GUI_FONT_PROP GUI_FontHZ16_Propcda1= {
      0xcda1,
      0xcdfe,
      &GUI_FontHZ16_CharInfo[1],
      (void *)&GUI_FontHZ16_Propcea1 
};
/*Ì¡--Ìþ*/
GUI_FLASH  const GUI_FONT_PROP GUI_FontHZ16_Propcca1= {
      0xcca1,
      0xccfe,
      &GUI_FontHZ16_CharInfo[1],
      (void *)&GUI_FontHZ16_Propcda1 
};
/*Ë¡--Ëþ*/
GUI_FLASH  const GUI_FONT_PROP GUI_FontHZ16_Propcba1= {
      0xcba1,
      0xcbfe,
      &GUI_FontHZ16_CharInfo[1],
      (void *)&GUI_FontHZ16_Propcca1 
};
/*Ê¡--Êþ*/
GUI_FLASH  const GUI_FONT_PROP GUI_FontHZ16_Propcaa1= {
      0xcaa1,
      0xcafe,
      &GUI_FontHZ16_CharInfo[1],
      (void *)&GUI_FontHZ16_Propcba1 
};
/*É¡--Éþ*/
GUI_FLASH  const GUI_FONT_PROP GUI_FontHZ16_Propc9a1= {
      0xc9a1,
      0xc9fe,
      &GUI_FontHZ16_CharInfo[1],
      (void *)&GUI_FontHZ16_Propcaa1 
};
/*È¡--Èþ*/
GUI_FLASH  const GUI_FONT_PROP GUI_FontHZ16_Propc8a1= {
      0xc8a1,
      0xc8fe,
      &GUI_FontHZ16_CharInfo[1],
      (void *)&GUI_FontHZ16_Propc9a1 
};
/*Ç¡--Çþ*/
GUI_FLASH  const GUI_FONT_PROP GUI_FontHZ16_Propc7a1= {
      0xc7a1,
      0xc7fe,
      &GUI_FontHZ16_CharInfo[1],
      (void *)&GUI_FontHZ16_Propc8a1 
};
/*Æ¡--Æþ*/
GUI_FLASH  const GUI_FONT_PROP GUI_FontHZ16_Propc6a1= {
      0xc6a1,
      0xc6fe,
      &GUI_FontHZ16_CharInfo[1],
      (void *)&GUI_FontHZ16_Propc7a1 
};
/*Å¡--Åþ*/
GUI_FLASH  const GUI_FONT_PROP GUI_FontHZ16_Propc5a1= {
      0xc5a1,
      0xc5fe,
      &GUI_FontHZ16_CharInfo[1],
      (void *)&GUI_FontHZ16_Propc6a1 
};
/*Ä¡--Äþ*/
GUI_FLASH  const GUI_FONT_PROP GUI_FontHZ16_Propc4a1= {
      0xc4a1,
      0xc4fe,
      &GUI_FontHZ16_CharInfo[1],
      (void *)&GUI_FontHZ16_Propc5a1 
};
/*Ã¡--Ãþ*/
GUI_FLASH  const GUI_FONT_PROP GUI_FontHZ16_Propc3a1= {
      0xc3a1,
      0xc3fe,
      &GUI_FontHZ16_CharInfo[1],
      (void *)&GUI_FontHZ16_Propc4a1 
};
/*Â¡--Âþ*/
GUI_FLASH  const GUI_FONT_PROP GUI_FontHZ16_Propc2a1= {
      0xc2a1,
      0xc2fe,
      &GUI_FontHZ16_CharInfo[1],
      (void *)&GUI_FontHZ16_Propc3a1 
};
/*Á¡--Áþ*/
GUI_FLASH  const GUI_FONT_PROP GUI_FontHZ16_Propc1a1= {
      0xc1a1,
      0xc1fe,
      &GUI_FontHZ16_CharInfo[1],
      (void *)&GUI_FontHZ16_Propc2a1 
};
/*À¡--Àþ*/
GUI_FLASH  const GUI_FONT_PROP GUI_FontHZ16_Propc0a1= {
      0xc0a1,
      0xc0fe,
      &GUI_FontHZ16_CharInfo[1],
      (void *)&GUI_FontHZ16_Propc1a1 
};
/*¿¡--¿þ*/
GUI_FLASH  const GUI_FONT_PROP GUI_FontHZ16_Propbfa1= {
      0xbfa1,
      0xbffe,
      &GUI_FontHZ16_CharInfo[1],
      (void *)&GUI_FontHZ16_Propc0a1 
};
/*¾¡--¾þ*/
GUI_FLASH  const GUI_FONT_PROP GUI_FontHZ16_Propbea1= {
      0xbea1,
      0xbefe,
      &GUI_FontHZ16_CharInfo[1],
      (void *)&GUI_FontHZ16_Propbfa1 
};
/*½¡--½þ*/
GUI_FLASH  const GUI_FONT_PROP GUI_FontHZ16_Propbda1= {
      0xbda1,
      0xbdfe,
      &GUI_FontHZ16_CharInfo[1],
      (void *)&GUI_FontHZ16_Propbea1 
};
/*¼¡--¼þ*/
GUI_FLASH  const GUI_FONT_PROP GUI_FontHZ16_Propbca1= {
      0xbca1,
      0xbcfe,
      &GUI_FontHZ16_CharInfo[1],
      (void *)&GUI_FontHZ16_Propbda1 
};
/*»¡--»þ*/
GUI_FLASH  const GUI_FONT_PROP GUI_FontHZ16_Propbba1= {
      0xbba1,
      0xbbfe,
      &GUI_FontHZ16_CharInfo[1],
      (void *)&GUI_FontHZ16_Propbca1 
};
/*º¡--ºþ*/
GUI_FLASH  const GUI_FONT_PROP GUI_FontHZ16_Propbaa1= {
      0xbaa1,
      0xbafe,
      &GUI_FontHZ16_CharInfo[1],
      (void *)&GUI_FontHZ16_Propbba1 
};
/*¹¡--¹þ*/
GUI_FLASH  const GUI_FONT_PROP GUI_FontHZ16_Propb9a1= {
      0xb9a1,
      0xb9fe,
      &GUI_FontHZ16_CharInfo[1],
      (void *)&GUI_FontHZ16_Propbaa1 
};
/*¸¡--¸þ*/
GUI_FLASH  const GUI_FONT_PROP GUI_FontHZ16_Propb8a1= {
      0xb8a1,
      0xb8fe,
      &GUI_FontHZ16_CharInfo[1],
      (void *)&GUI_FontHZ16_Propb9a1 
};
/*·¡--·þ*/
GUI_FLASH  const GUI_FONT_PROP GUI_FontHZ16_Propb7a1= {
      0xb7a1,
      0xb7fe,
      &GUI_FontHZ16_CharInfo[1],
      (void *)&GUI_FontHZ16_Propb8a1 
};
/*¶¡--¶þ*/
GUI_FLASH  const GUI_FONT_PROP GUI_FontHZ16_Propb6a1= {
      0xb6a1,
      0xb6fe,
      &GUI_FontHZ16_CharInfo[1],
      (void *)&GUI_FontHZ16_Propb7a1 
};
/*µ¡--µþ*/
GUI_FLASH  const GUI_FONT_PROP GUI_FontHZ16_Propb5a1= {
      0xb5a1,
      0xb5fe,
      &GUI_FontHZ16_CharInfo[1],
      (void *)&GUI_FontHZ16_Propb6a1 
};
/*´¡--´þ*/
GUI_FLASH  const GUI_FONT_PROP GUI_FontHZ16_Propb4a1= {
      0xb4a1,
      0xb4fe,
      &GUI_FontHZ16_CharInfo[1],
      (void *)&GUI_FontHZ16_Propb5a1 
};
/*³¡--³þ*/
GUI_FLASH  const GUI_FONT_PROP GUI_FontHZ16_Propb3a1= {
      0xb3a1,
      0xb3fe,
      &GUI_FontHZ16_CharInfo[1],
      (void *)&GUI_FontHZ16_Propb4a1 
};
/*²¡--²þ*/
GUI_FLASH  const GUI_FONT_PROP GUI_FontHZ16_Propb2a1= {
      0xb2a1,
      0xb2fe,
      &GUI_FontHZ16_CharInfo[1],
      (void *)&GUI_FontHZ16_Propb3a1 
};
/*±¡--±þ*/
GUI_FLASH  const GUI_FONT_PROP GUI_FontHZ16_Propb1a1= {
      0xb1a1,
      0xb1fe,
      &GUI_FontHZ16_CharInfo[1],
      (void *)&GUI_FontHZ16_Propb2a1 
};
/*°¡--°þ*/
GUI_FLASH  const GUI_FONT_PROP GUI_FontHZ16_Propb0a1= {
      0xb0a1,
      0xb0fe,
      &GUI_FontHZ16_CharInfo[1],
      (void *)&GUI_FontHZ16_Propb1a1 
};
/*©¡--©þ*/
GUI_FLASH  const GUI_FONT_PROP GUI_FontHZ16_Propa9a1= {
      0xa9a1,
      0xa9fe,
      &GUI_FontHZ16_CharInfo[1],
      (void *)&GUI_FontHZ16_Propb0a1 
};
/*¨¡--¨þ*/
GUI_FLASH  const GUI_FONT_PROP GUI_FontHZ16_Propa8a1= {
      0xa8a1,
      0xa8fe,
      &GUI_FontHZ16_CharInfo[1],
      (void *)&GUI_FontHZ16_Propa9a1 
};
/*§¡--§þ*/
GUI_FLASH  const GUI_FONT_PROP GUI_FontHZ16_Propa7a1= {
      0xa7a1,
      0xa7fe,
      &GUI_FontHZ16_CharInfo[1],
      (void *)&GUI_FontHZ16_Propa8a1 
};
/*¦¡--¦þ*/
GUI_FLASH  const GUI_FONT_PROP GUI_FontHZ16_Propa6a1= {
      0xa6a1,
      0xa6fe,
      &GUI_FontHZ16_CharInfo[1],
      (void *)&GUI_FontHZ16_Propa7a1 
};
/*¥¡--¥þ*/
GUI_FLASH  const GUI_FONT_PROP GUI_FontHZ16_Propa5a1= {
      0xa5a1,
      0xa5fe,
      &GUI_FontHZ16_CharInfo[1],
      (void *)&GUI_FontHZ16_Propa6a1 
};
/*¤¡--¤þ*/
GUI_FLASH  const GUI_FONT_PROP GUI_FontHZ16_Propa4a1= {
      0xa4a1,
      0xa4fe,
      &GUI_FontHZ16_CharInfo[1],
      (void *)&GUI_FontHZ16_Propa5a1 
};
/*£¡--£þ*/
GUI_FLASH  const GUI_FONT_PROP GUI_FontHZ16_Propa3a1= {
      0xa3a1,
      0xa3fe,
      &GUI_FontHZ16_CharInfo[1],
      (void *)&GUI_FontHZ16_Propa4a1 
};
/*¢¡--¢þ*/
GUI_FLASH  const GUI_FONT_PROP GUI_FontHZ16_Propa2a1= {
      0xa2a1,
      0xa2fe,
      &GUI_FontHZ16_CharInfo[1],
      (void *)&GUI_FontHZ16_Propa3a1 
};
/*¡¡--¡þ*/
GUI_FLASH  const GUI_FONT_PROP GUI_FontHZ16_Propa1a1= {
      0xa1a1,
      0xa1fe,
      &GUI_FontHZ16_CharInfo[1],
      (void *)&GUI_FontHZ16_Propa2a1 
};
//ASC×Ö·û
/* --*/ 
GUI_FLASH  const GUI_FONT_PROP GUI_FontHZ16_Prop0020= {
      0x0020,
      0x007f,
      &GUI_FontHZ16_CharInfo[0],
      (void *)&GUI_FontHZ16_Propa1a1 
};
GUI_FLASH const GUI_FONT GUI_FontHZ16 = {
      GUI_FONTTYPE_PROP_SJIS, 
      16, 
      16, 
      1,  
      1,  
      (void GUI_FLASH *)&GUI_FontHZ16_Prop0020
};

