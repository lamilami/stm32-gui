#line 1 "Source\\uCGUI\\TouchCalibration\\TouchCalibration.c"

















 

#line 1 "Source\\uCGUI\\TouchCalibration\\TouchCalibration.h"


#line 1 ".\\Source\\uCGUI\\Core\\GUI.h"





















 







#line 1 ".\\Source\\uCGUI\\Core\\GUI_ConfDefaults.h"





















 




#line 1 ".\\Source\\uCGUI\\Config\\GUIConf.h"

















 









								   







 





#line 28 ".\\Source\\uCGUI\\Core\\GUI_ConfDefaults.h"






 




 
#line 46 ".\\Source\\uCGUI\\Core\\GUI_ConfDefaults.h"




 












































#line 102 ".\\Source\\uCGUI\\Core\\GUI_ConfDefaults.h"













#line 122 ".\\Source\\uCGUI\\Core\\GUI_ConfDefaults.h"


 
#line 132 ".\\Source\\uCGUI\\Core\\GUI_ConfDefaults.h"

#line 140 ".\\Source\\uCGUI\\Core\\GUI_ConfDefaults.h"

 
#line 149 ".\\Source\\uCGUI\\Core\\GUI_ConfDefaults.h"

 





 
#line 164 ".\\Source\\uCGUI\\Core\\GUI_ConfDefaults.h"







 
	 	 			 		    	 				 	  			   	 	 	 	 	 	  	  	      	   		 	 	 		  		  	 		 	  	  			     			       	   	 			  		    	 	     	 				  	 					 	 			   	  	  			 				 		 	 	 			     			 
#line 31 ".\\Source\\uCGUI\\Core\\GUI.h"
#line 1 ".\\Source\\uCGUI\\Core\\GUIType.h"





















 




#line 1 ".\\Source\\uCGUI\\Core\\LCD.h"

















 




#line 24 ".\\Source\\uCGUI\\Core\\LCD.h"


















 
 
#line 52 ".\\Source\\uCGUI\\Core\\LCD.h"













 












 










 







 





 

typedef int LCD_DRAWMODE;
typedef unsigned long LCD_COLOR;

 





 

typedef struct { signed short x,y; } GUI_POINT;
typedef struct { signed short x0,y0,x1,y1; } LCD_RECT;
 

typedef struct {
  int              NumEntries; 
  char             HasTrans;         
  const LCD_COLOR  * pPalEntries; 
} LCD_LOGPALETTE; 

 
typedef struct {
  int x,y;
  unsigned char KeyStat;
} LCD_tMouseState;








 

typedef LCD_COLOR      tLCDDEV_Index2Color  (int Index);
typedef unsigned int   tLCDDEV_Color2Index  (LCD_COLOR Color);
typedef unsigned int   tLCDDEV_GetIndexMask (void);
LCD_COLOR      LCD_L0_Index2Color  (int Index);
LCD_COLOR      LCD_L0_1_Index2Color(int Index);
LCD_COLOR      LCD_L0_2_Index2Color(int Index);
LCD_COLOR      LCD_L0_3_Index2Color(int Index);
LCD_COLOR      LCD_L0_4_Index2Color(int Index);
unsigned int   LCD_L0_Color2Index  (LCD_COLOR Color);
unsigned int   LCD_L0_1_Color2Index(LCD_COLOR Color);
unsigned int   LCD_L0_2_Color2Index(LCD_COLOR Color);
unsigned int   LCD_L0_3_Color2Index(LCD_COLOR Color);
unsigned int   LCD_L0_4_Color2Index(LCD_COLOR Color);
unsigned int   LCD_L0_GetIndexMask  (void);
unsigned int   LCD_L0_1_GetIndexMask(void);
unsigned int   LCD_L0_2_GetIndexMask(void);
unsigned int   LCD_L0_3_GetIndexMask(void);
unsigned int   LCD_L0_4_GetIndexMask(void);





 

typedef struct {
  tLCDDEV_Color2Index*  pfColor2Index;
  tLCDDEV_Index2Color*  pfIndex2Color;
  tLCDDEV_GetIndexMask* pfGetIndexMask;
} LCD_API_COLOR_CONV;

extern const LCD_API_COLOR_CONV LCD_API_ColorConv_1;
extern const LCD_API_COLOR_CONV LCD_API_ColorConv_2;
extern const LCD_API_COLOR_CONV LCD_API_ColorConv_4;
extern const LCD_API_COLOR_CONV LCD_API_ColorConv_8666;



















 
typedef void         tLCDDEV_DrawHLine    (int x0, int y0,  int x1);
typedef void         tLCDDEV_DrawVLine    (int x , int y0,  int y1);
typedef void         tLCDDEV_FillRect     (int x0, int y0, int x1, int y1);
typedef unsigned int tLCDDEV_GetPixelIndex(int x, int y);
typedef void         tLCDDEV_SetPixelIndex(int x, int y, int ColorIndex);
typedef void         tLCDDEV_XorPixel     (int x, int y);
typedef void         tLCDDEV_FillPolygon  (const GUI_POINT* pPoints, int NumPoints, int x0, int y0);
typedef void         tLCDDEV_FillPolygonAA(const GUI_POINT* pPoints, int NumPoints, int x0, int y0);
typedef void         tLCDDEV_GetRect      (LCD_RECT*pRect);
typedef int          tLCDDEV_Init         (void);
typedef void         tLCDDEV_On           (void);
typedef void         tLCDDEV_Off          (void);
typedef void         tLCDDEV_SetLUTEntry  (unsigned char Pos, LCD_COLOR color);
typedef void *       tLCDDEV_GetDevFunc   (int Index);




 

  typedef struct tLCDDEV_APIList_struct tLCDDEV_APIList;


typedef void tLCDDEV_DrawBitmap   (int x0, int y0, int xsize, int ysize,
                       int BitsPerPixel, int BytesPerLine,
                       const unsigned char  * pData, int Diff,
                       const void* pTrans);    

struct tLCDDEV_APIList_struct {
  tLCDDEV_Color2Index*        pfColor2Index;
  tLCDDEV_Index2Color*        pfIndex2Color;
  tLCDDEV_GetIndexMask*       pfGetIndexMask;
  tLCDDEV_DrawBitmap*         pfDrawBitmap;
  tLCDDEV_DrawHLine*          pfDrawHLine;
  tLCDDEV_DrawVLine*          pfDrawVLine;
  tLCDDEV_FillRect*           pfFillRect;
  tLCDDEV_GetPixelIndex*      pfGetPixelIndex;
  tLCDDEV_GetRect*            pfGetRect;
  tLCDDEV_SetPixelIndex*      pfSetPixelIndex;
  tLCDDEV_XorPixel*           pfXorPixel;
  tLCDDEV_SetLUTEntry*        pfSetLUTEntry;
  tLCDDEV_GetDevFunc*         pfGetDevFunc;

    tLCDDEV_FillPolygon*      pfFillPolygon;
    tLCDDEV_FillPolygonAA*    pfFillPolygonAA;
    const tLCDDEV_APIList*    pMemDevAPI;
    unsigned                  BitsPerPixel;

};

  extern const struct tLCDDEV_APIList_struct GUI_MEMDEV__APIList1;
  extern const struct tLCDDEV_APIList_struct GUI_MEMDEV__APIList8;
  extern const struct tLCDDEV_APIList_struct GUI_MEMDEV__APIList16;























 

#line 285 ".\\Source\\uCGUI\\Core\\LCD.h"





 
 

int LCD_GetXSize(void);
int LCD_GetXSize_1(void);
int LCD_GetXSizeEx(int Index);

int LCD_GetYSize(void);
int LCD_GetYSize_1(void);
int LCD_GetYSizeEx(int Index);

int LCD_GetVXSize(void);
int LCD_GetVXSize_1(void);
int LCD_GetVXSizeEx(int Index);

int LCD_GetVYSize(void);
int LCD_GetVYSize_1(void);
int LCD_GetVYSizeEx(int Index);

unsigned long LCD_GetNumColors(void);
unsigned long LCD_GetNumColors_1(void);
unsigned long LCD_GetNumColorsEx(int Index);

int LCD_GetBitsPerPixel(void);
int LCD_GetBitsPerPixel_1(void);
int LCD_GetBitsPerPixelEx(int Index);

int LCD_GetFixedPalette(void);
int LCD_GetFixedPalette_1(void);
signed long LCD_GetFixedPaletteEx(int Index);

int LCD_GetXMag(void);
int LCD_GetXMag_1(void);
int LCD_GetXMagEx(int Index);

int LCD_GetYMag(void);
int LCD_GetYMag_1(void);
int LCD_GetYMagEx(int Index);

int LCD_GetMirrorXEx(int LayerIndex);
int LCD_GetMirrorYEx(int LayerIndex);
int LCD_GetSwapXYEx(int LayerIndex);

int LCD_GetSwapRBEx(int LayerIndex);
int LCD_GetDeltaModeEx(int LayerIndex);
int LCD_GetBitsPerPixel_L0Ex(int LayerIndex);

tLCDDEV_Index2Color * LCD_GetpfIndex2ColorEx(int LayerIndex);

int LCD_GetNumLayers(void);



#line 349 ".\\Source\\uCGUI\\Core\\LCD.h"



void * LCD_L0_GetDevFunc(int Index);






 
typedef void         tLCD_HL_DrawHLine    (int x0, int y0,  int x1);
typedef void         tLCD_HL_DrawPixel    (int x0, int y0);

typedef struct {
  tLCD_HL_DrawHLine*          pfDrawHLine;
  tLCD_HL_DrawPixel*          pfDrawPixel;
} tLCD_HL_APIList;

void LCD_DrawHLine(int x0, int y0,  int x1);
void LCD_DrawPixel(int x0, int y0);
void LCD_DrawVLine  (int x, int y0,  int y1);








 

void LCD_SetClipRectEx(const LCD_RECT* pRect);
void LCD_SetClipRectMax(void);

 
signed long  LCD_GetDevCap(int Index);

 
int LCD_Init(void);

void LCD_SetBkColor   (LCD_COLOR Color);  
void LCD_SetColor     (LCD_COLOR Color);  
void LCD_SetPixelIndex(int x, int y, int ColorIndex);

 
void LCD_InitLUT(void);

 

void         LCD_DrawBitmap_RLE8(int x0,int y0,int xsize, int ysize, const unsigned char  *pPixel, const LCD_LOGPALETTE  * pLogPal, int xMag, int yMag);
void         LCD_DrawBitmap_RLE4(int x0,int y0,int xsize, int ysize, const unsigned char  *pPixel, const LCD_LOGPALETTE  * pLogPal, int xMag, int yMag);
void         LCD_DrawBitmap_565 (int x0,int y0,int xsize, int ysize, const unsigned char  *pPixel, const LCD_LOGPALETTE  * pLogPal, int xMag, int yMag);
void         LCD_DrawBitmap_M565(int x0,int y0,int xsize, int ysize, const unsigned char  *pPixel, const LCD_LOGPALETTE  * pLogPal, int xMag, int yMag);

LCD_DRAWMODE LCD_SetDrawMode  (LCD_DRAWMODE dm);
void LCD_SetColorIndex(int Index);
void LCD_SetBkColorIndex(int Index);
void LCD_FillRect(int x0, int y0, int x1, int y1);
typedef void tLCD_SetPixelAA(int x, int y, unsigned char Intens);

void LCD_SetPixelAA(int x, int y, unsigned char Intens);
void LCD_SetPixelAA_NoTrans(int x, int y, unsigned char Intens);

LCD_COLOR    LCD_AA_MixColors(LCD_COLOR Color, LCD_COLOR BkColor, unsigned char Intens);
LCD_COLOR    LCD_MixColors256(LCD_COLOR Color, LCD_COLOR BkColor, unsigned Intens);
LCD_COLOR    LCD_GetPixelColor(int x, int y);      
unsigned int LCD_GetPixelIndex(int x, int y);
int          LCD_GetBkColorIndex (void);
int          LCD_GetColorIndex (void);






 



typedef void tLCD_DrawBitmap(int x0, int y0, int xsize, int ysize,
                             int xMul, int yMul, int BitsPerPixel, int BytesPerLine,
                             const unsigned char  * pPixel, const void * pTrans);
typedef void tRect2TextRect (LCD_RECT * pRect);

struct tLCD_APIList_struct {
  tLCD_DrawBitmap   * pfDrawBitmap;
  tRect2TextRect    * pfRect2TextRect;
};

typedef struct tLCD_APIList_struct tLCD_APIList;

extern tLCD_APIList LCD_APIListCCW;
extern tLCD_APIList LCD_APIListCW;
extern tLCD_APIList LCD_APIList180;

#line 451 ".\\Source\\uCGUI\\Core\\LCD.h"












 












unsigned char LCD_L0_ControlCache(unsigned char mode);
unsigned char LCD_L0_1_ControlCache(unsigned char mode);
unsigned char LCD_L0_2_ControlCache(unsigned char mode);
unsigned char LCD_L0_3_ControlCache(unsigned char mode);
unsigned char LCD_L0_4_ControlCache(unsigned char mode);
void LCD_L0_Refresh(void);
void LCD_L0_1_Refresh(void);
void LCD_L0_2_Refresh(void);
void LCD_L0_3_Refresh(void);
void LCD_L0_4_Refresh(void);
 
int  LCD_L0_CheckInit(void);        



 









 

int LCD_SelPage  (int NewPage);     
int LCD_ShowPage (int NewPage);     
int LCD_GetSelPage (void);          
int LCD_GetVisPage (void);          








 
  

int              LCD_Color2Index     (LCD_COLOR Color);
LCD_COLOR        LCD_Index2Color     (int Index);
LCD_COLOR        LCD_Index2ColorEx   (int i, unsigned int LayerIndex);






 

void LCD_X_Init(void);
void LCD_X_On  (void);
void LCD_X_Off (void);

char LCD_X_Read00(void);
char LCD_X_Read01(void);
void LCD_X_Write00(char c);
void LCD_X_Write01(char c);
void LCD_X_WriteM01(char * pData, int NumBytes);







 
	 	 			 		    	 				 	  			   	 	 	 	 	 	  	  	      	   		 	 	 		  		  	 		 	  	  			     			       	   	 			  		    	 	     	 				  	 					 	 			   	  	  			 				 		 	 	 			     			 
#line 28 ".\\Source\\uCGUI\\Core\\GUIType.h"
#line 29 ".\\Source\\uCGUI\\Core\\GUIType.h"






 

typedef const char *  GUI_ConstString;







 

typedef LCD_COLOR       GUI_COLOR;
typedef LCD_LOGPALETTE  GUI_LOGPALETTE;
typedef LCD_DRAWMODE    GUI_DRAWMODE;
typedef LCD_RECT        GUI_RECT;

typedef struct {
  void      (* pfDraw)(int x0,int y0,int xsize, int ysize, const unsigned char  * pPixel, const LCD_LOGPALETTE  * pLogPal, int xMag, int yMag);
  GUI_COLOR (* pfIndex2Color)(int Index);
} GUI_BITMAP_METHODS;

typedef struct {
  unsigned short XSize;
  unsigned short YSize;
  unsigned short BytesPerLine;
  unsigned short BitsPerPixel;
  const unsigned char  * pData;
  const GUI_LOGPALETTE  * pPal;
  const GUI_BITMAP_METHODS * pMethods;
} GUI_BITMAP;





 
typedef struct {
  unsigned short ID;            
  unsigned short Version;
  unsigned short XSize;
  unsigned short YSize;
  unsigned short BytesPerLine;
  unsigned short BitsPerPixel;
  unsigned short NumColors;
  unsigned short HasTrans;
} GUI_BITMAP_STREAM;

typedef struct {
  int x,y;
  unsigned char Pressed;
} GUI_PID_STATE;

typedef struct {
  int xPos;
  int yPos;
  int xSize;
  int ySize;
  int Delay;
} GUI_GIF_IMAGE_INFO;

typedef struct {
  int xSize;
  int ySize;
  int NumImages;
} GUI_GIF_INFO;







 



 
typedef struct {
  signed short c0;
  signed short c1;
} GUI_FONT_TRANSLIST;

typedef struct {
  unsigned short FirstChar;
  unsigned short LastChar;
  const GUI_FONT_TRANSLIST  * pList;
} GUI_FONT_TRANSINFO;

typedef struct {
  unsigned char XSize;
  unsigned char XDist;
  unsigned char BytesPerLine;
  const unsigned char  * pData;
} GUI_CHARINFO;

typedef struct GUI_FONT_PROP {
  unsigned short First;                                 
  unsigned short Last;                                  
  const GUI_CHARINFO  * paCharInfo;             
  const struct GUI_FONT_PROP  * pNext;         
} GUI_FONT_PROP;

typedef struct {
  const unsigned char  * pData;
  const unsigned char  * pTransData;
  const GUI_FONT_TRANSINFO  * pTrans;
  unsigned short FirstChar;
  unsigned short LastChar;
  unsigned char XSize;
  unsigned char XDist;
  unsigned char BytesPerLine;
} GUI_FONT_MONO;


typedef struct GUI_FONT_INFO {
  unsigned short First;                         
  unsigned short Last;                          
  const GUI_CHARINFO* paCharInfo;     
  const struct GUI_FONT_INFO* pNext;  
} GUI_FONT_INFO;










 
typedef struct {
  unsigned short Flags;
  unsigned char Baseline;
  unsigned char LHeight;      
  unsigned char CHeight;      
} GUI_FONTINFO;













 
typedef unsigned short  tGUI_GetCharCode(const char  *s);
typedef int  tGUI_GetCharSize(const char  *s);
typedef int  tGUI_CalcSizeOfChar(unsigned short Char);
typedef int  tGUI_Encode(char *s, unsigned short Char);

typedef struct {
  tGUI_GetCharCode*            pfGetCharCode;
  tGUI_GetCharSize*            pfGetCharSize;
  tGUI_CalcSizeOfChar*         pfCalcSizeOfChar;
  tGUI_Encode*                 pfEncode;
} GUI_UC_ENC_APILIST;






 

typedef int  tGUI_GetLineDistX(const char  *s, int Len);
typedef int  tGUI_GetLineLen(const char  *s, int MaxLen);
typedef void tGL_DispLine(const char  *s, int Len);

typedef struct {
  tGUI_GetLineDistX*          pfGetLineDistX;
  tGUI_GetLineLen*            pfGetLineLen;
  tGL_DispLine*               pfDispLine;
} tGUI_ENC_APIList;

extern const tGUI_ENC_APIList GUI_ENC_APIList_SJIS;













 

typedef struct GUI_FONT GUI_FONT;

typedef void GUI_DISPCHAR(unsigned short c);
typedef int  GUI_GETCHARDISTX(unsigned short c);
typedef void GUI_GETFONTINFO(const GUI_FONT  * pFont, GUI_FONTINFO * pfi);
typedef char GUI_ISINFONT   (const GUI_FONT  * pFont, unsigned short c);











 
void GUIMONO_DispChar (unsigned short c); int GUIMONO_GetCharDistX(unsigned short c); void GUIMONO_GetFontInfo (const GUI_FONT  * pFont, GUI_FONTINFO * pfi); char GUIMONO_IsInFont (const GUI_FONT  * pFont, unsigned short c);
#line 257 ".\\Source\\uCGUI\\Core\\GUIType.h"

 
void GUIPROP_DispChar (unsigned short c); int GUIPROP_GetCharDistX(unsigned short c); void GUIPROP_GetFontInfo (const GUI_FONT  * pFont, GUI_FONTINFO * pfi); char GUIPROP_IsInFont (const GUI_FONT  * pFont, unsigned short c);
#line 266 ".\\Source\\uCGUI\\Core\\GUIType.h"

 
void GUIPROP_DispChar (unsigned short c); int GUIPROP_GetCharDistX(unsigned short c); void GUIPROP_GetFontInfo (const GUI_FONT  * pFont, GUI_FONTINFO * pfi); char GUIPROP_IsInFont (const GUI_FONT  * pFont, unsigned short c);
#line 275 ".\\Source\\uCGUI\\Core\\GUIType.h"

 
void GUIPROPAA_DispChar (unsigned short c); int GUIPROPAA_GetCharDistX(unsigned short c); void GUIPROPAA_GetFontInfo (const GUI_FONT  * pFont, GUI_FONTINFO * pfi); char GUIPROPAA_IsInFont (const GUI_FONT  * pFont, unsigned short c);
#line 284 ".\\Source\\uCGUI\\Core\\GUIType.h"

 
void GUIPROP_AA2_DispChar (unsigned short c); int GUIPROP_AA2_GetCharDistX(unsigned short c); void GUIPROP_AA2_GetFontInfo (const GUI_FONT  * pFont, GUI_FONTINFO * pfi); char GUIPROP_AA2_IsInFont (const GUI_FONT  * pFont, unsigned short c);
#line 293 ".\\Source\\uCGUI\\Core\\GUIType.h"

 
void GUIPROP_AA2_DispChar (unsigned short c); int GUIPROP_AA2_GetCharDistX(unsigned short c); void GUIPROP_AA2_GetFontInfo (const GUI_FONT  * pFont, GUI_FONTINFO * pfi); char GUIPROP_AA2_IsInFont (const GUI_FONT  * pFont, unsigned short c);
#line 302 ".\\Source\\uCGUI\\Core\\GUIType.h"

 
void GUIPROP_AA4_DispChar (unsigned short c); int GUIPROP_AA4_GetCharDistX(unsigned short c); void GUIPROP_AA4_GetFontInfo (const GUI_FONT  * pFont, GUI_FONTINFO * pfi); char GUIPROP_AA4_IsInFont (const GUI_FONT  * pFont, unsigned short c);
#line 311 ".\\Source\\uCGUI\\Core\\GUIType.h"

 
void GUIPROP_AA4_DispChar (unsigned short c); int GUIPROP_AA4_GetCharDistX(unsigned short c); void GUIPROP_AA4_GetFontInfo (const GUI_FONT  * pFont, GUI_FONTINFO * pfi); char GUIPROP_AA4_IsInFont (const GUI_FONT  * pFont, unsigned short c);
#line 320 ".\\Source\\uCGUI\\Core\\GUIType.h"





struct GUI_FONT {
  GUI_DISPCHAR*     pfDispChar; 
  GUI_GETCHARDISTX* pfGetCharDistX; 
  GUI_GETFONTINFO*  pfGetFontInfo; 
  GUI_ISINFONT*     pfIsInFont;
  const tGUI_ENC_APIList* pafEncode;
  unsigned char YSize;
  unsigned char YDist;
  unsigned char XMag;
  unsigned char YMag;
  union {
    const void           * pFontData;
    const GUI_FONT_MONO  * pMono;
    const GUI_FONT_PROP  * pProp;
  } p;
  unsigned char Baseline;
  unsigned char LHeight;      
  unsigned char CHeight;      
};




 
typedef struct {
  unsigned long ID;            
  unsigned short YSize;         
  unsigned short YDist;         
  unsigned short Baseline;      
  unsigned short LHeight;       
  unsigned short CHeight;       
  unsigned short NumAreas;      
} GUI_SI_FONT;

typedef struct {
  unsigned short First;         
  unsigned short Last;          
} GUI_SIF_CHAR_AREA;

typedef struct {
  unsigned short XSize;         
  unsigned short XDist;         
  unsigned short BytesPerLine;  
  unsigned short Dummy;
  unsigned long OffData;       
} GUI_SIF_CHARINFO;

typedef struct tGUI_SIF_APIList_struct {
  GUI_DISPCHAR     * pDispChar;
  GUI_GETCHARDISTX * pGetCharDistX;
  GUI_GETFONTINFO  * pGetFontInfo;
  GUI_ISINFONT     * pIsInFont;
} tGUI_SIF_APIList;












 

#line 400 ".\\Source\\uCGUI\\Core\\GUIType.h"
typedef     signed short      GUI_HWIN;


 
	 	 			 		    	 				 	  			   	 	 	 	 	 	  	  	      	   		 	 	 		  		  	 		 	  	  			     			       	   	 			  		    	 	     	 				  	 					 	 			   	  	  			 				 		 	 	 			     			 
#line 32 ".\\Source\\uCGUI\\Core\\GUI.h"
#line 1 ".\\Source\\uCGUI\\Core\\GUIVersion.h"

















 








 
	 	 			 		    	 				 	  			   	 	 	 	 	 	  	  	      	   		 	 	 		  		  	 		 	  	  			     			       	   	 			  		    	 	     	 				  	 					 	 			   	  	  			 				 		 	 	 			     			 
#line 33 ".\\Source\\uCGUI\\Core\\GUI.h"











 









 











 

#line 86 ".\\Source\\uCGUI\\Core\\GUI.h"













 

#line 109 ".\\Source\\uCGUI\\Core\\GUI.h"




#line 123 ".\\Source\\uCGUI\\Core\\GUI.h"

#line 134 ".\\Source\\uCGUI\\Core\\GUI.h"

#line 145 ".\\Source\\uCGUI\\Core\\GUI.h"

#line 156 ".\\Source\\uCGUI\\Core\\GUI.h"






#line 170 ".\\Source\\uCGUI\\Core\\GUI.h"

#line 181 ".\\Source\\uCGUI\\Core\\GUI.h"

#line 192 ".\\Source\\uCGUI\\Core\\GUI.h"




































 








 
typedef enum { GUI_WRAPMODE_NONE, GUI_WRAPMODE_WORD, GUI_WRAPMODE_CHAR } GUI_WRAPMODE;






 






 











 













 












 

#line 316 ".\\Source\\uCGUI\\Core\\GUI.h"










 











 
extern const GUI_FONT GUI_FontHZ_SongTi_16;

 
extern const GUI_FONT GUI_Font8_ASCII,        GUI_Font8_1;
extern const GUI_FONT GUI_Font10S_ASCII,      GUI_Font10S_1;
extern const GUI_FONT GUI_Font10_ASCII,       GUI_Font10_1;
extern const GUI_FONT GUI_Font13_ASCII,       GUI_Font13_1;
extern const GUI_FONT GUI_Font13B_ASCII,      GUI_Font13B_1;
extern const GUI_FONT GUI_Font13H_ASCII,      GUI_Font13H_1;
extern const GUI_FONT GUI_Font13HB_ASCII,     GUI_Font13HB_1;
extern const GUI_FONT GUI_Font16_ASCII,       GUI_Font16_1,       GUI_Font16_HK,    GUI_Font16_1HK;
extern const GUI_FONT GUI_Font16B_ASCII,      GUI_Font16B_1;
extern const GUI_FONT GUI_Font24_ASCII,       GUI_Font24_1;
extern const GUI_FONT GUI_Font24B_ASCII,      GUI_Font24B_1;
extern const GUI_FONT GUI_Font32_ASCII,       GUI_Font32_1;
extern const GUI_FONT GUI_Font32B_ASCII,      GUI_Font32B_1;

 
extern const GUI_FONT GUI_Font4x6;
extern const GUI_FONT GUI_Font6x8,            GUI_Font6x9;
extern const GUI_FONT GUI_Font8x8,            GUI_Font8x9;
extern const GUI_FONT GUI_Font8x10_ASCII;
extern const GUI_FONT GUI_Font8x12_ASCII;
extern const GUI_FONT GUI_Font8x13_ASCII,     GUI_Font8x13_1;
extern const GUI_FONT GUI_Font8x15B_ASCII,    GUI_Font8x15B_1;
extern const GUI_FONT GUI_Font8x16,           GUI_Font8x17,       GUI_Font8x18;
extern const GUI_FONT GUI_Font8x16x1x2,       GUI_Font8x16x2x2,   GUI_Font8x16x3x3;

 
extern const GUI_FONT GUI_FontD24x32;
extern const GUI_FONT GUI_FontD32;
extern const GUI_FONT GUI_FontD36x48;
extern const GUI_FONT GUI_FontD48;
extern const GUI_FONT GUI_FontD48x64;
extern const GUI_FONT GUI_FontD64;
extern const GUI_FONT GUI_FontD60x80;
extern const GUI_FONT GUI_FontD80;

 
extern const GUI_FONT GUI_FontComic18B_ASCII, GUI_FontComic18B_1;
extern const GUI_FONT GUI_FontComic24B_ASCII, GUI_FontComic24B_1;













 

#line 403 ".\\Source\\uCGUI\\Core\\GUI.h"

#line 412 ".\\Source\\uCGUI\\Core\\GUI.h"

 






 











 
 










 

typedef struct GUI_CONTEXT GUI_CONTEXT;

#line 454 ".\\Source\\uCGUI\\Core\\GUI.h"
  void GUI_Lock(void);
  void GUI_Unlock(void);
  void GUITASK_Init(void);
  void GUITASK_CopyContext(void);
  GUI_CONTEXT * GUITASK_GetpContext(int Index);














 

typedef union {
  unsigned char  aColorIndex8[2];
  unsigned short aColorIndex16[2];
  unsigned long aColorIndex32[2];
} LCD_COLORINDEX_UNION;

struct GUI_CONTEXT {
 
  LCD_COLORINDEX_UNION LCD;
  LCD_RECT       ClipRect;
  unsigned char             DrawMode;
  unsigned char             SelLayer;
  unsigned char             TextStyle;
 
  GUI_RECT* pClipRect_HL;                 
  unsigned char        PenSize;
  unsigned char        PenShape;
  unsigned char        LineStyle;
  unsigned char        FillStyle;
 
  const GUI_FONT            * pAFont;

    const GUI_UC_ENC_APILIST * pUC_API;     

  signed short LBorder;
  signed short DispPosX, DispPosY;
  signed short DrawPosX, DrawPosY;
  signed short TextMode, TextAlign;
  GUI_COLOR Color, BkColor;            
 

    const GUI_RECT* WM__pUserClipRect;
    GUI_HWIN hAWin;
    int xOff, yOff;

 

    const tLCDDEV_APIList* pDeviceAPI;   
    signed short    hDevData;
    GUI_RECT    ClipRectPrev;

 

    const tLCD_HL_APIList* pLCD_HL;      
    unsigned char AA_Factor;
    unsigned char AA_HiResEnable;

};

 
#line 534 ".\\Source\\uCGUI\\Core\\GUI.h"






 
int          GUI_Init             (void);
void         GUI_SetDefault       (void);
GUI_DRAWMODE GUI_SetDrawMode      (GUI_DRAWMODE dm);
const char * GUI_GetVersionString (void);
void         GUI_SaveContext_W_M      (      GUI_CONTEXT* pContext);
void         GUI_RestoreContext   (const GUI_CONTEXT* pContext);
void         GUI_SetScreenSizeX   (int xSize);
void         GUI_SetScreenSizeY   (int ySize);
int          GUI_GetScreenSizeX   (void);
int          GUI_GetScreenSizeY   (void);
const GUI_RECT * GUI_SetClipRect  (const GUI_RECT * pRect);






 

int  GUI_RectsIntersect(const GUI_RECT* pr0, const GUI_RECT* pr1);
void GUI_MoveRect       (GUI_RECT *pRect, int x, int y);
void GUI_MergeRect      (GUI_RECT* pDest, const GUI_RECT* pr0, const GUI_RECT* pr1);
int  GUI__IntersectRects(GUI_RECT* pDest, const GUI_RECT* pr0, const GUI_RECT* pr1);
void GUI__IntersectRect (GUI_RECT* pDest, const GUI_RECT* pr0);
void GUI__ReduceRect    (GUI_RECT* pDest, const GUI_RECT *pRect, int Dist);






 

int  GUI__DivideRound     (int a, int b);
signed long  GUI__DivideRound32   (signed long a, signed long b);
int  GUI__SetText(signed short* phText, const char* s);








 
 
GUI_COLOR GUI_GetBkColor     (void);
GUI_COLOR GUI_GetColor       (void);
int       GUI_GetBkColorIndex(void);
int       GUI_GetColorIndex  (void);
unsigned char        GUI_GetPenSize     (void);
unsigned char        GUI_GetPenShape    (void);
unsigned char        GUI_GetLineStyle   (void);
unsigned char        GUI_GetFillStyle   (void);

void      GUI_SetBkColor   (GUI_COLOR);
void      GUI_SetColor     (GUI_COLOR);
void      GUI_SetBkColorIndex(int Index);
void      GUI_SetColorIndex(int Index);

unsigned char        GUI_SetPenSize   (unsigned char Size);
unsigned char        GUI_SetPenShape  (unsigned char Shape);
unsigned char        GUI_SetLineStyle (unsigned char Style);
unsigned char        GUI_SetFillStyle (unsigned char Style);

 
char      GUI_GetDecChar(void);
char      GUI_SetDecChar(char c);







 

int       GUI_Color2Index(GUI_COLOR color);
GUI_COLOR GUI_Color2VisColor(GUI_COLOR color);
char      GUI_ColorIsAvailable(GUI_COLOR color);
GUI_COLOR GUI_Index2Color(int Index);
void      GUI_InitLUT(void);
void      GUI_SetLUTEntry (unsigned char Pos, GUI_COLOR Color);
void      GUI_SetLUTColor (unsigned char Pos, GUI_COLOR Color);
void      GUI_SetLUTColorEx(unsigned char Pos, LCD_COLOR Color, unsigned int LayerIndex);
unsigned long       GUI_CalcColorDist (GUI_COLOR Color0, GUI_COLOR  Color1);
unsigned long       GUI_CalcVisColorError(GUI_COLOR color);






 
void GUI_Log      (const char *s);
void GUI_Log1     (const char *s, int p0);
void GUI_Log2     (const char *s, int p0, int p1);
void GUI_Log3     (const char *s, int p0, int p1, int p2);
void GUI_Log4     (const char *s, int p0, int p1, int p2,int p3);
void GUI_Warn     (const char *s);
void GUI_Warn1    (const char *s, int p0);
void GUI_Warn2    (const char *s, int p0, int p1);
void GUI_Warn3    (const char *s, int p0, int p1, int p2);
void GUI_Warn4    (const char *s, int p0, int p1, int p2, int p3);
void GUI_ErrorOut (const char *s);
void GUI_ErrorOut1(const char *s, int p0);
void GUI_ErrorOut2(const char *s, int p0, int p1);
void GUI_ErrorOut3(const char *s, int p0, int p1, int p2);
void GUI_ErrorOut4(const char *s, int p0, int p1, int p2, int p3);






 

