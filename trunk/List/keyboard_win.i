#line 1 "Source\\gui_app\\KeyBoard_Win.c"








 

#line 1 "D:\\Keil_ARM\\ARM\\RV31\\INC\\stddef.h"
 






 

 
 
 





 




#line 33 "D:\\Keil_ARM\\ARM\\RV31\\INC\\stddef.h"

typedef signed int ptrdiff_t;


  
  typedef unsigned int size_t;








   



      typedef unsigned short wchar_t;  
#line 69 "D:\\Keil_ARM\\ARM\\RV31\\INC\\stddef.h"



    

   









#line 90 "D:\\Keil_ARM\\ARM\\RV31\\INC\\stddef.h"



 
#line 12 "Source\\gui_app\\KeyBoard_Win.c"
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



 
	 	 			 		    	 				 	  			   	 	 	 	 	 	  	  	      	   		 	 	 		  		  	 		 	  	  			     			       	   	 			  		    	 	     	 				  	 					 	 			   	  	  			 				 		 	 	 			     			 
#line 13 "Source\\gui_app\\KeyBoard_Win.c"
#line 1 ".\\Source\\uCGUI\\Widget\\DIALOG.h"




















 




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

















 
	 	 			 		    	 				 	  			   	 	 	 	 	 	  	  	      	   		 	 	 		  		  	 		 	  	  			     			       	   	 			  		    	 	     	 				  	 					 	 			   	  	  			 				 		 	 	 			     			 
#line 27 ".\\Source\\uCGUI\\Widget\\DIALOG.h"
#line 1 ".\\Source\\uCGUI\\Widget\\BUTTON.h"

















 




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




 









	 	 			 		    	 				 	  			   	 	 	 	 	 	  	  	      	   		 	 	 		  		  	 		 	  	  			     			       	   	 			  		    	 	     	 				  	 					 	 			   	  	  			 				 		 	 	 			     			 
#line 28 ".\\Source\\uCGUI\\Widget\\DIALOG.h"
#line 1 ".\\Source\\uCGUI\\Widget\\CHECKBOX.h"

















 




#line 24 ".\\Source\\uCGUI\\Widget\\CHECKBOX.h"
#line 25 ".\\Source\\uCGUI\\Widget\\CHECKBOX.h"












 




 






 
#line 56 ".\\Source\\uCGUI\\Widget\\CHECKBOX.h"







 
typedef signed short CHECKBOX_Handle;






 

CHECKBOX_Handle CHECKBOX_Create        (int x0, int y0, int xsize, int ysize, GUI_HWIN hParent, int Id, int Flags);
CHECKBOX_Handle CHECKBOX_CreateIndirect(const GUI_WIDGET_CREATE_INFO* pCreateInfo, GUI_HWIN hWinParent, int x0, int y0, WM_CALLBACK* cb);
CHECKBOX_Handle CHECKBOX_CreateEx      (int x0, int y0, int xsize, int ysize, GUI_HWIN hParent,
                                        int WinFlags, int ExFlags, int Id);







 
void CHECKBOX_Callback(WM_MESSAGE *pMsg);






 

int                          CHECKBOX_GetDefaultAlign     (void);
GUI_COLOR                    CHECKBOX_GetDefaultBkColor   (void);
const GUI_FONT  * CHECKBOX_GetDefaultFont      (void);
int                          CHECKBOX_GetDefaultSpacing   (void);
int                          CHECKBOX_GetDefaultTextAlign (void);
GUI_COLOR                    CHECKBOX_GetDefaultTextColor (void);
void                         CHECKBOX_SetDefaultAlign     (int Align);
void                         CHECKBOX_SetDefaultBkColor   (GUI_COLOR Color);
GUI_COLOR                    CHECKBOX_SetDefaultFocusColor(GUI_COLOR Color);
void                         CHECKBOX_SetDefaultFont      (const GUI_FONT  * pFont);
void                         CHECKBOX_SetDefaultImage     (const GUI_BITMAP * pBitmap, unsigned int Index);
void                         CHECKBOX_SetDefaultSpacing   (int Spacing);
void                         CHECKBOX_SetDefaultTextAlign (int Align);
void                         CHECKBOX_SetDefaultTextColor (GUI_COLOR Color);






 

int       CHECKBOX_GetState     (CHECKBOX_Handle hObj);
int       CHECKBOX_GetText      (CHECKBOX_Handle hObj, char * pBuffer, int MaxLen);
int       CHECKBOX_IsChecked    (CHECKBOX_Handle hObj);
void      CHECKBOX_SetBkColor   (CHECKBOX_Handle hObj, GUI_COLOR Color);
GUI_COLOR CHECKBOX_SetBoxBkColor(CHECKBOX_Handle hObj, GUI_COLOR Color, int Index);
GUI_COLOR CHECKBOX_SetFocusColor(CHECKBOX_Handle hObj, GUI_COLOR Color);
void      CHECKBOX_SetFont      (CHECKBOX_Handle hObj, const GUI_FONT  * pFont);
void      CHECKBOX_SetImage     (CHECKBOX_Handle hObj, const GUI_BITMAP * pBitmap, unsigned int Index);
void      CHECKBOX_SetNumStates (CHECKBOX_Handle hObj, unsigned NumStates);
void      CHECKBOX_SetSpacing   (CHECKBOX_Handle hObj, unsigned Spacing);
void      CHECKBOX_SetState     (CHECKBOX_Handle hObj, unsigned State);
void      CHECKBOX_SetText      (CHECKBOX_Handle hObj, const char * pText);
void      CHECKBOX_SetTextAlign (CHECKBOX_Handle hObj, int Align);
void      CHECKBOX_SetTextColor (CHECKBOX_Handle hObj, GUI_COLOR Color);






 













	 	 			 		    	 				 	  			   	 	 	 	 	 	  	  	      	   		 	 	 		  		  	 		 	  	  			     			       	   	 			  		    	 	     	 				  	 					 	 			   	  	  			 				 		 	 	 			     			 
#line 29 ".\\Source\\uCGUI\\Widget\\DIALOG.h"
#line 1 ".\\Source\\uCGUI\\Widget\\DROPDOWN.h"

















 




#line 24 ".\\Source\\uCGUI\\Widget\\DROPDOWN.h"
#line 25 ".\\Source\\uCGUI\\Widget\\DROPDOWN.h"







typedef signed short DROPDOWN_Handle;




 






 












 












 

DROPDOWN_Handle DROPDOWN_Create        (GUI_HWIN hWinParent, int x0, int y0, int xsize, int ysize, int Flags);
DROPDOWN_Handle DROPDOWN_CreateIndirect(const GUI_WIDGET_CREATE_INFO* pCreateInfo, GUI_HWIN hWinParent, int x0, int y0, WM_CALLBACK* cb);
DROPDOWN_Handle DROPDOWN_CreateEx      (int x0, int y0, int xsize, int ysize, GUI_HWIN hParent,
                                        int WinFlags, int ExFlags, int Id);







 
void DROPDOWN_Callback(WM_MESSAGE * pMsg);






 

void     DROPDOWN_AddKey          (DROPDOWN_Handle hObj, int Key);
void     DROPDOWN_AddString       (DROPDOWN_Handle hObj, const char* s);
void     DROPDOWN_Collapse        (DROPDOWN_Handle hObj);
void     DROPDOWN_DecSel          (DROPDOWN_Handle hObj);
void     DROPDOWN_DeleteItem      (DROPDOWN_Handle hObj, unsigned int Index);
void     DROPDOWN_Expand          (DROPDOWN_Handle hObj);
unsigned DROPDOWN_GetItemSpacing  (DROPDOWN_Handle hObj);
int      DROPDOWN_GetNumItems     (DROPDOWN_Handle hObj);
int      DROPDOWN_GetSel          (DROPDOWN_Handle hObj);
void     DROPDOWN_IncSel          (DROPDOWN_Handle hObj);
void     DROPDOWN_InsertString    (DROPDOWN_Handle hObj, const char* s, unsigned int Index);
void     DROPDOWN_SetAutoScroll   (DROPDOWN_Handle hObj, int OnOff);
void     DROPDOWN_SetBkColor      (DROPDOWN_Handle hObj, unsigned int Index, GUI_COLOR color);
void     DROPDOWN_SetColor        (DROPDOWN_Handle hObj, unsigned int Index, GUI_COLOR Color);
void     DROPDOWN_SetFont         (DROPDOWN_Handle hObj, const GUI_FONT  * pfont);
void     DROPDOWN_SetItemSpacing  (DROPDOWN_Handle hObj, unsigned Value);
void     DROPDOWN_SetSel          (DROPDOWN_Handle hObj, int Sel);
void     DROPDOWN_SetScrollbarColor(DROPDOWN_Handle hObj, unsigned Index, GUI_COLOR Color);
void     DROPDOWN_SetScrollbarWidth(DROPDOWN_Handle hObj, unsigned Width);
void     DROPDOWN_SetTextAlign    (DROPDOWN_Handle hObj, int Align);
void     DROPDOWN_SetTextColor    (DROPDOWN_Handle hObj, unsigned int index, GUI_COLOR color);
void     DROPDOWN_SetTextHeight   (DROPDOWN_Handle hObj, unsigned TextHeight);







 
const GUI_FONT  * DROPDOWN_GetDefaultFont          (void);
void                         DROPDOWN_SetDefaultFont          (const GUI_FONT  * pFont);
GUI_COLOR                    DROPDOWN_SetDefaultColor         (int Index, GUI_COLOR Color);
GUI_COLOR                    DROPDOWN_SetDefaultScrollbarColor(int Index, GUI_COLOR Color);







	 	 			 		    	 				 	  			   	 	 	 	 	 	  	  	      	   		 	 	 		  		  	 		 	  	  			     			       	   	 			  		    	 	     	 				  	 					 	 			   	  	  			 				 		 	 	 			     			 
#line 30 ".\\Source\\uCGUI\\Widget\\DIALOG.h"
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






 

 



 



 









	 	 			 		    	 				 	  			   	 	 	 	 	 	  	  	      	   		 	 	 		  		  	 		 	  	  			     			       	   	 			  		    	 	     	 				  	 					 	 			   	  	  			 				 		 	 	 			     			 
#line 31 ".\\Source\\uCGUI\\Widget\\DIALOG.h"
#line 1 ".\\Source\\uCGUI\\Widget\\FRAMEWIN.h"

















 