int  GUI_BMP_Draw         (const void * pFileData, int x0, int y0);
int  GUI_BMP_GetXSize     (const void * pFileData);
int  GUI_BMP_GetYSize     (const void * pFileData);
void GUI_Clear            (void);
void GUI_ClearRect        (int x0, int y0, int x1, int y1);
void GUI_ClearRectEx      (const GUI_RECT* pRect);
void GUI_DrawArc          (int x0, int y0, int rx, int ry, int a0, int a1);
void GUI_DrawBitmap       (const GUI_BITMAP  * pBM, int x0, int y0);
void GUI_DrawBitmapMag    (const GUI_BITMAP  * pBM, int x0, int y0, int XMul, int YMul);
void GUI_DrawBitmapEx     (const GUI_BITMAP  * pBitmap, int x0, int y0, int xCenter, int yCenter, int xMag, int yMag);
void GUI_DrawBitmapExp    (int x0, int y0, int XSize, int YSize, int XMul,  int YMul, int BitsPerPixel, int BytesPerLine, const unsigned char  * pData, const GUI_LOGPALETTE  * pPal);
void GUI_DrawCircle       (int x0, int y0, int r);
void GUI_DrawEllipse      (int x0, int y0, int rx, int ry);
void GUI_DrawGraph        (signed short *pay, int NumPoints, int x0, int y0);
void GUI_DrawGraphEx      (signed short *pay, int NumPoints, int x0, int y0, int Numerator, int Denominator);
void GUI_DrawHLine        (int y0, int x0, int x1);
void GUI_DrawLine         (int x0, int y0, int x1, int y1);
void GUI_DrawLineRel      (int dx, int dy);
void GUI_DrawLineTo       (int x, int y);
void GUI_DrawPie          (int x0, int y0, int r, int a0, int a1, int Type);
void GUI_DrawPixel        (int x, int y);
void GUI_DrawPoint        (int x, int y);
void GUI_DrawPolygon      (const GUI_POINT* pPoints, int NumPoints, int x0, int y0);
void GUI_DrawPolyLine     (const GUI_POINT* pPoints, int NumPoints, int x0, int y0);
void GUI_DrawFocusRect    (const GUI_RECT *pRect, int Dist);
void GUI_DrawRect         (int x0, int y0, int x1, int y1);
void GUI_DrawRectEx       (const GUI_RECT *pRect);
void GUI_DrawVLine        (int x0, int y0, int y1);
void GUI_FillCircle       (int x0, int y0, int r);
void GUI_FillEllipse      (int x0, int y0, int rx, int ry);
void GUI_FillPolygon      (const GUI_POINT* pPoints, int NumPoints, int x0, int y0);
void GUI_FillRect         (int x0, int y0, int x1, int y1);
void GUI_FillRectEx       (const GUI_RECT* pRect);
void GUI_GetClientRect    (GUI_RECT* pRect);
int  GUI_GIF_Draw         (const void * pGIF, unsigned long NumBytes, int x0, int y0);
int  GUI_GIF_DrawEx       (const void * pGIF, unsigned long NumBytes, int x0, int y0, int Index);
int  GUI_GIF_GetComment   (const void * pGIF, unsigned long NumBytes, unsigned char * pBuffer, int MaxSize, int Index);
int  GUI_GIF_GetXSize     (const void * pGIF);
int  GUI_GIF_GetYSize     (const void * pGIF);
int  GUI_GIF_GetImageInfo (const void * pGIF, unsigned long NumBytes, GUI_GIF_IMAGE_INFO * pInfo, int Index);
int  GUI_GIF_GetInfo      (const void * pGIF, unsigned long NumBytes, GUI_GIF_INFO * pInfo);
void GUI_InvertRect       (int x0, int y0, int x1, int y1);
void GUI_MoveRel          (int dx, int dy);
void GUI_MoveTo           (int x, int y);






 
typedef struct {
  int XSize;
  int YSize;
} GUI_JPEG_INFO;

typedef int GUI_JPEG_GET_DATA_FUNC(void * p, int MaxNumBytes, const unsigned char ** ppData, unsigned StartOfFile);

int  GUI_JPEG_Draw        (const void * pFileData, int DataSize, int x0, int y0);
int  GUI_JPEG_DrawEx      (GUI_JPEG_GET_DATA_FUNC * fpGetData, void * p, int x0, int y0);
int  GUI_JPEG_DrawScaled  (const void * pFileData, int DataSize, int x0, int y0, int Num, int Denom);
int  GUI_JPEG_DrawScaledEx(GUI_JPEG_GET_DATA_FUNC * fpGetData, void * p, int x0, int y0, int Num, int Denom);
int  GUI_JPEG_GetInfo     (const void * pFileData, int DataSize, GUI_JPEG_INFO* pInfo);
int  GUI_JPEG_GetInfoEx   (GUI_JPEG_GET_DATA_FUNC * fpGetData, void * p, GUI_JPEG_INFO * pInfo);






 

typedef struct {
  const  GUI_BITMAP * pBitmap;
  int xHot, yHot;
} GUI_CURSOR;


  void               GUI_CURSOR_Activate   (void);
  void               GUI_CURSOR_Deactivate (void);
  int                GUI_CURSOR_GetState   (void);
  void               GUI_CURSOR_Hide       (void);
  void               GUI_CURSOR_SetXor     (const GUI_BITMAP * pBM, int x, int y);
  void               GUI_CURSOR_SetPosition(int x, int y);
  const GUI_CURSOR  * GUI_CURSOR_Select     (const GUI_CURSOR  * pCursor);
  void               GUI_CURSOR_Show       (void);










 
extern const GUI_CURSOR GUI_CursorArrowS,  GUI_CursorArrowSI;
extern const GUI_CURSOR GUI_CursorArrowM,  GUI_CursorArrowMI;
extern const GUI_CURSOR GUI_CursorArrowL,  GUI_CursorArrowLI;
extern const GUI_CURSOR GUI_CursorCrossS,  GUI_CursorCrossSI;
extern const GUI_CURSOR GUI_CursorCrossM,  GUI_CursorCrossMI;
extern const GUI_CURSOR GUI_CursorCrossL,  GUI_CursorCrossLI;
extern const GUI_CURSOR GUI_CursorHeaderM, GUI_CursorHeaderMI;

extern const GUI_BITMAP GUI_BitmapArrowS, GUI_BitmapArrowSI;
extern const GUI_BITMAP GUI_BitmapArrowM, GUI_BitmapArrowMI;
extern const GUI_BITMAP GUI_BitmapArrowL, GUI_BitmapArrowLI;
extern const GUI_BITMAP GUI_BitmapCrossS, GUI_BitmapCrossSI;
extern const GUI_BITMAP GUI_BitmapCrossM, GUI_BitmapCrossMI;
extern const GUI_BITMAP GUI_BitmapCrossL, GUI_BitmapCrossLI;






 

void  GUI_DispCEOL (void);
void  GUI_DispChar  (unsigned short c);
void  GUI_DispChars (unsigned short c, int Cnt);
void  GUI_DispCharAt(unsigned short c, signed short x, signed short y);
void  GUI_DispString         (const char  *s);
void  GUI_DispStringAt       (const char  *s, int x, int y);
void  GUI_DispStringAtCEOL   (const char  *s, int x, int y);
void  GUI_DispStringHCenterAt(const char  *s, int x, int y);
void  GUI__DispStringInRect  (const char  *s, GUI_RECT* pRect, int TextAlign, int MaxNumChars);
void  GUI_DispStringInRect   (const char  *s, GUI_RECT* pRect, int Flags);

  void  GUI_DispStringInRectEx (const char  *s, GUI_RECT* pRect, int TextAlign, int MaxLen, const tLCD_APIList * pLCD_Api);

void  GUI_DispStringInRectMax(const char  *s, GUI_RECT* pRect, int TextAlign, int MaxLen);  
void  GUI_DispStringInRectWrap(const char  *s, GUI_RECT* pRect, int TextAlign, GUI_WRAPMODE WrapMode);  
void  GUI_DispStringLen      (const char  *s, int Len);
void  GUI_GetTextExtend(GUI_RECT* pRect, const char  * s, int Len);
int   GUI_GetYAdjust(void);
int   GUI_GetDispPosX(void);
int   GUI_GetDispPosY(void);
const GUI_FONT  * GUI_GetFont(void);
int   GUI_GetCharDistX(unsigned short c);
int   GUI_GetStringDistX(const char  *s);
GUI_DRAWMODE GUI_GetDrawMode(void);
int   GUI_GetFontDistY(void);
int   GUI_GetFontSizeY(void);
void  GUI_GetFontInfo   (const GUI_FONT  * pFont, GUI_FONTINFO* pfi);
void  GUI_GetOrg(int * px, int * py);
int   GUI_GetYSizeOfFont(const GUI_FONT  * pFont);
int   GUI_GetYDistOfFont(const GUI_FONT  * pFont);
int   GUI_GetTextAlign(void);
int   GUI_GetTextMode(void);
char  GUI_IsInFont(const GUI_FONT  * pFont, unsigned short c);
int   GUI_SetTextAlign(int Align);
int   GUI_SetTextMode(int Mode);
char  GUI_SetTextStyle(char Style);
int   GUI_SetLBorder(int x);
void  GUI_SetOrg(int x, int y);
const GUI_FONT  * GUI_SetFont(const GUI_FONT  * pNewFont);
char  GUI_GotoXY(int x, int y);
char  GUI_GotoX(int x);
char  GUI_GotoY(int y);
void  GUI_DispNextLine(void);






 
void GUI_SIF_CreateFont(void * pFontData, GUI_FONT * pFont, const tGUI_SIF_APIList * pFontType);
void GUI_SIF_DeleteFont(GUI_FONT * pFont);






 

int   GUI_UC_ConvertUC2UTF8   (const unsigned short  * s, int Len, char * pBuffer, int BufferSize);
int   GUI_UC_ConvertUTF82UC   (const char  * s, int Len, unsigned short * pBuffer, int BufferSize);
int   GUI_UC_Encode           (char* s, unsigned short Char);
int   GUI_UC_GetCharSize      (const char  * s);
unsigned short   GUI_UC_GetCharCode      (const char  * s);
void  GUI_UC_SetEncodeNone    (void);
void  GUI_UC_SetEncodeUTF8    (void);

void GUI_UC_DispString(const unsigned short  *s);
void GUI_UC2DB (unsigned short Code, unsigned char* pOut);
unsigned short  GUI_DB2UC (unsigned char Byte0, unsigned char Byte1);






 

void GUI_DispBin  (unsigned long  v, unsigned char Len);
void GUI_DispBinAt(unsigned long  v, signed short x, signed short y, unsigned char Len);
void GUI_DispDec  (signed long v, unsigned char Len);
void GUI_DispDecAt (signed long v, signed short x, signed short y, unsigned char Len);
void GUI_DispDecMin(signed long v);
void GUI_DispDecShift(signed long v, unsigned char Len, unsigned char Shift);
void GUI_DispDecSpace(signed long v, unsigned char MaxDigits);
void GUI_DispHex  (unsigned long v, unsigned char Len);
void GUI_DispHexAt(unsigned long v, signed short x, signed short y, unsigned char Len);
void GUI_DispSDec(signed long v, unsigned char Len);
void GUI_DispSDecShift(signed long v, unsigned char Len, unsigned char Shift);










 

void GUI_DispFloat    (float v, char Len);
void GUI_DispFloatFix (float v, char Len, char Fract);
void GUI_DispFloatMin (float v, char Fract);
void GUI_DispSFloatFix(float v, char Len, char Fract);
void GUI_DispSFloatMin(float v, char Fract);







 


   
  signed short GUI_ALLOC_GetNumFreeBytes (void);
  signed short GUI_ALLOC_GetNumFreeBlocks(void);
  signed short GUI_ALLOC_GetNumUsedBytes (void);
  signed short GUI_ALLOC_GetNumUsedBlocks(void);
#line 905 ".\\Source\\uCGUI\\Core\\GUI.h"

signed short           GUI_ALLOC_AllocInit  (const void *pInitData, signed short Size);
signed short           GUI_ALLOC_AllocNoInit(signed short size);
signed short           GUI_ALLOC_AllocZero  (signed short size);
void               GUI_ALLOC_Free       (signed short  hMem);
void               GUI_ALLOC_FreePtrArray(signed short * pArray, int NumElems);
void               GUI_ALLOC_FreePtr    (signed short *phMem);
signed short GUI_ALLOC_GetSize    (signed short  hMem);
signed short GUI_ALLOC_GetMaxSize (void);
void*              GUI_ALLOC_h2p        (signed short  hMem);
void               GUI_ALLOC_Init       (void);
signed short           GUI_ALLOC_Realloc    (signed short hOld, int NewSize);
void               GUI_ALLOC_Lock       (void);
void               GUI_ALLOC_Unlock     (void);







 





  typedef signed short GUI_MEMDEV_Handle;
  typedef void GUI_CALLBACK_VOID_P(void* p);

  typedef struct {
    GUI_RECT rView, rPrev;
    char FirstCall;
  } GUI_AUTODEV;

  typedef struct {
    char DrawFixed;
    char IsMeasurement;
  } GUI_AUTODEV_INFO;

  int  GUI_MEMDEV_CreateAuto(GUI_AUTODEV * pAutoDev);
  void GUI_MEMDEV_DeleteAuto(GUI_AUTODEV * pAutoDev);
  int  GUI_MEMDEV_DrawAuto  (GUI_AUTODEV * pAutoDev, GUI_AUTODEV_INFO * pAutoDevInfo, GUI_CALLBACK_VOID_P * pfDraw, void * pData);

   
  GUI_MEMDEV_Handle GUI_MEMDEV_Create     (int x0, int y0, int XSize, int YSize);
  GUI_MEMDEV_Handle GUI_MEMDEV_CreateEx   (int x0, int y0, int XSize, int YSize, int Flags);
  GUI_MEMDEV_Handle GUI_MEMDEV_CreateFixed(int x0, int y0, int xsize, int ysize, int Flags,
                                           const tLCDDEV_APIList * pMemDevAPI,
                                           const LCD_API_COLOR_CONV * pColorConvAPI);
  void GUI_MEMDEV_Clear         (GUI_MEMDEV_Handle hMem);
  void GUI_MEMDEV_CopyFromLCD   (GUI_MEMDEV_Handle hMem);
  void GUI_MEMDEV_CopyFromLCDAA (GUI_MEMDEV_Handle hMem);
  void GUI_MEMDEV_CopyToLCD     (GUI_MEMDEV_Handle hMem);
  void GUI_MEMDEV_CopyToLCDAA   (GUI_MEMDEV_Handle hMem);
  void GUI_MEMDEV_CopyToLCDAt   (GUI_MEMDEV_Handle hMem, int x, int y);
  int  GUI_MEMDEV_CompareWithLCD(GUI_MEMDEV_Handle hMem, int*px, int*py, int *pExp, int*pAct);
  void GUI_MEMDEV_Delete        (GUI_MEMDEV_Handle MemDev);
  int  GUI_MEMDEV_GetXSize      (GUI_MEMDEV_Handle hMem);
  int  GUI_MEMDEV_GetYSize      (GUI_MEMDEV_Handle hMem);
  void GUI_MEMDEV_MarkDirty     (GUI_MEMDEV_Handle hMem, int x0, int y0, int x1, int y1);
  void GUI_MEMDEV_ReduceYSize   (GUI_MEMDEV_Handle hMem, int YSize);
  GUI_MEMDEV_Handle GUI_MEMDEV_Select (GUI_MEMDEV_Handle hMem);   
  void  GUI_MEMDEV_SetOrg        (GUI_MEMDEV_Handle hMem, int x0, int y0);
  void  GUI_MEMDEV_WriteAt       (GUI_MEMDEV_Handle hMem, int x, int y);
  void  GUI_MEMDEV_Write         (GUI_MEMDEV_Handle hMem);
  void  GUI_MEMDEV_WriteAlphaAt  (GUI_MEMDEV_Handle hMem, int Alpha, int x, int y);
  void  GUI_MEMDEV_WriteAlpha    (GUI_MEMDEV_Handle hMem, int Alpha);
  void  GUI_MEMDEV_WriteExAt     (GUI_MEMDEV_Handle hMem, int x, int y, int xMag, int yMag, int Alpha);
  void  GUI_MEMDEV_WriteEx       (GUI_MEMDEV_Handle hMem, int xMag, int yMag, int Alpha);
  int   GUI_MEMDEV_Draw          (GUI_RECT* pRect, GUI_CALLBACK_VOID_P* pfDraw, void* pData, int MemSize, int Flags);
  void* GUI_MEMDEV_GetDataPtr    (GUI_MEMDEV_Handle hMem);
  void  GUI_MEMDEV_SetColorConv  (GUI_MEMDEV_Handle hMem, const LCD_API_COLOR_CONV * pColorConvAPI);


void GUI_SelectLCD(void);
unsigned int GUI_SelectLayer(unsigned int Index);






 

typedef signed short GUI_MEASDEV_Handle;

GUI_MEASDEV_Handle GUI_MEASDEV_Create (void);
void               GUI_MEASDEV_Delete (GUI_MEASDEV_Handle hMemDev);
void               GUI_MEASDEV_Select (GUI_MEASDEV_Handle hMem);
void               GUI_MEASDEV_GetRect(GUI_MEASDEV_Handle hMem, GUI_RECT *pRect);
void               GUI_MEASDEV_ClearRect(GUI_MEASDEV_Handle hMem);






 
void GUI_RotatePolygon(GUI_POINT* pDest, const GUI_POINT* pSrc, int NumPoints, float Angle);
void GUI_MagnifyPolygon(GUI_POINT* pDest, const GUI_POINT* pSrc, int NumPoints, int Mag);
void GUI_EnlargePolygon(GUI_POINT* pDest, const GUI_POINT* pSrc, int NumPoints, int Len);






 
void GUI_DrawStreamedBitmap(const GUI_BITMAP_STREAM *pBitmapStream, int x, int y);






 
typedef void GUI_CALLBACK_VOID_U8_P(unsigned char Data, void * p);

void GUI_BMP_SerializeEx(GUI_CALLBACK_VOID_U8_P * pfSerialize, int x0, int y0, int xSize, int ySize, void * p);
void GUI_BMP_Serialize  (GUI_CALLBACK_VOID_U8_P * pfSerialize, void * p);






 
void GUI_Delay  (int Period);
int  GUI_GetTime(void);
int  GUI_Exec(void);          
int  GUI_Exec1(void);         








 
int     GUI_MessageBox   (const char * sMessage, const char * sCaption, int Flags);











 

typedef struct {
  int Time;
  unsigned long            Context;
} GUI_TIMER_MESSAGE;

typedef signed short GUI_TIMER_HANDLE;
typedef void GUI_TIMER_CALLBACK(  GUI_TIMER_MESSAGE* pTM);

GUI_TIMER_HANDLE GUI_TIMER_Create   (GUI_TIMER_CALLBACK* cb, int Time,  unsigned long Context, int Flags);
void             GUI_TIMER_Delete   (GUI_TIMER_HANDLE hObj);

 
void GUI_TIMER_SetPeriod (GUI_TIMER_HANDLE hObj, int Period);
void GUI_TIMER_SetTime   (GUI_TIMER_HANDLE hObj, int Period);
void GUI_TIMER_SetDelay  (GUI_TIMER_HANDLE hObj, int Delay);
void GUI_TIMER_Restart   (GUI_TIMER_HANDLE hObj);
int  GUI_TIMER_Exec(void);







 

void GUI_AA_DisableHiRes     (void);
void GUI_AA_EnableHiRes      (void);
int  GUI_AA_GetFactor        (void);
void GUI_AA_SetFactor        (int Factor);
void GUI_AA_DrawArc          (int x0, int y0, int rx, int ry, int a0, int a1);
void GUI_AA_DrawLine         (int x0, int y0, int x1, int y1);
void GUI_AA_DrawPolyOutline  (const GUI_POINT * pSrc, int NumPoints, int Thickness, int x, int y);
void GUI_AA_DrawPolyOutlineEx(const GUI_POINT * pSrc, int NumPoints, int Thickness, int x, int y, GUI_POINT * pBuffer);
void GUI_AA_FillCircle       (int x0, int y0, int r);
void GUI_AA_FillPolygon      (GUI_POINT* pPoints, int NumPoints, int x0, int y0);






 

 
void GUI_StoreKeyMsg(int Key, int Pressed);
void GUI_SendKeyMsg (int Key, int Pressed);
int  GUI_PollKeyMsg(void);

 
typedef int GUI_KEY_MSG_HOOK(int Key, int Pressed);
extern  GUI_KEY_MSG_HOOK* GUI_pfKeyMsgHook;
GUI_KEY_MSG_HOOK* GUI_SetKeyMsgHook(GUI_KEY_MSG_HOOK* pHook);

 
int  GUI_GetKey(void);
int  GUI_WaitKey(void);
void GUI_StoreKey(int c);
void GUI_ClearKeyBuffer(void);




 
void GUI_WaitEvent(void);




 

void GUI_PID_StoreState(const GUI_PID_STATE *pState);
int  GUI_PID_GetState  (      GUI_PID_STATE *pState);




 
int  GUI_MOUSE_GetState  (      GUI_PID_STATE *pState);
void GUI_MOUSE_StoreState(const GUI_PID_STATE *pState);




 

int  GUI_TOUCH_GetState     (GUI_PID_STATE *pState);
void GUI_TOUCH_GetUnstable  (int* px, int* py);   
void GUI_TOUCH_StoreState   (int x, int y);
void GUI_TOUCH_StoreStateEx (const GUI_PID_STATE *pState);
void GUI_TOUCH_StoreUnstable(int x, int y);





 
void GUI_MOUSE_DRIVER_PS2_Init(void);                
void GUI_MOUSE_DRIVER_PS2_OnRx(unsigned char Data);





 

void GUI_TOUCH_Exec(void);
void GUI_CTOUCH_Exec(void);
int  GUI_TOUCH_Calibrate(int Coord, int Log0, int Log1, int Phys0, int Phys1);
void GUI_TOUCH_SetDefaultCalibration(void);
int  GUI_TOUCH_GetxPhys(void);     
int  GUI_TOUCH_GetyPhys(void);     
void GUI_TOUCH_GetCalData(int Coord, int* pMin,int* pMax);













 

void GUI_TOUCH_X_ActivateX(void);
void GUI_TOUCH_X_ActivateY(void);
void GUI_TOUCH_X_Disable(void);
int  GUI_TOUCH_X_MeasureX(void);
int  GUI_TOUCH_X_MeasureY(void);






 

extern const GUI_BITMAP_METHODS GUI_BitmapMethodsRLE4;
extern const GUI_BITMAP_METHODS GUI_BitmapMethodsRLE8;
extern const GUI_BITMAP_METHODS GUI_BitmapMethodsRLE16;
extern const GUI_BITMAP_METHODS GUI_BitmapMethodsRLEM16;
extern const GUI_BITMAP_METHODS GUI_BitmapMethods555;
extern const GUI_BITMAP_METHODS GUI_BitmapMethodsM555;
extern const GUI_BITMAP_METHODS GUI_BitmapMethods565;
extern const GUI_BITMAP_METHODS GUI_BitmapMethodsM565;
extern const GUI_BITMAP_METHODS GUI_BitmapMethods888;
extern const GUI_BITMAP_METHODS GUI_BitmapMethodsM888;




#line 1225 ".\\Source\\uCGUI\\Core\\GUI.h"

extern const tGUI_SIF_APIList GUI_SIF_APIList_Prop;
extern const tGUI_SIF_APIList GUI_SIF_APIList_Prop_AA2;
extern const tGUI_SIF_APIList GUI_SIF_APIList_Prop_AA4;






 

#line 1493 ".\\Source\\uCGUI\\Core\\GUI.h"






 

#line 1511 ".\\Source\\uCGUI\\Core\\GUI.h"



 
	 	 			 		    	 				 	  			   	 	 	 	 	 	  	  	      	   		 	 	 		  		  	 		 	  	  			     			       	   	 			  		    	 	     	 				  	 					 	 			   	  	  			 				 		 	 	 			     			 
#line 4 "Source\\uCGUI\\TouchCalibration\\TouchCalibration.h"
#line 1 ".\\Source\\uCGUI\\Core\\LCD_ConfDefaults.h"

















 




#line 1 ".\\Source\\uCGUI\\Config\\LCDConf.h"




#line 11 ".\\Source\\uCGUI\\Config\\LCDConf.h"
extern 	void Lcd_Init(void); 



#line 24 ".\\Source\\uCGUI\\Core\\LCD_ConfDefaults.h"
#line 25 ".\\Source\\uCGUI\\Core\\LCD_ConfDefaults.h"







 













































































#line 116 ".\\Source\\uCGUI\\Core\\LCD_ConfDefaults.h"

#line 123 ".\\Source\\uCGUI\\Core\\LCD_ConfDefaults.h"






















 










 


















 


 

#line 186 ".\\Source\\uCGUI\\Core\\LCD_ConfDefaults.h"

#line 193 ".\\Source\\uCGUI\\Core\\LCD_ConfDefaults.h"









 









 

#line 229 ".\\Source\\uCGUI\\Core\\LCD_ConfDefaults.h"

 
#line 255 ".\\Source\\uCGUI\\Core\\LCD_ConfDefaults.h"

#line 267 ".\\Source\\uCGUI\\Core\\LCD_ConfDefaults.h"





 












#line 292 ".\\Source\\uCGUI\\Core\\LCD_ConfDefaults.h"

#line 312 ".\\Source\\uCGUI\\Core\\LCD_ConfDefaults.h"





#line 323 ".\\Source\\uCGUI\\Core\\LCD_ConfDefaults.h"


 









 
#line 426 ".\\Source\\uCGUI\\Core\\LCD_ConfDefaults.h"






 
#line 523 ".\\Source\\uCGUI\\Core\\LCD_ConfDefaults.h"






 
#line 620 ".\\Source\\uCGUI\\Core\\LCD_ConfDefaults.h"






 
#line 717 ".\\Source\\uCGUI\\Core\\LCD_ConfDefaults.h"








 


#line 737 ".\\Source\\uCGUI\\Core\\LCD_ConfDefaults.h"









	 	 			 		    	 				 	  			   	 	 	 	 	 	  	  	      	   		 	 	 		  		  	 		 	  	  			     			       	   	 			  		    	 	     	 				  	 					 	 			   	  	  			 				 		 	 	 			     			 
#line 5 "Source\\uCGUI\\TouchCalibration\\TouchCalibration.h"

#line 1 ".\\Source\\uCGUI\\Widget\\BUTTON.h"

















 




#line 1 ".\\Source\\uCGUI\\WM\\WM.h"

















 





#line 25 ".\\Source\\uCGUI\\WM\\WM.h"
#line 26 ".\\Source\\uCGUI\\WM\\WM.h"
#line 1 ".\\Source\\uCGUI\\WM\\WM_GUI.h"

















 








int       WM__InitIVRSearch(const GUI_RECT* pMaxRect);
int       WM__GetNextIVR   (void);
int       WM__GetOrgX_AA(void);
int       WM__GetOrgY_AA(void);










#line 50 ".\\Source\\uCGUI\\WM\\WM_GUI.h"








 
	 	 			 		    	 				 	  			   	 	 	 	 	 	  	  	      	   		 	 	 		  		  	 		 	  	  			     			       	   	 			  		    	 	     	 				  	 					 	 			   	  	  			 				 		 	 	 			     			 
#line 27 ".\\Source\\uCGUI\\WM\\WM.h"





 





 
#line 46 ".\\Source\\uCGUI\\WM\\WM.h"




 








 













 




 











 










 









 

typedef struct {
  int Key, PressedCnt;
} WM_KEY_INFO;

typedef struct {
  int NumItems, v, PageSize;
} WM_SCROLL_STATE;

typedef struct {
  int Done;
  int ReturnValue;
} WM_DIALOG_STATUS;

typedef struct {
  int x,y;
  unsigned char  State;
  unsigned char  StatePrev;
} WM_PID_STATE_CHANGED_INFO;








 









































#line 189 ".\\Source\\uCGUI\\WM\\WM.h"


















 
#line 218 ".\\Source\\uCGUI\\WM\\WM.h"






 









 










 

#line 254 ".\\Source\\uCGUI\\WM\\WM.h"
 




 





#line 272 ".\\Source\\uCGUI\\WM\\WM.h"




 

typedef struct WM_Obj     WM_Obj;
typedef struct WM_OBJ_X   WM_OBJ_X;
typedef struct WM_MESSAGE WM_MESSAGE;

typedef void WM_CALLBACK( WM_MESSAGE* pMsg);

struct WM_MESSAGE {
  int MsgId;             
  GUI_HWIN hWin;          
  GUI_HWIN hWinSrc;       
  union {
    const void* p;             
    int v;
    GUI_COLOR Color;
  } Data;
};

struct WM_Obj {
  GUI_RECT Rect;         
  GUI_RECT InvalidRect;  
  WM_CALLBACK* cb;       
  GUI_HWIN hNextLin;      
  GUI_HWIN hParent;
  GUI_HWIN hFirstChild;
  GUI_HWIN hNext;
  unsigned short Status;	           
};

struct WM_OBJ_X {        
  int    Dummy;
  struct WM_Obj Win;
};

typedef void WM_tfPollPID(void);
typedef void WM_tfForEach(GUI_HWIN hWin, void * pData);







 


void WM_Activate  (void);
void WM_Deactivate(void);
void WM_Init      (void);
int  WM_Exec      (void);     
int  WM_Exec1     (void);     
unsigned short  WM_SetCreateFlags(unsigned short Flags);
WM_tfPollPID* WM_SetpfPollPID(WM_tfPollPID* pf);
void WM_SetCapture(GUI_HWIN hObj, int AutoRelease);
void WM_SetCaptureMove(GUI_HWIN hWin, const GUI_PID_STATE* pState, int MinVisibility, int LimitTop);  
void WM_ReleaseCapture(void);






 

void    WM_AttachWindow              (GUI_HWIN hWin, GUI_HWIN hParent);
void    WM_AttachWindowAt            (GUI_HWIN hWin, GUI_HWIN hParent, int x, int y);
int     WM_CheckScrollPos            (WM_SCROLL_STATE* pScrollState, int Pos, int LowerDist, int UpperDist);  
void    WM_ClrHasTrans               (GUI_HWIN hWin);
GUI_HWIN WM_CreateWindow              (int x0, int y0, int xSize, int ySize, unsigned short Style, WM_CALLBACK* cb, int NumExtraBytes);
GUI_HWIN WM_CreateWindowAsChild       (int x0, int y0, int xSize, int ySize, GUI_HWIN hWinParent, unsigned short Style, WM_CALLBACK* cb, int NumExtraBytes);
void    WM_DeleteWindow              (GUI_HWIN hWin);
void    WM_DetachWindow              (GUI_HWIN hWin);
int     WM_GetHasTrans               (GUI_HWIN hWin);
GUI_HWIN WM_GetFocussedWindow         (void);
void    WM_HideWindow                (GUI_HWIN hWin);
void    WM_InvalidateArea            (const GUI_RECT* pRect);
void    WM_InvalidateRect            (GUI_HWIN hWin, const GUI_RECT*pRect);
void    WM_InvalidateWindow          (GUI_HWIN hWin);
void    WM_InvalidateWindowAndDescsEx(GUI_HWIN hWin, const GUI_RECT * pInvalidRect);
void    WM_InvalidateWindowAndDescs  (GUI_HWIN hWin);     
int     WM_IsEnabled                 (GUI_HWIN hObj);
int     WM_IsFocussable              (GUI_HWIN hWin);
int     WM_IsVisible                 (GUI_HWIN hWin);
int     WM_IsWindow                  (GUI_HWIN hWin);     
char    WM_IsCompletelyVisible       (GUI_HWIN hWin);     
void    WM_SetHasTrans               (GUI_HWIN hWin);
void    WM_SetId                     (GUI_HWIN hObj, int Id);
void    WM_SetTransState             (GUI_HWIN hWin, unsigned State);
void    WM_ShowWindow                (GUI_HWIN hWin);
void    WM_ValidateRect              (GUI_HWIN hWin, const GUI_RECT*pRect);
void    WM_ValidateWindow            (GUI_HWIN hWin);
int     WM_GetInvalidRect            (GUI_HWIN hWin, GUI_RECT * pRect);
void    WM_SetStayOnTop              (GUI_HWIN hWin, int OnOff);
int     WM_GetStayOnTop              (GUI_HWIN hWin);
void    WM_SetAnchor                 (GUI_HWIN hWin, unsigned short AnchorFlags);

 
void WM_MoveWindow                (GUI_HWIN hWin, int dx, int dy);
void WM_ResizeWindow              (GUI_HWIN hWin, int dx, int dy);
void WM_MoveTo                    (GUI_HWIN hWin, int x, int y);
void WM_MoveChildTo               (GUI_HWIN hWin, int x, int y);
void WM_SetSize                   (GUI_HWIN hWin, int XSize, int YSize);
void WM_SetWindowPos              (GUI_HWIN hWin, int xPos, int yPos, int xSize, int ySize);
int  WM_SetXSize                  (GUI_HWIN hWin, int xSize);
int  WM_SetYSize                  (GUI_HWIN hWin, int ySize);
int  WM_CreateTimer               (GUI_HWIN hWin, int UserID, int Period, int Mode);  
void WM_DeleteTimer               (GUI_HWIN hWin, int UserId);  
int  WM_SetScrollbarH             (GUI_HWIN hWin, int OnOff);  
int  WM_SetScrollbarV             (GUI_HWIN hWin, int OnOff);  


 
int WM_GetNumWindows(void);
int WM_GetNumInvalidWindows(void);

 
void WM_CheckScrollBounds(WM_SCROLL_STATE* pScrollState);  
int  WM_GetScrollPosH    (GUI_HWIN hWin);
int  WM_GetScrollPosV    (GUI_HWIN hWin);
void WM_SetScrollPosH    (GUI_HWIN hWin, unsigned ScrollPos);
void WM_SetScrollPosV    (GUI_HWIN hWin, unsigned ScrollPos);
int  WM_SetScrollValue   (WM_SCROLL_STATE* pScrollState, int v);  


 
WM_CALLBACK * WM_SetCallback(GUI_HWIN hWin, WM_CALLBACK * cb);
WM_CALLBACK * WM_GetCallback(GUI_HWIN hWin);

 
void WM_GetClientRect             (GUI_RECT* pRect);
void WM_GetClientRectEx           (GUI_HWIN hWin, GUI_RECT* pRect);
void WM_GetInsideRect             (GUI_RECT* pRect);
void WM_GetInsideRectEx           (GUI_HWIN hWin, GUI_RECT* pRect);
void WM_GetInsideRectExScrollbar  (GUI_HWIN hWin, GUI_RECT* pRect);  
void WM_GetWindowRect             (GUI_RECT* pRect);
void WM_GetWindowRectEx           (GUI_HWIN hWin, GUI_RECT* pRect);
int  WM_GetOrgX                   (void);
int  WM_GetOrgY                   (void);
int  WM_GetWindowOrgX             (GUI_HWIN hWin);
int  WM_GetWindowOrgY             (GUI_HWIN hWin);
int  WM_GetWindowSizeX            (GUI_HWIN hWin);
int  WM_GetWindowSizeY            (GUI_HWIN hWin);
GUI_HWIN WM_GetFirstChild          (GUI_HWIN hWin);
GUI_HWIN WM_GetNextSibling         (GUI_HWIN hWin);
GUI_HWIN WM_GetParent              (GUI_HWIN hWin);
GUI_HWIN WM_GetPrevSibling         (GUI_HWIN hWin);
int     WM_GetId                  (GUI_HWIN hWin);
GUI_HWIN WM_GetScrollbarV          (GUI_HWIN hWin);
GUI_HWIN WM_GetScrollbarH          (GUI_HWIN hWin);
GUI_HWIN WM_GetScrollPartner       (GUI_HWIN hWin);
GUI_HWIN WM_GetClientWindow        (GUI_HWIN hObj);
GUI_COLOR WM_GetBkColor           (GUI_HWIN hObj);

 
void WM_BringToBottom(GUI_HWIN hWin);
void WM_BringToTop(GUI_HWIN hWin);

GUI_COLOR WM_SetDesktopColor(GUI_COLOR Color);
GUI_COLOR WM_SetDesktopColorEx(GUI_COLOR Color, unsigned int LayerIndex);
void WM_SetDesktopColors(GUI_COLOR Color);

 
GUI_HWIN WM_SelectWindow           (GUI_HWIN  hWin);
GUI_HWIN WM_GetActiveWindow        (void);
void    WM_Paint                  (GUI_HWIN hObj);
void    WM_Update                 (GUI_HWIN hWin);
void    WM_PaintWindowAndDescs    (GUI_HWIN hWin);
void    WM_UpdateWindowAndDescs   (GUI_HWIN hWin);

 
GUI_HWIN WM_GetDesktopWindow    (void);
GUI_HWIN WM_GetDesktopWindowEx  (unsigned int LayerIndex);

 
const GUI_RECT* WM_SetUserClipRect(const GUI_RECT* pRect);
void            WM_SetDefault     (void);

 
void WM_EnableMemdev              (GUI_HWIN hWin);
void WM_DisableMemdev             (GUI_HWIN hWin);

int WM_OnKey(int Key, int Pressed);
void WM_MakeModal(GUI_HWIN hWin);









 

void      WM_NotifyParent         (GUI_HWIN hWin, int Notification);
void      WM_SendMessage          (GUI_HWIN hWin, WM_MESSAGE* p);
void      WM_SendMessageNoPara    (GUI_HWIN hWin, int MsgId);              
void      WM_DefaultProc          (WM_MESSAGE* pMsg);
int       WM_BroadcastMessage     (WM_MESSAGE* pMsg);
void      WM_SetScrollState       (GUI_HWIN hWin, const WM_SCROLL_STATE* pState);
void      WM_SetEnableState       (GUI_HWIN hItem, int State);
void      WM_SendToParent         (GUI_HWIN hWin, WM_MESSAGE* pMsg);
int       WM_HasCaptured          (GUI_HWIN hWin);
int       WM_HasFocus             (GUI_HWIN hWin);
int       WM_SetFocus             (GUI_HWIN hWin);
GUI_HWIN   WM_SetFocusOnNextChild  (GUI_HWIN hParent);      
GUI_HWIN   WM_SetFocusOnPrevChild  (GUI_HWIN hParent);      
GUI_HWIN   WM_GetDialogItem        (GUI_HWIN hWin, int Id);
void      WM_EnableWindow         (GUI_HWIN hWin);
void      WM_DisableWindow        (GUI_HWIN hWin);
void      WM_GetScrollState       (GUI_HWIN hObj, WM_SCROLL_STATE* pScrollState);
int       WM_GetUserData          (GUI_HWIN hWin,       void* pDest, int SizeOfBuffer);
int       WM_SetUserData          (GUI_HWIN hWin, const void* pSrc,  int SizeOfBuffer);





 

int       WM_HandlePID      (void);
GUI_HWIN   WM_Screen2hWin    (int x, int y);
GUI_HWIN   WM_Screen2hWinEx  (GUI_HWIN hStop, int x, int y);
void      WM_ForEachDesc    (GUI_HWIN hWin, WM_tfForEach * pcb, void * pData);
void      WM_SetScreenSize  (int xSize, int ySize);
int       WM_PollSimMsg     (void);




 










 













#line 545 ".\\Source\\uCGUI\\WM\\WM.h"

















 
	 	 			 		    	 				 	  			   	 	 	 	 	 	  	  	      	   		 	 	 		  		  	 		 	  	  			     			       	   	 			  		    	 	     	 				  	 					 	 			   	  	  			 				 		 	 	 			     			 
#line 24 ".\\Source\\uCGUI\\Widget\\BUTTON.h"
#line 1 ".\\Source\\uCGUI\\Widget\\DIALOG_Intern.h"




















 




#line 27 ".\\Source\\uCGUI\\Widget\\DIALOG_Intern.h"













 

typedef struct  GUI_WIDGET_CREATE_INFO_struct GUI_WIDGET_CREATE_INFO;
typedef GUI_HWIN GUI_WIDGET_CREATE_FUNC       (const GUI_WIDGET_CREATE_INFO* pCreate, GUI_HWIN hWin, int x0, int y0, WM_CALLBACK* cb);






 
struct GUI_WIDGET_CREATE_INFO_struct {
  GUI_WIDGET_CREATE_FUNC* pfCreateIndirect;
  const char* pName;                      
  signed short Id;                                 
  signed short x0, y0, xSize, ySize;               
  unsigned short Flags;                              
  signed long Para;                                
};






 

GUI_HWIN BUTTON_CreateIndirect   (const GUI_WIDGET_CREATE_INFO* pCreateInfo, GUI_HWIN hWinParent, int x0, int y0, WM_CALLBACK* cb);
GUI_HWIN CHECKBOX_CreateIndirect (const GUI_WIDGET_CREATE_INFO* pCreateInfo, GUI_HWIN hWinParent, int x0, int y0, WM_CALLBACK* cb);
GUI_HWIN EDIT_CreateIndirect     (const GUI_WIDGET_CREATE_INFO* pCreateInfo, GUI_HWIN hWinParent, int x0, int y0, WM_CALLBACK* cb);
GUI_HWIN FRAMEWIN_CreateIndirect (const GUI_WIDGET_CREATE_INFO* pCreateInfo, GUI_HWIN hWinParent, int x0, int y0, WM_CALLBACK* cb);
GUI_HWIN RADIO_CreateIndirect    (const GUI_WIDGET_CREATE_INFO* pCreateInfo, GUI_HWIN hWinParent, int x0, int y0, WM_CALLBACK* cb);
GUI_HWIN SLIDER_CreateIndirect   (const GUI_WIDGET_CREATE_INFO* pCreateInfo, GUI_HWIN hWinParent, int x0, int y0, WM_CALLBACK* cb);
GUI_HWIN SCROLLBAR_CreateIndirect(const GUI_WIDGET_CREATE_INFO* pCreateInfo, GUI_HWIN hWinParent, int x0, int y0, WM_CALLBACK* cb);
GUI_HWIN TEXT_CreateIndirect     (const GUI_WIDGET_CREATE_INFO* pCreateInfo, GUI_HWIN hWinParent, int x0, int y0, WM_CALLBACK* cb);






 
int     GUI_ExecDialogBox     (const GUI_WIDGET_CREATE_INFO* paWidget, int NumWidgets, WM_CALLBACK* cb, GUI_HWIN hParent, int x0, int y0);
int     GUI_ExecCreatedDialog (GUI_HWIN hDialog);
GUI_HWIN GUI_CreateDialogBox   (const GUI_WIDGET_CREATE_INFO* paWidget, int NumWidgets, WM_CALLBACK* cb, GUI_HWIN hParent, int x0, int y0);
void    GUI_SetDialogStatusPtr(GUI_HWIN hDialog, WM_DIALOG_STATUS* pDialogStatus);  
WM_DIALOG_STATUS*  GUI_GetDialogStatusPtr(GUI_HWIN hDialog);                        
void    GUI_EndDialog(GUI_HWIN hWin, int r);
LCD_COLOR DIALOG_GetBkColor(void);                                                 
LCD_COLOR DIALOG_SetBkColor(LCD_COLOR BkColor);                                    








	 	 			 		    	 				 	  			   	 	 	 	 	 	  	  	      	   		 	 	 		  		  	 		 	  	  			     			       	   	 			  		    	 	     	 				  	 					 	 			   	  	  			 				 		 	 	 			     			 
#line 25 ".\\Source\\uCGUI\\Widget\\BUTTON.h"
#line 1 ".\\Source\\uCGUI\\Widget\\WIDGET.h"

















 








#line 1 ".\\Source\\uCGUI\\WM\\WM_Intern.h"

















 




#line 24 ".\\Source\\uCGUI\\WM\\WM_Intern.h"
#line 1 ".\\Source\\uCGUI\\Core\\GUI_Protected.h"

















 




#line 24 ".\\Source\\uCGUI\\Core\\GUI_Protected.h"
#line 1 ".\\Source\\uCGUI\\Core\\LCD_Protected.h"

















 




#line 24 ".\\Source\\uCGUI\\Core\\LCD_Protected.h"






 

typedef struct {
  int              NumEntries; 
  const LCD_COLOR* pPalEntries; 
} LCD_PHYSPALETTE; 






 
extern const unsigned char LCD_aMirror[256];







 
unsigned LCD_Color2Index_User    (LCD_COLOR Color);
unsigned LCD_Color2Index_0       (LCD_COLOR Color, const LCD_PHYSPALETTE* pPhysPal);
unsigned LCD_Color2Index_1       (LCD_COLOR Color);
unsigned LCD_Color2Index_M1      (LCD_COLOR Color);
unsigned LCD_Color2Index_2       (LCD_COLOR Color);
unsigned LCD_Color2Index_M2      (LCD_COLOR Color);
unsigned LCD_Color2Index_4       (LCD_COLOR Color);
unsigned LCD_Color2Index_M4      (LCD_COLOR Color);
unsigned LCD_Color2Index_111     (LCD_COLOR Color);
unsigned LCD_Color2Index_222     (LCD_COLOR Color);
unsigned LCD_Color2Index_233     (LCD_COLOR Color);
unsigned LCD_Color2Index_323     (LCD_COLOR Color);
unsigned LCD_Color2Index_332     (LCD_COLOR Color);
unsigned LCD_Color2Index_444_12  (LCD_COLOR Color);
unsigned LCD_Color2Index_444_12_1(LCD_COLOR Color);
unsigned LCD_Color2Index_444_16  (LCD_COLOR Color);
unsigned LCD_Color2Index_555     (LCD_COLOR Color);
unsigned LCD_Color2Index_565     (LCD_COLOR Color);
unsigned LCD_Color2Index_556     (LCD_COLOR Color);
unsigned LCD_Color2Index_655     (LCD_COLOR Color);
unsigned LCD_Color2Index_666     (LCD_COLOR Color);
unsigned LCD_Color2Index_8666    (LCD_COLOR Color);
unsigned LCD_Color2Index_8666_1  (LCD_COLOR Color);
unsigned LCD_Color2Index_888     (LCD_COLOR Color);
unsigned LCD_Color2Index_M888    (LCD_COLOR Color);
unsigned LCD_Color2Index_M111    (LCD_COLOR Color);
unsigned LCD_Color2Index_M222    (LCD_COLOR Color);
unsigned LCD_Color2Index_M233    (LCD_COLOR Color);
unsigned LCD_Color2Index_M323    (LCD_COLOR Color);
unsigned LCD_Color2Index_M332    (LCD_COLOR Color);
unsigned LCD_Color2Index_M444_12 (LCD_COLOR Color);
unsigned LCD_Color2Index_M444_16 (LCD_COLOR Color);
unsigned LCD_Color2Index_M555    (LCD_COLOR Color);
unsigned LCD_Color2Index_M565    (LCD_COLOR Color);
unsigned LCD_Color2Index_M556    (LCD_COLOR Color);
unsigned LCD_Color2Index_M655    (LCD_COLOR Color);
unsigned LCD_Color2Index_M666    (LCD_COLOR Color);

LCD_COLOR LCD_Index2Color_User    (int Index);
LCD_COLOR LCD_Index2Color_0       (int Index, const LCD_PHYSPALETTE* pPhysPal);
LCD_COLOR LCD_Index2Color_1       (int Index);
LCD_COLOR LCD_Index2Color_2       (int Index);
LCD_COLOR LCD_Index2Color_4       (int Index);
LCD_COLOR LCD_Index2Color_111     (int Index);
LCD_COLOR LCD_Index2Color_222     (int Index);
LCD_COLOR LCD_Index2Color_233     (int Index);
LCD_COLOR LCD_Index2Color_323     (int Index);
LCD_COLOR LCD_Index2Color_332     (int Index);
LCD_COLOR LCD_Index2Color_444_12  (int Index);
LCD_COLOR LCD_Index2Color_444_12_1(int Index);
LCD_COLOR LCD_Index2Color_444_16  (int Index);
LCD_COLOR LCD_Index2Color_555     (int Index);
LCD_COLOR LCD_Index2Color_565     (int Index);
LCD_COLOR LCD_Index2Color_556     (int Index);
LCD_COLOR LCD_Index2Color_655     (int Index);
LCD_COLOR LCD_Index2Color_666     (int Index);
LCD_COLOR LCD_Index2Color_8666    (int Index);
LCD_COLOR LCD_Index2Color_8666_1  (int Index);
LCD_COLOR LCD_Index2Color_888     (int Index);
LCD_COLOR LCD_Index2Color_M888    (int Index);
LCD_COLOR LCD_Index2Color_M111    (int Index);
LCD_COLOR LCD_Index2Color_M222    (int Index);
LCD_COLOR LCD_Index2Color_M233    (int Index);
LCD_COLOR LCD_Index2Color_M323    (int Index);
LCD_COLOR LCD_Index2Color_M332    (int Index);
LCD_COLOR LCD_Index2Color_M444_12 (int Index);
LCD_COLOR LCD_Index2Color_M444_16 (int Index);
LCD_COLOR LCD_Index2Color_M555    (int Index);
LCD_COLOR LCD_Index2Color_M565    (int Index);
LCD_COLOR LCD_Index2Color_M556    (int Index);
LCD_COLOR LCD_Index2Color_M655    (int Index);
LCD_COLOR LCD_Index2Color_M666    (int Index);

unsigned LCD_GetIndexMask_User    (void);
unsigned LCD_GetIndexMask_0       (void);
unsigned LCD_GetIndexMask_1       (void);
unsigned LCD_GetIndexMask_M1      (void);
unsigned LCD_GetIndexMask_2       (void);
unsigned LCD_GetIndexMask_M2      (void);
unsigned LCD_GetIndexMask_4       (void);
unsigned LCD_GetIndexMask_M4      (void);
unsigned LCD_GetIndexMask_111     (void);
unsigned LCD_GetIndexMask_222     (void);
unsigned LCD_GetIndexMask_233     (void);
unsigned LCD_GetIndexMask_323     (void);
unsigned LCD_GetIndexMask_332     (void);
unsigned LCD_GetIndexMask_444_12  (void);
unsigned LCD_GetIndexMask_444_12_1(void);
unsigned LCD_GetIndexMask_444_16  (void);
unsigned LCD_GetIndexMask_555     (void);
unsigned LCD_GetIndexMask_565     (void);
unsigned LCD_GetIndexMask_556     (void);
unsigned LCD_GetIndexMask_655     (void);
unsigned LCD_GetIndexMask_666     (void);
unsigned LCD_GetIndexMask_8666    (void);
unsigned LCD_GetIndexMask_8666_1  (void);
unsigned LCD_GetIndexMask_888     (void);
unsigned LCD_GetIndexMask_M888    (void);
unsigned LCD_GetIndexMask_M111    (void);
unsigned LCD_GetIndexMask_M222    (void);
unsigned LCD_GetIndexMask_M233    (void);
unsigned LCD_GetIndexMask_M323    (void);
unsigned LCD_GetIndexMask_M332    (void);
unsigned LCD_GetIndexMask_M444_12 (void);
unsigned LCD_GetIndexMask_M444_16 (void);
unsigned LCD_GetIndexMask_M555    (void);
unsigned LCD_GetIndexMask_M565    (void);
unsigned LCD_GetIndexMask_M556    (void);
unsigned LCD_GetIndexMask_M655    (void);
unsigned LCD_GetIndexMask_M666    (void);

void LCD_SelectLCD(void);














 

unsigned int LCD_L0_Color2Index       (LCD_COLOR Color);
unsigned int LCD_L0_1_Color2Index     (LCD_COLOR Color);
unsigned int LCD_L0_2_Color2Index     (LCD_COLOR Color);
unsigned int LCD_L0_3_Color2Index     (LCD_COLOR Color);
unsigned int LCD_L0_4_Color2Index     (LCD_COLOR Color);
void         LCD_L0_DrawHLine         (int x0, int y0,  int x1);
void         LCD_L0_1_DrawHLine       (int x0, int y0,  int x1);
void         LCD_L0_2_DrawHLine       (int x0, int y0,  int x1);
void         LCD_L0_3_DrawHLine       (int x0, int y0,  int x1);
void         LCD_L0_4_DrawHLine       (int x0, int y0,  int x1);
void         LCD_L0_MAG_DrawHLine     (int x0, int y0,  int x1);
void         LCD_L0_DELTA_DrawHLine     (int x0, int y0,  int x1);
void         LCD_L0_DrawVLine         (int x,  int y0,  int y1);
void         LCD_L0_1_DrawVLine       (int x,  int y0,  int y1);
void         LCD_L0_2_DrawVLine       (int x,  int y0,  int y1);
void         LCD_L0_3_DrawVLine       (int x,  int y0,  int y1);
void         LCD_L0_4_DrawVLine       (int x,  int y0,  int y1);
void         LCD_L0_MAG_DrawVLine     (int x,  int y0,  int y1);
void         LCD_L0_DELTA_DrawVLine     (int x,  int y0,  int y1);
void         LCD_L0_FillRect          (int x0, int y0, int x1, int y1);
void         LCD_L0_1_FillRect        (int x0, int y0, int x1, int y1);
void         LCD_L0_2_FillRect        (int x0, int y0, int x1, int y1);
void         LCD_L0_3_FillRect        (int x0, int y0, int x1, int y1);
void         LCD_L0_4_FillRect        (int x0, int y0, int x1, int y1);
void         LCD_L0_MAG_FillRect      (int x0, int y0, int x1, int y1);
void         LCD_L0_DELTA_FillRect      (int x0, int y0, int x1, int y1);
unsigned int LCD_L0_GetPixelIndex     (int x,  int y);
unsigned int LCD_L0_1_GetPixelIndex   (int x,  int y);
unsigned int LCD_L0_2_GetPixelIndex   (int x,  int y);
unsigned int LCD_L0_3_GetPixelIndex   (int x,  int y);
unsigned int LCD_L0_4_GetPixelIndex   (int x,  int y);
unsigned int LCD_L0_MAG_GetPixelIndex (int x,  int y);
unsigned int LCD_L0_DELTA_GetPixelIndex (int x,  int y);
void         LCD_L0_GetRect           (LCD_RECT * pRect);
void         LCD_L0_1_GetRect         (LCD_RECT * pRect);
void         LCD_L0_2_GetRect         (LCD_RECT * pRect);
void         LCD_L0_3_GetRect         (LCD_RECT * pRect);
void         LCD_L0_4_GetRect         (LCD_RECT * pRect);
void         LCD_L0_SetPixelIndex     (int x,  int y, int ColorIndex);
void         LCD_L0_1_SetPixelIndex   (int x,  int y, int ColorIndex);
void         LCD_L0_2_SetPixelIndex   (int x,  int y, int ColorIndex);
void         LCD_L0_3_SetPixelIndex   (int x,  int y, int ColorIndex);
void         LCD_L0_4_SetPixelIndex   (int x,  int y, int ColorIndex);
void         LCD_L0_MAG_SetPixelIndex (int x,  int y, int ColorIndex);
void         LCD_L0_DELTA_SetPixelIndex (int x,  int y, int ColorIndex);
void         LCD_L0_XorPixel          (int x,  int y);
void         LCD_L0_1_XorPixel        (int x,  int y);
void         LCD_L0_2_XorPixel        (int x,  int y);
void         LCD_L0_3_XorPixel        (int x,  int y);
void         LCD_L0_4_XorPixel        (int x,  int y);
void         LCD_L0_MAG_XorPixel      (int x,  int y);
void         LCD_L0_DELTA_XorPixel      (int x,  int y);
int          LCD_L0_Init              (void);
int          LCD_L0_1_Init            (void);
int          LCD_L0_2_Init            (void);
int          LCD_L0_3_Init            (void);
int          LCD_L0_4_Init            (void);
int          LCD_L0_MAG_Init          (void);
int          LCD_L0_DELTA_Init          (void);
void         LCD_L0_On                (void);
void         LCD_L0_1_On              (void);
void         LCD_L0_2_On              (void);
void         LCD_L0_3_On              (void);
void         LCD_L0_4_On              (void);
void         LCD_L0_Off               (void);
void         LCD_L0_1_Off             (void);
void         LCD_L0_2_Off             (void);
void         LCD_L0_3_Off             (void);
void         LCD_L0_4_Off             (void);
void         LCD_L0_SetLUTEntry       (unsigned char Pos, LCD_COLOR color);
void         LCD_L0_1_SetLUTEntry     (unsigned char Pos, LCD_COLOR color);
void         LCD_L0_2_SetLUTEntry     (unsigned char Pos, LCD_COLOR color);
void         LCD_L0_3_SetLUTEntry     (unsigned char Pos, LCD_COLOR color);
void         LCD_L0_4_SetLUTEntry     (unsigned char Pos, LCD_COLOR color);
void *       LCD_L0_GetDevFunc        (int Index);
void *       LCD_L0_1_GetDevFunc      (int Index);
void *       LCD_L0_2_GetDevFunc      (int Index);
void *       LCD_L0_3_GetDevFunc      (int Index);
void *       LCD_L0_4_GetDevFunc      (int Index);
tLCDDEV_Index2Color * LCD_L0_GetpfIndex2Color(void);
tLCDDEV_Index2Color * LCD_L0_1_GetpfIndex2Color(void);
tLCDDEV_Index2Color * LCD_L0_2_GetpfIndex2Color(void);
tLCDDEV_Index2Color * LCD_L0_3_GetpfIndex2Color(void);
tLCDDEV_Index2Color * LCD_L0_4_GetpfIndex2Color(void);

void LCD_L0_ReInit       (void);  
void LCD_L0_1_ReInit     (void);
void LCD_L0_2_ReInit     (void);
void LCD_L0_3_ReInit     (void);
void LCD_L0_4_ReInit     (void);
void LCD_L0_Refresh      (void);  
                                 
 
void LCD_L0_1_Refresh    (void);
void LCD_L0_2_Refresh    (void);
void LCD_L0_3_Refresh    (void);
void LCD_L0_4_Refresh    (void);
void LCD_L0_SetOrg       (int x, int y);
void LCD_L0_1_SetOrg     (int x, int y);
void LCD_L0_2_SetOrg     (int x, int y);
void LCD_L0_3_SetOrg     (int x, int y);
void LCD_L0_4_SetOrg     (int x, int y);






 
	 	 			 		    	 				 	  			   	 	 	 	 	 	  	  	      	   		 	 	 		  		  	 		 	  	  			     			       	   	 			  		    	 	     	 				  	 					 	 			   	  	  			 				 		 	 	 			     			 
#line 25 ".\\Source\\uCGUI\\Core\\GUI_Protected.h"
#line 1 ".\\Source\\uCGUI\\Core\\GUIDebug.h"




















 




#line 27 ".\\Source\\uCGUI\\Core\\GUIDebug.h"
#line 1 ".\\Source\\uCGUI\\Core\\GUI_X.h"





















 




#line 28 ".\\Source\\uCGUI\\Core\\GUI_X.h"




















 

 
void GUI_X_Init(void);

 
void GUI_X_ExecIdle(void);

 
int  GUI_X_GetTime(void);
void GUI_X_Delay(int Period);

 
void GUI_X_Unlock(void);
void GUI_X_Lock(void);
unsigned long  GUI_X_GetTaskId(void);
void GUI_X_InitOS(void);

 
void GUI_X_WaitEvent(void);
void GUI_X_SignalEvent(void);
 
void GUI_X_Log(const char *s);
void GUI_X_Warn(const char *s);
void GUI_X_ErrorOut(const char *s); 






 
	 	 			 		    	 				 	  			   	 	 	 	 	 	  	  	      	   		 	 	 		  		  	 		 	  	  			     			       	   	 			  		    	 	     	 				  	 					 	 			   	  	  			 				 		 	 	 			     			 
#line 28 ".\\Source\\uCGUI\\Core\\GUIDebug.h"

#line 35 ".\\Source\\uCGUI\\Core\\GUIDebug.h"

#line 43 ".\\Source\\uCGUI\\Core\\GUIDebug.h"






 












 

 

#line 89 ".\\Source\\uCGUI\\Core\\GUIDebug.h"






 

 

#line 122 ".\\Source\\uCGUI\\Core\\GUIDebug.h"






 
 

#line 154 ".\\Source\\uCGUI\\Core\\GUIDebug.h"






 











 
	 	 			 		    	 				 	  			   	 	 	 	 	 	  	  	      	   		 	 	 		  		  	 		 	  	  			     			       	   	 			  		    	 	     	 				  	 					 	 			   	  	  			 				 		 	 	 			     			 
#line 26 ".\\Source\\uCGUI\\Core\\GUI_Protected.h"
#line 28 ".\\Source\\uCGUI\\Core\\GUI_Protected.h"














 








 


































 















 

#line 113 ".\\Source\\uCGUI\\Core\\GUI_Protected.h"






 

typedef signed short GUI_USAGE_Handle;
typedef struct tsUSAGE_APIList tUSAGE_APIList;
typedef struct GUI_Usage GUI_USAGE;




typedef GUI_USAGE_Handle tUSAGE_CreateCompatible(GUI_USAGE* p);
typedef void        tUSAGE_AddPixel        (GUI_USAGE* p, int x, int y);
typedef void        tUSAGE_AddHLine        (GUI_USAGE* p, int x0, int y0, int len);
typedef void        tUSAGE_Clear           (GUI_USAGE* p);
typedef void        tUSAGE_Delete          (GUI_USAGE_Handle h);
typedef int         tUSAGE_GetNextDirty    (GUI_USAGE* p, int *pxOff, int yOff);



void GUI_USAGE_DecUseCnt(GUI_USAGE_Handle  hUsage);

GUI_USAGE_Handle GUI_USAGE_BM_Create(int x0, int y0, int xsize, int ysize, int Flags);
void    GUI_USAGE_Select(GUI_USAGE_Handle hUsage);
void    GUI_USAGE_AddRect(GUI_USAGE*  pUsage, int x0, int y0, int xSize, int ySize);






struct tsUSAGE_APIList {
  tUSAGE_AddPixel*                pfAddPixel;
  tUSAGE_AddHLine*                pfAddHLine;
  tUSAGE_Clear*                   pfClear;
  tUSAGE_CreateCompatible*        pfCreateCompatible;
  tUSAGE_Delete*                  pfDelete;
  tUSAGE_GetNextDirty*            pfGetNextDirty;
} ;

struct GUI_Usage {
  signed short x0, y0, XSize, YSize;
  const tUSAGE_APIList *pAPI;
  signed short UseCnt;
};






 


  typedef struct {
    signed short                   x0, y0, XSize, YSize;
    int                    NumColors;
    unsigned               BytesPerLine;
    unsigned               BitsPerPixel;
    unsigned               LayerIndex;
    signed short               hUsage;
    tLCDDEV_Color2Index*   pfColor2Index;
    tLCDDEV_Index2Color*   pfIndex2Color;
    tLCDDEV_GetIndexMask*  pfGetIndexMask;
    const tLCDDEV_APIList* pAPIList;
  } GUI_MEMDEV;



  void         GUI_MEMDEV__CopyFromLCD (GUI_MEMDEV_Handle hMem);
  void         GUI_MEMDEV__GetRect     (GUI_RECT* pRect);
  unsigned     GUI_MEMDEV__Color2Index (LCD_COLOR Color);
  LCD_COLOR    GUI_MEMDEV__Index2Color (int Index);
  unsigned int GUI_MEMDEV__GetIndexMask(void);

  GUI_MEMDEV_Handle GUI_MEMDEV__CreateFixed(int x0, int y0, int xsize, int ysize, int Flags
                                          ,const tLCDDEV_APIList * pMemDevAPI
                                          ,tLCDDEV_Color2Index*        pfColor2Index
                                          ,tLCDDEV_Index2Color*        pfIndex2Color
                                          ,tLCDDEV_GetIndexMask*       pfGetIndexMask);








 

#line 214 ".\\Source\\uCGUI\\Core\\GUI_Protected.h"







 


int  GUI_cos(int angle);
int  GUI_sin(int angle);
extern const unsigned long GUI_Pow10[10];

 
int  GUI_AA_Init(int x0, int x1);
int  GUI_AA_Init_HiRes(int x0, int x1);
void GUI_AA_Exit(void);
signed short GUI_AA_HiRes2Pixel(int HiRes);

void GL_FillCircleAA_HiRes(int x0, int y0, int r);

void GUI_AA__DrawCharAA2NoTrans(int x0, int y0, int XSize, int YSize, int BytesPerLine, const unsigned char*pData);
void GUI_AA__DrawCharAA2Trans  (int x0, int y0, int XSize, int YSize, int BytesPerLine, const unsigned char*pData);
void GUI_AA__DrawCharAA4       (int x0, int y0, int XSize, int YSize, int BytesPerLine, const unsigned char*pData);

 
int        GUI_SIF__GetCharDistX(unsigned short c);
void       GUI_SIF__GetFontInfo (const GUI_FONT  * pFont, GUI_FONTINFO * pfi);
char       GUI_SIF__IsInFont    (const GUI_FONT  * pFont, unsigned short c);
const unsigned char * GUI_SIF__GetpCharInfo(const GUI_FONT  * pFont, unsigned short c);

 
void GUI_AddHex     (unsigned long v, unsigned char Len, char**ps);
void GUI_AddBin     (unsigned long v, unsigned char Len, char**ps);
void GUI_AddDecMin  (signed long v, char**ps);
void GUI_AddDec     (signed long v, unsigned char Len, char**ps);
void GUI_AddDecShift(signed long v, unsigned char Len, unsigned char Shift, char**ps);
long GUI_AddSign    (long v, char**ps);
int  GUI_Long2Len   (signed long v);

#line 262 ".\\Source\\uCGUI\\Core\\GUI_Protected.h"

int   GUI_UC__CalcSizeOfChar   (unsigned short Char);
unsigned short   GUI_UC__GetCharCodeInc   (const char  ** ps);
int   GUI_UC__NumChars2NumBytes(const char  * s, int NumChars);
int   GUI_UC__NumBytes2NumChars(const char  * s, int NumBytes);

int  GUI__GetLineNumChars  (const char  *s, int MaxNumChars);
int  GUI__GetNumChars      (const char  *s);
int  GUI__GetLineDistX     (const char  *s, int Len);
int  GUI__GetFontSizeY     (void);
int  GUI__HandleEOLine     (const char  **ps);
void GUI__DispLine         (const char  *s, int Len, const GUI_RECT* pr);
void GUI__AddSpaceHex      (unsigned long v, unsigned char Len, char**ps);
void GUI__CalcTextRect     (const char * pText, const GUI_RECT* pTextRectIn, GUI_RECT* pTextRectOut, int TextAlign);

int  GUI__WrapGetNumCharsDisp       (const char  * pText, int xSize, GUI_WRAPMODE WrapMode);
int  GUI__WrapGetNumCharsToNextLine (const char  * pText, int xSize, GUI_WRAPMODE WrapMode);
int  GUI__WrapGetNumBytesToNextLine (const char  * pText, int xSize, GUI_WRAPMODE WrapMode);
void GUI__memset    (unsigned char * p, unsigned char Fill, int NumBytes);
void GUI__memset16  (unsigned short* p, unsigned short Fill, int NumWords);
int  GUI__strlen    (const char  * s);
int  GUI__strcmp    (const char  * s0, const char  * s1);
int  GUI__strcmp_hp (signed short hs0, const char  * s1);

 
int  GUI__GetCursorPosX     (const char  * s, int Index, int MaxNumChars);
int  GUI__GetCursorPosChar  (const char  * s, int x, int NumCharsToNextLine);
unsigned short  GUI__GetCursorCharacter(const char  * s, int Index, int MaxNumChars, int * pIsRTL);

 
unsigned short  GUI__GetPresentationForm     (unsigned short Char, unsigned short Next, unsigned short Prev, int * pIgnoreNext);
void GUI__DispLineArabic          (const char  * s, int MaxNumChars, const GUI_RECT * pRect);
int  GUI__GetLineDistXArabic      (const char  * s, int MaxNumChars);
int  GUI__IsArabicCharacter       (unsigned short c);
int  GUI__GetCursorPosXArabic     (const char  * s, int Index, int MaxNumChars);
int  GUI__GetCursorPosCharArabic  (const char  * s, int x, int MaxNumChars);
unsigned short  GUI__GetCursorCharacterArabic(const char  * s, int Index, int MaxNumChars, int * pIsRTL);

 
unsigned short GUI__Read16(const unsigned char ** ppData);
unsigned long GUI__Read32(const unsigned char ** ppData);

 
void GUI__GetOrg(int * px, int * py);






 

void GL_DispChar         (unsigned short c);
void GL_DrawArc          (int x0, int y0, int rx, int ry, int a0, int a1);
void GL_DrawBitmap       (const GUI_BITMAP  * pBM, int x0, int y0);
void GL_DrawCircle       (int x0, int y0, int r);
void GL_DrawEllipse      (int x0, int y0, int rx, int ry);
void GL_DrawHLine        (int y0, int x0, int x1);
void GL_DrawPolygon      (const GUI_POINT* pPoints, int NumPoints, int x0, int y0);
void GL_DrawPoint        (int x, int y);
void GL_DrawLine1        (int x0, int y0, int x1, int y1);
void GL_DrawLine1Ex      (int x0, int y0, int x1, int y1, unsigned * pPixelCnt);
void GL_DrawLineRel      (int dx, int dy);
void GL_DrawLineTo       (int x, int y);
void GL_DrawLineToEx     (int x, int y, unsigned * pPixelCnt);
void GL_DrawLine         (int x0, int y0, int x1, int y1);
void GL_DrawLineEx       (int x0, int y0, int x1, int y1, unsigned * pPixelCnt);
void GL_MoveTo           (int x, int y);
void GL_FillCircle       (int x0, int y0, int r);
void GL_FillCircleAA     (int x0, int y0, int r);
void GL_FillEllipse      (int x0, int y0, int rx, int ry);
void GL_FillPolygon      (const GUI_POINT* pPoints, int NumPoints, int x0, int y0);
void GL_SetDefault       (void);







 
typedef int  GUI_tfTimer(void);
typedef char GUI_CURSOR_tfTempHide  (const GUI_RECT* pRect);
typedef void GUI_CURSOR_tfTempUnhide(void);
typedef int  WM_tfHandlePID(void);







 