#line 24 ".\\Source\\uCGUI\\Widget\\FRAMEWIN.h"
#line 26 ".\\Source\\uCGUI\\Widget\\FRAMEWIN.h"










 



 







 















 









 

typedef signed short FRAMEWIN_Handle;






 
FRAMEWIN_Handle FRAMEWIN_Create        (const char* pTitle, WM_CALLBACK* cb, int Flags, int x0, int y0, int xsize, int ysize);
FRAMEWIN_Handle FRAMEWIN_CreateAsChild (int x0, int y0, int xsize, int ysize, GUI_HWIN hParent, const char* pText, WM_CALLBACK* cb, int Flags);
FRAMEWIN_Handle FRAMEWIN_CreateIndirect(const GUI_WIDGET_CREATE_INFO* pCreateInfo, GUI_HWIN hWinParent, int x0, int y0, WM_CALLBACK* cb);
FRAMEWIN_Handle FRAMEWIN_CreateEx      (int x0, int y0, int xsize, int ysize, GUI_HWIN hParent,
                                        int WinFlags, int ExFlags, int Id, const char* pTitle, WM_CALLBACK* cb);







 
void FRAMEWIN_Callback(WM_MESSAGE * pMsg);






 







GUI_HWIN FRAMEWIN_AddButton     (FRAMEWIN_Handle hObj, int Flags, int Off, int Id);
GUI_HWIN FRAMEWIN_AddCloseButton(FRAMEWIN_Handle hObj, int Flags, int Off);
GUI_HWIN FRAMEWIN_AddMaxButton  (FRAMEWIN_Handle hObj, int Flags, int Off);
void    FRAMEWIN_AddMenu       (FRAMEWIN_Handle hObj, GUI_HWIN hMenu);
GUI_HWIN FRAMEWIN_AddMinButton  (FRAMEWIN_Handle hObj, int Flags, int Off);

void    FRAMEWIN_Minimize      (FRAMEWIN_Handle hObj);
void    FRAMEWIN_Maximize      (FRAMEWIN_Handle hObj);
void    FRAMEWIN_Restore       (FRAMEWIN_Handle hObj);






 
void FRAMEWIN_SetActive      (FRAMEWIN_Handle hObj, int State);
void FRAMEWIN_SetBarColor    (FRAMEWIN_Handle hObj, unsigned Index, GUI_COLOR Color);
void FRAMEWIN_SetBorderSize  (FRAMEWIN_Handle hObj, unsigned Size);
void FRAMEWIN_SetClientColor (FRAMEWIN_Handle hObj, GUI_COLOR Color);
void FRAMEWIN_SetFont        (FRAMEWIN_Handle hObj, const GUI_FONT  * pFont);
void FRAMEWIN_SetMoveable    (FRAMEWIN_Handle hObj, int State);
void FRAMEWIN_SetResizeable  (FRAMEWIN_Handle hObj, int State);
void FRAMEWIN_SetText        (FRAMEWIN_Handle hObj, const char* s);
void FRAMEWIN_SetTextAlign   (FRAMEWIN_Handle hObj, int Align);
void FRAMEWIN_SetTextColor   (FRAMEWIN_Handle hObj, GUI_COLOR Color);
void FRAMEWIN_SetTextColorEx (FRAMEWIN_Handle hObj, unsigned Index, GUI_COLOR Color);
void FRAMEWIN_SetTitleVis    (FRAMEWIN_Handle hObj, int Show);
int  FRAMEWIN_SetTitleHeight (FRAMEWIN_Handle hObj, int Height);






 
int FRAMEWIN_GetTitleHeight (FRAMEWIN_Handle hObj);
int FRAMEWIN_GetBorderSize  (FRAMEWIN_Handle hObj);
int FRAMEWIN_IsMinimized    (FRAMEWIN_Handle hObj);
int FRAMEWIN_IsMaximized    (FRAMEWIN_Handle hObj);






 
GUI_COLOR       FRAMEWIN_GetDefaultBarColor   (unsigned Index);
int             FRAMEWIN_GetDefaultBorderSize (void);
int             FRAMEWIN_GetDefaultTitleHeight(void);
GUI_COLOR       FRAMEWIN_GetDefaultClientColor(void);
const GUI_FONT  * FRAMEWIN_GetDefaultFont       (void);
GUI_COLOR       FRAMEWIN_GetDefaultTextColor  (unsigned Index);
void            FRAMEWIN_SetDefaultBarColor   (unsigned Index, GUI_COLOR Color);
void            FRAMEWIN_SetDefaultBorderSize (int DefaultBorderSize);
void            FRAMEWIN_SetDefaultTitleHeight(int DefaultTitleHeight);
void            FRAMEWIN_SetDefaultClientColor(GUI_COLOR Color);
void            FRAMEWIN_SetDefaultFont       (const GUI_FONT  * pFont);
int             FRAMEWIN_SetDefaultTextAlign  (int TextAlign);
void            FRAMEWIN_SetDefaultTextColor  (unsigned Index, GUI_COLOR Color);






 
#line 185 ".\\Source\\uCGUI\\Widget\\FRAMEWIN.h"







	 	 			 		    	 				 	  			   	 	 	 	 	 	  	  	      	   		 	 	 		  		  	 		 	  	  			     			       	   	 			  		    	 	     	 				  	 					 	 			   	  	  			 				 		 	 	 			     			 
#line 32 ".\\Source\\uCGUI\\Widget\\DIALOG.h"
#line 1 ".\\Source\\uCGUI\\Widget\\LISTBOX.h"

















 




#line 24 ".\\Source\\uCGUI\\Widget\\LISTBOX.h"
#line 25 ".\\Source\\uCGUI\\Widget\\LISTBOX.h"
#line 26 ".\\Source\\uCGUI\\Widget\\LISTBOX.h"












 






 








 
typedef signed short LISTBOX_Handle;







 





 
#line 76 ".\\Source\\uCGUI\\Widget\\LISTBOX.h"






 












 

LISTBOX_Handle LISTBOX_Create        (const GUI_ConstString* ppText, int x0, int y0, int xsize, int ysize, int Flags);
LISTBOX_Handle LISTBOX_CreateAsChild (const GUI_ConstString* ppText, GUI_HWIN hWinParent, int x0, int y0, int xsize, int ysize, int Flags);
LISTBOX_Handle LISTBOX_CreateIndirect(const GUI_WIDGET_CREATE_INFO* pCreateInfo, GUI_HWIN hWinParent, int x0, int y0, WM_CALLBACK* cb);
LISTBOX_Handle LISTBOX_CreateEx      (int x0, int y0, int xsize, int ysize, GUI_HWIN hParent,
                                      int WinFlags, int ExFlags, int Id, const GUI_ConstString* ppText);







 
void LISTBOX_Callback(WM_MESSAGE * pMsg);






 