extern const unsigned char  GUI_Pixels_ArrowS[45];
extern const unsigned char  GUI_Pixels_ArrowM[60];
extern const unsigned char  GUI_Pixels_ArrowL[150];
extern const unsigned char  GUI_Pixels_CrossS[33];
extern const unsigned char  GUI_Pixels_CrossM[126];
extern const unsigned char  GUI_Pixels_CrossL[248];
extern const unsigned char  GUI_PixelsHeaderM[5 * 17];


extern const GUI_LOGPALETTE GUI_CursorPal;
extern const GUI_LOGPALETTE GUI_CursorPalI;






 

extern GUI_RECT  GUI_RectDispString;  






 
extern int GUITASK__EntranceCnt;






 

int       GUI_GetBitmapPixelIndex(const GUI_BITMAP  * pBMP, unsigned x, unsigned y);
GUI_COLOR GUI_GetBitmapPixelColor(const GUI_BITMAP  * pBMP, unsigned x, unsigned y);

void      GUI__DrawBitmap16bpp(int x0, int y0, int xsize, int ysize, const unsigned char  * pPixel, const LCD_LOGPALETTE  * pLogPal, int xMag, int yMag, tLCDDEV_Index2Color * pfIndex2Color);

extern const GUI_UC_ENC_APILIST GUI_UC_None;






 







extern  GUI_CONTEXT        GUI_Context;         
extern  char               GUI_DecChar;
extern           GUI_tfTimer*       GUI_pfTimerExec;
extern           WM_tfHandlePID*    WM_pfHandlePID;
extern      void (*GUI_pfDispCharStyle)(unsigned short Char);


  extern const     tLCD_APIList *     GUI_pLCD_APIList;    



  extern GUI_CURSOR_tfTempHide*   GUI_CURSOR_pfTempHide;
  extern GUI_CURSOR_tfTempUnhide* GUI_CURSOR_pfTempUnhide;


extern signed short GUI_OrgX, GUI_OrgY;
extern unsigned char  GUI_MoveRTL;










 
	 	 			 		    	 				 	  			   	 	 	 	 	 	  	  	      	   		 	 	 		  		  	 		 	  	  			     			       	   	 			  		    	 	     	 				  	 					 	 			   	  	  			 				 		 	 	 			     			 
#line 25 ".\\Source\\uCGUI\\WM\\WM_Intern.h"

















 


 






#line 58 ".\\Source\\uCGUI\\WM\\WM_Intern.h"









#line 74 ".\\Source\\uCGUI\\WM\\WM_Intern.h"






 
typedef struct {
  GUI_HWIN hWin;
  WM_Obj* pWin;
} WM_PAINTINFO;

typedef struct {
  GUI_HWIN hOld;
  GUI_HWIN hNew;
} WM_NOTIFY_CHILD_HAS_FOCUS_INFO;

typedef struct WM_CRITICAL_HANDLE {
  struct  WM_CRITICAL_HANDLE * pNext;
  volatile GUI_HWIN hWin;
} WM_CRITICAL_HANDLE;






 
extern unsigned short                    WM__CreateFlags;
extern GUI_HWIN                WM__hCapture;
extern GUI_HWIN                WM__hWinFocus;
extern char                   WM__CaptureReleaseAuto;
extern WM_tfPollPID*          WM_pfPollPID;
extern unsigned char                     WM__PaintCallbackCnt;       
extern GUI_PID_STATE          WM_PID__StateLast;
extern unsigned char                     WM_IsActive;


  extern int     WM__TransWindowCnt;
  extern GUI_HWIN WM__hATransWindow;






extern WM_CRITICAL_HANDLE     WM__CHWinModal;
extern WM_CRITICAL_HANDLE     WM__CHWinLast;











extern unsigned short     WM__NumWindows;
extern unsigned short     WM__NumInvalidWindows;
extern GUI_HWIN WM__FirstWin;
extern WM_CRITICAL_HANDLE*  WM__pFirstCriticalHandle;







 

void    WM__ActivateClipRect        (void);
int     WM__ClipAtParentBorders     (GUI_RECT* pRect, GUI_HWIN hWin);
void    WM__Client2Screen           (const WM_Obj* pWin, GUI_RECT *pRect);
void    WM__DetachWindow            (GUI_HWIN hChild);
void    WM__ForEachDesc(GUI_HWIN hWin, WM_tfForEach * pcb, void * pData);
void    WM__GetClientRectWin        (const WM_Obj* pWin, GUI_RECT* pRect);
GUI_HWIN WM__GetFirstSibling         (GUI_HWIN hWin);
GUI_HWIN WM__GetFocussedChild        (GUI_HWIN hWin);
int     WM__GetHasFocus             (GUI_HWIN hWin);
GUI_HWIN WM__GetLastSibling          (GUI_HWIN hWin);
GUI_HWIN WM__GetPrevSibling          (GUI_HWIN hWin);
int     WM__GetWindowSizeX          (const WM_Obj* pWin);
int     WM__GetWindowSizeY          (const WM_Obj* pWin);
void    WM__InsertWindowIntoList    (GUI_HWIN hWin, GUI_HWIN hParent);
void    WM__Invalidate1Abs          (GUI_HWIN hWin, const GUI_RECT * pRect);
void    WM__InvalidateAreaBelow     (const GUI_RECT* pRect, GUI_HWIN StopWin);
void    WM__InvalidateRectEx        (const GUI_RECT* pInvalidRect, GUI_HWIN hParent, GUI_HWIN hStop);
void    WM__InvalidateTransAreaAbove(const GUI_RECT* pRect, GUI_HWIN StopWin);
int     WM__IntersectRect           (GUI_RECT* pDest, const GUI_RECT* pr0, const GUI_RECT* pr1);
int     WM__IsAncestor              (GUI_HWIN hChild, GUI_HWIN hParent);
int     WM__IsAncestorOrSelf        (GUI_HWIN hChild, GUI_HWIN hParent);
int     WM__IsChild                 (GUI_HWIN hWin, GUI_HWIN hParent);
int     WM__IsEnabled               (GUI_HWIN hWin);
int     WM__IsInModalArea           (GUI_HWIN hWin);
int     WM__IsInWindow              (WM_Obj * pWin, int x, int y);
int     WM__IsWindow                (GUI_HWIN hWin);
void    WM__LeaveIVRSearch          (void);
void    WM__MoveTo                  (GUI_HWIN hWin, int x, int y);
void    WM__MoveWindow              (GUI_HWIN hWin, int dx, int dy);
void    WM__NotifyVisChanged        (GUI_HWIN hWin, GUI_RECT * pRect);
int     WM__RectIsNZ                (const GUI_RECT* pr);
void    WM__RemoveWindowFromList    (GUI_HWIN hWin);
void    WM__RemoveFromLinList       (GUI_HWIN hWin);
void    WM__Screen2Client           (const WM_Obj* pWin, GUI_RECT *pRect);
void    WM__SendMsgNoData           (GUI_HWIN hWin, unsigned char MsgId);
void    WM__SendMessage             (GUI_HWIN hWin, WM_MESSAGE* pm);
void    WM__SendMessageIfEnabled    (GUI_HWIN hWin, WM_MESSAGE* pm);
void    WM__SendMessageNoPara       (GUI_HWIN hWin, int MsgId);
void    WM__SendPIDMessage          (GUI_HWIN hWin, WM_MESSAGE* pMsg);
int     WM__SetScrollbarH           (GUI_HWIN hWin, int OnOff);
int     WM__SetScrollbarV           (GUI_HWIN hWin, int OnOff);
void    WM__UpdateChildPositions    (WM_Obj* pObj, int dx0, int dy0, int dx1, int dy1);
void    WM_PID__GetPrevState        (GUI_PID_STATE* pPrevState);
void    WM_PID__SetPrevState        (GUI_PID_STATE* pPrevState);
void    WM__SendTouchMessage        (GUI_HWIN hWin, WM_MESSAGE* pMsg);

unsigned short     WM_GetFlags(GUI_HWIN hWin);
void    WM__PaintWinAndOverlays     (WM_PAINTINFO* pInfo);
int     WM__Paint                   (GUI_HWIN hWin, WM_Obj* pWin);
void    WM__AddCriticalHandle       (WM_CRITICAL_HANDLE* pCH);
void    WM__RemoveCriticalHandle    (WM_CRITICAL_HANDLE* pCH);









 
	 	 			 		    	 				 	  			   	 	 	 	 	 	  	  	      	   		 	 	 		  		  	 		 	  	  			     			       	   	 			  		    	 	     	 				  	 					 	 			   	  	  			 				 		 	 	 			     			 
#line 28 ".\\Source\\uCGUI\\Widget\\WIDGET.h"



#line 1 ".\\Source\\uCGUI\\Widget\\SCROLLBAR.h"

















 




#line 24 ".\\Source\\uCGUI\\Widget\\SCROLLBAR.h"
#line 25 ".\\Source\\uCGUI\\Widget\\SCROLLBAR.h"
#line 1 ".\\Source\\uCGUI\\Widget\\WIDGET.h"

















 

#line 275 ".\\Source\\uCGUI\\Widget\\WIDGET.h"



	 	 			 		    	 				 	  			   	 	 	 	 	 	  	  	      	   		 	 	 		  		  	 		 	  	  			     			       	   	 			  		    	 	     	 				  	 					 	 			   	  	  			 				 		 	 	 			     			 
#line 26 ".\\Source\\uCGUI\\Widget\\SCROLLBAR.h"












 







 





 








 
typedef signed short SCROLLBAR_Handle;






 
SCROLLBAR_Handle SCROLLBAR_Create        (int x0, int y0, int xsize, int ysize, GUI_HWIN hParent, int Id, int WinFlags, int SpecialFlags);
SCROLLBAR_Handle SCROLLBAR_CreateIndirect(const GUI_WIDGET_CREATE_INFO* pCreateInfo, GUI_HWIN hWinParent, int x0, int y0, WM_CALLBACK* cb);
SCROLLBAR_Handle SCROLLBAR_CreateAttached(GUI_HWIN hParent, int SpecialFlags);
SCROLLBAR_Handle SCROLLBAR_CreateEx      (int x0, int y0, int xsize, int ysize, GUI_HWIN hParent,
                                          int WinFlags, int ExFlags, int Id);







 
void SCROLLBAR_Callback(WM_MESSAGE * pMsg);






 

 

void      SCROLLBAR_AddValue   (SCROLLBAR_Handle hObj, int Add);
void      SCROLLBAR_Dec        (SCROLLBAR_Handle hObj);
void      SCROLLBAR_Inc        (SCROLLBAR_Handle hObj);
GUI_COLOR SCROLLBAR_SetColor   (SCROLLBAR_Handle hObj, int Index, GUI_COLOR Color);
void      SCROLLBAR_SetNumItems(SCROLLBAR_Handle hObj, int NumItems);
void      SCROLLBAR_SetPageSize(SCROLLBAR_Handle hObj, int PageSize);
void      SCROLLBAR_SetValue   (SCROLLBAR_Handle hObj, int v);
int       SCROLLBAR_SetWidth   (SCROLLBAR_Handle hObj, int Width);
void      SCROLLBAR_SetState   (SCROLLBAR_Handle hObj, const WM_SCROLL_STATE* pState);






 
int       SCROLLBAR_GetDefaultWidth  (void);
GUI_COLOR SCROLLBAR_SetDefaultColor  (GUI_COLOR Color, unsigned int Index);  
int       SCROLLBAR_SetDefaultWidth  (int DefaultWidth);






 
int SCROLLBAR_GetValue(SCROLLBAR_Handle hObj);






 










	 	 			 		    	 				 	  			   	 	 	 	 	 	  	  	      	   		 	 	 		  		  	 		 	  	  			     			       	   	 			  		    	 	     	 				  	 					 	 			   	  	  			 				 		 	 	 			     			 
#line 32 ".\\Source\\uCGUI\\Widget\\WIDGET.h"







 



 
#line 61 ".\\Source\\uCGUI\\Widget\\WIDGET.h"






 

#line 89 ".\\Source\\uCGUI\\Widget\\WIDGET.h"




 
















 






 








 

typedef struct {
  GUI_HWIN hWin;
  int     Cmd;          
  int     ItemIndex;
  int     x0, y0;
} WIDGET_ITEM_DRAW_INFO;

typedef int WIDGET_DRAW_ITEM_FUNC(const WIDGET_ITEM_DRAW_INFO * pDrawItemInfo);







 
typedef struct {
  void  (*pfDrawUp)(void);
  void  (*pfDrawDown)(void);
  void  (*pfDrawUpRect)  (const GUI_RECT *pRect);
  void  (*pfDrawDownRect)(const GUI_RECT *pRect);
  void  (*pfGetRect)(GUI_RECT *pRect);
  int EffectSize;
} WIDGET_EFFECT;

typedef struct {
  WM_Obj      Win;
  const WIDGET_EFFECT* pEffect;
  signed short Id;
  unsigned short State;
} WIDGET;









 
 
typedef struct GUI_DRAW GUI_DRAW;
typedef void   GUI_DRAW_SELF_CB (void);
 
typedef struct {
  void (* pfDraw)    (const GUI_DRAW * pObj, int x, int y);
  int  (* pfGetXSize)(const GUI_DRAW * pObj);
  int  (* pfGetYSize)(const GUI_DRAW * pObj);
} GUI_DRAW_CONSTS;

 
struct GUI_DRAW {
  const GUI_DRAW_CONSTS* pConsts;
  union {
    const void * pData;
    GUI_DRAW_SELF_CB* pfDraw;
  } Data;
  signed short xOff, yOff;
};

typedef signed short GUI_DRAW_HANDLE;

 
void GUI_DRAW__Draw    (GUI_DRAW_HANDLE hDrawObj, int x, int y);
int  GUI_DRAW__GetXSize(GUI_DRAW_HANDLE hDrawObj);
int  GUI_DRAW__GetYSize(GUI_DRAW_HANDLE hDrawObj);

 
signed short GUI_DRAW_BITMAP_Create  (const GUI_BITMAP* pBitmap, int x, int y);
signed short GUI_DRAW_BMP_Create     (const void* pBMP, int x, int y);
signed short GUI_DRAW_STREAMED_Create(const GUI_BITMAP_STREAM * pBitmap, int x, int y);
signed short GUI_DRAW_SELF_Create(GUI_DRAW_SELF_CB* pfDraw, int x, int y);






 

extern const WIDGET_EFFECT WIDGET_Effect_3D;
extern const WIDGET_EFFECT WIDGET_Effect_3D1L;
extern const WIDGET_EFFECT WIDGET_Effect_3D2L;
extern const WIDGET_EFFECT WIDGET_Effect_None;
extern const WIDGET_EFFECT WIDGET_Effect_Simple;






 

void      WIDGET__DrawFocusRect(WIDGET* pWidget, const GUI_RECT* pRect, int Dist);
void      WIDGET__DrawVLine(WIDGET* pWidget, int x, int y0, int y1);
void      WIDGET__EFFECT_DrawDownRect(WIDGET* pWidget, GUI_RECT* pRect);
void      WIDGET__EFFECT_DrawDown(WIDGET* pWidget);
void      WIDGET__EFFECT_DrawUpRect(WIDGET* pWidget, GUI_RECT* pRect);
void      WIDGET__FillRectEx(WIDGET* pWidget, const GUI_RECT* pRect);
int       WIDGET__GetWindowSizeX(GUI_HWIN hWin);
GUI_COLOR WIDGET__GetBkColor(GUI_HWIN hObj);
int       WIDGET__GetXSize(const WIDGET* pWidget);
int       WIDGET__GetYSize(const WIDGET* pWidget);
void      WIDGET__GetClientRect(WIDGET* pWidget, GUI_RECT* pRect);
void      WIDGET__GetInsideRect(WIDGET* pWidget, GUI_RECT* pRect);
void      WIDGET__Init(WIDGET* pWidget, int Id, unsigned short State);
void      WIDGET__RotateRect90(WIDGET* pWidget, GUI_RECT* pDest, const GUI_RECT* pRect);
void      WIDGET__SetScrollState(GUI_HWIN hWin, const WM_SCROLL_STATE* pVState, const WM_SCROLL_STATE* pState);
void      WIDGET__FillStringInRect(const char  * pText, const GUI_RECT * pFillRect, const GUI_RECT * pTextRectMax, const GUI_RECT * pTextRectAct);






 
void  WIDGET_SetState     (GUI_HWIN hObj, int State);
void  WIDGET_AndState     (GUI_HWIN hObj, int State);
void  WIDGET_OrState      (GUI_HWIN hObj, int State);
int   WIDGET_HandleActive (GUI_HWIN hObj, WM_MESSAGE* pMsg);
int   WIDGET_GetState     (GUI_HWIN hObj);
int   WIDGET_SetWidth     (GUI_HWIN hObj, int Width);

void  WIDGET_EFFECT_3D_DrawUp(void);

void  WIDGET_SetDefaultEffect_3D    (void);
void  WIDGET_SetDefaultEffect_3D1L  (void);
void  WIDGET_SetDefaultEffect_3D2L  (void);
void  WIDGET_SetDefaultEffect_None  (void);
void  WIDGET_SetDefaultEffect_Simple(void);

const WIDGET_EFFECT* WIDGET_SetDefaultEffect(const WIDGET_EFFECT* pEffect);

void  WIDGET_SetEffect              (GUI_HWIN hObj, const WIDGET_EFFECT* pEffect);

const WIDGET_EFFECT* WIDGET_GetDefaultEffect(void);
int   WIDGET_SetWidth(GUI_HWIN hObj, int Width);












	 	 			 		    	 				 	  			   	 	 	 	 	 	  	  	      	   		 	 	 		  		  	 		 	  	  			     			       	   	 			  		    	 	     	 				  	 					 	 			   	  	  			 				 		 	 	 			     			 
#line 26 ".\\Source\\uCGUI\\Widget\\BUTTON.h"











 
 







 







 







 




 









 
typedef signed short BUTTON_Handle;







 

BUTTON_Handle BUTTON_Create        (int x0, int y0, int xsize, int ysize, int ID, int Flags);
BUTTON_Handle BUTTON_CreateAsChild (int x0, int y0, int xsize, int ysize, GUI_HWIN hParent, int Id, int Flags);
BUTTON_Handle BUTTON_CreateIndirect(const GUI_WIDGET_CREATE_INFO* pCreateInfo, GUI_HWIN hWinParent, int x0, int y0, WM_CALLBACK* cb);
BUTTON_Handle BUTTON_CreateEx      (int x0, int y0, int xsize, int ysize, GUI_HWIN hParent,
                                    int WinFlags, int ExFlags, int Id);






 

GUI_COLOR                    BUTTON_GetDefaultBkColor   (unsigned Index);
const GUI_FONT  * BUTTON_GetDefaultFont      (void);
int                          BUTTON_GetDefaultTextAlign (void);
GUI_COLOR                    BUTTON_GetDefaultTextColor (unsigned Index);
void                         BUTTON_SetDefaultBkColor   (GUI_COLOR Color, unsigned Index);
GUI_COLOR                    BUTTON_SetDefaultFocusColor(GUI_COLOR Color);
void                         BUTTON_SetDefaultFont      (const GUI_FONT  * pFont);
void                         BUTTON_SetDefaultTextAlign (int Align);
void                         BUTTON_SetDefaultTextColor (GUI_COLOR Color, unsigned Index);













 
void BUTTON_Callback(WM_MESSAGE *pMsg);






 

GUI_COLOR        BUTTON_GetBkColor         (BUTTON_Handle hObj, unsigned int Index);
const GUI_BITMAP  * BUTTON_GetBitmap(BUTTON_Handle hObj,unsigned int Index);
const GUI_FONT  * BUTTON_GetFont(BUTTON_Handle hObj);
void             BUTTON_GetText            (BUTTON_Handle hObj, char * pBuffer, int MaxLen);
GUI_COLOR        BUTTON_GetTextColor       (BUTTON_Handle hObj, unsigned int Index);
unsigned         BUTTON_IsPressed          (BUTTON_Handle hObj);
void             BUTTON_SetBitmap          (BUTTON_Handle hObj, unsigned int Index, const GUI_BITMAP * pBitmap);
void             BUTTON_SetBitmapEx        (BUTTON_Handle hObj, unsigned int Index, const GUI_BITMAP * pBitmap, int x, int y);
void             BUTTON_SetBkColor         (BUTTON_Handle hObj, unsigned int Index, GUI_COLOR Color);
void             BUTTON_SetBMP             (BUTTON_Handle hObj, unsigned int Index, const void * pBitmap);
void             BUTTON_SetBMPEx           (BUTTON_Handle hObj, unsigned int Index, const void * pBitmap, int x, int y);
void             BUTTON_SetFont            (BUTTON_Handle hObj, const GUI_FONT  * pfont);
void             BUTTON_SetState           (BUTTON_Handle hObj, int State);                                     
void             BUTTON_SetPressed         (BUTTON_Handle hObj, int State);
GUI_COLOR        BUTTON_SetFocusColor      (BUTTON_Handle hObj, GUI_COLOR Color);
void             BUTTON_SetFocussable      (BUTTON_Handle hObj, int State);
void             BUTTON_SetStreamedBitmap  (BUTTON_Handle hObj, unsigned int Index, const GUI_BITMAP_STREAM * pBitmap);
void             BUTTON_SetStreamedBitmapEx(BUTTON_Handle hObj, unsigned int Index, const GUI_BITMAP_STREAM * pBitmap, int x, int y);
void             BUTTON_SetText            (BUTTON_Handle hObj, const char* s);
void             BUTTON_SetTextAlign       (BUTTON_Handle hObj, int Align);
void             BUTTON_SetTextColor       (BUTTON_Handle hObj, unsigned int Index, GUI_COLOR Color);
void             BUTTON_SetSelfDrawEx      (BUTTON_Handle hObj, unsigned int Index, void (*pDraw)(void), int x, int y);  
void             BUTTON_SetSelfDraw        (BUTTON_Handle hObj, unsigned int Index, void (*pDraw)(void));                




 









	 	 			 		    	 				 	  			   	 	 	 	 	 	  	  	      	   		 	 	 		  		  	 		 	  	  			     			       	   	 			  		    	 	     	 				  	 					 	 			   	  	  			 				 		 	 	 			     			 
#line 7 "Source\\uCGUI\\TouchCalibration\\TouchCalibration.h"
#line 1 ".\\Source\\uCGUI\\Widget\\EDIT.h"

















 




#line 24 ".\\Source\\uCGUI\\Widget\\EDIT.h"
#line 25 ".\\Source\\uCGUI\\Widget\\EDIT.h"















 






 




 











 






 






 
typedef signed short EDIT_Handle;
typedef void tEDIT_AddKeyEx    (EDIT_Handle hObj, int Key);
typedef void tEDIT_UpdateBuffer(EDIT_Handle hObj);











 

 


EDIT_Handle EDIT_Create        (int x0, int y0, int xsize, int ysize, int Id, int MaxLen, int Flags);
EDIT_Handle EDIT_CreateAsChild (int x0, int y0, int xsize, int ysize, GUI_HWIN hParent, int Id, int Flags, int MaxLen);
EDIT_Handle EDIT_CreateIndirect(const GUI_WIDGET_CREATE_INFO* pCreateInfo, GUI_HWIN hWinParent, int x0, int y0, WM_CALLBACK* cb);
EDIT_Handle EDIT_CreateEx      (int x0, int y0, int xsize, int ysize, GUI_HWIN hParent,
                                int WinFlags, int ExFlags, int Id, int MaxLen);







 
void EDIT_Callback(WM_MESSAGE * pMsg);







 














 

 
void EDIT_SetDefaultBkColor(unsigned int Index, GUI_COLOR Color);
void EDIT_SetDefaultFont(const GUI_FONT* pFont);
void EDIT_SetDefaultTextAlign(int Align);
void EDIT_SetDefaultTextColor(unsigned int Index, GUI_COLOR Color);

 
GUI_COLOR                    EDIT_GetDefaultBkColor(unsigned int Index);
const GUI_FONT  * EDIT_GetDefaultFont(void);
int                          EDIT_GetDefaultTextAlign(void);
GUI_COLOR                    EDIT_GetDefaultTextColor(unsigned int Index);

 
void EDIT_AddKey           (EDIT_Handle hObj, int Key);
void EDIT_ClearCursor      (EDIT_Handle hObj);
void EDIT_SetBkColor       (EDIT_Handle hObj, unsigned int Index, GUI_COLOR color);
void EDIT_SetCursorAtChar  (EDIT_Handle hObj, int Pos);
void EDIT_SetCursorAtPixel (EDIT_Handle hObj, int xPos);
void EDIT_SetFocussable    (EDIT_Handle hObj, int State);
void EDIT_SetFont          (EDIT_Handle hObj, const GUI_FONT  * pfont);
int  EDIT_SetInsertMode    (EDIT_Handle hObj, int OnOff);
void EDIT_SetMaxLen        (EDIT_Handle hObj, int MaxLen);
void EDIT_SetpfAddKeyEx    (EDIT_Handle hObj, tEDIT_AddKeyEx * pfAddKeyEx);
void EDIT_SetpfUpdateBuffer(EDIT_Handle hObj, tEDIT_UpdateBuffer * pfUpdateBuffer);
void EDIT_SetText          (EDIT_Handle hObj, const char* s);
void EDIT_SetTextAlign     (EDIT_Handle hObj, int Align);
void EDIT_SetTextColor     (EDIT_Handle hObj, unsigned int Index, GUI_COLOR color);
void EDIT_SetSel           (EDIT_Handle hObj, int FirstChar, int LastChar);

 
int   EDIT_GetCursorCharPos (EDIT_Handle hObj);
void  EDIT_GetCursorPixelPos(EDIT_Handle hObj, int * pxPos, int * pyPos);
float EDIT_GetFloatValue    (EDIT_Handle hObj);
int   EDIT_GetNumChars      (EDIT_Handle hObj);
void  EDIT_GetText          (EDIT_Handle hObj, char* sDest, int MaxLen);
signed long   EDIT_GetValue         (EDIT_Handle hObj);
void  EDIT_SetFloatValue    (EDIT_Handle hObj, float Value);
void  EDIT_SetValue         (EDIT_Handle hObj, signed long Value);






 

void  EDIT_SetHexMode(EDIT_Handle hEdit, unsigned long Value, unsigned long Min, unsigned long Max);
void  EDIT_SetBinMode(EDIT_Handle hEdit, unsigned long Value, unsigned long Min, unsigned long Max);
void  EDIT_SetDecMode(EDIT_Handle hEdit, signed long Value, signed long Min, signed long Max, int Shift, unsigned char Flags);
void  EDIT_SetFloatMode(EDIT_Handle hEdit, float Value, float Min, float Max, int Shift, unsigned char Flags);
void  EDIT_SetTextMode(EDIT_Handle hEdit);
void  EDIT_SetUlongMode(EDIT_Handle hEdit, unsigned long Value, unsigned long Min, unsigned long Max);

unsigned long   GUI_EditHex(unsigned long Value, unsigned long Min, unsigned long Max, int Len, int xsize);
unsigned long   GUI_EditBin(unsigned long Value, unsigned long Min, unsigned long Max, int Len, int xsize);
signed long   GUI_EditDec(signed long Value, signed long Min, signed long Max, int Len, int xsize, int Shift, unsigned char Flags);
float GUI_EditFloat(float Value, float Min, float Max, int Len, int xsize, int Shift, unsigned char Flags);
void  GUI_EditString(char * pString, int Len, int xsize);






 

 



 



 









	 	 			 		    	 				 	  			   	 	 	 	 	 	  	  	      	   		 	 	 		  		  	 		 	  	  			     			       	   	 			  		    	 	     	 				  	 					 	 			   	  	  			 				 		 	 	 			     			 
#line 8 "Source\\uCGUI\\TouchCalibration\\TouchCalibration.h"

#line 1 ".\\Source\\uCGUI\\LCDDriver\\Touch\\touch.h"



#line 1 ".\\Source\\APP\\touchc.h"
#line 1 ".\\Source\\FWLib\\cm3\\stm32f10x.h"























 



 



 
    






  


 
  


 

#line 59 ".\\Source\\FWLib\\cm3\\stm32f10x.h"


















 





#line 91 ".\\Source\\FWLib\\cm3\\stm32f10x.h"







            
#line 106 ".\\Source\\FWLib\\cm3\\stm32f10x.h"





 






 
#line 125 ".\\Source\\FWLib\\cm3\\stm32f10x.h"



 



 



 
#line 144 ".\\Source\\FWLib\\cm3\\stm32f10x.h"




 
typedef enum IRQn
{
 
  NonMaskableInt_IRQn         = -14,     
  MemoryManagement_IRQn       = -12,     
  BusFault_IRQn               = -11,     
  UsageFault_IRQn             = -10,     
  SVCall_IRQn                 = -5,      
  DebugMonitor_IRQn           = -4,      
  PendSV_IRQn                 = -2,      
  SysTick_IRQn                = -1,      

 
  WWDG_IRQn                   = 0,       
  PVD_IRQn                    = 1,       
  TAMPER_IRQn                 = 2,       
  RTC_IRQn                    = 3,       
  FLASH_IRQn                  = 4,       
  RCC_IRQn                    = 5,       
  EXTI0_IRQn                  = 6,       
  EXTI1_IRQn                  = 7,       
  EXTI2_IRQn                  = 8,       
  EXTI3_IRQn                  = 9,       
  EXTI4_IRQn                  = 10,      
  DMA1_Channel1_IRQn          = 11,      
  DMA1_Channel2_IRQn          = 12,      
  DMA1_Channel3_IRQn          = 13,      
  DMA1_Channel4_IRQn          = 14,      
  DMA1_Channel5_IRQn          = 15,      
  DMA1_Channel6_IRQn          = 16,      
  DMA1_Channel7_IRQn          = 17,      

#line 203 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

#line 224 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

#line 252 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

#line 278 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

#line 323 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

#line 364 ".\\Source\\FWLib\\cm3\\stm32f10x.h"


  ADC1_2_IRQn                 = 18,      
  USB_HP_CAN1_TX_IRQn         = 19,      
  USB_LP_CAN1_RX0_IRQn        = 20,      
  CAN1_RX1_IRQn               = 21,      
  CAN1_SCE_IRQn               = 22,      
  EXTI9_5_IRQn                = 23,      
  TIM1_BRK_TIM9_IRQn          = 24,      
  TIM1_UP_TIM10_IRQn          = 25,      
  TIM1_TRG_COM_TIM11_IRQn     = 26,      
  TIM1_CC_IRQn                = 27,      
  TIM2_IRQn                   = 28,      
  TIM3_IRQn                   = 29,      
  TIM4_IRQn                   = 30,      
  I2C1_EV_IRQn                = 31,      
  I2C1_ER_IRQn                = 32,      
  I2C2_EV_IRQn                = 33,      
  I2C2_ER_IRQn                = 34,      
  SPI1_IRQn                   = 35,      
  SPI2_IRQn                   = 36,      
  USART1_IRQn                 = 37,      
  USART2_IRQn                 = 38,      
  USART3_IRQn                 = 39,      
  EXTI15_10_IRQn              = 40,      
  RTCAlarm_IRQn               = 41,      
  USBWakeUp_IRQn              = 42,      
  TIM8_BRK_TIM12_IRQn         = 43,      
  TIM8_UP_TIM13_IRQn          = 44,      
  TIM8_TRG_COM_TIM14_IRQn     = 45,      
  TIM8_CC_IRQn                = 46,      
  ADC3_IRQn                   = 47,      
  FSMC_IRQn                   = 48,      
  SDIO_IRQn                   = 49,      
  TIM5_IRQn                   = 50,      
  SPI3_IRQn                   = 51,      
  UART4_IRQn                  = 52,      
  UART5_IRQn                  = 53,      
  TIM6_IRQn                   = 54,      
  TIM7_IRQn                   = 55,      
  DMA2_Channel1_IRQn          = 56,      
  DMA2_Channel2_IRQn          = 57,      
  DMA2_Channel3_IRQn          = 58,      
  DMA2_Channel4_5_IRQn        = 59       


#line 455 ".\\Source\\FWLib\\cm3\\stm32f10x.h"
} IRQn_Type;



 

#line 1 "..\\..\\..\\STM32F4\\STM32F4xx_DSP_StdPeriph_Lib_V1.0.1\\Libraries\\CMSIS\\Include\\core_cm3.h"
 




















 























 













 




 






 

 











#line 99 "..\\..\\..\\STM32F4\\STM32F4xx_DSP_StdPeriph_Lib_V1.0.1\\Libraries\\CMSIS\\Include\\core_cm3.h"

 


#line 120 "..\\..\\..\\STM32F4\\STM32F4xx_DSP_StdPeriph_Lib_V1.0.1\\Libraries\\CMSIS\\Include\\core_cm3.h"

#line 1 "D:\\Keil_ARM\\ARM\\RV31\\INC\\stdint.h"
 
 





 









#line 25 "D:\\Keil_ARM\\ARM\\RV31\\INC\\stdint.h"







 

     

     
typedef   signed          char int8_t;
typedef   signed short     int int16_t;
typedef   signed           int int32_t;
typedef   signed       __int64 int64_t;

     
typedef unsigned          char uint8_t;
typedef unsigned short     int uint16_t;
typedef unsigned           int uint32_t;
typedef unsigned       __int64 uint64_t;

     

     
     
typedef   signed          char int_least8_t;
typedef   signed short     int int_least16_t;
typedef   signed           int int_least32_t;
typedef   signed       __int64 int_least64_t;

     
typedef unsigned          char uint_least8_t;
typedef unsigned short     int uint_least16_t;
typedef unsigned           int uint_least32_t;
typedef unsigned       __int64 uint_least64_t;

     

     
typedef   signed           int int_fast8_t;
typedef   signed           int int_fast16_t;
typedef   signed           int int_fast32_t;
typedef   signed       __int64 int_fast64_t;

     
typedef unsigned           int uint_fast8_t;
typedef unsigned           int uint_fast16_t;
typedef unsigned           int uint_fast32_t;
typedef unsigned       __int64 uint_fast64_t;

     
typedef   signed           int intptr_t;
typedef unsigned           int uintptr_t;

     
typedef   signed       __int64 intmax_t;
typedef unsigned       __int64 uintmax_t;




     

     





     





     





     

     





     





     





     

     





     





     





     

     


     


     


     

     


     


     


     

     



     



     


     
    
 



#line 196 "D:\\Keil_ARM\\ARM\\RV31\\INC\\stdint.h"

     







     










     











#line 260 "D:\\Keil_ARM\\ARM\\RV31\\INC\\stdint.h"



 