int          LISTBOX_AddKey          (LISTBOX_Handle hObj, int Key);
void         LISTBOX_AddString       (LISTBOX_Handle hObj, const char* s);
void         LISTBOX_DecSel          (LISTBOX_Handle hObj);
void         LISTBOX_DeleteItem      (LISTBOX_Handle hObj, unsigned int Index);
unsigned     LISTBOX_GetItemSpacing  (LISTBOX_Handle hObj);
unsigned     LISTBOX_GetNumItems     (LISTBOX_Handle hObj);
int          LISTBOX_GetSel          (LISTBOX_Handle hObj);
const GUI_FONT  * LISTBOX_GetFont    (LISTBOX_Handle hObj);
int          LISTBOX_GetItemDisabled (LISTBOX_Handle hObj, unsigned Index);
int          LISTBOX_GetItemSel      (LISTBOX_Handle hObj, unsigned Index);
void         LISTBOX_GetItemText     (LISTBOX_Handle hObj, unsigned Index, char * pBuffer, int MaxSize);
int          LISTBOX_GetMulti        (LISTBOX_Handle hObj);
int          LISTBOX_GetScrollStepH  (LISTBOX_Handle hObj);
int          LISTBOX_GetTextAlign    (LISTBOX_Handle hObj);
void         LISTBOX_IncSel          (LISTBOX_Handle hObj);
void         LISTBOX_InsertString    (LISTBOX_Handle hObj, const char* s, unsigned int Index);
int          LISTBOX_OwnerDraw       (const WIDGET_ITEM_DRAW_INFO * pDrawItemInfo);
void         LISTBOX_SetAutoScrollH  (LISTBOX_Handle hObj, int OnOff);
void         LISTBOX_SetAutoScrollV  (LISTBOX_Handle hObj, int OnOff);
void         LISTBOX_SetBkColor      (LISTBOX_Handle hObj, unsigned int Index, GUI_COLOR color);
void         LISTBOX_SetFont         (LISTBOX_Handle hObj, const GUI_FONT  * pFont);
void         LISTBOX_SetItemDisabled (LISTBOX_Handle hObj, unsigned Index, int OnOff);
void         LISTBOX_SetItemSel      (LISTBOX_Handle hObj, unsigned Index, int OnOff);
void         LISTBOX_SetItemSpacing  (LISTBOX_Handle hObj, unsigned Value);
void         LISTBOX_SetMulti        (LISTBOX_Handle hObj, int Mode);
void         LISTBOX_SetOwner        (LISTBOX_Handle hObj, GUI_HWIN hOwner);
void         LISTBOX_SetOwnerDraw    (LISTBOX_Handle hObj, WIDGET_DRAW_ITEM_FUNC * pfDrawItem);
void         LISTBOX_SetScrollStepH  (LISTBOX_Handle hObj, int Value);
void         LISTBOX_SetSel          (LISTBOX_Handle hObj, int Sel);
void         LISTBOX_SetScrollbarColor(LISTBOX_Handle hObj, unsigned Index, GUI_COLOR Color);
void         LISTBOX_SetScrollbarWidth(LISTBOX_Handle hObj, unsigned Width);
void         LISTBOX_SetString       (LISTBOX_Handle hObj, const char* s, unsigned int Index);
void         LISTBOX_SetText         (LISTBOX_Handle hObj, const GUI_ConstString* ppText);
void         LISTBOX_SetTextAlign    (LISTBOX_Handle hObj, int Align);
GUI_COLOR    LISTBOX_SetTextColor    (LISTBOX_Handle hObj, unsigned int Index, GUI_COLOR Color);
int          LISTBOX_UpdateScrollers (LISTBOX_Handle hObj);
void         LISTBOX_InvalidateItem  (LISTBOX_Handle hObj, int Index);






 

const GUI_FONT * LISTBOX_GetDefaultFont(void);
int         LISTBOX_GetDefaultScrollStepH (void);
GUI_COLOR   LISTBOX_GetDefaultBkColor     (unsigned Index);
int         LISTBOX_GetDefaultTextAlign   (void);
GUI_COLOR   LISTBOX_GetDefaultTextColor   (unsigned Index);
void        LISTBOX_SetDefaultFont        (const GUI_FONT  * pFont);
void        LISTBOX_SetDefaultScrollStepH (int Value);
void        LISTBOX_SetDefaultBkColor     (unsigned Index, GUI_COLOR Color);
void        LISTBOX_SetDefaultTextAlign   (int Align);
void        LISTBOX_SetDefaultTextColor   (unsigned Index, GUI_COLOR Color);






 










	 	 			 		    	 				 	  			   	 	 	 	 	 	  	  	      	   		 	 	 		  		  	 		 	  	  			     			       	   	 			  		    	 	     	 				  	 					 	 			   	  	  			 				 		 	 	 			     			 
#line 33 ".\\Source\\uCGUI\\Widget\\DIALOG.h"
#line 1 ".\\Source\\uCGUI\\Widget\\MULTIEDIT.h"

















 




#line 24 ".\\Source\\uCGUI\\Widget\\MULTIEDIT.h"
#line 1 ".\\Source\\uCGUI\\Widget\\DIALOG.h"




















 

#line 56 ".\\Source\\uCGUI\\Widget\\DIALOG.h"
	 	 			 		    	 				 	  			   	 	 	 	 	 	  	  	      	   		 	 	 		  		  	 		 	  	  			     			       	   	 			  		    	 	     	 				  	 					 	 			   	  	  			 				 		 	 	 			     			 
#line 25 ".\\Source\\uCGUI\\Widget\\MULTIEDIT.h"






















 








 

typedef signed short MULTIEDIT_HANDLE;






 

MULTIEDIT_HANDLE MULTIEDIT_CreateEx      (int x0, int y0, int xsize, int ysize, GUI_HWIN hParent, int WinFlags, int ExFlags,
                                          int Id, int BufferSize, const char* pText);
MULTIEDIT_HANDLE MULTIEDIT_Create        (int x0, int y0, int xsize, int ysize, GUI_HWIN hParent,
                                          int Id, int Flags, int ExFlags, const char* pText, 
                                          int BufferSize);
MULTIEDIT_HANDLE MULTIEDIT_CreateIndirect(const GUI_WIDGET_CREATE_INFO* pCreateInfo, 
                                          GUI_HWIN hWinParent, int x0, int y0, WM_CALLBACK* cb);







 
void MULTIEDIT_Callback(WM_MESSAGE * pMsg);






 

int  MULTIEDIT_AddKey           (MULTIEDIT_HANDLE hObj, unsigned short Key);
int  MULTIEDIT_AddText          (MULTIEDIT_HANDLE hObj, const char * s);
int  MULTIEDIT_GetCursorCharPos (MULTIEDIT_HANDLE hObj);
void MULTIEDIT_GetCursorPixelPos(MULTIEDIT_HANDLE hObj, int * pxPos, int * pyPos);
void MULTIEDIT_GetPrompt        (MULTIEDIT_HANDLE hObj, char* sDest, int MaxNumChars);
int  MULTIEDIT_GetTextSize      (MULTIEDIT_HANDLE hObj);
void MULTIEDIT_GetText          (MULTIEDIT_HANDLE hObj, char* sDest, int MaxNumChars);
void MULTIEDIT_SetTextAlign     (MULTIEDIT_HANDLE hObj, int Align);
void MULTIEDIT_SetAutoScrollH   (MULTIEDIT_HANDLE hObj, int OnOff);
void MULTIEDIT_SetAutoScrollV   (MULTIEDIT_HANDLE hObj, int OnOff);
void MULTIEDIT_SetBkColor       (MULTIEDIT_HANDLE hObj, unsigned Index, GUI_COLOR color);
void MULTIEDIT_SetCursorCharPos (MULTIEDIT_HANDLE hObj, int x, int y);        
void MULTIEDIT_SetCursorPixelPos(MULTIEDIT_HANDLE hObj, int x, int y);        
void MULTIEDIT_SetCursorOffset  (MULTIEDIT_HANDLE hObj, int Offset);
void MULTIEDIT_SetHBorder       (MULTIEDIT_HANDLE hObj, unsigned HBorder);
void MULTIEDIT_SetFont          (MULTIEDIT_HANDLE hObj, const GUI_FONT  * pFont);
void MULTIEDIT_SetInsertMode    (MULTIEDIT_HANDLE hObj, int OnOff);
void MULTIEDIT_SetBufferSize    (MULTIEDIT_HANDLE hObj, int BufferSize);
void MULTIEDIT_SetMaxNumChars   (MULTIEDIT_HANDLE hObj, unsigned MaxNumChars);
void MULTIEDIT_SetPrompt        (MULTIEDIT_HANDLE hObj, const char* sPrompt);
void MULTIEDIT_SetReadOnly      (MULTIEDIT_HANDLE hObj, int OnOff);
void MULTIEDIT_SetPasswordMode  (MULTIEDIT_HANDLE hObj, int OnOff);
void MULTIEDIT_SetText          (MULTIEDIT_HANDLE hObj, const char* s);
void MULTIEDIT_SetTextColor     (MULTIEDIT_HANDLE hObj, unsigned Index, GUI_COLOR color);
void MULTIEDIT_SetWrapNone      (MULTIEDIT_HANDLE hObj);
void MULTIEDIT_SetWrapChar      (MULTIEDIT_HANDLE hObj);
void MULTIEDIT_SetWrapWord      (MULTIEDIT_HANDLE hObj);






 











	 	 			 		    	 				 	  			   	 	 	 	 	 	  	  	      	   		 	 	 		  		  	 		 	  	  			     			       	   	 			  		    	 	     	 				  	 					 	 			   	  	  			 				 		 	 	 			     			 
#line 34 ".\\Source\\uCGUI\\Widget\\DIALOG.h"
#line 1 ".\\Source\\uCGUI\\Widget\\RADIO.h"

















 




#line 24 ".\\Source\\uCGUI\\Widget\\RADIO.h"
#line 25 ".\\Source\\uCGUI\\Widget\\RADIO.h"










 












 






 









 

typedef signed short RADIO_Handle;






 

RADIO_Handle RADIO_Create        (int x0, int y0, int xsize, int ysize, GUI_HWIN hParent, int Id, int Flags, unsigned Para);
RADIO_Handle RADIO_CreateIndirect(const GUI_WIDGET_CREATE_INFO* pCreateInfo, GUI_HWIN hWinParent, int x0, int y0, WM_CALLBACK* cb);
RADIO_Handle RADIO_CreateEx      (int x0, int y0, int xsize, int ysize, GUI_HWIN hParent,
                                  int WinFlags, int ExFlags, int Id, int NumItems, int Spacing);







 
void RADIO_Callback(WM_MESSAGE * pMsg);






 

void      RADIO_SetDefaultFont      (const GUI_FONT * pFont);
GUI_COLOR RADIO_SetDefaultFocusColor(GUI_COLOR Color);
void      RADIO_SetDefaultImage     (const GUI_BITMAP * pBitmap, unsigned int Index);
void      RADIO_SetDefaultTextColor (GUI_COLOR TextColor);