#line 122 "..\\..\\..\\STM32F4\\STM32F4xx_DSP_StdPeriph_Lib_V1.0.1\\Libraries\\CMSIS\\Include\\core_cm3.h"
#line 1 "..\\..\\..\\STM32F4\\STM32F4xx_DSP_StdPeriph_Lib_V1.0.1\\Libraries\\CMSIS\\Include\\core_cmInstr.h"
 




















 





 



 


 









 







 







 






 








 







 







 









 









 
static __inline __asm uint32_t __REV16(uint32_t value)
{
  rev16 r0, r0
  bx lr
}








 
static __inline __asm int32_t __REVSH(int32_t value)
{
  revsh r0, r0
  bx lr
}










 









 









 









 











 











 











 







 










 










 









 






#line 582 "..\\..\\..\\STM32F4\\STM32F4xx_DSP_StdPeriph_Lib_V1.0.1\\Libraries\\CMSIS\\Include\\core_cmInstr.h"

   

#line 123 "..\\..\\..\\STM32F4\\STM32F4xx_DSP_StdPeriph_Lib_V1.0.1\\Libraries\\CMSIS\\Include\\core_cm3.h"
#line 1 "..\\..\\..\\STM32F4\\STM32F4xx_DSP_StdPeriph_Lib_V1.0.1\\Libraries\\CMSIS\\Include\\core_cmFunc.h"
 




















 





 



 


 





 
 






 
static __inline uint32_t __get_CONTROL(void)
{
  register uint32_t __regControl         __asm("control");
  return(__regControl);
}







 
static __inline void __set_CONTROL(uint32_t control)
{
  register uint32_t __regControl         __asm("control");
  __regControl = control;
}







 
static __inline uint32_t __get_IPSR(void)
{
  register uint32_t __regIPSR          __asm("ipsr");
  return(__regIPSR);
}







 
static __inline uint32_t __get_APSR(void)
{
  register uint32_t __regAPSR          __asm("apsr");
  return(__regAPSR);
}







 
static __inline uint32_t __get_xPSR(void)
{
  register uint32_t __regXPSR          __asm("xpsr");
  return(__regXPSR);
}







 
static __inline uint32_t __get_PSP(void)
{
  register uint32_t __regProcessStackPointer  __asm("psp");
  return(__regProcessStackPointer);
}







 
static __inline void __set_PSP(uint32_t topOfProcStack)
{
  register uint32_t __regProcessStackPointer  __asm("psp");
  __regProcessStackPointer = topOfProcStack;
}







 
static __inline uint32_t __get_MSP(void)
{
  register uint32_t __regMainStackPointer     __asm("msp");
  return(__regMainStackPointer);
}







 
static __inline void __set_MSP(uint32_t topOfMainStack)
{
  register uint32_t __regMainStackPointer     __asm("msp");
  __regMainStackPointer = topOfMainStack;
}







 
static __inline uint32_t __get_PRIMASK(void)
{
  register uint32_t __regPriMask         __asm("primask");
  return(__regPriMask);
}







 
static __inline void __set_PRIMASK(uint32_t priMask)
{
  register uint32_t __regPriMask         __asm("primask");
  __regPriMask = (priMask);
}
 







 







 








 
static __inline uint32_t  __get_BASEPRI(void)
{
  register uint32_t __regBasePri         __asm("basepri");
  return(__regBasePri);
}







 
static __inline void __set_BASEPRI(uint32_t basePri)
{
  register uint32_t __regBasePri         __asm("basepri");
  __regBasePri = (basePri & 0xff);
}
 






 
static __inline uint32_t __get_FAULTMASK(void)
{
  register uint32_t __regFaultMask       __asm("faultmask");
  return(__regFaultMask);
}







 
static __inline void __set_FAULTMASK(uint32_t faultMask)
{
  register uint32_t __regFaultMask       __asm("faultmask");
  __regFaultMask = (faultMask & (uint32_t)1);
}




#line 293 "..\\..\\..\\STM32F4\\STM32F4xx_DSP_StdPeriph_Lib_V1.0.1\\Libraries\\CMSIS\\Include\\core_cmFunc.h"


#line 605 "..\\..\\..\\STM32F4\\STM32F4xx_DSP_StdPeriph_Lib_V1.0.1\\Libraries\\CMSIS\\Include\\core_cmFunc.h"

 


#line 124 "..\\..\\..\\STM32F4\\STM32F4xx_DSP_StdPeriph_Lib_V1.0.1\\Libraries\\CMSIS\\Include\\core_cm3.h"








 
#line 154 "..\\..\\..\\STM32F4\\STM32F4xx_DSP_StdPeriph_Lib_V1.0.1\\Libraries\\CMSIS\\Include\\core_cm3.h"

 
#line 163 "..\\..\\..\\STM32F4\\STM32F4xx_DSP_StdPeriph_Lib_V1.0.1\\Libraries\\CMSIS\\Include\\core_cm3.h"

 





 








 





 


 
typedef union
{
  struct
  {

    uint32_t _reserved0:27;               





    uint32_t Q:1;                         
    uint32_t V:1;                         
    uint32_t C:1;                         
    uint32_t Z:1;                         
    uint32_t N:1;                         
  } b;                                    
  uint32_t w;                             
} APSR_Type;



 
typedef union
{
  struct
  {
    uint32_t ISR:9;                       
    uint32_t _reserved0:23;               
  } b;                                    
  uint32_t w;                             
} IPSR_Type;



 
typedef union
{
  struct
  {
    uint32_t ISR:9;                       

    uint32_t _reserved0:15;               





    uint32_t T:1;                         
    uint32_t IT:2;                        
    uint32_t Q:1;                         
    uint32_t V:1;                         
    uint32_t C:1;                         
    uint32_t Z:1;                         
    uint32_t N:1;                         
  } b;                                    
  uint32_t w;                             
} xPSR_Type;



 
typedef union
{
  struct
  {
    uint32_t nPRIV:1;                     
    uint32_t SPSEL:1;                     
    uint32_t FPCA:1;                      
    uint32_t _reserved0:29;               
  } b;                                    
  uint32_t w;                             
} CONTROL_Type;

 






 


 
typedef struct
{
  volatile uint32_t ISER[8];                  
       uint32_t RESERVED0[24];
  volatile uint32_t ICER[8];                  
       uint32_t RSERVED1[24];
  volatile uint32_t ISPR[8];                  
       uint32_t RESERVED2[24];
  volatile uint32_t ICPR[8];                  
       uint32_t RESERVED3[24];
  volatile uint32_t IABR[8];                  
       uint32_t RESERVED4[56];
  volatile uint8_t  IP[240];                  
       uint32_t RESERVED5[644];
  volatile  uint32_t STIR;                     
}  NVIC_Type;

 



 






 


 
typedef struct
{
  volatile const  uint32_t CPUID;                    
  volatile uint32_t ICSR;                     
  volatile uint32_t VTOR;                     
  volatile uint32_t AIRCR;                    
  volatile uint32_t SCR;                      
  volatile uint32_t CCR;                      
  volatile uint8_t  SHP[12];                  
  volatile uint32_t SHCSR;                    
  volatile uint32_t CFSR;                     
  volatile uint32_t HFSR;                     
  volatile uint32_t DFSR;                     
  volatile uint32_t MMFAR;                    
  volatile uint32_t BFAR;                     
  volatile uint32_t AFSR;                     
  volatile const  uint32_t PFR[2];                   
  volatile const  uint32_t DFR;                      
  volatile const  uint32_t ADR;                      
  volatile const  uint32_t MMFR[4];                  
  volatile const  uint32_t ISAR[5];                  
       uint32_t RESERVED0[5];
  volatile uint32_t CPACR;                    
} SCB_Type;

 















 






























 



 





















 









 


















 










































 









 









 















 






 


 
typedef struct
{
       uint32_t RESERVED0[1];
  volatile const  uint32_t ICTR;                     



       uint32_t RESERVED1[1];

} SCnSCB_Type;

 



 










 






 


 
typedef struct
{
  volatile uint32_t CTRL;                     
  volatile uint32_t LOAD;                     
  volatile uint32_t VAL;                      
  volatile const  uint32_t CALIB;                    
} SysTick_Type;

 












 



 



 









 






 


 
typedef struct
{
  volatile  union
  {
    volatile  uint8_t    u8;                   
    volatile  uint16_t   u16;                  
    volatile  uint32_t   u32;                  
  }  PORT [32];                           
       uint32_t RESERVED0[864];
  volatile uint32_t TER;                      
       uint32_t RESERVED1[15];
  volatile uint32_t TPR;                      
       uint32_t RESERVED2[15];
  volatile uint32_t TCR;                      
} ITM_Type;

 



 



























   







 


 
typedef struct
{
  volatile const  uint32_t TYPE;                     
  volatile uint32_t CTRL;                     
  volatile uint32_t RNR;                      
  volatile uint32_t RBAR;                     
  volatile uint32_t RASR;                     
  volatile uint32_t RBAR_A1;                  
  volatile uint32_t RASR_A1;                  
  volatile uint32_t RBAR_A2;                  
  volatile uint32_t RASR_A2;                  
  volatile uint32_t RBAR_A3;                  
  volatile uint32_t RASR_A3;                  
} MPU_Type;

 









 









 



 









 












 







 


 
typedef struct
{
  volatile uint32_t DHCSR;                    
  volatile  uint32_t DCRSR;                    
  volatile uint32_t DCRDR;                    
  volatile uint32_t DEMCR;                    
} CoreDebug_Type;

 




































 






 







































 




 

 
#line 850 "..\\..\\..\\STM32F4\\STM32F4xx_DSP_StdPeriph_Lib_V1.0.1\\Libraries\\CMSIS\\Include\\core_cm3.h"

#line 857 "..\\..\\..\\STM32F4\\STM32F4xx_DSP_StdPeriph_Lib_V1.0.1\\Libraries\\CMSIS\\Include\\core_cm3.h"






 





 






 



 



 










 
static __inline void NVIC_SetPriorityGrouping(uint32_t PriorityGroup)
{
  uint32_t reg_value;
  uint32_t PriorityGroupTmp = (PriorityGroup & (uint32_t)0x07);                

  reg_value  =  ((SCB_Type *) ((0xE000E000UL) + 0x0D00UL) )->AIRCR;                                                    
  reg_value &= ~((0xFFFFUL << 16) | (7UL << 8));              
  reg_value  =  (reg_value                                 |
                ((uint32_t)0x5FA << 16) |
                (PriorityGroupTmp << 8));                                      
  ((SCB_Type *) ((0xE000E000UL) + 0x0D00UL) )->AIRCR =  reg_value;
}








 
static __inline uint32_t NVIC_GetPriorityGrouping(void)
{
  return ((((SCB_Type *) ((0xE000E000UL) + 0x0D00UL) )->AIRCR & (7UL << 8)) >> 8);    
}








 
static __inline void NVIC_EnableIRQ(IRQn_Type IRQn)
{
  ((NVIC_Type *) ((0xE000E000UL) + 0x0100UL) )->ISER[((uint32_t)(IRQn) >> 5)] = (1 << ((uint32_t)(IRQn) & 0x1F));  
}








 
static __inline void NVIC_DisableIRQ(IRQn_Type IRQn)
{
  ((NVIC_Type *) ((0xE000E000UL) + 0x0100UL) )->ICER[((uint32_t)(IRQn) >> 5)] = (1 << ((uint32_t)(IRQn) & 0x1F));  
}










 
static __inline uint32_t NVIC_GetPendingIRQ(IRQn_Type IRQn)
{
  return((uint32_t) ((((NVIC_Type *) ((0xE000E000UL) + 0x0100UL) )->ISPR[(uint32_t)(IRQn) >> 5] & (1 << ((uint32_t)(IRQn) & 0x1F)))?1:0));  
}








 
static __inline void NVIC_SetPendingIRQ(IRQn_Type IRQn)
{
  ((NVIC_Type *) ((0xE000E000UL) + 0x0100UL) )->ISPR[((uint32_t)(IRQn) >> 5)] = (1 << ((uint32_t)(IRQn) & 0x1F));  
}








 
static __inline void NVIC_ClearPendingIRQ(IRQn_Type IRQn)
{
  ((NVIC_Type *) ((0xE000E000UL) + 0x0100UL) )->ICPR[((uint32_t)(IRQn) >> 5)] = (1 << ((uint32_t)(IRQn) & 0x1F));  
}








 
static __inline uint32_t NVIC_GetActive(IRQn_Type IRQn)
{
  return((uint32_t)((((NVIC_Type *) ((0xE000E000UL) + 0x0100UL) )->IABR[(uint32_t)(IRQn) >> 5] & (1 << ((uint32_t)(IRQn) & 0x1F)))?1:0));  
}












 
static __inline void NVIC_SetPriority(IRQn_Type IRQn, uint32_t priority)
{
  if(IRQn < 0) {
    ((SCB_Type *) ((0xE000E000UL) + 0x0D00UL) )->SHP[((uint32_t)(IRQn) & 0xF)-4] = ((priority << (8 - 4)) & 0xff); }  
  else {
    ((NVIC_Type *) ((0xE000E000UL) + 0x0100UL) )->IP[(uint32_t)(IRQn)] = ((priority << (8 - 4)) & 0xff);    }         
}













 
static __inline uint32_t NVIC_GetPriority(IRQn_Type IRQn)
{

  if(IRQn < 0) {
    return((uint32_t)(((SCB_Type *) ((0xE000E000UL) + 0x0D00UL) )->SHP[((uint32_t)(IRQn) & 0xF)-4] >> (8 - 4)));  }  
  else {
    return((uint32_t)(((NVIC_Type *) ((0xE000E000UL) + 0x0100UL) )->IP[(uint32_t)(IRQn)]           >> (8 - 4)));  }  
}















 
static __inline uint32_t NVIC_EncodePriority (uint32_t PriorityGroup, uint32_t PreemptPriority, uint32_t SubPriority)
{
  uint32_t PriorityGroupTmp = (PriorityGroup & 0x07);           
  uint32_t PreemptPriorityBits;
  uint32_t SubPriorityBits;

  PreemptPriorityBits = ((7 - PriorityGroupTmp) > 4) ? 4 : 7 - PriorityGroupTmp;
  SubPriorityBits     = ((PriorityGroupTmp + 4) < 7) ? 0 : PriorityGroupTmp - 7 + 4;

  return (
           ((PreemptPriority & ((1 << (PreemptPriorityBits)) - 1)) << SubPriorityBits) |
           ((SubPriority     & ((1 << (SubPriorityBits    )) - 1)))
         );
}















 
static __inline void NVIC_DecodePriority (uint32_t Priority, uint32_t PriorityGroup, uint32_t* pPreemptPriority, uint32_t* pSubPriority)
{
  uint32_t PriorityGroupTmp = (PriorityGroup & 0x07);           
  uint32_t PreemptPriorityBits;
  uint32_t SubPriorityBits;

  PreemptPriorityBits = ((7 - PriorityGroupTmp) > 4) ? 4 : 7 - PriorityGroupTmp;
  SubPriorityBits     = ((PriorityGroupTmp + 4) < 7) ? 0 : PriorityGroupTmp - 7 + 4;

  *pPreemptPriority = (Priority >> SubPriorityBits) & ((1 << (PreemptPriorityBits)) - 1);
  *pSubPriority     = (Priority                   ) & ((1 << (SubPriorityBits    )) - 1);
}





 
static __inline void NVIC_SystemReset(void)
{
  __dsb(0xF);                                                     
 
  ((SCB_Type *) ((0xE000E000UL) + 0x0D00UL) )->AIRCR  = ((0x5FA << 16)      |
                 (((SCB_Type *) ((0xE000E000UL) + 0x0D00UL) )->AIRCR & (7UL << 8)) |
                 (1UL << 2));                    
  __dsb(0xF);                                                      
  while(1);                                                     
}

 



 



 











 
static __inline uint32_t SysTick_Config(uint32_t ticks)
{
  if (ticks > (0xFFFFFFUL << 0))  return (1);             

  ((SysTick_Type *) ((0xE000E000UL) + 0x0010UL) )->LOAD  = (ticks & (0xFFFFFFUL << 0)) - 1;       
  NVIC_SetPriority (SysTick_IRQn, (1<<4) - 1);   
  ((SysTick_Type *) ((0xE000E000UL) + 0x0010UL) )->VAL   = 0;                                           
  ((SysTick_Type *) ((0xE000E000UL) + 0x0010UL) )->CTRL  = (1UL << 2) |
                   (1UL << 1)   |
                   (1UL << 0);                     
  return (0);                                                   
}



 



 



 

extern volatile int32_t ITM_RxBuffer;                     











 
static __inline uint32_t ITM_SendChar (uint32_t ch)
{
  if ((((CoreDebug_Type *) (0xE000EDF0UL))->DEMCR & (1UL << 24))  &&       
      (((ITM_Type *) (0xE0000000UL) )->TCR & (1UL << 0))                  &&       
      (((ITM_Type *) (0xE0000000UL) )->TER & (1UL << 0)        )                    )      
  {
    while (((ITM_Type *) (0xE0000000UL) )->PORT[0].u32 == 0);
    ((ITM_Type *) (0xE0000000UL) )->PORT[0].u8 = (uint8_t) ch;
  }
  return (ch);
}










 
static __inline int32_t ITM_ReceiveChar (void) {
  int32_t ch = -1;                            

  if (ITM_RxBuffer != 0x5AA55AA5) {
    ch = ITM_RxBuffer;
    ITM_RxBuffer = 0x5AA55AA5;        
  }

  return (ch);
}









 
static __inline int32_t ITM_CheckChar (void) {

  if (ITM_RxBuffer == 0x5AA55AA5) {
    return (0);                                  
  } else {
    return (1);                                  
  }
}

 





#line 462 ".\\Source\\FWLib\\cm3\\stm32f10x.h"
#line 1 ".\\Source\\FWLib\\cm3\\system_stm32f10x.h"


















 



 



   
  


 









 



 




 

extern uint32_t SystemCoreClock;           



 



 



 



 



 



 
  
extern void SystemInit(void);
extern void SystemCoreClockUpdate(void);


 









 
  


   
 
#line 463 ".\\Source\\FWLib\\cm3\\stm32f10x.h"
#line 464 ".\\Source\\FWLib\\cm3\\stm32f10x.h"



   

 
typedef int32_t  s32;
typedef int16_t s16;
typedef int8_t  s8;

typedef const int32_t sc32;   
typedef const int16_t sc16;   
typedef const int8_t sc8;    

typedef volatile int32_t  vs32;
typedef volatile int16_t  vs16;
typedef volatile int8_t   vs8;

typedef volatile const int32_t vsc32;   
typedef volatile const int16_t vsc16;   
typedef volatile const int8_t vsc8;    

typedef uint32_t  u32;
typedef uint16_t u16;
typedef uint8_t  u8;

typedef const uint32_t uc32;   
typedef const uint16_t uc16;   
typedef const uint8_t uc8;    

typedef volatile uint32_t  vu32;
typedef volatile uint16_t vu16;
typedef volatile uint8_t  vu8;

typedef volatile const uint32_t vuc32;   
typedef volatile const uint16_t vuc16;   
typedef volatile const uint8_t vuc8;    

typedef enum {RESET = 0, SET = !RESET} FlagStatus, ITStatus;

typedef enum {DISABLE = 0, ENABLE = !DISABLE} FunctionalState;


typedef enum {ERROR = 0, SUCCESS = !ERROR} ErrorStatus;

 





 



    



 

typedef struct
{
  volatile uint32_t SR;
  volatile uint32_t CR1;
  volatile uint32_t CR2;
  volatile uint32_t SMPR1;
  volatile uint32_t SMPR2;
  volatile uint32_t JOFR1;
  volatile uint32_t JOFR2;
  volatile uint32_t JOFR3;
  volatile uint32_t JOFR4;
  volatile uint32_t HTR;
  volatile uint32_t LTR;
  volatile uint32_t SQR1;
  volatile uint32_t SQR2;
  volatile uint32_t SQR3;
  volatile uint32_t JSQR;
  volatile uint32_t JDR1;
  volatile uint32_t JDR2;
  volatile uint32_t JDR3;
  volatile uint32_t JDR4;
  volatile uint32_t DR;
} ADC_TypeDef;



 

typedef struct
{
  uint32_t  RESERVED0;
  volatile uint16_t DR1;
  uint16_t  RESERVED1;
  volatile uint16_t DR2;
  uint16_t  RESERVED2;
  volatile uint16_t DR3;
  uint16_t  RESERVED3;
  volatile uint16_t DR4;
  uint16_t  RESERVED4;
  volatile uint16_t DR5;
  uint16_t  RESERVED5;
  volatile uint16_t DR6;
  uint16_t  RESERVED6;
  volatile uint16_t DR7;
  uint16_t  RESERVED7;
  volatile uint16_t DR8;
  uint16_t  RESERVED8;
  volatile uint16_t DR9;
  uint16_t  RESERVED9;
  volatile uint16_t DR10;
  uint16_t  RESERVED10; 
  volatile uint16_t RTCCR;
  uint16_t  RESERVED11;
  volatile uint16_t CR;
  uint16_t  RESERVED12;
  volatile uint16_t CSR;
  uint16_t  RESERVED13[5];
  volatile uint16_t DR11;
  uint16_t  RESERVED14;
  volatile uint16_t DR12;
  uint16_t  RESERVED15;
  volatile uint16_t DR13;
  uint16_t  RESERVED16;
  volatile uint16_t DR14;
  uint16_t  RESERVED17;
  volatile uint16_t DR15;
  uint16_t  RESERVED18;
  volatile uint16_t DR16;
  uint16_t  RESERVED19;
  volatile uint16_t DR17;
  uint16_t  RESERVED20;
  volatile uint16_t DR18;
  uint16_t  RESERVED21;
  volatile uint16_t DR19;
  uint16_t  RESERVED22;
  volatile uint16_t DR20;
  uint16_t  RESERVED23;
  volatile uint16_t DR21;
  uint16_t  RESERVED24;
  volatile uint16_t DR22;
  uint16_t  RESERVED25;
  volatile uint16_t DR23;
  uint16_t  RESERVED26;
  volatile uint16_t DR24;
  uint16_t  RESERVED27;
  volatile uint16_t DR25;
  uint16_t  RESERVED28;
  volatile uint16_t DR26;
  uint16_t  RESERVED29;
  volatile uint16_t DR27;
  uint16_t  RESERVED30;
  volatile uint16_t DR28;
  uint16_t  RESERVED31;
  volatile uint16_t DR29;
  uint16_t  RESERVED32;
  volatile uint16_t DR30;
  uint16_t  RESERVED33; 
  volatile uint16_t DR31;
  uint16_t  RESERVED34;
  volatile uint16_t DR32;
  uint16_t  RESERVED35;
  volatile uint16_t DR33;
  uint16_t  RESERVED36;
  volatile uint16_t DR34;
  uint16_t  RESERVED37;
  volatile uint16_t DR35;
  uint16_t  RESERVED38;
  volatile uint16_t DR36;
  uint16_t  RESERVED39;
  volatile uint16_t DR37;
  uint16_t  RESERVED40;
  volatile uint16_t DR38;
  uint16_t  RESERVED41;
  volatile uint16_t DR39;
  uint16_t  RESERVED42;
  volatile uint16_t DR40;
  uint16_t  RESERVED43;
  volatile uint16_t DR41;
  uint16_t  RESERVED44;
  volatile uint16_t DR42;
  uint16_t  RESERVED45;    
} BKP_TypeDef;
  


 

typedef struct
{
  volatile uint32_t TIR;
  volatile uint32_t TDTR;
  volatile uint32_t TDLR;
  volatile uint32_t TDHR;
} CAN_TxMailBox_TypeDef;



 
  
typedef struct
{
  volatile uint32_t RIR;
  volatile uint32_t RDTR;
  volatile uint32_t RDLR;
  volatile uint32_t RDHR;
} CAN_FIFOMailBox_TypeDef;



 
  
typedef struct
{
  volatile uint32_t FR1;
  volatile uint32_t FR2;
} CAN_FilterRegister_TypeDef;



 
  
typedef struct
{
  volatile uint32_t MCR;
  volatile uint32_t MSR;
  volatile uint32_t TSR;
  volatile uint32_t RF0R;
  volatile uint32_t RF1R;
  volatile uint32_t IER;
  volatile uint32_t ESR;
  volatile uint32_t BTR;
  uint32_t  RESERVED0[88];
  CAN_TxMailBox_TypeDef sTxMailBox[3];
  CAN_FIFOMailBox_TypeDef sFIFOMailBox[2];
  uint32_t  RESERVED1[12];
  volatile uint32_t FMR;
  volatile uint32_t FM1R;
  uint32_t  RESERVED2;
  volatile uint32_t FS1R;
  uint32_t  RESERVED3;
  volatile uint32_t FFA1R;
  uint32_t  RESERVED4;
  volatile uint32_t FA1R;
  uint32_t  RESERVED5[8];

  CAN_FilterRegister_TypeDef sFilterRegister[14];



} CAN_TypeDef;



 
typedef struct
{
  volatile uint32_t CFGR;
  volatile uint32_t OAR;
  volatile uint32_t PRES;
  volatile uint32_t ESR;
  volatile uint32_t CSR;
  volatile uint32_t TXD;
  volatile uint32_t RXD;  
} CEC_TypeDef;



 

typedef struct
{
  volatile uint32_t DR;
  volatile uint8_t  IDR;
  uint8_t   RESERVED0;
  uint16_t  RESERVED1;
  volatile uint32_t CR;
} CRC_TypeDef;



 

typedef struct
{
  volatile uint32_t CR;
  volatile uint32_t SWTRIGR;
  volatile uint32_t DHR12R1;
  volatile uint32_t DHR12L1;
  volatile uint32_t DHR8R1;
  volatile uint32_t DHR12R2;
  volatile uint32_t DHR12L2;
  volatile uint32_t DHR8R2;
  volatile uint32_t DHR12RD;
  volatile uint32_t DHR12LD;
  volatile uint32_t DHR8RD;
  volatile uint32_t DOR1;
  volatile uint32_t DOR2;



} DAC_TypeDef;



 

typedef struct
{
  volatile uint32_t IDCODE;
  volatile uint32_t CR;	
}DBGMCU_TypeDef;



 

typedef struct
{
  volatile uint32_t CCR;
  volatile uint32_t CNDTR;
  volatile uint32_t CPAR;
  volatile uint32_t CMAR;
} DMA_Channel_TypeDef;

typedef struct
{
  volatile uint32_t ISR;
  volatile uint32_t IFCR;
} DMA_TypeDef;



 

typedef struct
{
  volatile uint32_t MACCR;
  volatile uint32_t MACFFR;
  volatile uint32_t MACHTHR;
  volatile uint32_t MACHTLR;
  volatile uint32_t MACMIIAR;
  volatile uint32_t MACMIIDR;
  volatile uint32_t MACFCR;
  volatile uint32_t MACVLANTR;              
       uint32_t RESERVED0[2];
  volatile uint32_t MACRWUFFR;              
  volatile uint32_t MACPMTCSR;
       uint32_t RESERVED1[2];
  volatile uint32_t MACSR;                  
  volatile uint32_t MACIMR;
  volatile uint32_t MACA0HR;
  volatile uint32_t MACA0LR;
  volatile uint32_t MACA1HR;
  volatile uint32_t MACA1LR;
  volatile uint32_t MACA2HR;
  volatile uint32_t MACA2LR;
  volatile uint32_t MACA3HR;
  volatile uint32_t MACA3LR;                
       uint32_t RESERVED2[40];
  volatile uint32_t MMCCR;                  
  volatile uint32_t MMCRIR;
  volatile uint32_t MMCTIR;
  volatile uint32_t MMCRIMR;
  volatile uint32_t MMCTIMR;                
       uint32_t RESERVED3[14];
  volatile uint32_t MMCTGFSCCR;             
  volatile uint32_t MMCTGFMSCCR;
       uint32_t RESERVED4[5];
  volatile uint32_t MMCTGFCR;
       uint32_t RESERVED5[10];
  volatile uint32_t MMCRFCECR;
  volatile uint32_t MMCRFAECR;
       uint32_t RESERVED6[10];
  volatile uint32_t MMCRGUFCR;
       uint32_t RESERVED7[334];
  volatile uint32_t PTPTSCR;
  volatile uint32_t PTPSSIR;
  volatile uint32_t PTPTSHR;
  volatile uint32_t PTPTSLR;
  volatile uint32_t PTPTSHUR;
  volatile uint32_t PTPTSLUR;
  volatile uint32_t PTPTSAR;
  volatile uint32_t PTPTTHR;
  volatile uint32_t PTPTTLR;
       uint32_t RESERVED8[567];
  volatile uint32_t DMABMR;
  volatile uint32_t DMATPDR;
  volatile uint32_t DMARPDR;
  volatile uint32_t DMARDLAR;
  volatile uint32_t DMATDLAR;
  volatile uint32_t DMASR;
  volatile uint32_t DMAOMR;
  volatile uint32_t DMAIER;
  volatile uint32_t DMAMFBOCR;
       uint32_t RESERVED9[9];
  volatile uint32_t DMACHTDR;
  volatile uint32_t DMACHRDR;
  volatile uint32_t DMACHTBAR;
  volatile uint32_t DMACHRBAR;
} ETH_TypeDef;



 

typedef struct
{
  volatile uint32_t IMR;
  volatile uint32_t EMR;
  volatile uint32_t RTSR;
  volatile uint32_t FTSR;
  volatile uint32_t SWIER;
  volatile uint32_t PR;
} EXTI_TypeDef;



 

typedef struct
{
  volatile uint32_t ACR;
  volatile uint32_t KEYR;
  volatile uint32_t OPTKEYR;
  volatile uint32_t SR;
  volatile uint32_t CR;
  volatile uint32_t AR;
  volatile uint32_t RESERVED;
  volatile uint32_t OBR;
  volatile uint32_t WRPR;

  uint32_t RESERVED1[8]; 
  volatile uint32_t KEYR2;
  uint32_t RESERVED2;   
  volatile uint32_t SR2;
  volatile uint32_t CR2;
  volatile uint32_t AR2; 

} FLASH_TypeDef;



 
  
typedef struct
{
  volatile uint16_t RDP;
  volatile uint16_t USER;
  volatile uint16_t Data0;
  volatile uint16_t Data1;
  volatile uint16_t WRP0;
  volatile uint16_t WRP1;
  volatile uint16_t WRP2;
  volatile uint16_t WRP3;
} OB_TypeDef;



 

typedef struct
{
  volatile uint32_t BTCR[8];   
} FSMC_Bank1_TypeDef; 



 
  
typedef struct
{
  volatile uint32_t BWTR[7];
} FSMC_Bank1E_TypeDef;



 
  
typedef struct
{
  volatile uint32_t PCR2;
  volatile uint32_t SR2;
  volatile uint32_t PMEM2;
  volatile uint32_t PATT2;
  uint32_t  RESERVED0;   
  volatile uint32_t ECCR2; 
} FSMC_Bank2_TypeDef;  



 
  
typedef struct
{
  volatile uint32_t PCR3;
  volatile uint32_t SR3;
  volatile uint32_t PMEM3;
  volatile uint32_t PATT3;
  uint32_t  RESERVED0;   
  volatile uint32_t ECCR3; 
} FSMC_Bank3_TypeDef; 



 
  
typedef struct
{
  volatile uint32_t PCR4;
  volatile uint32_t SR4;
  volatile uint32_t PMEM4;
  volatile uint32_t PATT4;
  volatile uint32_t PIO4; 
} FSMC_Bank4_TypeDef; 



 

typedef struct
{
  volatile uint32_t CRL;
  volatile uint32_t CRH;
  volatile uint32_t IDR;
  volatile uint32_t ODR;
  volatile uint32_t BSRR;
  volatile uint32_t BRR;
  volatile uint32_t LCKR;
} GPIO_TypeDef;



 

typedef struct
{
  volatile uint32_t EVCR;
  volatile uint32_t MAPR;
  volatile uint32_t EXTICR[4];
  uint32_t RESERVED0;
  volatile uint32_t MAPR2;  
} AFIO_TypeDef;


 

typedef struct
{
  volatile uint16_t CR1;
  uint16_t  RESERVED0;
  volatile uint16_t CR2;
  uint16_t  RESERVED1;
  volatile uint16_t OAR1;
  uint16_t  RESERVED2;
  volatile uint16_t OAR2;
  uint16_t  RESERVED3;
  volatile uint16_t DR;
  uint16_t  RESERVED4;
  volatile uint16_t SR1;
  uint16_t  RESERVED5;
  volatile uint16_t SR2;
  uint16_t  RESERVED6;
  volatile uint16_t CCR;
  uint16_t  RESERVED7;
  volatile uint16_t TRISE;
  uint16_t  RESERVED8;
} I2C_TypeDef;



 

typedef struct
{
  volatile uint32_t KR;
  volatile uint32_t PR;
  volatile uint32_t RLR;
  volatile uint32_t SR;
} IWDG_TypeDef;



 

typedef struct
{
  volatile uint32_t CR;
  volatile uint32_t CSR;
} PWR_TypeDef;



 

typedef struct
{
  volatile uint32_t CR;
  volatile uint32_t CFGR;
  volatile uint32_t CIR;
  volatile uint32_t APB2RSTR;
  volatile uint32_t APB1RSTR;
  volatile uint32_t AHBENR;
  volatile uint32_t APB2ENR;
  volatile uint32_t APB1ENR;
  volatile uint32_t BDCR;
  volatile uint32_t CSR;










} RCC_TypeDef;



 

typedef struct
{
  volatile uint16_t CRH;
  uint16_t  RESERVED0;
  volatile uint16_t CRL;
  uint16_t  RESERVED1;
  volatile uint16_t PRLH;
  uint16_t  RESERVED2;
  volatile uint16_t PRLL;
  uint16_t  RESERVED3;
  volatile uint16_t DIVH;
  uint16_t  RESERVED4;
  volatile uint16_t DIVL;
  uint16_t  RESERVED5;
  volatile uint16_t CNTH;
  uint16_t  RESERVED6;
  volatile uint16_t CNTL;
  uint16_t  RESERVED7;
  volatile uint16_t ALRH;
  uint16_t  RESERVED8;
  volatile uint16_t ALRL;
  uint16_t  RESERVED9;
} RTC_TypeDef;



 

typedef struct
{
  volatile uint32_t POWER;
  volatile uint32_t CLKCR;
  volatile uint32_t ARG;
  volatile uint32_t CMD;
  volatile const uint32_t RESPCMD;
  volatile const uint32_t RESP1;
  volatile const uint32_t RESP2;
  volatile const uint32_t RESP3;
  volatile const uint32_t RESP4;
  volatile uint32_t DTIMER;
  volatile uint32_t DLEN;
  volatile uint32_t DCTRL;
  volatile const uint32_t DCOUNT;
  volatile const uint32_t STA;
  volatile uint32_t ICR;
  volatile uint32_t MASK;
  uint32_t  RESERVED0[2];
  volatile const uint32_t FIFOCNT;
  uint32_t  RESERVED1[13];
  volatile uint32_t FIFO;
} SDIO_TypeDef;



 