const GUI_FONT * RADIO_GetDefaultFont      (void);
GUI_COLOR                   RADIO_GetDefaultTextColor (void);






 

void      RADIO_AddValue     (RADIO_Handle hObj, int Add);
void      RADIO_Dec          (RADIO_Handle hObj);
int       RADIO_GetText      (RADIO_Handle hObj, unsigned Index, char * pBuffer, int MaxLen);
void      RADIO_Inc          (RADIO_Handle hObj);
void      RADIO_SetBkColor   (RADIO_Handle hObj, GUI_COLOR Color);
GUI_COLOR RADIO_SetFocusColor(RADIO_Handle hObj, GUI_COLOR Color);
void      RADIO_SetFont      (RADIO_Handle hObj, const GUI_FONT * pFont);
void      RADIO_SetGroupId   (RADIO_Handle hObj, unsigned char GroupId);
void      RADIO_SetImage     (RADIO_Handle hObj, const GUI_BITMAP * pBitmap, unsigned int Index);
void      RADIO_SetText      (RADIO_Handle hObj, const char* pText, unsigned Index);
void      RADIO_SetTextColor (RADIO_Handle hObj, GUI_COLOR Color);
void      RADIO_SetValue     (RADIO_Handle hObj, int v);






 
int RADIO_GetValue(RADIO_Handle hObj);








 
	 	 			 		    	 				 	  			   	 	 	 	 	 	  	  	      	   		 	 	 		  		  	 		 	  	  			     			       	   	 			  		    	 	     	 				  	 					 	 			   	  	  			 				 		 	 	 			     			 
#line 35 ".\\Source\\uCGUI\\Widget\\DIALOG.h"
#line 1 ".\\Source\\uCGUI\\Widget\\SLIDER.h"

















 




#line 24 ".\\Source\\uCGUI\\Widget\\SLIDER.h"
#line 25 ".\\Source\\uCGUI\\Widget\\SLIDER.h"
#line 26 ".\\Source\\uCGUI\\Widget\\SLIDER.h"












 




 





 








 
typedef signed short SLIDER_Handle;






 

SLIDER_Handle SLIDER_Create        (int x0, int y0, int xsize, int ysize, GUI_HWIN hParent, int Id, int WinFlags, int SpecialFlags);
SLIDER_Handle SLIDER_CreateIndirect(const GUI_WIDGET_CREATE_INFO* pCreateInfo, GUI_HWIN hWinParent, int x0, int y0, WM_CALLBACK* cb);
SLIDER_Handle SLIDER_CreateEx      (int x0, int y0, int xsize, int ysize, GUI_HWIN hParent,
                                    int WinFlags, int ExFlags, int Id);







 
void SLIDER_Callback(WM_MESSAGE * pMsg);






 

 


 
void      SLIDER_Dec          (SLIDER_Handle hObj);
void      SLIDER_Inc          (SLIDER_Handle hObj);
void      SLIDER_SetBkColor   (SLIDER_Handle hObj, GUI_COLOR Color);
GUI_COLOR SLIDER_SetFocusColor(SLIDER_Handle hObj, GUI_COLOR Color);
void      SLIDER_SetNumTicks  (SLIDER_Handle hObj, int NumTicks);
void      SLIDER_SetRange     (SLIDER_Handle hObj, int Min, int Max);
void      SLIDER_SetValue     (SLIDER_Handle hObj, int v);
void      SLIDER_SetWidth     (SLIDER_Handle hObj, int Width);






 

void      SLIDER_SetDefaultBkColor   (GUI_COLOR Color);
GUI_COLOR SLIDER_SetDefaultFocusColor(GUI_COLOR Color);






 
int SLIDER_GetValue(SLIDER_Handle hObj);







	 	 			 		    	 				 	  			   	 	 	 	 	 	  	  	      	   		 	 	 		  		  	 		 	  	  			     			       	   	 			  		    	 	     	 				  	 					 	 			   	  	  			 				 		 	 	 			     			 
#line 36 ".\\Source\\uCGUI\\Widget\\DIALOG.h"
#line 1 ".\\Source\\uCGUI\\Widget\\TEXT.h"

















 




#line 24 ".\\Source\\uCGUI\\Widget\\TEXT.h"
#line 25 ".\\Source\\uCGUI\\Widget\\TEXT.h"
#line 26 ".\\Source\\uCGUI\\Widget\\TEXT.h"
#line 27 ".\\Source\\uCGUI\\Widget\\TEXT.h"












 




 















 
typedef signed short TEXT_Handle;






 












 

TEXT_Handle TEXT_Create        (int x0, int y0, int xsize, int ysize, int Id, int Flags, const char * s, int Align);
TEXT_Handle TEXT_CreateAsChild (int x0, int y0, int xsize, int ysize, GUI_HWIN hParent, int Id, int Flags, const char * s, int Align);
TEXT_Handle TEXT_CreateIndirect(const GUI_WIDGET_CREATE_INFO* pCreateInfo, GUI_HWIN hWinParent, int x0, int y0, WM_CALLBACK* cb);
TEXT_Handle TEXT_CreateEx      (int x0, int y0, int xsize, int ysize, GUI_HWIN hParent,
                                int WinFlags, int ExFlags, int Id, const char* pText);







 
void TEXT_Callback(WM_MESSAGE * pMsg);






 

 

void TEXT_SetBkColor  (TEXT_Handle pObj, GUI_COLOR Color);  
void TEXT_SetFont     (TEXT_Handle pObj, const GUI_FONT  * pFont);
void TEXT_SetText     (TEXT_Handle pObj, const char* s);
void TEXT_SetTextAlign(TEXT_Handle pObj, int Align);
void TEXT_SetTextColor(TEXT_Handle pObj, GUI_COLOR Color);
void TEXT_SetWrapMode (TEXT_Handle hObj, GUI_WRAPMODE WrapMode);






 

void                         TEXT_SetDefaultFont     (const GUI_FONT  * pFont);
const GUI_FONT  * TEXT_GetDefaultFont     (void);
void                         TEXT_SetDefaultTextColor(GUI_COLOR Color);
GUI_WRAPMODE                 TEXT_SetDefaultWrapMode (GUI_WRAPMODE WrapMode);







	 	 			 		    	 				 	  			   	 	 	 	 	 	  	  	      	   		 	 	 		  		  	 		 	  	  			     			       	   	 			  		    	 	     	 				  	 					 	 			   	  	  			 				 		 	 	 			     			 
#line 37 ".\\Source\\uCGUI\\Widget\\DIALOG.h"







GUI_HWIN WINDOW_CreateIndirect(const GUI_WIDGET_CREATE_INFO* pCreateInfo, GUI_HWIN hWinParent, int x0, int y0, WM_CALLBACK* cb);
void    WINDOW_SetDefaultBkColor(GUI_COLOR Color);

void WINDOW_Callback(WM_MESSAGE * pMsg);








	 	 			 		    	 				 	  			   	 	 	 	 	 	  	  	      	   		 	 	 		  		  	 		 	  	  			     			       	   	 			  		    	 	     	 				  	 					 	 			   	  	  			 				 		 	 	 			     			 
#line 14 "Source\\gui_app\\KeyBoard_Win.c"

#line 16 "Source\\gui_app\\KeyBoard_Win.c"
#line 17 "Source\\gui_app\\KeyBoard_Win.c"
#line 18 "Source\\gui_app\\KeyBoard_Win.c"
#line 19 "Source\\gui_app\\KeyBoard_Win.c"
#line 20 "Source\\gui_app\\KeyBoard_Win.c"
#line 21 "Source\\gui_app\\KeyBoard_Win.c"
#line 22 "Source\\gui_app\\KeyBoard_Win.c"
#line 23 "Source\\gui_app\\KeyBoard_Win.c"
#line 24 "Source\\gui_app\\KeyBoard_Win.c"
#line 25 "Source\\gui_app\\KeyBoard_Win.c"
#line 26 "Source\\gui_app\\KeyBoard_Win.c"
#line 1 ".\\Source\\uCGUI\\Widget\\PROGBAR.h"

















 




#line 24 ".\\Source\\uCGUI\\Widget\\PROGBAR.h"
#line 25 ".\\Source\\uCGUI\\Widget\\PROGBAR.h"












 



 








 
typedef signed short PROGBAR_Handle;







 

PROGBAR_Handle PROGBAR_Create        (int x0, int y0, int xsize, int ysize, int Flags);
PROGBAR_Handle PROGBAR_CreateAsChild (int x0, int y0, int xsize, int ysize, GUI_HWIN hParent, int Id, int Flags);
PROGBAR_Handle PROGBAR_CreateIndirect(const GUI_WIDGET_CREATE_INFO* pCreateInfo, GUI_HWIN hWinParent, int x0, int y0, WM_CALLBACK* cb);
PROGBAR_Handle PROGBAR_CreateEx      (int x0, int y0, int xsize, int ysize, GUI_HWIN hParent,
                                      int WinFlags, int ExFlags, int Id);






 
void PROGBAR_Callback(WM_MESSAGE * pMsg);






 











 