typedef struct
{
  volatile uint16_t CR1;
  uint16_t  RESERVED0;
  volatile uint16_t CR2;
  uint16_t  RESERVED1;
  volatile uint16_t SR;
  uint16_t  RESERVED2;
  volatile uint16_t DR;
  uint16_t  RESERVED3;
  volatile uint16_t CRCPR;
  uint16_t  RESERVED4;
  volatile uint16_t RXCRCR;
  uint16_t  RESERVED5;
  volatile uint16_t TXCRCR;
  uint16_t  RESERVED6;
  volatile uint16_t I2SCFGR;
  uint16_t  RESERVED7;
  volatile uint16_t I2SPR;
  uint16_t  RESERVED8;  
} SPI_TypeDef;



 

typedef struct
{
  volatile uint16_t CR1;
  uint16_t  RESERVED0;
  volatile uint16_t CR2;
  uint16_t  RESERVED1;
  volatile uint16_t SMCR;
  uint16_t  RESERVED2;
  volatile uint16_t DIER;
  uint16_t  RESERVED3;
  volatile uint16_t SR;
  uint16_t  RESERVED4;
  volatile uint16_t EGR;
  uint16_t  RESERVED5;
  volatile uint16_t CCMR1;
  uint16_t  RESERVED6;
  volatile uint16_t CCMR2;
  uint16_t  RESERVED7;
  volatile uint16_t CCER;
  uint16_t  RESERVED8;
  volatile uint16_t CNT;
  uint16_t  RESERVED9;
  volatile uint16_t PSC;
  uint16_t  RESERVED10;
  volatile uint16_t ARR;
  uint16_t  RESERVED11;
  volatile uint16_t RCR;
  uint16_t  RESERVED12;
  volatile uint16_t CCR1;
  uint16_t  RESERVED13;
  volatile uint16_t CCR2;
  uint16_t  RESERVED14;
  volatile uint16_t CCR3;
  uint16_t  RESERVED15;
  volatile uint16_t CCR4;
  uint16_t  RESERVED16;
  volatile uint16_t BDTR;
  uint16_t  RESERVED17;
  volatile uint16_t DCR;
  uint16_t  RESERVED18;
  volatile uint16_t DMAR;
  uint16_t  RESERVED19;
} TIM_TypeDef;



 
 
typedef struct
{
  volatile uint16_t SR;
  uint16_t  RESERVED0;
  volatile uint16_t DR;
  uint16_t  RESERVED1;
  volatile uint16_t BRR;
  uint16_t  RESERVED2;
  volatile uint16_t CR1;
  uint16_t  RESERVED3;
  volatile uint16_t CR2;
  uint16_t  RESERVED4;
  volatile uint16_t CR3;
  uint16_t  RESERVED5;
  volatile uint16_t GTPR;
  uint16_t  RESERVED6;
} USART_TypeDef;



 

typedef struct
{
  volatile uint32_t CR;
  volatile uint32_t CFR;
  volatile uint32_t SR;
} WWDG_TypeDef;



 
  


 











 




#line 1295 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

#line 1318 ".\\Source\\FWLib\\cm3\\stm32f10x.h"



#line 1337 ".\\Source\\FWLib\\cm3\\stm32f10x.h"




















 
  


   

#line 1437 ".\\Source\\FWLib\\cm3\\stm32f10x.h"



 



 
  
  

 
    
 
 
 

 
 
 
 
 

 



 



 


 
 
 
 
 

 











 
#line 1498 ".\\Source\\FWLib\\cm3\\stm32f10x.h"




 





 
 
 
 
 

 


 


 


 


 


 


 


 


 


 


 


 


 


 


 


 


 


 


 


 


 


 


 


 


 


 


 


 


 


 


 


 


 


 


 


 


 


 


 


 


 


 


 





 



 






 
 
 
 
 

 
#line 1674 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

#line 1681 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

 
 








 








 






#line 1717 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

 











 











 













 






#line 1833 ".\\Source\\FWLib\\cm3\\stm32f10x.h"




#line 1853 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

 





#line 1866 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

 
#line 1885 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

#line 1894 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

 
#line 1902 ".\\Source\\FWLib\\cm3\\stm32f10x.h"



















#line 1927 ".\\Source\\FWLib\\cm3\\stm32f10x.h"












 













#line 1959 ".\\Source\\FWLib\\cm3\\stm32f10x.h"





#line 1973 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

#line 1980 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

#line 1990 ".\\Source\\FWLib\\cm3\\stm32f10x.h"











 


















#line 2026 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

 
#line 2034 ".\\Source\\FWLib\\cm3\\stm32f10x.h"



















#line 2059 ".\\Source\\FWLib\\cm3\\stm32f10x.h"












 













#line 2091 ".\\Source\\FWLib\\cm3\\stm32f10x.h"





#line 2105 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

#line 2112 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

#line 2122 ".\\Source\\FWLib\\cm3\\stm32f10x.h"











 








 








   
#line 2161 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

#line 2256 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

#line 2283 ".\\Source\\FWLib\\cm3\\stm32f10x.h"
 
 
 
 
 
 

 




































































 




































































 
#line 2445 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

 
#line 2463 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

 
#line 2481 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

#line 2498 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

 
#line 2516 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

 
#line 2535 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

 

 






 
#line 2562 ".\\Source\\FWLib\\cm3\\stm32f10x.h"






 








 









 








 








 









 










 




#line 2637 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

 










#line 2668 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

 





 
#line 2683 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

 
#line 2692 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

   
#line 2701 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

 
#line 2710 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

 





 
#line 2725 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

 
#line 2734 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

   
#line 2743 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

 
#line 2752 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

 





 
#line 2767 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

 
#line 2776 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

   
#line 2785 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

 
#line 2794 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

 





 
#line 2809 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

 
#line 2818 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

   
#line 2827 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

 
#line 2836 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

#line 2845 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

#line 2854 ".\\Source\\FWLib\\cm3\\stm32f10x.h"


 
#line 2864 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

 
 
 
 
 

 





 


 


 




 
 
 
 
 

 
#line 2928 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

 
#line 2963 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

 
#line 2998 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

 
#line 3033 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

 
#line 3068 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

 





 





 





 





 





 





 





 





 






 
#line 3135 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

 



 









 
#line 3159 ".\\Source\\FWLib\\cm3\\stm32f10x.h"




 




 
#line 3175 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

 





 
#line 3197 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

 
 





 
#line 3212 ".\\Source\\FWLib\\cm3\\stm32f10x.h"
 
#line 3219 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

 




 






 


 


 


 
 
 
 
 

 
#line 3268 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

 
#line 3290 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

 
#line 3312 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

 
#line 3334 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

 
#line 3356 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

 
#line 3378 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

 
 
 
 
 

 
#line 3414 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

 
#line 3444 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

 
#line 3454 ".\\Source\\FWLib\\cm3\\stm32f10x.h"















 
#line 3478 ".\\Source\\FWLib\\cm3\\stm32f10x.h"















 
#line 3502 ".\\Source\\FWLib\\cm3\\stm32f10x.h"















 
#line 3526 ".\\Source\\FWLib\\cm3\\stm32f10x.h"















 
#line 3550 ".\\Source\\FWLib\\cm3\\stm32f10x.h"















 
#line 3574 ".\\Source\\FWLib\\cm3\\stm32f10x.h"















 
#line 3598 ".\\Source\\FWLib\\cm3\\stm32f10x.h"















 


 


 


 


 


 


 


 


 


 



 


 


 



 


 


 


 



 


 


 


 


 
 
 
 
 

 






 
#line 3699 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

#line 3708 ".\\Source\\FWLib\\cm3\\stm32f10x.h"















  
 
#line 3731 ".\\Source\\FWLib\\cm3\\stm32f10x.h"


















 








































 


















































 


 


 


 


 


 


 
#line 3866 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

#line 3873 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

#line 3880 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

#line 3887 ".\\Source\\FWLib\\cm3\\stm32f10x.h"







 
#line 3901 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

#line 3908 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

#line 3915 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

#line 3922 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

#line 3929 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

#line 3936 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

 
#line 3944 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

#line 3951 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

#line 3958 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

#line 3965 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

#line 3972 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

#line 3979 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

 
#line 3987 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

#line 3994 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

#line 4001 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

#line 4008 ".\\Source\\FWLib\\cm3\\stm32f10x.h"





 


 


 


 


 



 
 
 
 
 

 









































 



 


 


 


 


 


 


 



 



 



 


 


 



 
 
 
 
 
 





 






 


 
#line 4150 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

 
#line 4160 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

 


 


 
 
 
 
 

 
















 









#line 4208 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

 

























 
#line 4251 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

 
#line 4265 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

 
#line 4275 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

 




























 





















 




























 





















 
#line 4394 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

 


 


 


 


 


 


 


 


 
#line 4429 ".\\Source\\FWLib\\cm3\\stm32f10x.h"





#line 4440 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

 
#line 4448 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

#line 4455 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

 


 
 
 
 
 

 




 
#line 4477 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

 


 


 


 


 


 


 


 


 
 
 
 
 

 


 





 


 



 
 
 
 
 

 
#line 4539 ".\\Source\\FWLib\\cm3\\stm32f10x.h"



 
#line 4551 ".\\Source\\FWLib\\cm3\\stm32f10x.h"







 


 
 
 
 
 

 











#line 4589 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

 











#line 4612 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

 











#line 4635 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

 











#line 4658 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

 








































 








































 








































 








































 


































 


































 


































 


































 



























 



























 



























 
#line 5055 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

 
#line 5064 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

 
#line 5073 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

 
#line 5084 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

#line 5094 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

#line 5104 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

#line 5114 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

 
#line 5125 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

#line 5135 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

#line 5145 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

#line 5155 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

 
#line 5166 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

#line 5176 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

#line 5186 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

#line 5196 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

 
#line 5207 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

#line 5217 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

#line 5227 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

#line 5237 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

 
#line 5248 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

#line 5258 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

#line 5268 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

#line 5278 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

 
#line 5289 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

#line 5299 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

#line 5309 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

#line 5319 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

 
#line 5330 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

#line 5340 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

#line 5350 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

#line 5360 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

 


 


 
 
 
 
 

 




 












 


 






#line 5408 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

 


 


 


 


 


 


 


 


 
















 


 
#line 5478 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

 
#line 5493 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

 
#line 5519 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

 


 


 
 
 
 
 

 
 























 























 























 























 























 























 























 























 
 
#line 5740 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

 
#line 5752 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

 






 
#line 5769 ".\\Source\\FWLib\\cm3\\stm32f10x.h"



     


 
 


 


 


 


 


 


 


 


 

 


 


 


 


 


 


 


 


 

 


 


 


 


 


 


 


 


 


 


 


 


 


 


 


 


 

 


 


 


 


 


 


 


 


 

 


#line 5913 ".\\Source\\FWLib\\cm3\\stm32f10x.h"



 


#line 5925 ".\\Source\\FWLib\\cm3\\stm32f10x.h"



 


#line 5937 ".\\Source\\FWLib\\cm3\\stm32f10x.h"



 


#line 5949 ".\\Source\\FWLib\\cm3\\stm32f10x.h"



 


#line 5961 ".\\Source\\FWLib\\cm3\\stm32f10x.h"



 


#line 5973 ".\\Source\\FWLib\\cm3\\stm32f10x.h"



 


#line 5985 ".\\Source\\FWLib\\cm3\\stm32f10x.h"



 


#line 5997 ".\\Source\\FWLib\\cm3\\stm32f10x.h"



 

 


#line 6011 ".\\Source\\FWLib\\cm3\\stm32f10x.h"



 


#line 6023 ".\\Source\\FWLib\\cm3\\stm32f10x.h"



 


#line 6035 ".\\Source\\FWLib\\cm3\\stm32f10x.h"



 


#line 6047 ".\\Source\\FWLib\\cm3\\stm32f10x.h"



 


#line 6059 ".\\Source\\FWLib\\cm3\\stm32f10x.h"



 


#line 6071 ".\\Source\\FWLib\\cm3\\stm32f10x.h"



 


#line 6083 ".\\Source\\FWLib\\cm3\\stm32f10x.h"



 


#line 6095 ".\\Source\\FWLib\\cm3\\stm32f10x.h"



 


#line 6107 ".\\Source\\FWLib\\cm3\\stm32f10x.h"



 


#line 6119 ".\\Source\\FWLib\\cm3\\stm32f10x.h"



 


#line 6131 ".\\Source\\FWLib\\cm3\\stm32f10x.h"



 


#line 6143 ".\\Source\\FWLib\\cm3\\stm32f10x.h"



 


#line 6155 ".\\Source\\FWLib\\cm3\\stm32f10x.h"



 


#line 6167 ".\\Source\\FWLib\\cm3\\stm32f10x.h"



 


#line 6179 ".\\Source\\FWLib\\cm3\\stm32f10x.h"



 


#line 6191 ".\\Source\\FWLib\\cm3\\stm32f10x.h"



 
 
 
 
 

 
 
#line 6211 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

 
#line 6222 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

 
#line 6240 ".\\Source\\FWLib\\cm3\\stm32f10x.h"











 





 





 
#line 6278 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

 












 
#line 6299 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

 
 






 




 





 





 






 




 





 





 






   




 





 





 





 




 





 





 





 




 





 





 
 


 
#line 6439 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

 
#line 6456 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

 
#line 6473 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

 
#line 6490 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

 
#line 6524 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

 
#line 6558 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

 
#line 6592 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

 
#line 6626 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

 
#line 6660 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

 
#line 6694 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

 
#line 6728 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

 
#line 6762 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

 
#line 6796 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

 
#line 6830 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

 
#line 6864 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

 
#line 6898 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

 
#line 6932 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

 
#line 6966 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

 
#line 7000 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

 
#line 7034 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

 
#line 7068 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

 
#line 7102 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

 
#line 7136 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

 
#line 7170 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

 
#line 7204 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

 
#line 7238 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

 
#line 7272 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

 
#line 7306 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

 
#line 7340 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

 
#line 7374 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

 
#line 7408 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

 
#line 7442 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

 
 
 
 
 

 









#line 7469 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

 
#line 7477 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

 
#line 7487 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

 


 


 


 


 





















 




 
 
 
 
 

 
#line 7548 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

 
#line 7557 ".\\Source\\FWLib\\cm3\\stm32f10x.h"







 



#line 7578 ".\\Source\\FWLib\\cm3\\stm32f10x.h"



 



 


 
#line 7603 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

 
#line 7613 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

 




 


 
 
 
 
 

 
#line 7639 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

 


 



 
#line 7663 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

 
#line 7672 ".\\Source\\FWLib\\cm3\\stm32f10x.h"







 
#line 7692 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

 
#line 7703 ".\\Source\\FWLib\\cm3\\stm32f10x.h"



 
 
 
 
 

 


#line 7732 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

 









#line 7766 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

 
 
 
 
 

 









 


 


 





 
#line 7806 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

 


 









 


 

 



 



 



 



 



 



 



 



#line 8270 ".\\Source\\FWLib\\cm3\\stm32f10x.h"



 

 

  

#line 1 ".\\Source\\APP\\stm32f10x_conf.h"



















  

 



 
 
#line 1 ".\\Source\\FWLib\\inc\\stm32f10x_adc.h"



















  

 







 
#line 1 ".\\Source\\FWLib\\cm3\\stm32f10x.h"























 



 



 
    
#line 8310 ".\\Source\\FWLib\\cm3\\stm32f10x.h"



 

  

 

 
#line 32 ".\\Source\\FWLib\\inc\\stm32f10x_adc.h"



 



 



 



 

typedef struct
{
  uint32_t ADC_Mode;                      

 

  FunctionalState ADC_ScanConvMode;       

 

  FunctionalState ADC_ContinuousConvMode; 

 

  uint32_t ADC_ExternalTrigConv;          

 

  uint32_t ADC_DataAlign;                 
 

  uint8_t ADC_NbrOfChannel;               

 
}ADC_InitTypeDef;


 



 










 

#line 103 ".\\Source\\FWLib\\inc\\stm32f10x_adc.h"

#line 114 ".\\Source\\FWLib\\inc\\stm32f10x_adc.h"


 



 

#line 128 ".\\Source\\FWLib\\inc\\stm32f10x_adc.h"




#line 138 ".\\Source\\FWLib\\inc\\stm32f10x_adc.h"

#line 153 ".\\Source\\FWLib\\inc\\stm32f10x_adc.h"


 



 







 



 

#line 191 ".\\Source\\FWLib\\inc\\stm32f10x_adc.h"




#line 204 ".\\Source\\FWLib\\inc\\stm32f10x_adc.h"


 



 

#line 228 ".\\Source\\FWLib\\inc\\stm32f10x_adc.h"


 



 

















#line 265 ".\\Source\\FWLib\\inc\\stm32f10x_adc.h"


 



 

#line 281 ".\\Source\\FWLib\\inc\\stm32f10x_adc.h"


 



 

#line 296 ".\\Source\\FWLib\\inc\\stm32f10x_adc.h"

#line 304 ".\\Source\\FWLib\\inc\\stm32f10x_adc.h"


 



 











 



 

#line 337 ".\\Source\\FWLib\\inc\\stm32f10x_adc.h"


 



 





 



 





 



 





 



 





  




 




 



 





 



 





 



 



 



 



 

void ADC_DeInit(ADC_TypeDef* ADCx);
void ADC_Init(ADC_TypeDef* ADCx, ADC_InitTypeDef* ADC_InitStruct);
void ADC_StructInit(ADC_InitTypeDef* ADC_InitStruct);
void ADC_Cmd(ADC_TypeDef* ADCx, FunctionalState NewState);
void ADC_DMACmd(ADC_TypeDef* ADCx, FunctionalState NewState);
void ADC_ITConfig(ADC_TypeDef* ADCx, uint16_t ADC_IT, FunctionalState NewState);
void ADC_ResetCalibration(ADC_TypeDef* ADCx);
FlagStatus ADC_GetResetCalibrationStatus(ADC_TypeDef* ADCx);
void ADC_StartCalibration(ADC_TypeDef* ADCx);
FlagStatus ADC_GetCalibrationStatus(ADC_TypeDef* ADCx);
void ADC_SoftwareStartConvCmd(ADC_TypeDef* ADCx, FunctionalState NewState);
FlagStatus ADC_GetSoftwareStartConvStatus(ADC_TypeDef* ADCx);
void ADC_DiscModeChannelCountConfig(ADC_TypeDef* ADCx, uint8_t Number);
void ADC_DiscModeCmd(ADC_TypeDef* ADCx, FunctionalState NewState);
void ADC_RegularChannelConfig(ADC_TypeDef* ADCx, uint8_t ADC_Channel, uint8_t Rank, uint8_t ADC_SampleTime);
void ADC_ExternalTrigConvCmd(ADC_TypeDef* ADCx, FunctionalState NewState);
uint16_t ADC_GetConversionValue(ADC_TypeDef* ADCx);
uint32_t ADC_GetDualModeConversionValue(void);
void ADC_AutoInjectedConvCmd(ADC_TypeDef* ADCx, FunctionalState NewState);
void ADC_InjectedDiscModeCmd(ADC_TypeDef* ADCx, FunctionalState NewState);
void ADC_ExternalTrigInjectedConvConfig(ADC_TypeDef* ADCx, uint32_t ADC_ExternalTrigInjecConv);
void ADC_ExternalTrigInjectedConvCmd(ADC_TypeDef* ADCx, FunctionalState NewState);
void ADC_SoftwareStartInjectedConvCmd(ADC_TypeDef* ADCx, FunctionalState NewState);
FlagStatus ADC_GetSoftwareStartInjectedConvCmdStatus(ADC_TypeDef* ADCx);
void ADC_InjectedChannelConfig(ADC_TypeDef* ADCx, uint8_t ADC_Channel, uint8_t Rank, uint8_t ADC_SampleTime);
void ADC_InjectedSequencerLengthConfig(ADC_TypeDef* ADCx, uint8_t Length);
void ADC_SetInjectedOffset(ADC_TypeDef* ADCx, uint8_t ADC_InjectedChannel, uint16_t Offset);
uint16_t ADC_GetInjectedConversionValue(ADC_TypeDef* ADCx, uint8_t ADC_InjectedChannel);
void ADC_AnalogWatchdogCmd(ADC_TypeDef* ADCx, uint32_t ADC_AnalogWatchdog);
void ADC_AnalogWatchdogThresholdsConfig(ADC_TypeDef* ADCx, uint16_t HighThreshold, uint16_t LowThreshold);
void ADC_AnalogWatchdogSingleChannelConfig(ADC_TypeDef* ADCx, uint8_t ADC_Channel);
void ADC_TempSensorVrefintCmd(FunctionalState NewState);
FlagStatus ADC_GetFlagStatus(ADC_TypeDef* ADCx, uint8_t ADC_FLAG);
void ADC_ClearFlag(ADC_TypeDef* ADCx, uint8_t ADC_FLAG);
ITStatus ADC_GetITStatus(ADC_TypeDef* ADCx, uint16_t ADC_IT);
void ADC_ClearITPendingBit(ADC_TypeDef* ADCx, uint16_t ADC_IT);









 



 



 

 
#line 29 ".\\Source\\APP\\stm32f10x_conf.h"
#line 1 ".\\Source\\FWLib\\inc\\stm32f10x_bkp.h"



















  

 







 
#line 32 ".\\Source\\FWLib\\inc\\stm32f10x_bkp.h"



 



 



 



 



 



 







 



 

#line 77 ".\\Source\\FWLib\\inc\\stm32f10x_bkp.h"


 



 

#line 127 ".\\Source\\FWLib\\inc\\stm32f10x_bkp.h"

#line 142 ".\\Source\\FWLib\\inc\\stm32f10x_bkp.h"




 



 



 



 



 

void BKP_DeInit(void);
void BKP_TamperPinLevelConfig(uint16_t BKP_TamperPinLevel);
void BKP_TamperPinCmd(FunctionalState NewState);
void BKP_ITConfig(FunctionalState NewState);
void BKP_RTCOutputConfig(uint16_t BKP_RTCOutputSource);
void BKP_SetRTCCalibrationValue(uint8_t CalibrationValue);
void BKP_WriteBackupRegister(uint16_t BKP_DR, uint16_t Data);
uint16_t BKP_ReadBackupRegister(uint16_t BKP_DR);
FlagStatus BKP_GetFlagStatus(void);
void BKP_ClearFlag(void);
ITStatus BKP_GetITStatus(void);
void BKP_ClearITPendingBit(void);








 



 



 

 
#line 30 ".\\Source\\APP\\stm32f10x_conf.h"
#line 1 ".\\Source\\FWLib\\inc\\stm32f10x_can.h"



















  

 







 
#line 32 ".\\Source\\FWLib\\inc\\stm32f10x_can.h"



 



 



 






 

typedef struct
{
  uint16_t CAN_Prescaler;    
  
  uint8_t CAN_Mode;         
 

  uint8_t CAN_SJW;          

 

  uint8_t CAN_BS1;          
 

  uint8_t CAN_BS2;          
 
  
  FunctionalState CAN_TTCM; 
 
  
  FunctionalState CAN_ABOM;  
 

  FunctionalState CAN_AWUM;  
 

  FunctionalState CAN_NART;  
 

  FunctionalState CAN_RFLM;  
 

  FunctionalState CAN_TXFP;  
 
} CAN_InitTypeDef;



 

typedef struct
{
  uint16_t CAN_FilterIdHigh;             

 

  uint16_t CAN_FilterIdLow;              

 

  uint16_t CAN_FilterMaskIdHigh;         


 

  uint16_t CAN_FilterMaskIdLow;          


 

  uint16_t CAN_FilterFIFOAssignment;     
 
  
  uint8_t CAN_FilterNumber;               

  uint8_t CAN_FilterMode;                
 

  uint8_t CAN_FilterScale;               
 

  FunctionalState CAN_FilterActivation;  
 
} CAN_FilterInitTypeDef;



 

typedef struct
{
  uint32_t StdId;  
 

  uint32_t ExtId;  
 

  uint8_t IDE;     
 

  uint8_t RTR;     
 

  uint8_t DLC;     
 

  uint8_t Data[8];  
} CanTxMsg;



 

typedef struct
{
  uint32_t StdId;  
 

  uint32_t ExtId;  
 

  uint8_t IDE;     
 

  uint8_t RTR;     
 

  uint8_t DLC;     
 

  uint8_t Data[8];  

  uint8_t FMI;     
 
} CanRxMsg;



 



 



 






 



 










 



 










 



 

#line 247 ".\\Source\\FWLib\\inc\\stm32f10x_can.h"




 



 

#line 265 ".\\Source\\FWLib\\inc\\stm32f10x_can.h"





 



 





 



 







 



 








 



 









 



 








 



 



 



 








 



 







 



 







 



 








 



 








 



 






 



 






 



 

 
 

 




 
#line 446 ".\\Source\\FWLib\\inc\\stm32f10x_can.h"

 



 

 





#line 467 ".\\Source\\FWLib\\inc\\stm32f10x_can.h"








 

  


 


  


 
#line 493 ".\\Source\\FWLib\\inc\\stm32f10x_can.h"

 



 






 





#line 518 ".\\Source\\FWLib\\inc\\stm32f10x_can.h"

#line 525 ".\\Source\\FWLib\\inc\\stm32f10x_can.h"



 



 



 



 



 

void CAN_DeInit(CAN_TypeDef* CANx);
uint8_t CAN_Init(CAN_TypeDef* CANx, CAN_InitTypeDef* CAN_InitStruct);
void CAN_FilterInit(CAN_FilterInitTypeDef* CAN_FilterInitStruct);
void CAN_StructInit(CAN_InitTypeDef* CAN_InitStruct);
void CAN_SlaveStartBank(uint8_t CAN_BankNumber); 
void CAN_ITConfig(CAN_TypeDef* CANx, uint32_t CAN_IT, FunctionalState NewState);
uint8_t CAN_Transmit(CAN_TypeDef* CANx, CanTxMsg* TxMessage);
uint8_t CAN_TransmitStatus(CAN_TypeDef* CANx, uint8_t TransmitMailbox);
void CAN_CancelTransmit(CAN_TypeDef* CANx, uint8_t Mailbox);
void CAN_FIFORelease(CAN_TypeDef* CANx, uint8_t FIFONumber);
uint8_t CAN_MessagePending(CAN_TypeDef* CANx, uint8_t FIFONumber);
void CAN_Receive(CAN_TypeDef* CANx, uint8_t FIFONumber, CanRxMsg* RxMessage);
void CAN_DBGFreeze(CAN_TypeDef* CANx, FunctionalState NewState);
uint8_t CAN_Sleep(CAN_TypeDef* CANx);
uint8_t CAN_WakeUp(CAN_TypeDef* CANx);
FlagStatus CAN_GetFlagStatus(CAN_TypeDef* CANx, uint32_t CAN_FLAG);
void CAN_ClearFlag(CAN_TypeDef* CANx, uint32_t CAN_FLAG);
ITStatus CAN_GetITStatus(CAN_TypeDef* CANx, uint32_t CAN_IT);
void CAN_ClearITPendingBit(CAN_TypeDef* CANx, uint32_t CAN_IT);








 



 



 

 
#line 31 ".\\Source\\APP\\stm32f10x_conf.h"
#line 1 ".\\Source\\FWLib\\inc\\stm32f10x_cec.h"



















  

 







 
#line 32 ".\\Source\\FWLib\\inc\\stm32f10x_cec.h"



 



 
  



 
   


  
typedef struct
{
  uint16_t CEC_BitTimingMode; 
 
  uint16_t CEC_BitPeriodMode; 
 
}CEC_InitTypeDef;



 



  
  


  







 



  







  




  
#line 99 ".\\Source\\FWLib\\inc\\stm32f10x_cec.h"


  




  



  



  




 



 
   


  
#line 135 ".\\Source\\FWLib\\inc\\stm32f10x_cec.h"



  
#line 146 ".\\Source\\FWLib\\inc\\stm32f10x_cec.h"


                               
#line 156 ".\\Source\\FWLib\\inc\\stm32f10x_cec.h"



  



  



 
 


 



  
void CEC_DeInit(void);
void CEC_Init(CEC_InitTypeDef* CEC_InitStruct);
void CEC_Cmd(FunctionalState NewState);
void CEC_ITConfig(FunctionalState NewState);
void CEC_OwnAddressConfig(uint8_t CEC_OwnAddress);
void CEC_SetPrescaler(uint16_t CEC_Prescaler);
void CEC_SendDataByte(uint8_t Data);
uint8_t CEC_ReceiveDataByte(void);
void CEC_StartOfMessage(void);
void CEC_EndOfMessageCmd(FunctionalState NewState);
FlagStatus CEC_GetFlagStatus(uint32_t CEC_FLAG);
void CEC_ClearFlag(uint32_t CEC_FLAG);
ITStatus CEC_GetITStatus(uint8_t CEC_IT);
void CEC_ClearITPendingBit(uint16_t CEC_IT);









  



  



  

 
#line 32 ".\\Source\\APP\\stm32f10x_conf.h"
#line 1 ".\\Source\\FWLib\\inc\\stm32f10x_crc.h"



















  

 







 
#line 32 ".\\Source\\FWLib\\inc\\stm32f10x_crc.h"



 



 



 



 



 



 



 



 



 

void CRC_ResetDR(void);
uint32_t CRC_CalcCRC(uint32_t Data);
uint32_t CRC_CalcBlockCRC(uint32_t pBuffer[], uint32_t BufferLength);
uint32_t CRC_GetCRC(void);
void CRC_SetIDRegister(uint8_t IDValue);
uint8_t CRC_GetIDRegister(void);








 



 



 

 
#line 33 ".\\Source\\APP\\stm32f10x_conf.h"
#line 1 ".\\Source\\FWLib\\inc\\stm32f10x_dac.h"



















  

 







 
#line 32 ".\\Source\\FWLib\\inc\\stm32f10x_dac.h"



 



 



 



 

typedef struct
{
  uint32_t DAC_Trigger;                      
 

  uint32_t DAC_WaveGeneration;               

 

  uint32_t DAC_LFSRUnmask_TriangleAmplitude; 

 

  uint32_t DAC_OutputBuffer;                 
 
}DAC_InitTypeDef;



 



 



 

#line 93 ".\\Source\\FWLib\\inc\\stm32f10x_dac.h"

#line 103 ".\\Source\\FWLib\\inc\\stm32f10x_dac.h"



 



 

#line 118 ".\\Source\\FWLib\\inc\\stm32f10x_dac.h"


 



 

#line 150 ".\\Source\\FWLib\\inc\\stm32f10x_dac.h"

#line 175 ".\\Source\\FWLib\\inc\\stm32f10x_dac.h"


 



 







 



 







 



 

#line 213 ".\\Source\\FWLib\\inc\\stm32f10x_dac.h"


 



 







 



 




 
#line 260 ".\\Source\\FWLib\\inc\\stm32f10x_dac.h"



 



 



 



 

void DAC_DeInit(void);
void DAC_Init(uint32_t DAC_Channel, DAC_InitTypeDef* DAC_InitStruct);
void DAC_StructInit(DAC_InitTypeDef* DAC_InitStruct);
void DAC_Cmd(uint32_t DAC_Channel, FunctionalState NewState);



void DAC_DMACmd(uint32_t DAC_Channel, FunctionalState NewState);
void DAC_SoftwareTriggerCmd(uint32_t DAC_Channel, FunctionalState NewState);
void DAC_DualSoftwareTriggerCmd(FunctionalState NewState);
void DAC_WaveGenerationCmd(uint32_t DAC_Channel, uint32_t DAC_Wave, FunctionalState NewState);
void DAC_SetChannel1Data(uint32_t DAC_Align, uint16_t Data);
void DAC_SetChannel2Data(uint32_t DAC_Align, uint16_t Data);
void DAC_SetDualChannelData(uint32_t DAC_Align, uint16_t Data2, uint16_t Data1);
uint16_t DAC_GetDataOutputValue(uint32_t DAC_Channel);
#line 298 ".\\Source\\FWLib\\inc\\stm32f10x_dac.h"








 



 



 

 
#line 34 ".\\Source\\APP\\stm32f10x_conf.h"
#line 1 ".\\Source\\FWLib\\inc\\stm32f10x_dbgmcu.h"



















  

 







 
#line 32 ".\\Source\\FWLib\\inc\\stm32f10x_dbgmcu.h"



 



 



 



 



 

#line 79 ".\\Source\\FWLib\\inc\\stm32f10x_dbgmcu.h"
                                              



  



 



 



 

uint32_t DBGMCU_GetREVID(void);
uint32_t DBGMCU_GetDEVID(void);
void DBGMCU_Config(uint32_t DBGMCU_Periph, FunctionalState NewState);








 



 



 

 
#line 35 ".\\Source\\APP\\stm32f10x_conf.h"
#line 1 ".\\Source\\FWLib\\inc\\stm32f10x_dma.h"



















  

 







 
#line 32 ".\\Source\\FWLib\\inc\\stm32f10x_dma.h"



 



 



 



 

typedef struct
{
  uint32_t DMA_PeripheralBaseAddr;  

  uint32_t DMA_MemoryBaseAddr;      

  uint32_t DMA_DIR;                
 

  uint32_t DMA_BufferSize;         

 

  uint32_t DMA_PeripheralInc;      
 

  uint32_t DMA_MemoryInc;          
 

  uint32_t DMA_PeripheralDataSize; 
 

  uint32_t DMA_MemoryDataSize;     
 

  uint32_t DMA_Mode;               


 

  uint32_t DMA_Priority;           
 

  uint32_t DMA_M2M;                
 
}DMA_InitTypeDef;



 



 

#line 106 ".\\Source\\FWLib\\inc\\stm32f10x_dma.h"



 







 



 







 



 







 



 

#line 153 ".\\Source\\FWLib\\inc\\stm32f10x_dma.h"


 



 

#line 167 ".\\Source\\FWLib\\inc\\stm32f10x_dma.h"


 



 






 



 

#line 194 ".\\Source\\FWLib\\inc\\stm32f10x_dma.h"


 



 







 



 






#line 247 ".\\Source\\FWLib\\inc\\stm32f10x_dma.h"

#line 268 ".\\Source\\FWLib\\inc\\stm32f10x_dma.h"



#line 295 ".\\Source\\FWLib\\inc\\stm32f10x_dma.h"



 



 
#line 331 ".\\Source\\FWLib\\inc\\stm32f10x_dma.h"

#line 352 ".\\Source\\FWLib\\inc\\stm32f10x_dma.h"



#line 379 ".\\Source\\FWLib\\inc\\stm32f10x_dma.h"


 



 





 



 



 



 



 

void DMA_DeInit(DMA_Channel_TypeDef* DMAy_Channelx);
void DMA_Init(DMA_Channel_TypeDef* DMAy_Channelx, DMA_InitTypeDef* DMA_InitStruct);
void DMA_StructInit(DMA_InitTypeDef* DMA_InitStruct);
void DMA_Cmd(DMA_Channel_TypeDef* DMAy_Channelx, FunctionalState NewState);
void DMA_ITConfig(DMA_Channel_TypeDef* DMAy_Channelx, uint32_t DMA_IT, FunctionalState NewState);
void DMA_SetCurrDataCounter(DMA_Channel_TypeDef* DMAy_Channelx, uint16_t DataNumber); 
uint16_t DMA_GetCurrDataCounter(DMA_Channel_TypeDef* DMAy_Channelx);
FlagStatus DMA_GetFlagStatus(uint32_t DMA_FLAG);
void DMA_ClearFlag(uint32_t DMA_FLAG);
ITStatus DMA_GetITStatus(uint32_t DMA_IT);
void DMA_ClearITPendingBit(uint32_t DMA_IT);








 



 



 

 
#line 36 ".\\Source\\APP\\stm32f10x_conf.h"
#line 1 ".\\Source\\FWLib\\inc\\stm32f10x_exti.h"



















  

 







 
#line 32 ".\\Source\\FWLib\\inc\\stm32f10x_exti.h"



 



 



 



 

typedef enum
{
  EXTI_Mode_Interrupt = 0x00,
  EXTI_Mode_Event = 0x04
}EXTIMode_TypeDef;





 

typedef enum
{
  EXTI_Trigger_Rising = 0x08,
  EXTI_Trigger_Falling = 0x0C,  
  EXTI_Trigger_Rising_Falling = 0x10
}EXTITrigger_TypeDef;






 

typedef struct
{
  uint32_t EXTI_Line;               
 
   
  EXTIMode_TypeDef EXTI_Mode;       
 

  EXTITrigger_TypeDef EXTI_Trigger; 
 

  FunctionalState EXTI_LineCmd;     
  
}EXTI_InitTypeDef;



 



 



 

#line 123 ".\\Source\\FWLib\\inc\\stm32f10x_exti.h"
                                          
#line 135 ".\\Source\\FWLib\\inc\\stm32f10x_exti.h"

                    


 



 



 



 



 

void EXTI_DeInit(void);
void EXTI_Init(EXTI_InitTypeDef* EXTI_InitStruct);
void EXTI_StructInit(EXTI_InitTypeDef* EXTI_InitStruct);
void EXTI_GenerateSWInterrupt(uint32_t EXTI_Line);
FlagStatus EXTI_GetFlagStatus(uint32_t EXTI_Line);
void EXTI_ClearFlag(uint32_t EXTI_Line);
ITStatus EXTI_GetITStatus(uint32_t EXTI_Line);
void EXTI_ClearITPendingBit(uint32_t EXTI_Line);








 



 



 

 
#line 37 ".\\Source\\APP\\stm32f10x_conf.h"
#line 1 ".\\Source\\FWLib\\inc\\stm32f10x_flash.h"



















  

 







 
#line 32 ".\\Source\\FWLib\\inc\\stm32f10x_flash.h"



 



 



 



 

typedef enum
{ 
  FLASH_BUSY = 1,
  FLASH_ERROR_PG,
  FLASH_ERROR_WRP,
  FLASH_COMPLETE,
  FLASH_TIMEOUT
}FLASH_Status;



 



 



 

#line 76 ".\\Source\\FWLib\\inc\\stm32f10x_flash.h"


 



 







 



 







 



 

 
#line 117 ".\\Source\\FWLib\\inc\\stm32f10x_flash.h"

 
#line 143 ".\\Source\\FWLib\\inc\\stm32f10x_flash.h"

 
#line 210 ".\\Source\\FWLib\\inc\\stm32f10x_flash.h"











 



 







 



 







 



 








 


 
#line 269 ".\\Source\\FWLib\\inc\\stm32f10x_flash.h"


 


 







#line 293 ".\\Source\\FWLib\\inc\\stm32f10x_flash.h"



 



 
















 
#line 345 ".\\Source\\FWLib\\inc\\stm32f10x_flash.h"



 



 



 



 



 

 
void FLASH_SetLatency(uint32_t FLASH_Latency);
void FLASH_HalfCycleAccessCmd(uint32_t FLASH_HalfCycleAccess);
void FLASH_PrefetchBufferCmd(uint32_t FLASH_PrefetchBuffer);
void FLASH_Unlock(void);
void FLASH_Lock(void);
FLASH_Status FLASH_ErasePage(uint32_t Page_Address);
FLASH_Status FLASH_EraseAllPages(void);
FLASH_Status FLASH_EraseOptionBytes(void);
FLASH_Status FLASH_ProgramWord(uint32_t Address, uint32_t Data);
FLASH_Status FLASH_ProgramHalfWord(uint32_t Address, uint16_t Data);
FLASH_Status FLASH_ProgramOptionByteData(uint32_t Address, uint8_t Data);
FLASH_Status FLASH_EnableWriteProtection(uint32_t FLASH_Pages);
FLASH_Status FLASH_ReadOutProtection(FunctionalState NewState);
FLASH_Status FLASH_UserOptionByteConfig(uint16_t OB_IWDG, uint16_t OB_STOP, uint16_t OB_STDBY);
uint32_t FLASH_GetUserOptionByte(void);
uint32_t FLASH_GetWriteProtectionOptionByte(void);
FlagStatus FLASH_GetReadOutProtectionStatus(void);
FlagStatus FLASH_GetPrefetchBufferStatus(void);
void FLASH_ITConfig(uint32_t FLASH_IT, FunctionalState NewState);
FlagStatus FLASH_GetFlagStatus(uint32_t FLASH_FLAG);
void FLASH_ClearFlag(uint32_t FLASH_FLAG);
FLASH_Status FLASH_GetStatus(void);
FLASH_Status FLASH_WaitForLastOperation(uint32_t Timeout);

 
void FLASH_UnlockBank1(void);
void FLASH_LockBank1(void);
FLASH_Status FLASH_EraseAllBank1Pages(void);
FLASH_Status FLASH_GetBank1Status(void);
FLASH_Status FLASH_WaitForLastBank1Operation(uint32_t Timeout);


 
void FLASH_UnlockBank2(void);
void FLASH_LockBank2(void);
FLASH_Status FLASH_EraseAllBank2Pages(void);
FLASH_Status FLASH_GetBank2Status(void);
FLASH_Status FLASH_WaitForLastBank2Operation(uint32_t Timeout);
FLASH_Status FLASH_BootConfig(uint16_t FLASH_BOOT);









 



 



 

 
#line 38 ".\\Source\\APP\\stm32f10x_conf.h"
#line 1 ".\\Source\\FWLib\\inc\\stm32f10x_fsmc.h"



















  

 







 
#line 32 ".\\Source\\FWLib\\inc\\stm32f10x_fsmc.h"



 



 



 



 

typedef struct
{
  uint32_t FSMC_AddressSetupTime;       


 

  uint32_t FSMC_AddressHoldTime;        


 

  uint32_t FSMC_DataSetupTime;          


 

  uint32_t FSMC_BusTurnAroundDuration;  


 

  uint32_t FSMC_CLKDivision;            

 

  uint32_t FSMC_DataLatency;            





 

  uint32_t FSMC_AccessMode;             
 
}FSMC_NORSRAMTimingInitTypeDef;



 

typedef struct
{
  uint32_t FSMC_Bank;                
 

  uint32_t FSMC_DataAddressMux;      

 

  uint32_t FSMC_MemoryType;          

 

  uint32_t FSMC_MemoryDataWidth;     
 

  uint32_t FSMC_BurstAccessMode;     

 
                                       
  uint32_t FSMC_AsynchronousWait;     

 

  uint32_t FSMC_WaitSignalPolarity;  

 

  uint32_t FSMC_WrapMode;            

 

  uint32_t FSMC_WaitSignalActive;    


 

  uint32_t FSMC_WriteOperation;      
 

  uint32_t FSMC_WaitSignal;          

 

  uint32_t FSMC_ExtendedMode;        
 

  uint32_t FSMC_WriteBurst;          
  

  FSMC_NORSRAMTimingInitTypeDef* FSMC_ReadWriteTimingStruct;    

  FSMC_NORSRAMTimingInitTypeDef* FSMC_WriteTimingStruct;            
}FSMC_NORSRAMInitTypeDef;



 

typedef struct
{
  uint32_t FSMC_SetupTime;      



 

  uint32_t FSMC_WaitSetupTime;  



 

  uint32_t FSMC_HoldSetupTime;  




 

  uint32_t FSMC_HiZSetupTime;   



 
}FSMC_NAND_PCCARDTimingInitTypeDef;



 

typedef struct
{
  uint32_t FSMC_Bank;              
 

  uint32_t FSMC_Waitfeature;      
 

  uint32_t FSMC_MemoryDataWidth;  
 

  uint32_t FSMC_ECC;              
 

  uint32_t FSMC_ECCPageSize;      
 

  uint32_t FSMC_TCLRSetupTime;    

 

  uint32_t FSMC_TARSetupTime;     

  

  FSMC_NAND_PCCARDTimingInitTypeDef*  FSMC_CommonSpaceTimingStruct;     

  FSMC_NAND_PCCARDTimingInitTypeDef*  FSMC_AttributeSpaceTimingStruct;  
}FSMC_NANDInitTypeDef;



 

typedef struct
{
  uint32_t FSMC_Waitfeature;    
 

  uint32_t FSMC_TCLRSetupTime;  

 

  uint32_t FSMC_TARSetupTime;   

  

  
  FSMC_NAND_PCCARDTimingInitTypeDef*  FSMC_CommonSpaceTimingStruct;  

  FSMC_NAND_PCCARDTimingInitTypeDef*  FSMC_AttributeSpaceTimingStruct;    
  
  FSMC_NAND_PCCARDTimingInitTypeDef*  FSMC_IOSpaceTimingStruct;    
}FSMC_PCCARDInitTypeDef;



 



 



 






 



   




 



     



 



















 



 








 



 

#line 316 ".\\Source\\FWLib\\inc\\stm32f10x_fsmc.h"



 



 








 



 







 
  


 







 
  


 








 



 








 



 








 



 





                              


 



 







 



 









 



 







 



 





 



 





 



 





 



 





 



 





 



 





 



 

#line 520 ".\\Source\\FWLib\\inc\\stm32f10x_fsmc.h"



 



 
  


 



 








 




 








 



 

#line 576 ".\\Source\\FWLib\\inc\\stm32f10x_fsmc.h"



 



 





 



 





 



 





 



 





 



 





 



 





 



 

#line 652 ".\\Source\\FWLib\\inc\\stm32f10x_fsmc.h"


 



 

#line 668 ".\\Source\\FWLib\\inc\\stm32f10x_fsmc.h"





 



 



 



 



 



 

void FSMC_NORSRAMDeInit(uint32_t FSMC_Bank);
void FSMC_NANDDeInit(uint32_t FSMC_Bank);
void FSMC_PCCARDDeInit(void);
void FSMC_NORSRAMInit(FSMC_NORSRAMInitTypeDef* FSMC_NORSRAMInitStruct);
void FSMC_NANDInit(FSMC_NANDInitTypeDef* FSMC_NANDInitStruct);
void FSMC_PCCARDInit(FSMC_PCCARDInitTypeDef* FSMC_PCCARDInitStruct);
void FSMC_NORSRAMStructInit(FSMC_NORSRAMInitTypeDef* FSMC_NORSRAMInitStruct);
void FSMC_NANDStructInit(FSMC_NANDInitTypeDef* FSMC_NANDInitStruct);
void FSMC_PCCARDStructInit(FSMC_PCCARDInitTypeDef* FSMC_PCCARDInitStruct);
void FSMC_NORSRAMCmd(uint32_t FSMC_Bank, FunctionalState NewState);
void FSMC_NANDCmd(uint32_t FSMC_Bank, FunctionalState NewState);
void FSMC_PCCARDCmd(FunctionalState NewState);
void FSMC_NANDECCCmd(uint32_t FSMC_Bank, FunctionalState NewState);
uint32_t FSMC_GetECC(uint32_t FSMC_Bank);
void FSMC_ITConfig(uint32_t FSMC_Bank, uint32_t FSMC_IT, FunctionalState NewState);
FlagStatus FSMC_GetFlagStatus(uint32_t FSMC_Bank, uint32_t FSMC_FLAG);
void FSMC_ClearFlag(uint32_t FSMC_Bank, uint32_t FSMC_FLAG);
ITStatus FSMC_GetITStatus(uint32_t FSMC_Bank, uint32_t FSMC_IT);
void FSMC_ClearITPendingBit(uint32_t FSMC_Bank, uint32_t FSMC_IT);








 



 



  

 
#line 39 ".\\Source\\APP\\stm32f10x_conf.h"
#line 1 ".\\Source\\FWLib\\inc\\stm32f10x_gpio.h"



















  

 







 
#line 32 ".\\Source\\FWLib\\inc\\stm32f10x_gpio.h"



 



 



 

#line 52 ".\\Source\\FWLib\\inc\\stm32f10x_gpio.h"
                                     


 

typedef enum
{ 
  GPIO_Speed_10MHz = 1,
  GPIO_Speed_2MHz, 
  GPIO_Speed_50MHz
}GPIOSpeed_TypeDef;





 

typedef enum
{ GPIO_Mode_AIN = 0x0,
  GPIO_Mode_IN_FLOATING = 0x04,
  GPIO_Mode_IPD = 0x28,
  GPIO_Mode_IPU = 0x48,
  GPIO_Mode_Out_OD = 0x14,
  GPIO_Mode_Out_PP = 0x10,
  GPIO_Mode_AF_OD = 0x1C,
  GPIO_Mode_AF_PP = 0x18
}GPIOMode_TypeDef;








 

typedef struct
{
  uint16_t GPIO_Pin;             
 

  GPIOSpeed_TypeDef GPIO_Speed;  
 

  GPIOMode_TypeDef GPIO_Mode;    
 
}GPIO_InitTypeDef;




 

typedef enum
{ Bit_RESET = 0,
  Bit_SET
}BitAction;





 



 



 

#line 143 ".\\Source\\FWLib\\inc\\stm32f10x_gpio.h"



#line 162 ".\\Source\\FWLib\\inc\\stm32f10x_gpio.h"



 



 

#line 203 ".\\Source\\FWLib\\inc\\stm32f10x_gpio.h"







#line 216 ".\\Source\\FWLib\\inc\\stm32f10x_gpio.h"






#line 244 ".\\Source\\FWLib\\inc\\stm32f10x_gpio.h"
                              


  



 

#line 265 ".\\Source\\FWLib\\inc\\stm32f10x_gpio.h"

#line 273 ".\\Source\\FWLib\\inc\\stm32f10x_gpio.h"



 



 

#line 298 ".\\Source\\FWLib\\inc\\stm32f10x_gpio.h"

#line 315 ".\\Source\\FWLib\\inc\\stm32f10x_gpio.h"



 



  








                                                 


 



 



 



 

void GPIO_DeInit(GPIO_TypeDef* GPIOx);
void GPIO_AFIODeInit(void);
void GPIO_Init(GPIO_TypeDef* GPIOx, GPIO_InitTypeDef* GPIO_InitStruct);
void GPIO_StructInit(GPIO_InitTypeDef* GPIO_InitStruct);
uint8_t GPIO_ReadInputDataBit(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);
uint16_t GPIO_ReadInputData(GPIO_TypeDef* GPIOx);
uint8_t GPIO_ReadOutputDataBit(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);
uint16_t GPIO_ReadOutputData(GPIO_TypeDef* GPIOx);
void GPIO_SetBits(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);
void GPIO_ResetBits(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);
void GPIO_WriteBit(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, BitAction BitVal);
void GPIO_Write(GPIO_TypeDef* GPIOx, uint16_t PortVal);
void GPIO_PinLockConfig(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);
void GPIO_EventOutputConfig(uint8_t GPIO_PortSource, uint8_t GPIO_PinSource);
void GPIO_EventOutputCmd(FunctionalState NewState);
void GPIO_PinRemapConfig(uint32_t GPIO_Remap, FunctionalState NewState);
void GPIO_EXTILineConfig(uint8_t GPIO_PortSource, uint8_t GPIO_PinSource);
void GPIO_ETH_MediaInterfaceConfig(uint32_t GPIO_ETH_MediaInterface);








 



 



 

 
#line 40 ".\\Source\\APP\\stm32f10x_conf.h"
#line 1 ".\\Source\\FWLib\\inc\\stm32f10x_i2c.h"



















  

 







 
#line 32 ".\\Source\\FWLib\\inc\\stm32f10x_i2c.h"



 



 



 



 

typedef struct
{
  uint32_t I2C_ClockSpeed;          
 

  uint16_t I2C_Mode;                
 

  uint16_t I2C_DutyCycle;           
 

  uint16_t I2C_OwnAddress1;         
 

  uint16_t I2C_Ack;                 
 

  uint16_t I2C_AcknowledgedAddress; 
 
}I2C_InitTypeDef;



  




 





 

#line 91 ".\\Source\\FWLib\\inc\\stm32f10x_i2c.h"


 



 







  



 







 



 







 



 







  



 

#line 165 ".\\Source\\FWLib\\inc\\stm32f10x_i2c.h"


 



 







 



 







  



 







  



 

#line 223 ".\\Source\\FWLib\\inc\\stm32f10x_i2c.h"



#line 233 ".\\Source\\FWLib\\inc\\stm32f10x_i2c.h"


 



 



 

#line 252 ".\\Source\\FWLib\\inc\\stm32f10x_i2c.h"



 

#line 271 ".\\Source\\FWLib\\inc\\stm32f10x_i2c.h"



#line 285 ".\\Source\\FWLib\\inc\\stm32f10x_i2c.h"


 



 




 







 
 

























 

 


 





























 

  
 


 
 

 






 
























 

    
 



 



 



























 

  
 

 


 
 


 


 

#line 483 ".\\Source\\FWLib\\inc\\stm32f10x_i2c.h"


 



 




 



 




 



 



 



 



 

void I2C_DeInit(I2C_TypeDef* I2Cx);
void I2C_Init(I2C_TypeDef* I2Cx, I2C_InitTypeDef* I2C_InitStruct);
void I2C_StructInit(I2C_InitTypeDef* I2C_InitStruct);
void I2C_Cmd(I2C_TypeDef* I2Cx, FunctionalState NewState);
void I2C_DMACmd(I2C_TypeDef* I2Cx, FunctionalState NewState);
void I2C_DMALastTransferCmd(I2C_TypeDef* I2Cx, FunctionalState NewState);
void I2C_GenerateSTART(I2C_TypeDef* I2Cx, FunctionalState NewState);
void I2C_GenerateSTOP(I2C_TypeDef* I2Cx, FunctionalState NewState);
void I2C_AcknowledgeConfig(I2C_TypeDef* I2Cx, FunctionalState NewState);
void I2C_OwnAddress2Config(I2C_TypeDef* I2Cx, uint8_t Address);
void I2C_DualAddressCmd(I2C_TypeDef* I2Cx, FunctionalState NewState);
void I2C_GeneralCallCmd(I2C_TypeDef* I2Cx, FunctionalState NewState);
void I2C_ITConfig(I2C_TypeDef* I2Cx, uint16_t I2C_IT, FunctionalState NewState);
void I2C_SendData(I2C_TypeDef* I2Cx, uint8_t Data);
uint8_t I2C_ReceiveData(I2C_TypeDef* I2Cx);
void I2C_Send7bitAddress(I2C_TypeDef* I2Cx, uint8_t Address, uint8_t I2C_Direction);
uint16_t I2C_ReadRegister(I2C_TypeDef* I2Cx, uint8_t I2C_Register);
void I2C_SoftwareResetCmd(I2C_TypeDef* I2Cx, FunctionalState NewState);
void I2C_SMBusAlertConfig(I2C_TypeDef* I2Cx, uint16_t I2C_SMBusAlert);
void I2C_TransmitPEC(I2C_TypeDef* I2Cx, FunctionalState NewState);
void I2C_PECPositionConfig(I2C_TypeDef* I2Cx, uint16_t I2C_PECPosition);
void I2C_CalculatePEC(I2C_TypeDef* I2Cx, FunctionalState NewState);
uint8_t I2C_GetPEC(I2C_TypeDef* I2Cx);
void I2C_ARPCmd(I2C_TypeDef* I2Cx, FunctionalState NewState);
void I2C_StretchClockCmd(I2C_TypeDef* I2Cx, FunctionalState NewState);
void I2C_FastModeDutyCycleConfig(I2C_TypeDef* I2Cx, uint16_t I2C_DutyCycle);













































































 





 
ErrorStatus I2C_CheckEvent(I2C_TypeDef* I2Cx, uint32_t I2C_EVENT);




 
uint32_t I2C_GetLastEvent(I2C_TypeDef* I2Cx);




 
FlagStatus I2C_GetFlagStatus(I2C_TypeDef* I2Cx, uint32_t I2C_FLAG);



 

void I2C_ClearFlag(I2C_TypeDef* I2Cx, uint32_t I2C_FLAG);
ITStatus I2C_GetITStatus(I2C_TypeDef* I2Cx, uint32_t I2C_IT);
void I2C_ClearITPendingBit(I2C_TypeDef* I2Cx, uint32_t I2C_IT);








  



  



  

 
#line 41 ".\\Source\\APP\\stm32f10x_conf.h"
#line 1 ".\\Source\\FWLib\\inc\\stm32f10x_iwdg.h"



















  

 







 
#line 32 ".\\Source\\FWLib\\inc\\stm32f10x_iwdg.h"



 



 



 



 



 



 







 



 

#line 83 ".\\Source\\FWLib\\inc\\stm32f10x_iwdg.h"


 



 







 



 



 



 



 

void IWDG_WriteAccessCmd(uint16_t IWDG_WriteAccess);
void IWDG_SetPrescaler(uint8_t IWDG_Prescaler);
void IWDG_SetReload(uint16_t Reload);
void IWDG_ReloadCounter(void);
void IWDG_Enable(void);
FlagStatus IWDG_GetFlagStatus(uint16_t IWDG_FLAG);








 



 



 

 
#line 42 ".\\Source\\APP\\stm32f10x_conf.h"
#line 1 ".\\Source\\FWLib\\inc\\stm32f10x_pwr.h"



















  

 







 
#line 32 ".\\Source\\FWLib\\inc\\stm32f10x_pwr.h"



 



  



  



  



  



  

#line 69 ".\\Source\\FWLib\\inc\\stm32f10x_pwr.h"


 



 







 



 




 


 



 










 



 



 



 



 

void PWR_DeInit(void);
void PWR_BackupAccessCmd(FunctionalState NewState);
void PWR_PVDCmd(FunctionalState NewState);
void PWR_PVDLevelConfig(uint32_t PWR_PVDLevel);
void PWR_WakeUpPinCmd(FunctionalState NewState);
void PWR_EnterSTOPMode(uint32_t PWR_Regulator, uint8_t PWR_STOPEntry);
void PWR_EnterSTANDBYMode(void);
FlagStatus PWR_GetFlagStatus(uint32_t PWR_FLAG);
void PWR_ClearFlag(uint32_t PWR_FLAG);








 



 



 

 
#line 43 ".\\Source\\APP\\stm32f10x_conf.h"
#line 1 ".\\Source\\FWLib\\inc\\stm32f10x_rcc.h"



















  

 







 
#line 32 ".\\Source\\FWLib\\inc\\stm32f10x_rcc.h"



 



 



 

typedef struct
{
  uint32_t SYSCLK_Frequency;   
  uint32_t HCLK_Frequency;     
  uint32_t PCLK1_Frequency;    
  uint32_t PCLK2_Frequency;    
  uint32_t ADCCLK_Frequency;   
}RCC_ClocksTypeDef;



 



 



 









  



 



#line 93 ".\\Source\\FWLib\\inc\\stm32f10x_rcc.h"



  



 
#line 125 ".\\Source\\FWLib\\inc\\stm32f10x_rcc.h"

#line 140 ".\\Source\\FWLib\\inc\\stm32f10x_rcc.h"


 



 
#line 174 ".\\Source\\FWLib\\inc\\stm32f10x_rcc.h"


 




 
#line 195 ".\\Source\\FWLib\\inc\\stm32f10x_rcc.h"


 

#line 282 ".\\Source\\FWLib\\inc\\stm32f10x_rcc.h"




 

#line 294 ".\\Source\\FWLib\\inc\\stm32f10x_rcc.h"


 



 

#line 316 ".\\Source\\FWLib\\inc\\stm32f10x_rcc.h"


  



 

#line 332 ".\\Source\\FWLib\\inc\\stm32f10x_rcc.h"


 



 

#line 346 ".\\Source\\FWLib\\inc\\stm32f10x_rcc.h"

#line 363 ".\\Source\\FWLib\\inc\\stm32f10x_rcc.h"




 




 








 
#line 395 ".\\Source\\FWLib\\inc\\stm32f10x_rcc.h"


#line 422 ".\\Source\\FWLib\\inc\\stm32f10x_rcc.h"
  



 

#line 434 ".\\Source\\FWLib\\inc\\stm32f10x_rcc.h"


 



 








 



 

#line 461 ".\\Source\\FWLib\\inc\\stm32f10x_rcc.h"


 



 







#line 488 ".\\Source\\FWLib\\inc\\stm32f10x_rcc.h"


 



 

#line 517 ".\\Source\\FWLib\\inc\\stm32f10x_rcc.h"




  



 

#line 552 ".\\Source\\FWLib\\inc\\stm32f10x_rcc.h"
 




 



 







#line 585 ".\\Source\\FWLib\\inc\\stm32f10x_rcc.h"



 



 

#line 605 ".\\Source\\FWLib\\inc\\stm32f10x_rcc.h"

#line 624 ".\\Source\\FWLib\\inc\\stm32f10x_rcc.h"




 



 



 



 



 

void RCC_DeInit(void);
void RCC_HSEConfig(uint32_t RCC_HSE);
ErrorStatus RCC_WaitForHSEStartUp(void);
void RCC_AdjustHSICalibrationValue(uint8_t HSICalibrationValue);
void RCC_HSICmd(FunctionalState NewState);
void RCC_PLLConfig(uint32_t RCC_PLLSource, uint32_t RCC_PLLMul);
void RCC_PLLCmd(FunctionalState NewState);





#line 665 ".\\Source\\FWLib\\inc\\stm32f10x_rcc.h"

void RCC_SYSCLKConfig(uint32_t RCC_SYSCLKSource);
uint8_t RCC_GetSYSCLKSource(void);
void RCC_HCLKConfig(uint32_t RCC_SYSCLK);
void RCC_PCLK1Config(uint32_t RCC_HCLK);
void RCC_PCLK2Config(uint32_t RCC_HCLK);
void RCC_ITConfig(uint8_t RCC_IT, FunctionalState NewState);


 void RCC_USBCLKConfig(uint32_t RCC_USBCLKSource);




void RCC_ADCCLKConfig(uint32_t RCC_PCLK2);






void RCC_LSEConfig(uint8_t RCC_LSE);
void RCC_LSICmd(FunctionalState NewState);
void RCC_RTCCLKConfig(uint32_t RCC_RTCCLKSource);
void RCC_RTCCLKCmd(FunctionalState NewState);
void RCC_GetClocksFreq(RCC_ClocksTypeDef* RCC_Clocks);
void RCC_AHBPeriphClockCmd(uint32_t RCC_AHBPeriph, FunctionalState NewState);
void RCC_APB2PeriphClockCmd(uint32_t RCC_APB2Periph, FunctionalState NewState);
void RCC_APB1PeriphClockCmd(uint32_t RCC_APB1Periph, FunctionalState NewState);





void RCC_APB2PeriphResetCmd(uint32_t RCC_APB2Periph, FunctionalState NewState);
void RCC_APB1PeriphResetCmd(uint32_t RCC_APB1Periph, FunctionalState NewState);
void RCC_BackupResetCmd(FunctionalState NewState);
void RCC_ClockSecuritySystemCmd(FunctionalState NewState);
void RCC_MCOConfig(uint8_t RCC_MCO);
FlagStatus RCC_GetFlagStatus(uint8_t RCC_FLAG);
void RCC_ClearFlag(void);
ITStatus RCC_GetITStatus(uint8_t RCC_IT);
void RCC_ClearITPendingBit(uint8_t RCC_IT);








 



 



  

 
#line 44 ".\\Source\\APP\\stm32f10x_conf.h"
#line 1 ".\\Source\\FWLib\\inc\\stm32f10x_rtc.h"



















  

 







 
#line 32 ".\\Source\\FWLib\\inc\\stm32f10x_rtc.h"



 



  



  



  



 



 

#line 63 ".\\Source\\FWLib\\inc\\stm32f10x_rtc.h"


  



 

#line 81 ".\\Source\\FWLib\\inc\\stm32f10x_rtc.h"



 



 



 



 



 

void RTC_ITConfig(uint16_t RTC_IT, FunctionalState NewState);
void RTC_EnterConfigMode(void);
void RTC_ExitConfigMode(void);
uint32_t  RTC_GetCounter(void);
void RTC_SetCounter(uint32_t CounterValue);
void RTC_SetPrescaler(uint32_t PrescalerValue);
void RTC_SetAlarm(uint32_t AlarmValue);
uint32_t  RTC_GetDivider(void);
void RTC_WaitForLastTask(void);
void RTC_WaitForSynchro(void);
FlagStatus RTC_GetFlagStatus(uint16_t RTC_FLAG);
void RTC_ClearFlag(uint16_t RTC_FLAG);
ITStatus RTC_GetITStatus(uint16_t RTC_IT);
void RTC_ClearITPendingBit(uint16_t RTC_IT);








 



 



 

 
#line 45 ".\\Source\\APP\\stm32f10x_conf.h"
#line 1 ".\\Source\\FWLib\\inc\\stm32f10x_sdio.h"



















  

 







 
#line 32 ".\\Source\\FWLib\\inc\\stm32f10x_sdio.h"



 



 



 

typedef struct
{
  uint32_t SDIO_ClockEdge;            
 

  uint32_t SDIO_ClockBypass;          

 

  uint32_t SDIO_ClockPowerSave;       

 

  uint32_t SDIO_BusWide;              
 

  uint32_t SDIO_HardwareFlowControl;  
 

  uint8_t SDIO_ClockDiv;              
 
                                           
} SDIO_InitTypeDef;

typedef struct
{
  uint32_t SDIO_Argument;  


 

  uint32_t SDIO_CmdIndex;   

  uint32_t SDIO_Response;  
 

  uint32_t SDIO_Wait;      
 

  uint32_t SDIO_CPSM;      

 
} SDIO_CmdInitTypeDef;

typedef struct
{
  uint32_t SDIO_DataTimeOut;     

  uint32_t SDIO_DataLength;      
 
  uint32_t SDIO_DataBlockSize;  
 
 
  uint32_t SDIO_TransferDir;    

 
 
  uint32_t SDIO_TransferMode;   
 
 
  uint32_t SDIO_DPSM;           

 
} SDIO_DataInitTypeDef;



  



 



 







 



 







  



 







 



 









 



 







 



 






  




 

#line 221 ".\\Source\\FWLib\\inc\\stm32f10x_sdio.h"


  



 




 



 

#line 244 ".\\Source\\FWLib\\inc\\stm32f10x_sdio.h"


 



 








 



 






  



 

#line 282 ".\\Source\\FWLib\\inc\\stm32f10x_sdio.h"


 



 




 



 

#line 329 ".\\Source\\FWLib\\inc\\stm32f10x_sdio.h"


 



 







 



 







 



 






 



 

#line 420 ".\\Source\\FWLib\\inc\\stm32f10x_sdio.h"



#line 447 ".\\Source\\FWLib\\inc\\stm32f10x_sdio.h"





 



 







 



 



 



 



 

void SDIO_DeInit(void);
void SDIO_Init(SDIO_InitTypeDef* SDIO_InitStruct);
void SDIO_StructInit(SDIO_InitTypeDef* SDIO_InitStruct);
void SDIO_ClockCmd(FunctionalState NewState);
void SDIO_SetPowerState(uint32_t SDIO_PowerState);
uint32_t SDIO_GetPowerState(void);
void SDIO_ITConfig(uint32_t SDIO_IT, FunctionalState NewState);
void SDIO_DMACmd(FunctionalState NewState);
void SDIO_SendCommand(SDIO_CmdInitTypeDef *SDIO_CmdInitStruct);
void SDIO_CmdStructInit(SDIO_CmdInitTypeDef* SDIO_CmdInitStruct);
uint8_t SDIO_GetCommandResponse(void);
uint32_t SDIO_GetResponse(uint32_t SDIO_RESP);
void SDIO_DataConfig(SDIO_DataInitTypeDef* SDIO_DataInitStruct);
void SDIO_DataStructInit(SDIO_DataInitTypeDef* SDIO_DataInitStruct);
uint32_t SDIO_GetDataCounter(void);
uint32_t SDIO_ReadData(void);
void SDIO_WriteData(uint32_t Data);
uint32_t SDIO_GetFIFOCount(void);
void SDIO_StartSDIOReadWait(FunctionalState NewState);
void SDIO_StopSDIOReadWait(FunctionalState NewState);
void SDIO_SetSDIOReadWaitMode(uint32_t SDIO_ReadWaitMode);
void SDIO_SetSDIOOperation(FunctionalState NewState);
void SDIO_SendSDIOSuspendCmd(FunctionalState NewState);
void SDIO_CommandCompletionCmd(FunctionalState NewState);
void SDIO_CEATAITCmd(FunctionalState NewState);
void SDIO_SendCEATACmd(FunctionalState NewState);
FlagStatus SDIO_GetFlagStatus(uint32_t SDIO_FLAG);
void SDIO_ClearFlag(uint32_t SDIO_FLAG);
ITStatus SDIO_GetITStatus(uint32_t SDIO_IT);
void SDIO_ClearITPendingBit(uint32_t SDIO_IT);








 



 



 

 
#line 46 ".\\Source\\APP\\stm32f10x_conf.h"
#line 1 ".\\Source\\FWLib\\inc\\stm32f10x_spi.h"



















  

 







 
#line 32 ".\\Source\\FWLib\\inc\\stm32f10x_spi.h"



 



  



 



 

typedef struct
{
  uint16_t SPI_Direction;           
 

  uint16_t SPI_Mode;                
 

  uint16_t SPI_DataSize;            
 

  uint16_t SPI_CPOL;                
 

  uint16_t SPI_CPHA;                
 

  uint16_t SPI_NSS;                 

 
 
  uint16_t SPI_BaudRatePrescaler;   



 

  uint16_t SPI_FirstBit;            
 

  uint16_t SPI_CRCPolynomial;        
}SPI_InitTypeDef;



 