void            PROGBAR_SetBarColor (PROGBAR_Handle hObj, unsigned int index, GUI_COLOR color);
void            PROGBAR_SetFont     (PROGBAR_Handle hObj, const GUI_FONT  * pfont);
void            PROGBAR_SetMinMax   (PROGBAR_Handle hObj, int Min, int Max);
void            PROGBAR_SetText     (PROGBAR_Handle hObj, const char* s);
void            PROGBAR_SetTextAlign(PROGBAR_Handle hObj, int Align);
void            PROGBAR_SetTextColor(PROGBAR_Handle hObj, unsigned int index, GUI_COLOR color);
void            PROGBAR_SetTextPos  (PROGBAR_Handle hObj, int XOff, int YOff);
void            PROGBAR_SetValue    (PROGBAR_Handle hObj, int v);







	 	 			 		    	 				 	  			   	 	 	 	 	 	  	  	      	   		 	 	 		  		  	 		 	  	  			     			       	   	 			  		    	 	     	 				  	 					 	 			   	  	  			 				 		 	 	 			     			 
#line 27 "Source\\gui_app\\KeyBoard_Win.c"
#line 28 "Source\\gui_app\\KeyBoard_Win.c"
#line 1 ".\\Source\\uCGUI\\Widget\\LISTVIEW.h"

















 




#line 24 ".\\Source\\uCGUI\\Widget\\LISTVIEW.h"
#line 25 ".\\Source\\uCGUI\\Widget\\LISTVIEW.h"
#line 1 ".\\Source\\uCGUI\\Widget\\HEADER.h"

















 




#line 24 ".\\Source\\uCGUI\\Widget\\HEADER.h"
#line 25 ".\\Source\\uCGUI\\Widget\\HEADER.h"
#line 26 ".\\Source\\uCGUI\\Widget\\HEADER.h"












 

typedef signed short HEADER_Handle;






 

HEADER_Handle HEADER_Create        (int x0, int y0, int xsize, int ysize, GUI_HWIN hParent, int Id, int Flags, int SpecialFlags);
HEADER_Handle HEADER_CreateIndirect(const GUI_WIDGET_CREATE_INFO * pCreateInfo, GUI_HWIN hWinParent, int x0, int y0, WM_CALLBACK * cb);
HEADER_Handle HEADER_CreateAttached(GUI_HWIN hParent, int Id, int SpecialFlags);
HEADER_Handle HEADER_CreateEx      (int x0, int y0, int xsize, int ysize, GUI_HWIN hParent,
                                    int WinFlags, int ExFlags, int Id);







 
void HEADER_Callback(WM_MESSAGE * pMsg);






 












 

 
GUI_COLOR          HEADER_SetDefaultBkColor  (GUI_COLOR Color);
const GUI_CURSOR  * HEADER_SetDefaultCursor   (const GUI_CURSOR * pCursor);
const GUI_FONT  *   HEADER_SetDefaultFont     (const GUI_FONT  * pFont);
int                HEADER_SetDefaultBorderH (int Spacing);
int                HEADER_SetDefaultBorderV (int Spacing);
GUI_COLOR          HEADER_SetDefaultTextColor(GUI_COLOR Color);

 
GUI_COLOR          HEADER_GetDefaultBkColor  (void);
const GUI_CURSOR  * HEADER_GetDefaultCursor   (void);
const GUI_FONT  *   HEADER_GetDefaultFont     (void);
int                HEADER_GetDefaultBorderH  (void);
int                HEADER_GetDefaultBorderV  (void);
GUI_COLOR          HEADER_GetDefaultTextColor(void);






 

void HEADER_AddItem            (HEADER_Handle hObj, int Width, const char * s, int Align);
void HEADER_DeleteItem         (HEADER_Handle hObj, unsigned Index);
int  HEADER_GetHeight          (HEADER_Handle hObj);
int  HEADER_GetItemWidth       (HEADER_Handle hObj, unsigned int Index);
int  HEADER_GetNumItems        (HEADER_Handle hObj);
int  HEADER_GetSel             (HEADER_Handle hObj);
void HEADER_SetBitmap          (HEADER_Handle hObj, unsigned int Index, const GUI_BITMAP * pBitmap);
void HEADER_SetBitmapEx        (HEADER_Handle hObj, unsigned int Index, const GUI_BITMAP * pBitmap, int x, int y);
void HEADER_SetBkColor         (HEADER_Handle hObj, GUI_COLOR Color);
void HEADER_SetBMP             (HEADER_Handle hObj, unsigned int Index, const void * pBitmap);
void HEADER_SetBMPEx           (HEADER_Handle hObj, unsigned int Index, const void * pBitmap, int x, int y);
void HEADER_SetDirIndicator    (HEADER_Handle hObj, int Column, int Reverse);  
void HEADER_SetDragLimit       (HEADER_Handle hObj, unsigned DragLimit);
void HEADER_SetFont            (HEADER_Handle hObj, const GUI_FONT  * pFont);
void HEADER_SetHeight          (HEADER_Handle hObj, int Height);
void HEADER_SetTextAlign       (HEADER_Handle hObj, unsigned int Index, int Align);
void HEADER_SetItemText        (HEADER_Handle hObj, unsigned int Index, const char * s);
void HEADER_SetItemWidth       (HEADER_Handle hObj, unsigned int Index, int Width);
void HEADER_SetScrollPos       (HEADER_Handle hObj, int ScrollPos);
void HEADER_SetStreamedBitmap  (HEADER_Handle hObj, unsigned int Index, const GUI_BITMAP_STREAM * pBitmap);
void HEADER_SetStreamedBitmapEx(HEADER_Handle hObj, unsigned int Index, const GUI_BITMAP_STREAM * pBitmap, int x, int y);
void HEADER_SetTextColor       (HEADER_Handle hObj, GUI_COLOR Color);






 

#line 147 ".\\Source\\uCGUI\\Widget\\HEADER.h"







	 	 			 		    	 				 	  			   	 	 	 	 	 	  	  	      	   		 	 	 		  		  	 		 	  	  			     			       	   	 			  		    	 	     	 				  	 					 	 			   	  	  			 				 		 	 	 			     			 
#line 26 ".\\Source\\uCGUI\\Widget\\LISTVIEW.h"










 









 











 

typedef signed short LISTVIEW_Handle;






 

LISTVIEW_Handle LISTVIEW_Create        (int x0, int y0, int xsize, int ysize, GUI_HWIN hParent, int Id, int Flags, int SpecialFlags);
LISTVIEW_Handle LISTVIEW_CreateAttached(GUI_HWIN hParent, int Id, int SpecialFlags);
LISTVIEW_Handle LISTVIEW_CreateIndirect(const GUI_WIDGET_CREATE_INFO* pCreateInfo, GUI_HWIN hWinParent, int x0, int y0, WM_CALLBACK* cb);
LISTVIEW_Handle LISTVIEW_CreateEx      (int x0, int y0, int xsize, int ysize, GUI_HWIN hParent,
                                        int WinFlags, int ExFlags, int Id);







 
void LISTVIEW_Callback(WM_MESSAGE * pMsg);






 












 

int             LISTVIEW_AddColumn          (LISTVIEW_Handle hObj, int Width, const char * s, int Align);
int             LISTVIEW_AddRow             (LISTVIEW_Handle hObj, const GUI_ConstString * ppText);
int             LISTVIEW_CompareText        (const void * p0, const void * p1);
int             LISTVIEW_CompareDec         (const void * p0, const void * p1);
void            LISTVIEW_DecSel             (LISTVIEW_Handle hObj);
void            LISTVIEW_DeleteColumn       (LISTVIEW_Handle hObj, unsigned Index);
void            LISTVIEW_DeleteRow          (LISTVIEW_Handle hObj, unsigned Index);
void            LISTVIEW_DeleteAllRows      (LISTVIEW_Handle hObj);
void            LISTVIEW_DisableRow         (LISTVIEW_Handle hObj, unsigned Row);
void            LISTVIEW_DisableSort        (LISTVIEW_Handle hObj);
void            LISTVIEW_EnableRow          (LISTVIEW_Handle hObj, unsigned Row);
void            LISTVIEW_EnableSort         (LISTVIEW_Handle hObj);
GUI_COLOR       LISTVIEW_GetBkColor         (LISTVIEW_Handle hObj, unsigned Index);
const GUI_FONT * LISTVIEW_GetFont(LISTVIEW_Handle hObj);
HEADER_Handle   LISTVIEW_GetHeader          (LISTVIEW_Handle hObj);
void            LISTVIEW_GetItemText        (LISTVIEW_Handle hObj, unsigned Column, unsigned Row, char* pBuffer, unsigned MaxSize);
unsigned        LISTVIEW_GetNumColumns      (LISTVIEW_Handle hObj);
unsigned        LISTVIEW_GetNumRows         (LISTVIEW_Handle hObj);
int             LISTVIEW_GetSel             (LISTVIEW_Handle hObj);
int             LISTVIEW_GetSelUnsorted     (LISTVIEW_Handle hObj);
GUI_COLOR       LISTVIEW_GetTextColor       (LISTVIEW_Handle hObj, unsigned Index);
unsigned long             LISTVIEW_GetUserData        (LISTVIEW_Handle hObj, unsigned Row);
void            LISTVIEW_IncSel             (LISTVIEW_Handle hObj);
int             LISTVIEW_InsertRow          (LISTVIEW_Handle hObj, unsigned Index, const GUI_ConstString * ppText);
void            LISTVIEW_SetAutoScrollH     (LISTVIEW_Handle hObj, int OnOff);
void            LISTVIEW_SetAutoScrollV     (LISTVIEW_Handle hObj, int OnOff);
void            LISTVIEW_SetBkColor         (LISTVIEW_Handle hObj, unsigned int Index, GUI_COLOR Color);
void            LISTVIEW_SetColumnWidth     (LISTVIEW_Handle hObj, unsigned int Index, int Width);
void            LISTVIEW_SetCompareFunc     (LISTVIEW_Handle hObj, unsigned Column, int (* fpCompare)(const void * p0, const void * p1));
void            LISTVIEW_SetFont            (LISTVIEW_Handle hObj, const GUI_FONT  * pFont);
int             LISTVIEW_SetGridVis         (LISTVIEW_Handle hObj, int Show);
void            LISTVIEW_SetItemBkColor     (LISTVIEW_Handle hObj, unsigned Column, unsigned Row, unsigned int Index, GUI_COLOR Color);
void            LISTVIEW_SetItemText        (LISTVIEW_Handle hObj, unsigned Column, unsigned Row, const char * s);
void            LISTVIEW_SetItemTextColor   (LISTVIEW_Handle hObj, unsigned Column, unsigned Row, unsigned int Index, GUI_COLOR Color);
void            LISTVIEW_SetLBorder         (LISTVIEW_Handle hObj, unsigned BorderSize);
void            LISTVIEW_SetRBorder         (LISTVIEW_Handle hObj, unsigned BorderSize);
unsigned        LISTVIEW_SetRowHeight       (LISTVIEW_Handle hObj, unsigned RowHeight);
void            LISTVIEW_SetSel             (LISTVIEW_Handle hObj, int Sel);
void            LISTVIEW_SetSelUnsorted     (LISTVIEW_Handle hObj, int Sel);
unsigned        LISTVIEW_SetSort            (LISTVIEW_Handle hObj, unsigned Column, unsigned Reverse);
void            LISTVIEW_SetTextAlign       (LISTVIEW_Handle hObj, unsigned int Index, int Align);
void            LISTVIEW_SetTextColor       (LISTVIEW_Handle hObj, unsigned int Index, GUI_COLOR Color);
void            LISTVIEW_SetUserData        (LISTVIEW_Handle hObj, unsigned Row, unsigned long UserData);






 

GUI_COLOR        LISTVIEW_SetDefaultBkColor  (unsigned Index, GUI_COLOR Color);
const GUI_FONT  * LISTVIEW_SetDefaultFont     (const GUI_FONT  * pFont);
GUI_COLOR        LISTVIEW_SetDefaultGridColor(GUI_COLOR Color);
GUI_COLOR        LISTVIEW_SetDefaultTextColor(unsigned Index, GUI_COLOR Color);








 
	 	 			 		    	 				 	  			   	 	 	 	 	 	  	  	      	   		 	 	 		  		  	 		 	  	  			     			       	   	 			  		    	 	     	 				  	 					 	 			   	  	  			 				 		 	 	 			     			 
#line 29 "Source\\gui_app\\KeyBoard_Win.c"
#line 1 "Source\\gui_app\\KeyBoard_Win.h"





typedef enum work_state
{
 ENGLISH_S =0 ,
 ENGLISH_B = 1,
 CHINESE = 2,

SFLOAT =3

}EWorkState;


typedef struct  KeyBoard_H
{
  EWorkState work_state;			
  char* pdata_head;					
  char* pdata_end;
  char* pdata;

  char* pch_data_head;				
  char* pch_data_end;
  char* pch_data;

  char* pnum_data_head;				
  char* pnum_data_end;
  char* pnum_data;

  int  num_ch;

  char* res_ch_data_head;			
  char* res_ch_data_end;
  char* res_ch_data;

  char use_now;
	 
}TKeyBoard_H;

extern void KeyBoard_Win(TKeyBoard_H* keyboard_h) ;



#line 30 "Source\\gui_app\\KeyBoard_Win.c"

extern char *PYSearch(unsigned char *msg ,int *num);






 

#line 53 "Source\\gui_app\\KeyBoard_Win.c"




#line 83 "Source\\gui_app\\KeyBoard_Win.c"

#line 92 "Source\\gui_app\\KeyBoard_Win.c"



















extern const GUI_FONT GUI_FontHZ_SongTi_16;

TKeyBoard_H* keyboard_win_h;


char dat;
char* ch_dat;
int num ;

char data[20];
char ch_data[120];
char key[60];
char num_add_ch[60];
char res_ch[60];

void ID_A_Z(WM_MESSAGE * pMsg)
{
	int i,j,k;
	
	k = 0;
    
	if(keyboard_win_h->work_state == CHINESE)
	{  
	*(keyboard_win_h->pdata++) = WM_GetId(pMsg->hWinSrc) + (97 - (0x800+16));
	ch_dat = PYSearch(keyboard_win_h->pdata_head , &(keyboard_win_h->num_ch));
		if(ch_dat == '\0')
		{
		keyboard_win_h->num_ch = 0;
		keyboard_win_h->pdata--;  
		return;
		}
	keyboard_win_h->pch_data_head = ch_dat;

	keyboard_win_h->pch_data_end = keyboard_win_h->pch_data_head + 2*(keyboard_win_h->num_ch);

	keyboard_win_h->pch_data = ch_dat;

	keyboard_win_h->pnum_data = keyboard_win_h->pnum_data_head;
	
	if(keyboard_win_h->num_ch > 0)
	{
	
		if(keyboard_win_h->pch_data_end - keyboard_win_h->pch_data > 14)
		{
			k = 7;
		}else{
		
			k = (keyboard_win_h->pch_data_end - keyboard_win_h->pch_data)/2;
		}
			
		for(j= 0; j<k; j++)
		{
			*(keyboard_win_h->pnum_data++) = j+'1';
			
			*(keyboard_win_h->pnum_data++) = *(keyboard_win_h->pch_data++);
			
			*(keyboard_win_h->pnum_data++) = *(keyboard_win_h->pch_data++); 
			
			*(keyboard_win_h->pnum_data++) = ' ';
		}

			if(k<7)
		{
			for(j=0; j<4*(7-k);j++)
			{
			*(keyboard_win_h->pnum_data++) = '\0';
			}
		
		
		
		
		}

		TEXT_SetText(WM_GetDialogItem(pMsg->hWin, (0x800+2)),keyboard_win_h->pdata_head);
	
		EDIT_SetText(WM_GetDialogItem(pMsg->hWin, (0x800+3)),keyboard_win_h->pnum_data_head);
		
		if(keyboard_win_h->pdata == keyboard_win_h->pdata_end)
		keyboard_win_h->pdata = keyboard_win_h->pdata_head;
	}

	}else if(keyboard_win_h->work_state == ENGLISH_S){
	
		*(keyboard_win_h->res_ch_data++) = WM_GetId(pMsg->hWinSrc) + (97 - (0x800+16));

		EDIT_SetText(WM_GetDialogItem(pMsg->hWin, (0x800+1)),keyboard_win_h->res_ch_data_head);
	
	}else if(keyboard_win_h->work_state == ENGLISH_B){
	
		*(keyboard_win_h->res_ch_data++) = WM_GetId(pMsg->hWinSrc) +(65 - (0x800+16));
		EDIT_SetText(WM_GetDialogItem(pMsg->hWin, (0x800+1)),keyboard_win_h->res_ch_data_head);

	}
}


void ID_key_R(WM_MESSAGE * pMsg)
{
	int i,j,k;

	if(keyboard_win_h->pch_data_end - keyboard_win_h->pch_data > 0)
	{
		keyboard_win_h->pnum_data = keyboard_win_h->pnum_data_head;
		
		if(keyboard_win_h->pch_data_end - keyboard_win_h->pch_data > 14)
		{
			k = 7;

		}else{
			k = (keyboard_win_h->pch_data_end - keyboard_win_h->pch_data)/2;

		}

		for(j= 0; j<k; j++)
		{
			*(keyboard_win_h->pnum_data++) = j+'1';
	
			*(keyboard_win_h->pnum_data++) = *(keyboard_win_h->pch_data++);  

			*(keyboard_win_h->pnum_data++) = *(keyboard_win_h->pch_data++);  
			
			*(keyboard_win_h->pnum_data++) = ' ';
		}
		if(k<7)
		{
			for(j=0; j<4*(7-k);j++)
			{
			*(keyboard_win_h->pnum_data++) = '\0';
			}
			for(j=0; j<2*(7-k);j++)
			{
			keyboard_win_h->pch_data++;
			}
		}
	}
		EDIT_SetText(WM_GetDialogItem(pMsg->hWin, (0x800+3)),keyboard_win_h->pnum_data_head);
}


void ID_key_L(WM_MESSAGE * pMsg)
{
	int i,j;
	int k;

	
	

	if((keyboard_win_h->pch_data - 28 >= keyboard_win_h->pch_data_head)&&(keyboard_win_h->pch_data > 0))
	{
		keyboard_win_h->pnum_data = keyboard_win_h->pnum_data_head;
		
		keyboard_win_h->pch_data = keyboard_win_h->pch_data - 28;					

		for(j= 0; (j<7)&& (*(keyboard_win_h->pch_data)!='\0'); j++)
		{
			*(keyboard_win_h->pnum_data++) = j+'1';

			*(keyboard_win_h->pnum_data++) = *(keyboard_win_h->pch_data++);
			
			*(keyboard_win_h->pnum_data++) = *(keyboard_win_h->pch_data++);
			
			*(keyboard_win_h->pnum_data++) = ' ';
		}		
	
		EDIT_SetText(WM_GetDialogItem(pMsg->hWin, (0x800+3)),keyboard_win_h->pnum_data_head);
	}
}