typedef struct
{

  uint16_t I2S_Mode;         
 

  uint16_t I2S_Standard;     
 

  uint16_t I2S_DataFormat;   
 

  uint16_t I2S_MCLKOutput;   
 

  uint32_t I2S_AudioFreq;    
 

  uint16_t I2S_CPOL;         
 
}I2S_InitTypeDef;



 



 










 
  
#line 135 ".\\Source\\FWLib\\inc\\stm32f10x_spi.h"


 



 







 



 







  



 







 



 







 



 







  



 

#line 219 ".\\Source\\FWLib\\inc\\stm32f10x_spi.h"


  



 







 



 

#line 247 ".\\Source\\FWLib\\inc\\stm32f10x_spi.h"


 



 

#line 265 ".\\Source\\FWLib\\inc\\stm32f10x_spi.h"


 



 

#line 281 ".\\Source\\FWLib\\inc\\stm32f10x_spi.h"


  



 







 



 

#line 311 ".\\Source\\FWLib\\inc\\stm32f10x_spi.h"






  



 







 



 






 



 







 



 






 



 







 



 

#line 395 ".\\Source\\FWLib\\inc\\stm32f10x_spi.h"


 



 

#line 416 ".\\Source\\FWLib\\inc\\stm32f10x_spi.h"


 



 




 



 



 



 



 

void SPI_I2S_DeInit(SPI_TypeDef* SPIx);
void SPI_Init(SPI_TypeDef* SPIx, SPI_InitTypeDef* SPI_InitStruct);
void I2S_Init(SPI_TypeDef* SPIx, I2S_InitTypeDef* I2S_InitStruct);
void SPI_StructInit(SPI_InitTypeDef* SPI_InitStruct);
void I2S_StructInit(I2S_InitTypeDef* I2S_InitStruct);
void SPI_Cmd(SPI_TypeDef* SPIx, FunctionalState NewState);
void I2S_Cmd(SPI_TypeDef* SPIx, FunctionalState NewState);
void SPI_I2S_ITConfig(SPI_TypeDef* SPIx, uint8_t SPI_I2S_IT, FunctionalState NewState);
void SPI_I2S_DMACmd(SPI_TypeDef* SPIx, uint16_t SPI_I2S_DMAReq, FunctionalState NewState);
void SPI_I2S_SendData(SPI_TypeDef* SPIx, uint16_t Data);
uint16_t SPI_I2S_ReceiveData(SPI_TypeDef* SPIx);
void SPI_NSSInternalSoftwareConfig(SPI_TypeDef* SPIx, uint16_t SPI_NSSInternalSoft);
void SPI_SSOutputCmd(SPI_TypeDef* SPIx, FunctionalState NewState);
void SPI_DataSizeConfig(SPI_TypeDef* SPIx, uint16_t SPI_DataSize);
void SPI_TransmitCRC(SPI_TypeDef* SPIx);
void SPI_CalculateCRC(SPI_TypeDef* SPIx, FunctionalState NewState);
uint16_t SPI_GetCRC(SPI_TypeDef* SPIx, uint8_t SPI_CRC);
uint16_t SPI_GetCRCPolynomial(SPI_TypeDef* SPIx);
void SPI_BiDirectionalLineConfig(SPI_TypeDef* SPIx, uint16_t SPI_Direction);
FlagStatus SPI_I2S_GetFlagStatus(SPI_TypeDef* SPIx, uint16_t SPI_I2S_FLAG);
void SPI_I2S_ClearFlag(SPI_TypeDef* SPIx, uint16_t SPI_I2S_FLAG);
ITStatus SPI_I2S_GetITStatus(SPI_TypeDef* SPIx, uint8_t SPI_I2S_IT);
void SPI_I2S_ClearITPendingBit(SPI_TypeDef* SPIx, uint8_t SPI_I2S_IT);








 



 



 

 
#line 47 ".\\Source\\APP\\stm32f10x_conf.h"
#line 1 ".\\Source\\FWLib\\inc\\stm32f10x_tim.h"



















  

 







 
#line 32 ".\\Source\\FWLib\\inc\\stm32f10x_tim.h"



 



  



  




 

typedef struct
{
  uint16_t TIM_Prescaler;         
 

  uint16_t TIM_CounterMode;       
 

  uint16_t TIM_Period;            

  

  uint16_t TIM_ClockDivision;     
 

  uint8_t TIM_RepetitionCounter;  






 
} TIM_TimeBaseInitTypeDef;       



 

typedef struct
{
  uint16_t TIM_OCMode;        
 

  uint16_t TIM_OutputState;   
 

  uint16_t TIM_OutputNState;  

 

  uint16_t TIM_Pulse;         
 

  uint16_t TIM_OCPolarity;    
 

  uint16_t TIM_OCNPolarity;   

 

  uint16_t TIM_OCIdleState;   

 

  uint16_t TIM_OCNIdleState;  

 
} TIM_OCInitTypeDef;



 

typedef struct
{

  uint16_t TIM_Channel;      
 

  uint16_t TIM_ICPolarity;   
 

  uint16_t TIM_ICSelection;  
 

  uint16_t TIM_ICPrescaler;  
 

  uint16_t TIM_ICFilter;     
 
} TIM_ICInitTypeDef;




 

typedef struct
{

  uint16_t TIM_OSSRState;        
 

  uint16_t TIM_OSSIState;        
 

  uint16_t TIM_LOCKLevel;        
  

  uint16_t TIM_DeadTime;         

 

  uint16_t TIM_Break;            
 

  uint16_t TIM_BreakPolarity;    
 

  uint16_t TIM_AutomaticOutput;  
 
} TIM_BDTRInitTypeDef;



 

#line 185 ".\\Source\\FWLib\\inc\\stm32f10x_tim.h"

 



 






 
#line 204 ".\\Source\\FWLib\\inc\\stm32f10x_tim.h"
									                                 
 
#line 215 ".\\Source\\FWLib\\inc\\stm32f10x_tim.h"

                                             
#line 224 ".\\Source\\FWLib\\inc\\stm32f10x_tim.h"

 
#line 235 ".\\Source\\FWLib\\inc\\stm32f10x_tim.h"

 
#line 248 ".\\Source\\FWLib\\inc\\stm32f10x_tim.h"

                                         
#line 265 ".\\Source\\FWLib\\inc\\stm32f10x_tim.h"

 
#line 278 ".\\Source\\FWLib\\inc\\stm32f10x_tim.h"
                                                                                                                                                                                                                          


  



 

#line 307 ".\\Source\\FWLib\\inc\\stm32f10x_tim.h"


 



 







  



 

#line 340 ".\\Source\\FWLib\\inc\\stm32f10x_tim.h"


  



 

#line 354 ".\\Source\\FWLib\\inc\\stm32f10x_tim.h"


 



 

#line 372 ".\\Source\\FWLib\\inc\\stm32f10x_tim.h"


  



 







 



 
  






 



 







  



 







  



 







  



 







  



 







  



 







  



 







  



 

#line 496 ".\\Source\\FWLib\\inc\\stm32f10x_tim.h"


  



 







 



 







  



 







  



 







  



 

#line 560 ".\\Source\\FWLib\\inc\\stm32f10x_tim.h"


  



 

#line 576 ".\\Source\\FWLib\\inc\\stm32f10x_tim.h"


  



 

#line 592 ".\\Source\\FWLib\\inc\\stm32f10x_tim.h"


  



 

#line 609 ".\\Source\\FWLib\\inc\\stm32f10x_tim.h"

#line 618 ".\\Source\\FWLib\\inc\\stm32f10x_tim.h"


  



 

#line 664 ".\\Source\\FWLib\\inc\\stm32f10x_tim.h"


  



 

#line 708 ".\\Source\\FWLib\\inc\\stm32f10x_tim.h"


  



 

#line 724 ".\\Source\\FWLib\\inc\\stm32f10x_tim.h"



  



 

#line 741 ".\\Source\\FWLib\\inc\\stm32f10x_tim.h"


  



 

#line 769 ".\\Source\\FWLib\\inc\\stm32f10x_tim.h"


  



 

#line 783 ".\\Source\\FWLib\\inc\\stm32f10x_tim.h"


  



  






 



 







  



 







  



 

#line 832 ".\\Source\\FWLib\\inc\\stm32f10x_tim.h"


  




 

#line 850 ".\\Source\\FWLib\\inc\\stm32f10x_tim.h"



  



 

#line 865 ".\\Source\\FWLib\\inc\\stm32f10x_tim.h"


  



 







  



 





                                     


  



 







  



 

#line 926 ".\\Source\\FWLib\\inc\\stm32f10x_tim.h"


  



 

#line 942 ".\\Source\\FWLib\\inc\\stm32f10x_tim.h"


  



 







  



 

#line 986 ".\\Source\\FWLib\\inc\\stm32f10x_tim.h"
                               
                               



  



 




  



 




  



 



 



  



 

void TIM_DeInit(TIM_TypeDef* TIMx);
void TIM_TimeBaseInit(TIM_TypeDef* TIMx, TIM_TimeBaseInitTypeDef* TIM_TimeBaseInitStruct);
void TIM_OC1Init(TIM_TypeDef* TIMx, TIM_OCInitTypeDef* TIM_OCInitStruct);
void TIM_OC2Init(TIM_TypeDef* TIMx, TIM_OCInitTypeDef* TIM_OCInitStruct);
void TIM_OC3Init(TIM_TypeDef* TIMx, TIM_OCInitTypeDef* TIM_OCInitStruct);
void TIM_OC4Init(TIM_TypeDef* TIMx, TIM_OCInitTypeDef* TIM_OCInitStruct);
void TIM_ICInit(TIM_TypeDef* TIMx, TIM_ICInitTypeDef* TIM_ICInitStruct);
void TIM_PWMIConfig(TIM_TypeDef* TIMx, TIM_ICInitTypeDef* TIM_ICInitStruct);
void TIM_BDTRConfig(TIM_TypeDef* TIMx, TIM_BDTRInitTypeDef *TIM_BDTRInitStruct);
void TIM_TimeBaseStructInit(TIM_TimeBaseInitTypeDef* TIM_TimeBaseInitStruct);
void TIM_OCStructInit(TIM_OCInitTypeDef* TIM_OCInitStruct);
void TIM_ICStructInit(TIM_ICInitTypeDef* TIM_ICInitStruct);
void TIM_BDTRStructInit(TIM_BDTRInitTypeDef* TIM_BDTRInitStruct);
void TIM_Cmd(TIM_TypeDef* TIMx, FunctionalState NewState);
void TIM_CtrlPWMOutputs(TIM_TypeDef* TIMx, FunctionalState NewState);
void TIM_ITConfig(TIM_TypeDef* TIMx, uint16_t TIM_IT, FunctionalState NewState);
void TIM_GenerateEvent(TIM_TypeDef* TIMx, uint16_t TIM_EventSource);
void TIM_DMAConfig(TIM_TypeDef* TIMx, uint16_t TIM_DMABase, uint16_t TIM_DMABurstLength);
void TIM_DMACmd(TIM_TypeDef* TIMx, uint16_t TIM_DMASource, FunctionalState NewState);
void TIM_InternalClockConfig(TIM_TypeDef* TIMx);
void TIM_ITRxExternalClockConfig(TIM_TypeDef* TIMx, uint16_t TIM_InputTriggerSource);
void TIM_TIxExternalClockConfig(TIM_TypeDef* TIMx, uint16_t TIM_TIxExternalCLKSource,
                                uint16_t TIM_ICPolarity, uint16_t ICFilter);
void TIM_ETRClockMode1Config(TIM_TypeDef* TIMx, uint16_t TIM_ExtTRGPrescaler, uint16_t TIM_ExtTRGPolarity,
                             uint16_t ExtTRGFilter);
void TIM_ETRClockMode2Config(TIM_TypeDef* TIMx, uint16_t TIM_ExtTRGPrescaler, 
                             uint16_t TIM_ExtTRGPolarity, uint16_t ExtTRGFilter);
void TIM_ETRConfig(TIM_TypeDef* TIMx, uint16_t TIM_ExtTRGPrescaler, uint16_t TIM_ExtTRGPolarity,
                   uint16_t ExtTRGFilter);
void TIM_PrescalerConfig(TIM_TypeDef* TIMx, uint16_t Prescaler, uint16_t TIM_PSCReloadMode);
void TIM_CounterModeConfig(TIM_TypeDef* TIMx, uint16_t TIM_CounterMode);
void TIM_SelectInputTrigger(TIM_TypeDef* TIMx, uint16_t TIM_InputTriggerSource);
void TIM_EncoderInterfaceConfig(TIM_TypeDef* TIMx, uint16_t TIM_EncoderMode,
                                uint16_t TIM_IC1Polarity, uint16_t TIM_IC2Polarity);
void TIM_ForcedOC1Config(TIM_TypeDef* TIMx, uint16_t TIM_ForcedAction);
void TIM_ForcedOC2Config(TIM_TypeDef* TIMx, uint16_t TIM_ForcedAction);
void TIM_ForcedOC3Config(TIM_TypeDef* TIMx, uint16_t TIM_ForcedAction);
void TIM_ForcedOC4Config(TIM_TypeDef* TIMx, uint16_t TIM_ForcedAction);
void TIM_ARRPreloadConfig(TIM_TypeDef* TIMx, FunctionalState NewState);
void TIM_SelectCOM(TIM_TypeDef* TIMx, FunctionalState NewState);
void TIM_SelectCCDMA(TIM_TypeDef* TIMx, FunctionalState NewState);
void TIM_CCPreloadControl(TIM_TypeDef* TIMx, FunctionalState NewState);
void TIM_OC1PreloadConfig(TIM_TypeDef* TIMx, uint16_t TIM_OCPreload);
void TIM_OC2PreloadConfig(TIM_TypeDef* TIMx, uint16_t TIM_OCPreload);
void TIM_OC3PreloadConfig(TIM_TypeDef* TIMx, uint16_t TIM_OCPreload);
void TIM_OC4PreloadConfig(TIM_TypeDef* TIMx, uint16_t TIM_OCPreload);
void TIM_OC1FastConfig(TIM_TypeDef* TIMx, uint16_t TIM_OCFast);
void TIM_OC2FastConfig(TIM_TypeDef* TIMx, uint16_t TIM_OCFast);
void TIM_OC3FastConfig(TIM_TypeDef* TIMx, uint16_t TIM_OCFast);
void TIM_OC4FastConfig(TIM_TypeDef* TIMx, uint16_t TIM_OCFast);
void TIM_ClearOC1Ref(TIM_TypeDef* TIMx, uint16_t TIM_OCClear);
void TIM_ClearOC2Ref(TIM_TypeDef* TIMx, uint16_t TIM_OCClear);
void TIM_ClearOC3Ref(TIM_TypeDef* TIMx, uint16_t TIM_OCClear);
void TIM_ClearOC4Ref(TIM_TypeDef* TIMx, uint16_t TIM_OCClear);
void TIM_OC1PolarityConfig(TIM_TypeDef* TIMx, uint16_t TIM_OCPolarity);
void TIM_OC1NPolarityConfig(TIM_TypeDef* TIMx, uint16_t TIM_OCNPolarity);
void TIM_OC2PolarityConfig(TIM_TypeDef* TIMx, uint16_t TIM_OCPolarity);
void TIM_OC2NPolarityConfig(TIM_TypeDef* TIMx, uint16_t TIM_OCNPolarity);
void TIM_OC3PolarityConfig(TIM_TypeDef* TIMx, uint16_t TIM_OCPolarity);
void TIM_OC3NPolarityConfig(TIM_TypeDef* TIMx, uint16_t TIM_OCNPolarity);
void TIM_OC4PolarityConfig(TIM_TypeDef* TIMx, uint16_t TIM_OCPolarity);
void TIM_CCxCmd(TIM_TypeDef* TIMx, uint16_t TIM_Channel, uint16_t TIM_CCx);
void TIM_CCxNCmd(TIM_TypeDef* TIMx, uint16_t TIM_Channel, uint16_t TIM_CCxN);
void TIM_SelectOCxM(TIM_TypeDef* TIMx, uint16_t TIM_Channel, uint16_t TIM_OCMode);
void TIM_UpdateDisableConfig(TIM_TypeDef* TIMx, FunctionalState NewState);
void TIM_UpdateRequestConfig(TIM_TypeDef* TIMx, uint16_t TIM_UpdateSource);
void TIM_SelectHallSensor(TIM_TypeDef* TIMx, FunctionalState NewState);
void TIM_SelectOnePulseMode(TIM_TypeDef* TIMx, uint16_t TIM_OPMode);
void TIM_SelectOutputTrigger(TIM_TypeDef* TIMx, uint16_t TIM_TRGOSource);
void TIM_SelectSlaveMode(TIM_TypeDef* TIMx, uint16_t TIM_SlaveMode);
void TIM_SelectMasterSlaveMode(TIM_TypeDef* TIMx, uint16_t TIM_MasterSlaveMode);
void TIM_SetCounter(TIM_TypeDef* TIMx, uint16_t Counter);
void TIM_SetAutoreload(TIM_TypeDef* TIMx, uint16_t Autoreload);
void TIM_SetCompare1(TIM_TypeDef* TIMx, uint16_t Compare1);
void TIM_SetCompare2(TIM_TypeDef* TIMx, uint16_t Compare2);
void TIM_SetCompare3(TIM_TypeDef* TIMx, uint16_t Compare3);
void TIM_SetCompare4(TIM_TypeDef* TIMx, uint16_t Compare4);
void TIM_SetIC1Prescaler(TIM_TypeDef* TIMx, uint16_t TIM_ICPSC);
void TIM_SetIC2Prescaler(TIM_TypeDef* TIMx, uint16_t TIM_ICPSC);
void TIM_SetIC3Prescaler(TIM_TypeDef* TIMx, uint16_t TIM_ICPSC);
void TIM_SetIC4Prescaler(TIM_TypeDef* TIMx, uint16_t TIM_ICPSC);
void TIM_SetClockDivision(TIM_TypeDef* TIMx, uint16_t TIM_CKD);
uint16_t TIM_GetCapture1(TIM_TypeDef* TIMx);
uint16_t TIM_GetCapture2(TIM_TypeDef* TIMx);
uint16_t TIM_GetCapture3(TIM_TypeDef* TIMx);
uint16_t TIM_GetCapture4(TIM_TypeDef* TIMx);
uint16_t TIM_GetCounter(TIM_TypeDef* TIMx);
uint16_t TIM_GetPrescaler(TIM_TypeDef* TIMx);
FlagStatus TIM_GetFlagStatus(TIM_TypeDef* TIMx, uint16_t TIM_FLAG);
void TIM_ClearFlag(TIM_TypeDef* TIMx, uint16_t TIM_FLAG);
ITStatus TIM_GetITStatus(TIM_TypeDef* TIMx, uint16_t TIM_IT);
void TIM_ClearITPendingBit(TIM_TypeDef* TIMx, uint16_t TIM_IT);








  



  



 

 
#line 48 ".\\Source\\APP\\stm32f10x_conf.h"
#line 1 ".\\Source\\FWLib\\inc\\stm32f10x_usart.h"



















  

 







 
#line 32 ".\\Source\\FWLib\\inc\\stm32f10x_usart.h"



 



  



  



  
  
typedef struct
{
  uint32_t USART_BaudRate;            


 

  uint16_t USART_WordLength;          
 

  uint16_t USART_StopBits;            
 

  uint16_t USART_Parity;              




 
 
  uint16_t USART_Mode;                
 

  uint16_t USART_HardwareFlowControl; 

 
} USART_InitTypeDef;



  
  
typedef struct
{

  uint16_t USART_Clock;   
 

  uint16_t USART_CPOL;    
 

  uint16_t USART_CPHA;    
 

  uint16_t USART_LastBit; 

 
} USART_ClockInitTypeDef;



  



  
  
















  
  


                                    




  



  
  
#line 145 ".\\Source\\FWLib\\inc\\stm32f10x_usart.h"


  



  
  
#line 159 ".\\Source\\FWLib\\inc\\stm32f10x_usart.h"


  



  
  





  



  
#line 186 ".\\Source\\FWLib\\inc\\stm32f10x_usart.h"


  



  






  



 
  






  



 







 



 







  



 
  
#line 263 ".\\Source\\FWLib\\inc\\stm32f10x_usart.h"


 



 







  



 







 



 
  







 



 







  



 

#line 335 ".\\Source\\FWLib\\inc\\stm32f10x_usart.h"
                              
#line 343 ".\\Source\\FWLib\\inc\\stm32f10x_usart.h"



  



  



  



  



 

void USART_DeInit(USART_TypeDef* USARTx);
void USART_Init(USART_TypeDef* USARTx, USART_InitTypeDef* USART_InitStruct);
void USART_StructInit(USART_InitTypeDef* USART_InitStruct);
void USART_ClockInit(USART_TypeDef* USARTx, USART_ClockInitTypeDef* USART_ClockInitStruct);
void USART_ClockStructInit(USART_ClockInitTypeDef* USART_ClockInitStruct);
void USART_Cmd(USART_TypeDef* USARTx, FunctionalState NewState);
void USART_ITConfig(USART_TypeDef* USARTx, uint16_t USART_IT, FunctionalState NewState);
void USART_DMACmd(USART_TypeDef* USARTx, uint16_t USART_DMAReq, FunctionalState NewState);
void USART_SetAddress(USART_TypeDef* USARTx, uint8_t USART_Address);
void USART_WakeUpConfig(USART_TypeDef* USARTx, uint16_t USART_WakeUp);
void USART_ReceiverWakeUpCmd(USART_TypeDef* USARTx, FunctionalState NewState);
void USART_LINBreakDetectLengthConfig(USART_TypeDef* USARTx, uint16_t USART_LINBreakDetectLength);
void USART_LINCmd(USART_TypeDef* USARTx, FunctionalState NewState);
void USART_SendData(USART_TypeDef* USARTx, uint16_t Data);
uint16_t USART_ReceiveData(USART_TypeDef* USARTx);
void USART_SendBreak(USART_TypeDef* USARTx);
void USART_SetGuardTime(USART_TypeDef* USARTx, uint8_t USART_GuardTime);
void USART_SetPrescaler(USART_TypeDef* USARTx, uint8_t USART_Prescaler);
void USART_SmartCardCmd(USART_TypeDef* USARTx, FunctionalState NewState);
void USART_SmartCardNACKCmd(USART_TypeDef* USARTx, FunctionalState NewState);
void USART_HalfDuplexCmd(USART_TypeDef* USARTx, FunctionalState NewState);
void USART_OverSampling8Cmd(USART_TypeDef* USARTx, FunctionalState NewState);
void USART_OneBitMethodCmd(USART_TypeDef* USARTx, FunctionalState NewState);
void USART_IrDAConfig(USART_TypeDef* USARTx, uint16_t USART_IrDAMode);
void USART_IrDACmd(USART_TypeDef* USARTx, FunctionalState NewState);
FlagStatus USART_GetFlagStatus(USART_TypeDef* USARTx, uint16_t USART_FLAG);
void USART_ClearFlag(USART_TypeDef* USARTx, uint16_t USART_FLAG);
ITStatus USART_GetITStatus(USART_TypeDef* USARTx, uint16_t USART_IT);
void USART_ClearITPendingBit(USART_TypeDef* USARTx, uint16_t USART_IT);








  



  



  

 
#line 49 ".\\Source\\APP\\stm32f10x_conf.h"
#line 1 ".\\Source\\FWLib\\inc\\stm32f10x_wwdg.h"



















  

 







 
#line 32 ".\\Source\\FWLib\\inc\\stm32f10x_wwdg.h"



 



  



  
  


  



  
  


  
  
#line 67 ".\\Source\\FWLib\\inc\\stm32f10x_wwdg.h"



  



  



  


  



  
  
void WWDG_DeInit(void);
void WWDG_SetPrescaler(uint32_t WWDG_Prescaler);
void WWDG_SetWindowValue(uint8_t WindowValue);
void WWDG_EnableIT(void);
void WWDG_SetCounter(uint8_t Counter);
void WWDG_Enable(uint8_t Counter);
FlagStatus WWDG_GetFlagStatus(void);
void WWDG_ClearFlag(void);









  



  



  

 
#line 50 ".\\Source\\APP\\stm32f10x_conf.h"
#line 1 ".\\Source\\FWLib\\inc\\misc.h"



















  

 







 
#line 32 ".\\Source\\FWLib\\inc\\misc.h"



 



 



 



 

typedef struct
{
  uint8_t NVIC_IRQChannel;                    


 

  uint8_t NVIC_IRQChannelPreemptionPriority;  

 

  uint8_t NVIC_IRQChannelSubPriority;         

 

  FunctionalState NVIC_IRQChannelCmd;         

    
} NVIC_InitTypeDef;
 


 



 
























 



 



 



 







 



 

#line 132 ".\\Source\\FWLib\\inc\\misc.h"


 



 

#line 150 ".\\Source\\FWLib\\inc\\misc.h"















 



 







 



 



 



 



 

void NVIC_PriorityGroupConfig(uint32_t NVIC_PriorityGroup);
void NVIC_Init(NVIC_InitTypeDef* NVIC_InitStruct);
void NVIC_SetVectorTable(uint32_t NVIC_VectTab, uint32_t Offset);
void NVIC_SystemLPConfig(uint8_t LowPowerMode, FunctionalState NewState);
void SysTick_CLKSourceConfig(uint32_t SysTick_CLKSource);









 



 



 

 
#line 51 ".\\Source\\APP\\stm32f10x_conf.h"

 
 

 
 

 
#line 73 ".\\Source\\APP\\stm32f10x_conf.h"



 
#line 8281 ".\\Source\\FWLib\\cm3\\stm32f10x.h"




 

















 









 

  

 

 
#line 4 ".\\Source\\APP\\touchc.h"





#line 16 ".\\Source\\APP\\touchc.h"

#line 24 ".\\Source\\APP\\touchc.h"
 























#line 5 ".\\Source\\uCGUI\\LCDDriver\\Touch\\touch.h"
#line 1 ".\\Source\\BSP\\bsp.h"











 














 








 
#line 38 ".\\Source\\BSP\\bsp.h"

























 












 








 






 






 

void BSP_Init(void);
void BSP_IntDisAll(void);
unsigned int  OS_CPU_SysTickClkFreq (void);
u16 TPReadX(void);
u16 TPReadY(void);
FLASH_Status flash_pro(uint32_t start_address, uint16_t* data,unsigned int lenth);
void  MMA845X_TIM6_Init(void);
void MMA845X_TIM6_interrupt_conf(FunctionalState status);


#line 6 ".\\Source\\uCGUI\\LCDDriver\\Touch\\touch.h"











 

 
    






  





 






typedef struct{

	uint16_t usAdcNowX;
	uint16_t usAdcNowY;

}TTOUCH_P;

 
typedef struct 
{
	u16 X0;
	u16 Y0;
	u16 X; 
	u16 Y;						   	    
	u8  Key_Sta;
	
	float xfac;
	float yfac;
	short xoff;
	short yoff;
}Pen_Holder;




extern Pen_Holder Pen_Point; 
extern TTOUCH_P g_tTP;

void Touch_Init(void);
void Pen_Int_Set(u8 en); 
void Touch_Configuration(void);
void ADS_Write_Byte(u8 num);
u16 ADS_Read_AD(u8 CMD);
u16 ADS_Read_XY(u8 xy);
u8 Read_TP_Once(void);
u8 Read_ADS2(u16 *x,u16 *y);
u8 Read_ADS(u16 *x,u16 *y);
void Drow_Touch_Point(u16 x,u16 y);
u8 Get_Adjdata(void);
void Refreshes_Screen(void);
void Convert_Pos(void);
void Draw_Big_Point(u16 x,u16 y);
void Touch_Adjust(void);


void get_calibrate_data(uint16_t* cal_data);
FLASH_Status  save_calibrate_to_flash(uint16_t* data);
unsigned int get_calibrate_state(void);


uint16_t TOUCH_DataFilter(uint8_t xy);
uint8_t TOUCH_ReadAdcXY(uint16_t *_usX, uint16_t *_usY);
void TOUCH_Scan(void);

#line 11 "Source\\uCGUI\\TouchCalibration\\TouchCalibration.h"




typedef struct{
	   int a;
	   int b;
	   int c;

}TFact;


static int _Log2Phys(int l, signed long l0, signed long l1, signed long p0, signed long p1);
static void _Calibrate(int Coord, int Log0, int Log1, int Phys0, int Phys1, int *p0, int *p1);
void _ExecCalibration(void);
int get_calibration(void);
int run_cal(void);

void myAD2XY( int *adx , int *ady );
void GUI_myTOUCH_Calibrate(int *Logx, int *Logy, int *xPhys, int *yPhys);
void Calibration(void);




#line 21 "Source\\uCGUI\\TouchCalibration\\TouchCalibration.c"








 
int admy;
int admx;
int admk[10];
TFact Factors[10][10];


static int _Log2Phys(int l, signed long l0, signed long l1, signed long p0, signed long p1) {
  return p0 + ((p1 - p0) * (l - l0)) / (l1 - l0);
}

static void _Calibrate(int Coord, int Log0, int Log1, int Phys0, int Phys1, int *p0, int *p1) {
  int l0 = 0;
  int l1 = (Coord == 0) ? (800) - 1 : (480) - 1;
  *p0 = _Log2Phys(l0, Log0, Log1, Phys0, Phys1);
  *p1 = _Log2Phys(l1, Log0, Log1, Phys0, Phys1);
}






 

void _ExecCalibration(void) {
  int x,y;
  uint16_t data[6];
  uint16_t get_data[6];
  int ax_Phys[2],ay_Phys[2];
 
  int ax[2] = { 15, (800) -1-15};

  int ay[2] = { (480)-1-15, 15};
  GUI_TOUCH_SetDefaultCalibration();
 
  GUI_SetBkColor(0x0000FF);  
  GUI_Clear();
  GUI_SetColor(0xFFFFFF);  GUI_FillCircle(ax[0], ay[0], 10);
  GUI_SetColor(0x0000FF);    GUI_FillCircle(ax[0], ay[0], 5);
  GUI_SetColor(0xFFFFFF);
  GUI_DispStringAt("Press here", ax[0]+20, ay[0]);
  do {








  x = TPReadX();
  y = TPReadY();
  if ((x>=3700)&&(y>=3400)&&(x<3800)&&(y<3600)) {


      ax_Phys[0] = GUI_TOUCH_GetxPhys();
      ay_Phys[0] = GUI_TOUCH_GetyPhys();
      break;
    }
    GUI_Delay (3000);
  } while (1);
 
  GUI_Clear();
  GUI_DispStringAt("OK", ax[0]+20, ay[0]);
  do {
    GUI_PID_STATE State;
    GUI_TOUCH_GetState(&State);
    if (State.Pressed == 0) {
      break;
    }
    GUI_Delay (100);
  } while (1);
 
  GUI_SetBkColor(0x0000FF);  
  GUI_Clear();
  GUI_SetColor(0xFFFFFF);  GUI_FillCircle(ax[1], ay[1], 10);
  GUI_SetColor(0x0000FF);    GUI_FillCircle(ax[1], ay[1], 5);
  GUI_SetColor(0xFFFFFF);
  GUI_SetTextAlign((1<<0));
  GUI_DispStringAt("Press here", ax[1]-20, ay[1]);
  do {


  x = TPReadX();
  y = TPReadY();
  if ((y>450)&&(y<620)&&(x>350)&&(x<450)) {








      ax_Phys[1] = GUI_TOUCH_GetxPhys();
      ay_Phys[1] = GUI_TOUCH_GetyPhys();
      break;
    }
    GUI_Delay (3000);
  } while (1);
  GUI_TOUCH_Calibrate(0, ax[0], ax[1], ax_Phys[0], ax_Phys[1]);
  GUI_TOUCH_Calibrate(1, ay[0], ay[1], ay_Phys[0], ay_Phys[1]);
  {  
    int x0, x1;
    int y0, y1;
    GUI_Clear();
    _Calibrate(0, ax[0], ax[1], ax_Phys[0], ax_Phys[1], &x0, &x1);
    _Calibrate(1, ay[0], ay[1], ay_Phys[0], ay_Phys[1], &y0, &y1);
    GUI_DispStringAt("x0: ", 0, 0); GUI_DispDec(x0, 4); GUI_DispNextLine();
    GUI_DispString  ("x1: ");       GUI_DispDec(x1, 4); GUI_DispNextLine();
    GUI_DispString  ("y0: ");       GUI_DispDec(y0, 4); GUI_DispNextLine();
    GUI_DispString  ("y1: ");       GUI_DispDec(y1, 4); GUI_DispNextLine();
    GUI_DispString  ("Please touch display to continue...");
    GUI_Delay(1000);

	data[0]=  0xE1E1;
	data[1]= ax_Phys[0];
	data[2]= ay_Phys[0];
	data[3]= ax_Phys[1];
	data[4]= ay_Phys[1];


	save_calibrate_to_flash(data);
	get_calibrate_data(get_data);

	GUI_DispStringAt("x0: ", 100, 0); GUI_DispDec(get_data[1], 4); GUI_DispNextLine();
    GUI_DispString  ("x1: ");       GUI_DispDec(get_data[2], 4); GUI_DispNextLine();
    GUI_DispString  ("y0: ");       GUI_DispDec(get_data[3], 4); GUI_DispNextLine();
    GUI_DispString  ("y1: ");       GUI_DispDec(get_data[4], 4); GUI_DispNextLine();
	GUI_DispString  ("state: ");       GUI_DispDec(get_data[0], 4); GUI_DispNextLine();


    do {
      GUI_PID_STATE State;
      GUI_TOUCH_GetState(&State);
      if (State.Pressed)
      break;
      GUI_Delay (10);
    } while (1);
  }
}



int run_cal(void)
{
  if(get_calibrate_state()== 0xE1E1)
  {
  	get_calibration();
  }else{

  	 _ExecCalibration();





  }
}

int get_calibration(void)
{
  uint16_t cal_data[5];
  int ax_Phys[2],ay_Phys[2];
  int ax[2] = { 15, (800) -1-15};
  int ay[2] = { (480)-1-15, 15};

  get_calibrate_data(cal_data);

  ax_Phys[0] = cal_data[1];
  ay_Phys[0] = cal_data[2];
  
  ax_Phys[1] = cal_data[3];
  ay_Phys[1] = cal_data[4];
  
  GUI_TOUCH_Calibrate(0, ax[0], ax[1], ax_Phys[0], ax_Phys[1]);
  GUI_TOUCH_Calibrate(1, ay[0], ay[1], ay_Phys[0], ay_Phys[1]);
}


#line 386 "Source\\uCGUI\\TouchCalibration\\TouchCalibration.c"