void ID_1_0(WM_MESSAGE * pMsg)
{
	int num,j;
	
	if((keyboard_win_h->work_state == CHINESE)&&(keyboard_win_h->pnum_data != keyboard_win_h->pnum_data_head))
	{
		num = 	WM_GetId(pMsg->hWinSrc)-(0x800+5);
        num =   num*4;
		*(keyboard_win_h->res_ch_data++) = *(keyboard_win_h->pnum_data_head+num+1);
		*(keyboard_win_h->res_ch_data++) = *(keyboard_win_h->pnum_data_head+num+2);
		EDIT_SetText(WM_GetDialogItem(pMsg->hWin, (0x800+1)),keyboard_win_h->res_ch_data_head);
		
		keyboard_win_h->pnum_data = keyboard_win_h->pnum_data_head;
		for(j=0;j<28;j++)
		{
		*(keyboard_win_h->pnum_data++) = '\0';	
		}
		keyboard_win_h->pnum_data = keyboard_win_h->pnum_data_head;
		EDIT_SetText(WM_GetDialogItem(pMsg->hWin, (0x800+3)),keyboard_win_h->pnum_data_head);

		for(j=0;(keyboard_win_h->pdata) != (keyboard_win_h->pdata_head);j++)
		{
		*(keyboard_win_h->pdata--) = '\0';
		}
		*(keyboard_win_h->pdata) ='\0';
		TEXT_SetText(WM_GetDialogItem(pMsg->hWin, (0x800+2)),keyboard_win_h->pdata_head);

	}else if(keyboard_win_h->work_state != CHINESE){

		*(keyboard_win_h->res_ch_data++) = WM_GetId(pMsg->hWinSrc) + (48 - (0x800+4));
		EDIT_SetText(WM_GetDialogItem(pMsg->hWin, (0x800+1)),keyboard_win_h->res_ch_data_head);
	
	}
}

void ID_DT(WM_MESSAGE * pMsg)
{
	*(keyboard_win_h->res_ch_data++) = WM_GetId(pMsg->hWinSrc) + (46- (0x800+43));
	EDIT_SetText(WM_GetDialogItem(pMsg->hWin, (0x800+1)),keyboard_win_h->res_ch_data_head);
}


void OnCancleCliked(WM_MESSAGE *pMsg)
{
	int i;
	keyboard_win_h->res_ch_data = keyboard_win_h->res_ch_data_head;
	for(i=0; i<60;i++)
	{
	 *(keyboard_win_h->res_ch_data++) = '\0';
	}
	keyboard_win_h->res_ch_data = keyboard_win_h->res_ch_data_head;
	GUI_EndDialog(pMsg->hWin, 0);
}

void ID_KEY_ENTER(WM_MESSAGE *pMsg)
{
	
	GUI_EndDialog(pMsg->hWin, 0);
}


void Show_Work_State(WM_MESSAGE *pMsg)
{

	
	
	
	
	
	
	if(keyboard_win_h->work_state == ENGLISH_S)
	{
	BUTTON_SetText(WM_GetDialogItem(pMsg->hWin, (0x800+53)), "en");
	}else if(keyboard_win_h->work_state == ENGLISH_B)
	{
	BUTTON_SetText(WM_GetDialogItem(pMsg->hWin, (0x800+53)), "EN");
	}else if(keyboard_win_h->work_state == CHINESE)
	{
	BUTTON_SetText(WM_GetDialogItem(pMsg->hWin, (0x800+53)), "CH");
	}else if(keyboard_win_h->work_state == SFLOAT){
	
	BUTTON_SetText(WM_GetDialogItem(pMsg->hWin, (0x800+53)), "FL");
	}

	
	
	
	
	

}


void ID_Key_CN(WM_MESSAGE * pMsg)
{
	if(keyboard_win_h->work_state == CHINESE)
	{
		keyboard_win_h->work_state = ENGLISH_S;

	}else {
		keyboard_win_h->work_state++;
	}
	
	Show_Work_State(pMsg);
}


void ID_key_S4(WM_MESSAGE *pMsg)
{
	int i,j,k;
	
	k = 0;
    
	if(keyboard_win_h->work_state == CHINESE)
	{ 
		if(keyboard_win_h->pch_data > keyboard_win_h->pch_data_head)
		{
	keyboard_win_h->pdata--;
		}

	*(keyboard_win_h->pdata) ='\0';
	
	ch_dat = PYSearch(keyboard_win_h->pdata_head , &(keyboard_win_h->num_ch));
	if(ch_dat == '\0')
	{
		keyboard_win_h->num_ch = 0;
		
		
	}
	keyboard_win_h->pch_data_head = ch_dat;

	keyboard_win_h->pch_data_end = keyboard_win_h->pch_data_head + 2*(keyboard_win_h->num_ch);

	keyboard_win_h->pch_data = ch_dat;

	keyboard_win_h->pnum_data = keyboard_win_h->pnum_data_head;
	
	if(keyboard_win_h->num_ch > 0)
	{
		if(keyboard_win_h->pch_data_end - keyboard_win_h->pch_data > 14)
		{
			k = 7;
		}else{
		
			k = (keyboard_win_h->pch_data_end - keyboard_win_h->pch_data)/2;
		}
			
		for(j= 0; j<k; j++)
		{
			*(keyboard_win_h->pnum_data++) = j+'1';

			*(keyboard_win_h->pnum_data++) = *(keyboard_win_h->pch_data++);

			*(keyboard_win_h->pnum_data++) = *(keyboard_win_h->pch_data++); 
			
			*(keyboard_win_h->pnum_data++) = ' ';
		}

			if(k<7)
		{
			for(j=0; j<4*(7-k);j++)
			{
			*(keyboard_win_h->pnum_data++) = '\0';
			}
		
		
		
		
		}
	}else{
		for(j=0; j<28;j++)
			{
			*(keyboard_win_h->pnum_data++) = '\0';
			}
	}

	TEXT_SetText(WM_GetDialogItem(pMsg->hWin, (0x800+2)),keyboard_win_h->pdata_head);
	
	EDIT_SetText(WM_GetDialogItem(pMsg->hWin, (0x800+3)),keyboard_win_h->pnum_data_head);

	}else{
	
	keyboard_win_h->res_ch_data--;
	*(keyboard_win_h->res_ch_data--) = '\0';
	EDIT_SetText(WM_GetDialogItem(pMsg->hWin, (0x800+1)),keyboard_win_h->res_ch_data_head);

	}
}


void ID_KEY_BU(WM_MESSAGE *pMsg)
{
	if(keyboard_win_h->work_state == CHINESE)
	{
		
	 if(keyboard_win_h->res_ch_data != keyboard_win_h->res_ch_data_end)
	 {
		keyboard_win_h->res_ch_data--;
		*(keyboard_win_h->res_ch_data--)='\0';
		*(keyboard_win_h->res_ch_data) ='\0';
	 }	
	
	}else{
	if(keyboard_win_h->res_ch_data != keyboard_win_h->res_ch_data_end)
	 {
		keyboard_win_h->res_ch_data--;
		*(keyboard_win_h->res_ch_data) ='\0';
	 }	
	
	}
	EDIT_SetText(WM_GetDialogItem(pMsg->hWin, (0x800+1)),keyboard_win_h->res_ch_data_head);

}


void OnxxxClicked(pMsg)
{
		
   
}


void KeyBoard_Win_Init(void)
{
	int i;
	
	keyboard_win_h->pdata = data;
	keyboard_win_h->pdata_head = data;
	keyboard_win_h->pdata_end = keyboard_win_h->pdata_head + 20;
	keyboard_win_h->pch_data = ch_data;
	keyboard_win_h->pch_data_head = ch_data;
	keyboard_win_h->pch_data_end = keyboard_win_h->pch_data_head + 120;

	keyboard_win_h->pnum_data_head = num_add_ch;
	keyboard_win_h->pnum_data = num_add_ch;

	keyboard_win_h->res_ch_data_head = res_ch;
	keyboard_win_h->res_ch_data = res_ch;

	for(i=0;i<20;i++)
		data[i] = '\0';

	for(i=0;i<60;i++)
		res_ch[i]='\0';

}













 






















































 



static const GUI_WIDGET_CREATE_INFO _aDialogCreate_Key[] = {
    { FRAMEWIN_CreateIndirect,  "KEY_BOARD",         0,                       0,  0,  472,354,0,0},
    { EDIT_CreateIndirect,       0,               (0x800+1),        8,  11, 298,21, 0,30},
    { TEXT_CreateIndirect,      "TEXT0",             (0x800+2),          8,  35, 48, 16, 0,0},
    { BUTTON_CreateIndirect,    "1",                 (0x800+5),     7,  105,37, 37, 0,0},
    { BUTTON_CreateIndirect,    "2",                 (0x800+6),     53, 105,37, 37, 0,0},
    { BUTTON_CreateIndirect,    "3",                 (0x800+7),     99, 105,37, 37, 0,0},
    { BUTTON_CreateIndirect,    "4",                 (0x800+8),     145,105,37, 37, 0,0},
    { BUTTON_CreateIndirect,    "5",                 (0x800+9),     191,105,37, 37, 0,0},
    { BUTTON_CreateIndirect,    "6",                 (0x800+10),     237,105,37, 37, 0,0},
    { BUTTON_CreateIndirect,    "7",                 (0x800+11),     283,105,37, 37, 0,0},
    { BUTTON_CreateIndirect,    "8",                 (0x800+12),     329,105,37, 37, 0,0},
    { BUTTON_CreateIndirect,    "9",                 (0x800+13),     375,105,37, 37, 0,0},
    { BUTTON_CreateIndirect,    "0",                 (0x800+4),     421,105,37, 37, 0,0},
    { BUTTON_CreateIndirect,    "<",                 (0x800+14),     260,57, 58, 28, 0,0},
    { BUTTON_CreateIndirect,    ">",                 (0x800+15),     329,57, 64, 28, 0,0},
    { BUTTON_CreateIndirect,    "q",                 (0x800+32),     8,  151,37, 37, 0,0},
    { BUTTON_CreateIndirect,    "w",                 (0x800+38),     53, 151,37, 37, 0,0},
    { BUTTON_CreateIndirect,    "e",                 (0x800+20),     99, 151,37, 37, 0,0},
    { BUTTON_CreateIndirect,    "r",                 (0x800+33),     145,151,37, 37, 0,0},
    { BUTTON_CreateIndirect,    "t",                 (0x800+35),     192,151,37, 37, 0,0},
    { BUTTON_CreateIndirect,    "y",                 (0x800+40),     237,151,37, 37, 0,0},
    { BUTTON_CreateIndirect,    "u",                 (0x800+36),     283,151,37, 37, 0,0},
    { BUTTON_CreateIndirect,    "i",                 (0x800+24),     329,151,37, 37, 0,0},
    { BUTTON_CreateIndirect,    "o",                 (0x800+30),     375,151,37, 37, 0,0},
    { BUTTON_CreateIndirect,    "p",                 (0x800+31),     421,151,37, 37, 0,0},
    { BUTTON_CreateIndirect,    "a",                 (0x800+16),     7,  197,37, 37, 0,0},
    { BUTTON_CreateIndirect,    "s",                 (0x800+34),     53, 197,37, 37, 0,0},
    { BUTTON_CreateIndirect,    "d",                 (0x800+19),     99, 199,37, 37, 0,0},
    { BUTTON_CreateIndirect,    "f",                 (0x800+21),     145,197,37, 37, 0,0},
    { BUTTON_CreateIndirect,    "g",                 (0x800+22),     191,197,37, 37, 0,0},
    { BUTTON_CreateIndirect,    "h",                 (0x800+23),     237,197,37, 37, 0,0},
    { BUTTON_CreateIndirect,    "j",                 (0x800+25),     283,197,37, 37, 0,0},
    { BUTTON_CreateIndirect,    "k",                 (0x800+26),     329,197,37, 37, 0,0},
    { BUTTON_CreateIndirect,    "l",                 (0x800+27),     375,197,37, 37, 0,0},
    { BUTTON_CreateIndirect,    "CN",                (0x800+53),     421,197,40, 86, 0,0},
    { BUTTON_CreateIndirect,    "z",                 (0x800+41),     7,  243,37, 37, 0,0},
    { BUTTON_CreateIndirect,    "x",                 (0x800+39),     53, 243,37, 37, 0,0},
    { BUTTON_CreateIndirect,    "c",                 (0x800+18),     99, 243,37, 37, 0,0},
    { BUTTON_CreateIndirect,    "v",                 (0x800+37),     145,243,37, 37, 0,0},
    { BUTTON_CreateIndirect,    "b",                 (0x800+17),     191,243,37, 37, 0,0},
    { BUTTON_CreateIndirect,    "n",                 (0x800+29),     237,243,37, 37, 0,0},
    { BUTTON_CreateIndirect,    "m",                 (0x800+28),     283,243,37, 37, 0,0},
    { BUTTON_CreateIndirect,    ".",                 (0x800+43),    329,243,37, 37, 0,0},
    { BUTTON_CreateIndirect,    "BUTTON",            (0x800+44),    375,243,37, 37, 0,0},
	{ BUTTON_CreateIndirect,  "<Del",                (0x800+45),    421,2, 37, 37, 0,0},
	{ BUTTON_CreateIndirect,    "BUTTON",            (0x800+46),    8,  287,37, 37, 0,0},
    { BUTTON_CreateIndirect,    "BUTTON",            (0x800+47),    53, 287,37, 37, 0,0},
    { BUTTON_CreateIndirect,    "enter",             (0x800+48),   99, 291,160,36, 0,0},
    { BUTTON_CreateIndirect,    "cancel",            (0x800+49),   265,291,196,36, 0,0},
    { BUTTON_CreateIndirect,    "<Del",            (0x800+50),    421,53, 37, 37, 0,0},


    { EDIT_CreateIndirect,       0,               (0x800+3),          8,  54, 234,31, 0,30}
};









 

void PaintDialog_Key(WM_MESSAGE * pMsg)
{
    GUI_HWIN hWin = pMsg->hWin;

}







 

void InitDialog_Key(WM_MESSAGE * pMsg)
{
	int i;
    GUI_HWIN hWin = pMsg->hWin;
    
    
    
    FRAMEWIN_SetFont(hWin,&GUI_FontHZ_SongTi_16);
    
    
    
    
    TEXT_SetFont(WM_GetDialogItem(hWin,(0x800+2)),&GUI_Font16_ASCII);
    
    
    
	if(keyboard_win_h->work_state != CHINESE)
	{
	 EDIT_SetFont(WM_GetDialogItem(hWin,(0x800+3)),&GUI_Font16_ASCII);	
	}else{
    EDIT_SetFont(WM_GetDialogItem(hWin,(0x800+3)),&GUI_FontHZ_SongTi_16);
	}

	EDIT_SetFont(WM_GetDialogItem(hWin,(0x800+1)),&GUI_FontHZ_SongTi_16);
    
    
    
    BUTTON_SetFont(WM_GetDialogItem(hWin,(0x800+53)),&GUI_Font10_1);
    BUTTON_SetTextAlign(WM_GetDialogItem(hWin,(0x800+53)),(0<<2)|(2<<0));
    
    
    
    BUTTON_SetFont(WM_GetDialogItem(hWin,(0x800+45)),&GUI_Font10_ASCII);
	


	
	Show_Work_State(pMsg);
}







 
static void _cbCallback_Key(WM_MESSAGE * pMsg) 
{
    int NCode, Id;
    GUI_HWIN hWin = pMsg->hWin;
    switch (pMsg->MsgId) 
    {
        case 0x000F:
            PaintDialog_Key(pMsg);
            break;
        case 29:
            InitDialog_Key(pMsg);
            break;
        case 14:
            switch (((WM_KEY_INFO*)(pMsg->Data.p))->Key) 
            {
                case 27:
                    GUI_EndDialog(hWin, 1);
                    break;
                case 13:
                    GUI_EndDialog(hWin, 0);
                    break;
            }
            break;
        case 38:
            Id = WM_GetId(pMsg->hWinSrc); 
            NCode = pMsg->Data.v;
			
			 
				if((Id >= (0x800+16))&&(Id <= (0x800+41)))
				{
					if(NCode == 1)
					{
					ID_A_Z(pMsg);
					break;
					}
				}else if((Id >= (0x800+4))&&(Id <= (0x800+13))){
					if(NCode == 1)
					{
					ID_1_0(pMsg);
					break;
					}
				}
			else
			{
				switch (Id) 
				{
                case 1:
                    if(NCode==1)
                        GUI_EndDialog(hWin, 0);
                    break;
                case 2:
                    if(NCode==1)
                        GUI_EndDialog(hWin, 0);
                    break;
				case (0x800+49):
                    switch(NCode)
                    {
                        case 1:
							
							OnCancleCliked(pMsg);
                            
                            break;
                    }
			   
				case (0x800+53):
					switch(NCode)
					{
						case 1:
							ID_Key_CN(pMsg);
							break;	
					}
					break;

				case (0x800+15):
					switch(NCode)
					{
						case 1:
							ID_key_R(pMsg);
						break;
					}
					break;

				case (0x800+14):
					switch(NCode)
					{
						case 1:
						ID_key_L(pMsg);
						break;
					}
                    break;
				
				case (0x800+50):
					switch(NCode)
					{
						case 1:
						ID_key_S4(pMsg);
						break;
					
					}
					break;
				case (0x800+43):
					switch(NCode)
					{
					case 1:
					ID_DT(pMsg);
					break;
					}
					break;

				case (0x800+45):
					switch(NCode)
					{
						case 1:
						ID_KEY_BU(pMsg);
						break;
					}
					break;

					case  (0x800+48):
					switch(NCode)
					{
						case 1:
						ID_KEY_ENTER(pMsg);
						break;
					}
					break;
				}
			}
            break;
        default:
            WM_DefaultProc(pMsg);
    }
}







 
void KeyBoard_Win(TKeyBoard_H* keyboard_h) 
{ 



	keyboard_win_h = keyboard_h;
	
    WM_SetDesktopColor(0xFFFFFF);     
    WM_SetCreateFlags((1<<2));   
	KeyBoard_Win_Init();
    
    
    
    
    
    
    
    
    
    
    GUI_ExecDialogBox(_aDialogCreate_Key, (sizeof(_aDialogCreate_Key) / sizeof(_aDialogCreate_Key[0])), &_cbCallback_Key, 0, 200, 50);

}

