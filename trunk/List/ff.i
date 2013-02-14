#line 1 "Source\\SDHC\\fatfs\\ff.c"




























































































 

#line 1 "Source\\SDHC\\fatfs\\ff.h"














 








#line 1 "Source\\SDHC\\fatfs\\integer.h"
 
 
 




#line 14 "Source\\SDHC\\fatfs\\integer.h"

 
typedef int				INT;
typedef unsigned int	UINT;

 
typedef char			CHAR;
typedef unsigned char	UCHAR;
typedef unsigned char	BYTE;

 
typedef short			SHORT;
typedef unsigned short	USHORT;
typedef unsigned short	WORD;
typedef unsigned short	WCHAR;

 
typedef long			LONG;
typedef unsigned long	ULONG;
typedef unsigned long	DWORD;



#line 25 "Source\\SDHC\\fatfs\\ff.h"
#line 1 "Source\\SDHC\\fatfs\\ffconf.h"







 






 




 





 









 



 



 



 



 





 































 














 




 









 





 


 







 





 




 





 












 



 










 




 


#line 26 "Source\\SDHC\\fatfs\\ff.h"







 

#line 47 "Source\\SDHC\\fatfs\\ff.h"





 

#line 66 "Source\\SDHC\\fatfs\\ff.h"
typedef char TCHAR;








 

typedef struct {
	BYTE	fs_type;		 
	BYTE	drv;			 
	BYTE	csize;			 
	BYTE	n_fats;			 
	BYTE	wflag;			 
	BYTE	fsi_flag;		 
	WORD	id;				 
	WORD	n_rootdir;		 
#line 93 "Source\\SDHC\\fatfs\\ff.h"
	DWORD	last_clust;		 
	DWORD	free_clust;		 
	DWORD	fsi_sector;		 




	DWORD	n_fatent;		 
	DWORD	fsize;			 
	DWORD	fatbase;		 
	DWORD	dirbase;		 
	DWORD	database;		 
	DWORD	winsect;		 
	BYTE	win[512];	 
} FATFS;



 

typedef struct {
	FATFS*	fs;				 
	WORD	id;				 
	BYTE	flag;			 
	BYTE	pad1;
	DWORD	fptr;			 
	DWORD	fsize;			 
	DWORD	sclust;			 
	DWORD	clust;			 
	DWORD	dsect;			 

	DWORD	dir_sect;		 
	BYTE*	dir_ptr;		 
#line 134 "Source\\SDHC\\fatfs\\ff.h"
	BYTE	buf[512];	 

} FIL;



 

typedef struct {
	FATFS*	fs;				 
	WORD	id;				 
	WORD	index;			 
	DWORD	sclust;			 
	DWORD	clust;			 
	DWORD	sect;			 
	BYTE*	dir;			 
	BYTE*	fn;				 




} DIR;



 

typedef struct {
	DWORD	fsize;			 
	WORD	fdate;			 
	WORD	ftime;			 
	BYTE	fattrib;		 
	TCHAR	fname[13];		 




} FILINFO;



 

typedef enum {
	FR_OK = 0,				 
	FR_DISK_ERR,			 
	FR_INT_ERR,				 
	FR_NOT_READY,			 
	FR_NO_FILE,				 
	FR_NO_PATH,				 
	FR_INVALID_NAME,		 
	FR_DENIED,				 
	FR_EXIST,				 
	FR_INVALID_OBJECT,		 
	FR_WRITE_PROTECTED,		 
	FR_INVALID_DRIVE,		 
	FR_NOT_ENABLED,			 
	FR_NO_FILESYSTEM,		 
	FR_MKFS_ABORTED,		 
	FR_TIMEOUT,				 
	FR_LOCKED,				 
	FR_NOT_ENOUGH_CORE,		 
	FR_TOO_MANY_OPEN_FILES,	 
	FR_INVALID_PARAMETER	 
} FRESULT;



 
 

FRESULT f_mount (BYTE, FATFS*);						 
FRESULT f_open (FIL*, const TCHAR*, BYTE);			 
FRESULT f_read (FIL*, void*, UINT, UINT*);			 
FRESULT f_lseek (FIL*, DWORD);						 
FRESULT f_close (FIL*);								 
FRESULT f_opendir (DIR*, const TCHAR*);				 
FRESULT f_readdir (DIR*, FILINFO*);					 
FRESULT f_stat (const TCHAR*, FILINFO*);			 
FRESULT f_write (FIL*, const void*, UINT, UINT*);	 
FRESULT f_getfree (const TCHAR*, DWORD*, FATFS**);	 
FRESULT f_truncate (FIL*);							 
FRESULT f_sync (FIL*);								 
FRESULT f_unlink (const TCHAR*);					 
FRESULT	f_mkdir (const TCHAR*);						 
FRESULT f_chmod (const TCHAR*, BYTE, BYTE);			 
FRESULT f_utime (const TCHAR*, const FILINFO*);		 
FRESULT f_rename (const TCHAR*, const TCHAR*);		 
FRESULT f_chdrive (BYTE);							 
FRESULT f_chdir (const TCHAR*);						 
FRESULT f_getcwd (TCHAR*, UINT);					 
FRESULT f_forward (FIL*, UINT(*)(const BYTE*,UINT), UINT, UINT*);	 
FRESULT f_mkfs (BYTE, BYTE, UINT);					 
FRESULT	f_fdisk (BYTE, const DWORD[], void*);		 
int f_putc (TCHAR, FIL*);							 
int f_puts (const TCHAR*, FIL*);					 
int f_printf (FIL*, const TCHAR*, ...);				 
TCHAR* f_gets (TCHAR*, int, FIL*);					 













 
 

 

DWORD get_fattime (void);


 
#line 262 "Source\\SDHC\\fatfs\\ff.h"

 
#line 270 "Source\\SDHC\\fatfs\\ff.h"




 
 


 





#line 292 "Source\\SDHC\\fatfs\\ff.h"


 






 

#line 311 "Source\\SDHC\\fatfs\\ff.h"


 




 
 

#line 332 "Source\\SDHC\\fatfs\\ff.h"





#line 96 "Source\\SDHC\\fatfs\\ff.c"
#line 1 "Source\\SDHC\\fatfs\\diskio.h"


 






#line 11 "Source\\SDHC\\fatfs\\diskio.h"


 
typedef BYTE	DSTATUS;

 
typedef enum {
	RES_OK = 0,		 
	RES_ERROR,		 
	RES_WRPRT,		 
	RES_NOTRDY,		 
	RES_PARERR		 
} DRESULT;


 
 

int assign_drives (int, int);
DSTATUS disk_initialize (BYTE);
DSTATUS disk_status (BYTE);
DRESULT disk_read (BYTE, BYTE*, DWORD, BYTE);

DRESULT disk_write (BYTE, const BYTE*, DWORD, BYTE);

DRESULT disk_ioctl (BYTE, BYTE, void*);



 






 

 






 




 






 




 



#line 97 "Source\\SDHC\\fatfs\\ff.c"






 






 
#line 119 "Source\\SDHC\\fatfs\\ff.c"


 
#line 132 "Source\\SDHC\\fatfs\\ff.c"




 
#line 148 "Source\\SDHC\\fatfs\\ff.c"


 




 

#line 345 "Source\\SDHC\\fatfs\\ff.c"







 




#line 372 "Source\\SDHC\\fatfs\\ff.c"







 
#line 387 "Source\\SDHC\\fatfs\\ff.c"


 
 






 

#line 436 "Source\\SDHC\\fatfs\\ff.c"

#line 456 "Source\\SDHC\\fatfs\\ff.c"


 
 
 



 


static
FATFS *FatFs[1];	 




static
WORD Fsid;				 
















#line 512 "Source\\SDHC\\fatfs\\ff.c"








 


 
 
 

 
static
void mem_cpy (void* dst, const void* src, UINT cnt) {
	BYTE *d = (BYTE*)dst;
	const BYTE *s = (const BYTE*)src;

#line 540 "Source\\SDHC\\fatfs\\ff.c"
	while (cnt--)
		*d++ = *s++;
}

 
static
void mem_set (void* dst, int val, UINT cnt) {
	BYTE *d = (BYTE*)dst;

	while (cnt--)
		*d++ = (BYTE)val;
}

 
static
int mem_cmp (const void* dst, const void* src, UINT cnt) {
	const BYTE *d = (const BYTE *)dst, *s = (const BYTE *)src;
	int r = 0;

	while (cnt-- && (r = *d++ - *s++) == 0) ;
	return r;
}

 
static
int chk_chr (const char* str, int chr) {
	while (*str && *str != chr) str++;
	return *str;
}



 
 
 
#line 600 "Source\\SDHC\\fatfs\\ff.c"



 
 
 
#line 711 "Source\\SDHC\\fatfs\\ff.c"



 
 
 

static
FRESULT move_window (
	FATFS *fs,		 
	DWORD sector	 
)					 
{
	DWORD wsect;


	wsect = fs->winsect;
	if (wsect != sector) {	 

		if (fs->wflag) {	 
			if (disk_write(fs->drv, fs->win, wsect, 1) != RES_OK)
				return FR_DISK_ERR;
			fs->wflag = 0;
			if (wsect < (fs->fatbase + fs->fsize)) {	 
				BYTE nf;
				for (nf = fs->n_fats; nf > 1; nf--) {	 
					wsect += fs->fsize;
					disk_write(fs->drv, fs->win, wsect, 1);
				}
			}
		}

		if (sector) {
			if (disk_read(fs->drv, fs->win, sector, 1) != RES_OK)
				return FR_DISK_ERR;
			fs->winsect = sector;
		}
	}

	return FR_OK;
}




 
 
 

static
FRESULT sync (	 
	FATFS *fs	 
)
{
	FRESULT res;


	res = move_window(fs, 0);
	if (res == FR_OK) {
		 
		if (fs->fs_type == 3 && fs->fsi_flag) {
			fs->winsect = 0;
			 
			mem_set(fs->win, 0, 512);
			*(BYTE*)(fs->win+510)=(BYTE)(0xAA55); *((BYTE*)(fs->win+510)+1)=(BYTE)((WORD)(0xAA55)>>8);
			*(BYTE*)(fs->win+0)=(BYTE)(0x41615252); *((BYTE*)(fs->win+0)+1)=(BYTE)((WORD)(0x41615252)>>8); *((BYTE*)(fs->win+0)+2)=(BYTE)((DWORD)(0x41615252)>>16); *((BYTE*)(fs->win+0)+3)=(BYTE)((DWORD)(0x41615252)>>24);
			*(BYTE*)(fs->win+484)=(BYTE)(0x61417272); *((BYTE*)(fs->win+484)+1)=(BYTE)((WORD)(0x61417272)>>8); *((BYTE*)(fs->win+484)+2)=(BYTE)((DWORD)(0x61417272)>>16); *((BYTE*)(fs->win+484)+3)=(BYTE)((DWORD)(0x61417272)>>24);
			*(BYTE*)(fs->win+488)=(BYTE)(fs->free_clust); *((BYTE*)(fs->win+488)+1)=(BYTE)((WORD)(fs->free_clust)>>8); *((BYTE*)(fs->win+488)+2)=(BYTE)((DWORD)(fs->free_clust)>>16); *((BYTE*)(fs->win+488)+3)=(BYTE)((DWORD)(fs->free_clust)>>24);
			*(BYTE*)(fs->win+492)=(BYTE)(fs->last_clust); *((BYTE*)(fs->win+492)+1)=(BYTE)((WORD)(fs->last_clust)>>8); *((BYTE*)(fs->win+492)+2)=(BYTE)((DWORD)(fs->last_clust)>>16); *((BYTE*)(fs->win+492)+3)=(BYTE)((DWORD)(fs->last_clust)>>24);
			 
			disk_write(fs->drv, fs->win, fs->fsi_sector, 1);
			fs->fsi_flag = 0;
		}
		 
		if (disk_ioctl(fs->drv, 0, 0) != RES_OK)
			res = FR_DISK_ERR;
	}

	return res;
}





 
 
 


DWORD clust2sect (	 
	FATFS *fs,		 
	DWORD clst		 
)
{
	clst -= 2;
	if (clst >= (fs->n_fatent - 2)) return 0;		 
	return clst * fs->csize + fs->database;
}




 
 
 


DWORD get_fat (	 
	FATFS *fs,	 
	DWORD clst	 
)
{
	UINT wc, bc;
	BYTE *p;


	if (clst < 2 || clst >= fs->n_fatent)	 
		return 1;

	switch (fs->fs_type) {
	case 1 :
		bc = (UINT)clst; bc += bc / 2;
		if (move_window(fs, fs->fatbase + (bc / 512U))) break;
		wc = fs->win[bc % 512U]; bc++;
		if (move_window(fs, fs->fatbase + (bc / 512U))) break;
		wc |= fs->win[bc % 512U] << 8;
		return (clst & 1) ? (wc >> 4) : (wc & 0xFFF);

	case 2 :
		if (move_window(fs, fs->fatbase + (clst / (512U / 2)))) break;
		p = &fs->win[clst * 2 % 512U];
		return (WORD)(((WORD)*((BYTE*)(p)+1)<<8)|(WORD)*(BYTE*)(p));

	case 3 :
		if (move_window(fs, fs->fatbase + (clst / (512U / 4)))) break;
		p = &fs->win[clst * 4 % 512U];
		return (DWORD)(((DWORD)*((BYTE*)(p)+3)<<24)|((DWORD)*((BYTE*)(p)+2)<<16)|((WORD)*((BYTE*)(p)+1)<<8)| *(BYTE*)(p)) & 0x0FFFFFFF;
	}

	return 0xFFFFFFFF;	 
}




 
 
 


FRESULT put_fat (
	FATFS *fs,	 
	DWORD clst,	 
	DWORD val	 
)
{
	UINT bc;
	BYTE *p;
	FRESULT res;


	if (clst < 2 || clst >= fs->n_fatent) {	 
		res = FR_INT_ERR;

	} else {
		switch (fs->fs_type) {
		case 1 :
			bc = clst; bc += bc / 2;
			res = move_window(fs, fs->fatbase + (bc / 512U));
			if (res != FR_OK) break;
			p = &fs->win[bc % 512U];
			*p = (clst & 1) ? ((*p & 0x0F) | ((BYTE)val << 4)) : (BYTE)val;
			bc++;
			fs->wflag = 1;
			res = move_window(fs, fs->fatbase + (bc / 512U));
			if (res != FR_OK) break;
			p = &fs->win[bc % 512U];
			*p = (clst & 1) ? (BYTE)(val >> 4) : ((*p & 0xF0) | ((BYTE)(val >> 8) & 0x0F));
			break;

		case 2 :
			res = move_window(fs, fs->fatbase + (clst / (512U / 2)));
			if (res != FR_OK) break;
			p = &fs->win[clst * 2 % 512U];
			*(BYTE*)(p)=(BYTE)((WORD)val); *((BYTE*)(p)+1)=(BYTE)((WORD)((WORD)val)>>8);
			break;

		case 3 :
			res = move_window(fs, fs->fatbase + (clst / (512U / 4)));
			if (res != FR_OK) break;
			p = &fs->win[clst * 4 % 512U];
			val |= (DWORD)(((DWORD)*((BYTE*)(p)+3)<<24)|((DWORD)*((BYTE*)(p)+2)<<16)|((WORD)*((BYTE*)(p)+1)<<8)| *(BYTE*)(p)) & 0xF0000000;
			*(BYTE*)(p)=(BYTE)(val); *((BYTE*)(p)+1)=(BYTE)((WORD)(val)>>8); *((BYTE*)(p)+2)=(BYTE)((DWORD)(val)>>16); *((BYTE*)(p)+3)=(BYTE)((DWORD)(val)>>24);
			break;

		default :
			res = FR_INT_ERR;
		}
		fs->wflag = 1;
	}

	return res;
}





 
 
 

static
FRESULT remove_chain (
	FATFS *fs,			 
	DWORD clst			 
)
{
	FRESULT res;
	DWORD nxt;




	if (clst < 2 || clst >= fs->n_fatent) {	 
		res = FR_INT_ERR;

	} else {
		res = FR_OK;
		while (clst < fs->n_fatent) {			 
			nxt = get_fat(fs, clst);			 
			if (nxt == 0) break;				 
			if (nxt == 1) { res = FR_INT_ERR; break; }	 
			if (nxt == 0xFFFFFFFF) { res = FR_DISK_ERR; break; }	 
			res = put_fat(fs, clst, 0);			 
			if (res != FR_OK) break;
			if (fs->free_clust != 0xFFFFFFFF) {	 
				fs->free_clust++;
				fs->fsi_flag = 1;
			}
#line 962 "Source\\SDHC\\fatfs\\ff.c"
			clst = nxt;	 
		}
	}

	return res;
}





 
 
 

static
DWORD create_chain (	 
	FATFS *fs,			 
	DWORD clst			 
)
{
	DWORD cs, ncl, scl;
	FRESULT res;


	if (clst == 0) {		 
		scl = fs->last_clust;			 
		if (!scl || scl >= fs->n_fatent) scl = 1;
	}
	else {					 
		cs = get_fat(fs, clst);			 
		if (cs < 2) return 1;			 
		if (cs < fs->n_fatent) return cs;	 
		scl = clst;
	}

	ncl = scl;				 
	for (;;) {
		ncl++;							 
		if (ncl >= fs->n_fatent) {		 
			ncl = 2;
			if (ncl > scl) return 0;	 
		}
		cs = get_fat(fs, ncl);			 
		if (cs == 0) break;				 
		if (cs == 0xFFFFFFFF || cs == 1) 
			return cs;
		if (ncl == scl) return 0;		 
	}

	res = put_fat(fs, ncl, 0x0FFFFFFF);	 
	if (res == FR_OK && clst != 0) {
		res = put_fat(fs, clst, ncl);	 
	}
	if (res == FR_OK) {
		fs->last_clust = ncl;			 
		if (fs->free_clust != 0xFFFFFFFF) {
			fs->free_clust--;
			fs->fsi_flag = 1;
		}
	} else {
		ncl = (res == FR_DISK_ERR) ? 0xFFFFFFFF : 1;
	}

	return ncl;		 
}




 
 
 

#line 1057 "Source\\SDHC\\fatfs\\ff.c"



 
 
 

static
FRESULT dir_sdi (
	DIR *dj,		 
	WORD idx		 
)
{
	DWORD clst;
	WORD ic;


	dj->index = idx;
	clst = dj->sclust;
	if (clst == 1 || clst >= dj->fs->n_fatent)	 
		return FR_INT_ERR;
	if (!clst && dj->fs->fs_type == 3)	 
		clst = dj->fs->dirbase;

	if (clst == 0) {	 
		dj->clust = clst;
		if (idx >= dj->fs->n_rootdir)		 
			return FR_INT_ERR;
		dj->sect = dj->fs->dirbase + idx / (512U / 32);	 
	}
	else {				 
		ic = 512U / 32 * dj->fs->csize;	 
		while (idx >= ic) {	 
			clst = get_fat(dj->fs, clst);				 
			if (clst == 0xFFFFFFFF) return FR_DISK_ERR;	 
			if (clst < 2 || clst >= dj->fs->n_fatent)	 
				return FR_INT_ERR;
			idx -= ic;
		}
		dj->clust = clst;
		dj->sect = clust2sect(dj->fs, clst) + idx / (512U / 32);	 
	}

	dj->dir = dj->fs->win + (idx % (512U / 32)) * 32;	 

	return FR_OK;	 
}




 
 
 

static
FRESULT dir_next (	 
	DIR *dj,		 
	int stretch		 
)
{
	DWORD clst;
	WORD i;


	stretch = stretch;		 
	i = dj->index + 1;
	if (!i || !dj->sect)	 
		return FR_NO_FILE;

	if (!(i % (512U / 32))) {	 
		dj->sect++;					 

		if (dj->clust == 0) {	 
			if (i >= dj->fs->n_rootdir)	 
				return FR_NO_FILE;
		}
		else {					 
			if (((i / (512U / 32)) & (dj->fs->csize - 1)) == 0) {	 
				clst = get_fat(dj->fs, dj->clust);				 
				if (clst <= 1) return FR_INT_ERR;
				if (clst == 0xFFFFFFFF) return FR_DISK_ERR;
				if (clst >= dj->fs->n_fatent) {					 

					BYTE c;
					if (!stretch) return FR_NO_FILE;			 
					clst = create_chain(dj->fs, dj->clust);		 
					if (clst == 0) return FR_DENIED;			 
					if (clst == 1) return FR_INT_ERR;
					if (clst == 0xFFFFFFFF) return FR_DISK_ERR;
					 
					if (move_window(dj->fs, 0)) return FR_DISK_ERR;	 
					mem_set(dj->fs->win, 0, 512U);			 
					dj->fs->winsect = clust2sect(dj->fs, clst);	 
					for (c = 0; c < dj->fs->csize; c++) {		 
						dj->fs->wflag = 1;
						if (move_window(dj->fs, 0)) return FR_DISK_ERR;
						dj->fs->winsect++;
					}
					dj->fs->winsect -= c;						 



				}
				dj->clust = clst;				 
				dj->sect = clust2sect(dj->fs, clst);
			}
		}
	}

	dj->index = i;
	dj->dir = dj->fs->win + (i % (512U / 32)) * 32;

	return FR_OK;
}




 
 
 
#line 1278 "Source\\SDHC\\fatfs\\ff.c"



 
 
 
#line 1324 "Source\\SDHC\\fatfs\\ff.c"




 
 
 
#line 1344 "Source\\SDHC\\fatfs\\ff.c"




 
 
 

static
FRESULT dir_find (
	DIR *dj			 
)
{
	FRESULT res;
	BYTE c, *dir;




	res = dir_sdi(dj, 0);			 
	if (res != FR_OK) return res;




	do {
		res = move_window(dj->fs, dj->sect);
		if (res != FR_OK) break;
		dir = dj->dir;					 
		c = dir[0];
		if (c == 0) { res = FR_NO_FILE; break; }	 
#line 1397 "Source\\SDHC\\fatfs\\ff.c"
		if (!(dir[11] & 0x08) && !mem_cmp(dir, dj->fn, 11))  
			break;

		res = dir_next(dj, 0);		 
	} while (res == FR_OK);

	return res;
}




 
 
 

static
FRESULT dir_read (
	DIR *dj			 
)
{
	FRESULT res;
	BYTE c, *dir;




	res = FR_NO_FILE;
	while (dj->sect) {
		res = move_window(dj->fs, dj->sect);
		if (res != FR_OK) break;
		dir = dj->dir;					 
		c = dir[0];
		if (c == 0) { res = FR_NO_FILE; break; }	 
#line 1451 "Source\\SDHC\\fatfs\\ff.c"
		if (c != 0xE5 && (0 || c != '.') && !(dir[11] & 0x08))	 
			break;

		res = dir_next(dj, 0);				 
		if (res != FR_OK) break;
	}

	if (res != FR_OK) dj->sect = 0;

	return res;
}




 
 
 

static
FRESULT dir_register (	 
	DIR *dj				 
)
{
	FRESULT res;
	BYTE c, *dir;
#line 1541 "Source\\SDHC\\fatfs\\ff.c"
	res = dir_sdi(dj, 0);
	if (res == FR_OK) {
		do {	 
			res = move_window(dj->fs, dj->sect);
			if (res != FR_OK) break;
			c = *dj->dir;
			if (c == 0xE5 || c == 0) break;	 
			res = dir_next(dj, 1);			 
		} while (res == FR_OK);
	}


	if (res == FR_OK) {		 
		res = move_window(dj->fs, dj->sect);
		if (res == FR_OK) {
			dir = dj->dir;
			mem_set(dir, 0, 32);	 
			mem_cpy(dir, dj->fn, 11);	 



			dj->fs->wflag = 1;
		}
	}

	return res;
}





 
 
 

static
FRESULT dir_remove (	 
	DIR *dj				 
)
{
	FRESULT res;
#line 1601 "Source\\SDHC\\fatfs\\ff.c"
	res = dir_sdi(dj, dj->index);
	if (res == FR_OK) {
		res = move_window(dj->fs, dj->sect);
		if (res == FR_OK) {
			*dj->dir = 0xE5;			 
			dj->fs->wflag = 1;
		}
	}


	return res;
}





 
 
 

static
FRESULT create_name (
	DIR *dj,			 
	const TCHAR **path	 
)
{




#line 1754 "Source\\SDHC\\fatfs\\ff.c"
	BYTE b, c, d, *sfn;
	UINT ni, si, i;
	const char *p;

	 
	for (p = *path; *p == '/' || *p == '\\'; p++) ;	 
	sfn = dj->fn;
	mem_set(sfn, ' ', 11);
	si = i = b = 0; ni = 8;
#line 1776 "Source\\SDHC\\fatfs\\ff.c"
	for (;;) {
		c = (BYTE)p[si++];
		if (c <= ' ' || c == '/' || c == '\\') break;	 
		if (c == '.' || i >= ni) {
			if (ni != 8 || c != '.') return FR_INVALID_NAME;
			i = 8; ni = 11;
			b <<= 2; continue;
		}
		if (c >= 0x80) {				 
			b |= 3;						 




			return FR_INVALID_NAME;


		}
		if (0) {				 
			d = (BYTE)p[si++];			 
			if (!0 || i >= ni - 1)	 
				return FR_INVALID_NAME;
			sfn[i++] = c;
			sfn[i++] = d;
		} else {						 
			if (chk_chr("\"*+,:;<=>\?[]|\x7F", c))	 
				return FR_INVALID_NAME;
			if ((((c)>= 'A')&&((c)<= 'Z'))) {			 
				b |= 2;
			} else {
				if ((((c)>= 'a')&&((c)<= 'z'))) {		 
					b |= 1; c -= 0x20;
				}
			}
			sfn[i++] = c;
		}
	}
	*path = &p[si];						 
	c = (c <= ' ') ? 0x04 : 0;		 

	if (!i) return FR_INVALID_NAME;		 
	if (sfn[0] == 0xE5) sfn[0] = 0x05;	 

	if (ni == 8) b <<= 2;
	if ((b & 0x03) == 0x01) c |= 0x10;	 
	if ((b & 0x0C) == 0x04) c |= 0x08;	 

	sfn[11] = c;		 

	return FR_OK;

}




 
 
 

static
void get_fileinfo (		 
	DIR *dj,			 
	FILINFO *fno	 	 
)
{
	UINT i;
	BYTE nt, *dir;
	TCHAR *p, c;


	p = fno->fname;
	if (dj->sect) {
		dir = dj->dir;
		nt = dir[12];		 
		for (i = 0; i < 8; i++) {	 
			c = dir[i];
			if (c == ' ') break;
			if (c == 0x05) c = (TCHAR)0xE5;
			if (0 && (nt & 0x08) && (((c)>= 'A')&&((c)<= 'Z'))) c += 0x20;
#line 1862 "Source\\SDHC\\fatfs\\ff.c"
			*p++ = c;
		}
		if (dir[8] != ' ') {		 
			*p++ = '.';
			for (i = 8; i < 11; i++) {
				c = dir[i];
				if (c == ' ') break;
				if (0 && (nt & 0x10) && (((c)>= 'A')&&((c)<= 'Z'))) c += 0x20;
#line 1876 "Source\\SDHC\\fatfs\\ff.c"
				*p++ = c;
			}
		}
		fno->fattrib = dir[11];				 
		fno->fsize = (DWORD)(((DWORD)*((BYTE*)(dir+28)+3)<<24)|((DWORD)*((BYTE*)(dir+28)+2)<<16)|((WORD)*((BYTE*)(dir+28)+1)<<8)| *(BYTE*)(dir+28));	 
		fno->fdate = (WORD)(((WORD)*((BYTE*)(dir+24)+1)<<8)|(WORD)*(BYTE*)(dir+24));		 
		fno->ftime = (WORD)(((WORD)*((BYTE*)(dir+22)+1)<<8)|(WORD)*(BYTE*)(dir+22));		 
	}
	*p = 0;		 

#line 1908 "Source\\SDHC\\fatfs\\ff.c"
}





 
 
 

static
FRESULT follow_path (	 
	DIR *dj,			 
	const TCHAR *path	 
)
{
	FRESULT res;
	BYTE *dir, ns;


#line 1935 "Source\\SDHC\\fatfs\\ff.c"
	if (*path == '/' || *path == '\\')	 
		path++;
	dj->sclust = 0;						 


	if ((UINT)*path < ' ') {			 
		res = dir_sdi(dj, 0);
		dj->dir = 0;

	} else {							 
		for (;;) {
			res = create_name(dj, &path);	 
			if (res != FR_OK) break;
			res = dir_find(dj);				 
			ns = *(dj->fn+11);
			if (res != FR_OK) {				 
				if (res != FR_NO_FILE) break;	 
				 
				if (0 && (ns & 0x20)) {	 
					dj->sclust = 0; dj->dir = 0;	 
					res = FR_OK;
					if (!(ns & 0x04)) continue;
				} else {							 
					if (!(ns & 0x04)) res = FR_NO_PATH;
				}
				break;
			}
			if (ns & 0x04) break;			 
			dir = dj->dir;						 
			if (!(dir[11] & 0x10)) {	 
				res = FR_NO_PATH; break;
			}
			dj->sclust = (((DWORD)(WORD)(((WORD)*((BYTE*)(dir+20)+1)<<8)|(WORD)*(BYTE*)(dir+20))<<16) | (WORD)(((WORD)*((BYTE*)(dir+26)+1)<<8)|(WORD)*(BYTE*)(dir+26)));
		}
	}

	return res;
}




 
 
 

static
BYTE check_fs (	 
	FATFS *fs,	 
	DWORD sect	 
)
{
	if (disk_read(fs->drv, fs->win, sect, 1) != RES_OK)	 
		return 3;
	if ((WORD)(((WORD)*((BYTE*)(&fs->win[510])+1)<<8)|(WORD)*(BYTE*)(&fs->win[510])) != 0xAA55)		 
		return 2;

	if (((DWORD)(((DWORD)*((BYTE*)(&fs->win[54])+3)<<24)|((DWORD)*((BYTE*)(&fs->win[54])+2)<<16)|((WORD)*((BYTE*)(&fs->win[54])+1)<<8)| *(BYTE*)(&fs->win[54])) & 0xFFFFFF) == 0x544146)	 
		return 0;
	if (((DWORD)(((DWORD)*((BYTE*)(&fs->win[82])+3)<<24)|((DWORD)*((BYTE*)(&fs->win[82])+2)<<16)|((WORD)*((BYTE*)(&fs->win[82])+1)<<8)| *(BYTE*)(&fs->win[82])) & 0xFFFFFF) == 0x544146)
		return 0;

	return 1;
}




 
 
 

static
FRESULT chk_mounted (	 
	const TCHAR **path,	 
	FATFS **rfs,		 
	BYTE chk_wp			 
)
{
	BYTE fmt, b, pi, *tbl;
	UINT vol;
	DSTATUS stat;
	DWORD bsect, fasize, tsect, sysect, nclst, szbfat;
	WORD nrsv;
	const TCHAR *p = *path;
	FATFS *fs;

	 
	vol = p[0] - '0';					 
	if (vol <= 9 && p[1] == ':') {		 
		p += 2; *path = p;				 
	} else {							 



		vol = 0;						 

	}

	 
	if (vol >= 1) 				 
		return FR_INVALID_DRIVE;
	*rfs = fs = FatFs[vol];				 
	if (!fs) return FR_NOT_ENABLED;		 

	;						 

	if (fs->fs_type) {					 
		stat = disk_status(fs->drv);
		if (!(stat & 0x01)) {		 
			if (!0 && chk_wp && (stat & 0x04))	 
				return FR_WRITE_PROTECTED;
			return FR_OK;				 
		}
	}

	 
	 

	fs->fs_type = 0;					 
	fs->drv = (vol);				 
	stat = disk_initialize(fs->drv);	 
	if (stat & 0x01)				 
		return FR_NOT_READY;			 
	if (!0 && chk_wp && (stat & 0x04))	 
		return FR_WRITE_PROTECTED;




	 
	fmt = check_fs(fs, bsect = 0);		 
	if (0 && !fmt) fmt = 1;	 
	if (fmt == 1) {						 
		 
		pi = 0;
		if (pi) pi--;
		tbl = &fs->win[446 + pi * 16]; 
		if (tbl[4]) {						 
			bsect = (DWORD)(((DWORD)*((BYTE*)(&tbl[8])+3)<<24)|((DWORD)*((BYTE*)(&tbl[8])+2)<<16)|((WORD)*((BYTE*)(&tbl[8])+1)<<8)| *(BYTE*)(&tbl[8]));		 
			fmt = check_fs(fs, bsect);		 
		}
	}
	if (fmt == 3) return FR_DISK_ERR;
	if (fmt) return FR_NO_FILESYSTEM;		 

	 

	if ((WORD)(((WORD)*((BYTE*)(fs->win+11)+1)<<8)|(WORD)*(BYTE*)(fs->win+11)) != 512U)		 
		return FR_NO_FILESYSTEM;

	fasize = (WORD)(((WORD)*((BYTE*)(fs->win+22)+1)<<8)|(WORD)*(BYTE*)(fs->win+22));				 
	if (!fasize) fasize = (DWORD)(((DWORD)*((BYTE*)(fs->win+36)+3)<<24)|((DWORD)*((BYTE*)(fs->win+36)+2)<<16)|((WORD)*((BYTE*)(fs->win+36)+1)<<8)| *(BYTE*)(fs->win+36));
	fs->fsize = fasize;

	fs->n_fats = b = fs->win[16];				 
	if (b != 1 && b != 2) return FR_NO_FILESYSTEM;		 
	fasize *= b;										 

	fs->csize = b = fs->win[13];			 
	if (!b || (b & (b - 1))) return FR_NO_FILESYSTEM;	 

	fs->n_rootdir = (WORD)(((WORD)*((BYTE*)(fs->win+17)+1)<<8)|(WORD)*(BYTE*)(fs->win+17));	 
	if (fs->n_rootdir % (512U / 32)) return FR_NO_FILESYSTEM;	 

	tsect = (WORD)(((WORD)*((BYTE*)(fs->win+19)+1)<<8)|(WORD)*(BYTE*)(fs->win+19));				 
	if (!tsect) tsect = (DWORD)(((DWORD)*((BYTE*)(fs->win+32)+3)<<24)|((DWORD)*((BYTE*)(fs->win+32)+2)<<16)|((WORD)*((BYTE*)(fs->win+32)+1)<<8)| *(BYTE*)(fs->win+32));

	nrsv = (WORD)(((WORD)*((BYTE*)(fs->win+14)+1)<<8)|(WORD)*(BYTE*)(fs->win+14));				 
	if (!nrsv) return FR_NO_FILESYSTEM;					 

	 
	sysect = nrsv + fasize + fs->n_rootdir / (512U / 32);	 
	if (tsect < sysect) return FR_NO_FILESYSTEM;		 
	nclst = (tsect - sysect) / fs->csize;				 
	if (!nclst) return FR_NO_FILESYSTEM;				 
	fmt = 1;
	if (nclst >= 4086) fmt = 2;
	if (nclst >= 65526) fmt = 3;

	 
	fs->n_fatent = nclst + 2;							 
	fs->database = bsect + sysect;						 
	fs->fatbase = bsect + nrsv; 						 
	if (fmt == 3) {
		if (fs->n_rootdir) return FR_NO_FILESYSTEM;		 
		fs->dirbase = (DWORD)(((DWORD)*((BYTE*)(fs->win+44)+3)<<24)|((DWORD)*((BYTE*)(fs->win+44)+2)<<16)|((WORD)*((BYTE*)(fs->win+44)+1)<<8)| *(BYTE*)(fs->win+44));	 
		szbfat = fs->n_fatent * 4;						 
	} else {
		if (!fs->n_rootdir)	return FR_NO_FILESYSTEM;	 
		fs->dirbase = fs->fatbase + fasize;				 
		szbfat = (fmt == 2) ?					 
			fs->n_fatent * 2 : fs->n_fatent * 3 / 2 + (fs->n_fatent & 1);
	}
	if (fs->fsize < (szbfat + (512U - 1)) / 512U)	 
		return FR_NO_FILESYSTEM;


	 
	fs->free_clust = 0xFFFFFFFF;
	fs->last_clust = 0;

	 
	if (fmt == 3) {
	 	fs->fsi_flag = 0;
		fs->fsi_sector = bsect + (WORD)(((WORD)*((BYTE*)(fs->win+48)+1)<<8)|(WORD)*(BYTE*)(fs->win+48));
		if (disk_read(fs->drv, fs->win, fs->fsi_sector, 1) == RES_OK &&
			(WORD)(((WORD)*((BYTE*)(fs->win+510)+1)<<8)|(WORD)*(BYTE*)(fs->win+510)) == 0xAA55 &&
			(DWORD)(((DWORD)*((BYTE*)(fs->win+0)+3)<<24)|((DWORD)*((BYTE*)(fs->win+0)+2)<<16)|((WORD)*((BYTE*)(fs->win+0)+1)<<8)| *(BYTE*)(fs->win+0)) == 0x41615252 &&
			(DWORD)(((DWORD)*((BYTE*)(fs->win+484)+3)<<24)|((DWORD)*((BYTE*)(fs->win+484)+2)<<16)|((WORD)*((BYTE*)(fs->win+484)+1)<<8)| *(BYTE*)(fs->win+484)) == 0x61417272) {
				fs->last_clust = (DWORD)(((DWORD)*((BYTE*)(fs->win+492)+3)<<24)|((DWORD)*((BYTE*)(fs->win+492)+2)<<16)|((WORD)*((BYTE*)(fs->win+492)+1)<<8)| *(BYTE*)(fs->win+492));
				fs->free_clust = (DWORD)(((DWORD)*((BYTE*)(fs->win+488)+3)<<24)|((DWORD)*((BYTE*)(fs->win+488)+2)<<16)|((WORD)*((BYTE*)(fs->win+488)+1)<<8)| *(BYTE*)(fs->win+488));
		}
	}

	fs->fs_type = fmt;		 
	fs->id = ++Fsid;		 
	fs->winsect = 0;		 
	fs->wflag = 0;
#line 2160 "Source\\SDHC\\fatfs\\ff.c"

	return FR_OK;
}




 
 
 

static
FRESULT validate (	 
	FATFS *fs,		 
	WORD id			 
)
{
	if (!fs || !fs->fs_type || fs->id != id)
		return FR_INVALID_OBJECT;

	;		 

	if (disk_status(fs->drv) & 0x01)
		return FR_NOT_READY;

	return FR_OK;
}








 



 
 
 

FRESULT f_mount (
	BYTE vol,		 
	FATFS *fs		 
)
{
	FATFS *rfs;


	if (vol >= 1)		 
		return FR_INVALID_DRIVE;
	rfs = FatFs[vol];			 

	if (rfs) {
#line 2222 "Source\\SDHC\\fatfs\\ff.c"
		rfs->fs_type = 0;		 
	}

	if (fs) {
		fs->fs_type = 0;		 



	}
	FatFs[vol] = fs;			 

	return FR_OK;
}




 
 
 

FRESULT f_open (
	FIL *fp,			 
	const TCHAR *path,	 
	BYTE mode			 
)
{
	FRESULT res;
	DIR dj;
	BYTE *dir;
	BYTE sfn[12];


	fp->fs = 0;			 


	mode &= 0x01 | 0x02 | 0x08 | 0x10 | 0x04;
	res = chk_mounted(&path, &dj.fs, (BYTE)(mode & ~0x01));




	(dj). fn = sfn;
	if (res == FR_OK)
		res = follow_path(&dj, path);	 
	dir = dj.dir;


	if (res == FR_OK) {
		if (!dir)	 
			res = FR_INVALID_NAME;




	}
	 
	if (mode & (0x08 | 0x10 | 0x04)) {
		DWORD dw, cl;

		if (res != FR_OK) {					 
			if (res == FR_NO_FILE)			 



				res = dir_register(&dj);

			mode |= 0x08;		 
			dir = dj.dir;					 
		}
		else {								 
			if (dir[11] & (0x01 | 0x10)) {	 
				res = FR_DENIED;
			} else {
				if (mode & 0x04)	 
					res = FR_EXIST;
			}
		}
		if (res == FR_OK && (mode & 0x08)) {	 
			dw = get_fattime();					 
			*(BYTE*)(dir+14)=(BYTE)(dw); *((BYTE*)(dir+14)+1)=(BYTE)((WORD)(dw)>>8); *((BYTE*)(dir+14)+2)=(BYTE)((DWORD)(dw)>>16); *((BYTE*)(dir+14)+3)=(BYTE)((DWORD)(dw)>>24);
			dir[11] = 0;					 
			*(BYTE*)(dir+28)=(BYTE)(0); *((BYTE*)(dir+28)+1)=(BYTE)((WORD)(0)>>8); *((BYTE*)(dir+28)+2)=(BYTE)((DWORD)(0)>>16); *((BYTE*)(dir+28)+3)=(BYTE)((DWORD)(0)>>24);		 
			cl = (((DWORD)(WORD)(((WORD)*((BYTE*)(dir+20)+1)<<8)|(WORD)*(BYTE*)(dir+20))<<16) | (WORD)(((WORD)*((BYTE*)(dir+26)+1)<<8)|(WORD)*(BYTE*)(dir+26)));					 
			{*(BYTE*)(dir+26)=(BYTE)(0); *((BYTE*)(dir+26)+1)=(BYTE)((WORD)(0)>>8); *(BYTE*)(dir+20)=(BYTE)((DWORD)0>>16); *((BYTE*)(dir+20)+1)=(BYTE)((WORD)((DWORD)0>>16)>>8);};					 
			dj.fs->wflag = 1;
			if (cl) {							 
				dw = dj.fs->winsect;
				res = remove_chain(dj.fs, cl);
				if (res == FR_OK) {
					dj.fs->last_clust = cl - 1;	 
					res = move_window(dj.fs, dw);
				}
			}
		}
	}
	else {	 
		if (res == FR_OK) {						 
			if (dir[11] & 0x10) {		 
				res = FR_NO_FILE;
			} else {
				if ((mode & 0x02) && (dir[11] & 0x01))  
					res = FR_DENIED;
			}
		}
	}
	if (res == FR_OK) {
		if (mode & 0x08)			 
			mode |= 0x20;
		fp->dir_sect = dj.fs->winsect;			 
		fp->dir_ptr = dir;




	}

#line 2349 "Source\\SDHC\\fatfs\\ff.c"
	;

	if (res == FR_OK) {
		fp->flag = mode;					 
		fp->sclust = (((DWORD)(WORD)(((WORD)*((BYTE*)(dir+20)+1)<<8)|(WORD)*(BYTE*)(dir+20))<<16) | (WORD)(((WORD)*((BYTE*)(dir+26)+1)<<8)|(WORD)*(BYTE*)(dir+26)));			 
		fp->fsize = (DWORD)(((DWORD)*((BYTE*)(dir+28)+3)<<24)|((DWORD)*((BYTE*)(dir+28)+2)<<16)|((WORD)*((BYTE*)(dir+28)+1)<<8)| *(BYTE*)(dir+28));	 
		fp->fptr = 0;						 
		fp->dsect = 0;



		fp->fs = dj.fs; fp->id = dj.fs->id;	 
	}

	return res;
}




 
 
 

FRESULT f_read (
	FIL *fp, 		 
	void *buff,		 
	UINT btr,		 
	UINT *br		 
)
{
	FRESULT res;
	DWORD clst, sect, remain;
	UINT rcnt, cc;
	BYTE csect, *rbuff = buff;


	*br = 0;	 

	res = validate(fp->fs, fp->id);				 
	if (res != FR_OK) return res;
	if (fp->flag & 0x80)					 
		return FR_INT_ERR;
	if (!(fp->flag & 0x01)) 					 
		return FR_DENIED;
	remain = fp->fsize - fp->fptr;
	if (btr > remain) btr = (UINT)remain;		 

	for ( ;  btr;								 
		rbuff += rcnt, fp->fptr += rcnt, *br += rcnt, btr -= rcnt) {
		if ((fp->fptr % 512U) == 0) {		 
			csect = (BYTE)(fp->fptr / 512U & (fp->fs->csize - 1));	 
			if (!csect) {						 
				if (fp->fptr == 0) {			 
					clst = fp->sclust;			 
				} else {						 





						clst = get_fat(fp->fs, fp->clust);	 
				}
				if (clst < 2) { fp->flag |= 0x80; return FR_INT_ERR; };
				if (clst == 0xFFFFFFFF) { fp->flag |= 0x80; return FR_DISK_ERR; };
				fp->clust = clst;				 
			}
			sect = clust2sect(fp->fs, fp->clust);	 
			if (!sect) { fp->flag |= 0x80; return FR_INT_ERR; };
			sect += csect;
			cc = btr / 512U;				 
			if (cc) {							 
				if (csect + cc > fp->fs->csize)	 
					cc = fp->fs->csize - csect;
				if (disk_read(fp->fs->drv, rbuff, sect, (BYTE)cc) != RES_OK)
					{ fp->flag |= 0x80; return FR_DISK_ERR; };





				if ((fp->flag & 0x40) && fp->dsect - sect < cc)
					mem_cpy(rbuff + ((fp->dsect - sect) * 512U), fp->buf, 512U);


				rcnt = 512U * cc;			 
				continue;
			}

			if (fp->dsect != sect) {			 

				if (fp->flag & 0x40) {		 
					if (disk_write(fp->fs->drv, fp->buf, fp->dsect, 1) != RES_OK)
						{ fp->flag |= 0x80; return FR_DISK_ERR; };
					fp->flag &= ~0x40;
				}

				if (disk_read(fp->fs->drv, fp->buf, sect, 1) != RES_OK)	 
					{ fp->flag |= 0x80; return FR_DISK_ERR; };
			}

			fp->dsect = sect;
		}
		rcnt = 512U - (fp->fptr % 512U);	 
		if (rcnt > btr) rcnt = btr;





		mem_cpy(rbuff, &fp->buf[fp->fptr % 512U], rcnt);	 

	}

	return FR_OK;
}





 
 
 

FRESULT f_write (
	FIL *fp,			 
	const void *buff,	 
	UINT btw,			 
	UINT *bw			 
)
{
	FRESULT res;
	DWORD clst, sect;
	UINT wcnt, cc;
	const BYTE *wbuff = buff;
	BYTE csect;


	*bw = 0;	 

	res = validate(fp->fs, fp->id);			 
	if (res != FR_OK) return res;
	if (fp->flag & 0x80)				 
		return FR_INT_ERR;
	if (!(fp->flag & 0x02))				 
		return FR_DENIED;
	if ((DWORD)(fp->fsize + btw) < fp->fsize) btw = 0;	 

	for ( ;  btw;							 
		wbuff += wcnt, fp->fptr += wcnt, *bw += wcnt, btw -= wcnt) {
		if ((fp->fptr % 512U) == 0) {	 
			csect = (BYTE)(fp->fptr / 512U & (fp->fs->csize - 1));	 
			if (!csect) {					 
				if (fp->fptr == 0) {		 
					clst = fp->sclust;		 
					if (clst == 0)			 
						fp->sclust = clst = create_chain(fp->fs, 0);	 
				} else {					 





						clst = create_chain(fp->fs, fp->clust);	 
				}
				if (clst == 0) break;		 
				if (clst == 1) { fp->flag |= 0x80; return FR_INT_ERR; };
				if (clst == 0xFFFFFFFF) { fp->flag |= 0x80; return FR_DISK_ERR; };
				fp->clust = clst;			 
			}




			if (fp->flag & 0x40) {		 
				if (disk_write(fp->fs->drv, fp->buf, fp->dsect, 1) != RES_OK)
					{ fp->flag |= 0x80; return FR_DISK_ERR; };
				fp->flag &= ~0x40;
			}

			sect = clust2sect(fp->fs, fp->clust);	 
			if (!sect) { fp->flag |= 0x80; return FR_INT_ERR; };
			sect += csect;
			cc = btw / 512U;			 
			if (cc) {						 
				if (csect + cc > fp->fs->csize)	 
					cc = fp->fs->csize - csect;
				if (disk_write(fp->fs->drv, wbuff, sect, (BYTE)cc) != RES_OK)
					{ fp->flag |= 0x80; return FR_DISK_ERR; };
#line 2545 "Source\\SDHC\\fatfs\\ff.c"
				if (fp->dsect - sect < cc) {  
					mem_cpy(fp->buf, wbuff + ((fp->dsect - sect) * 512U), 512U);
					fp->flag &= ~0x40;
				}

				wcnt = 512U * cc;		 
				continue;
			}
#line 2559 "Source\\SDHC\\fatfs\\ff.c"
			if (fp->dsect != sect) {		 
				if (fp->fptr < fp->fsize &&
					disk_read(fp->fs->drv, fp->buf, sect, 1) != RES_OK)
						{ fp->flag |= 0x80; return FR_DISK_ERR; };
			}

			fp->dsect = sect;
		}
		wcnt = 512U - (fp->fptr % 512U); 
		if (wcnt > btw) wcnt = btw;
#line 2575 "Source\\SDHC\\fatfs\\ff.c"
		mem_cpy(&fp->buf[fp->fptr % 512U], wbuff, wcnt);	 
		fp->flag |= 0x40;

	}

	if (fp->fptr > fp->fsize) fp->fsize = fp->fptr;	 
	fp->flag |= 0x20;						 

	return FR_OK;
}




 
 
 

FRESULT f_sync (
	FIL *fp		 
)
{
	FRESULT res;
	DWORD tim;
	BYTE *dir;


	res = validate(fp->fs, fp->id);		 
	if (res == FR_OK) {
		if (fp->flag & 0x20) {	 

			if (fp->flag & 0x40) {
				if (disk_write(fp->fs->drv, fp->buf, fp->dsect, 1) != RES_OK)
					return FR_DISK_ERR;
				fp->flag &= ~0x40;
			}

			 
			res = move_window(fp->fs, fp->dir_sect);
			if (res == FR_OK) {
				dir = fp->dir_ptr;
				dir[11] |= 0x20;					 
				*(BYTE*)(dir+28)=(BYTE)(fp->fsize); *((BYTE*)(dir+28)+1)=(BYTE)((WORD)(fp->fsize)>>8); *((BYTE*)(dir+28)+2)=(BYTE)((DWORD)(fp->fsize)>>16); *((BYTE*)(dir+28)+3)=(BYTE)((DWORD)(fp->fsize)>>24);		 
				{*(BYTE*)(dir+26)=(BYTE)(fp->sclust); *((BYTE*)(dir+26)+1)=(BYTE)((WORD)(fp->sclust)>>8); *(BYTE*)(dir+20)=(BYTE)((DWORD)fp->sclust>>16); *((BYTE*)(dir+20)+1)=(BYTE)((WORD)((DWORD)fp->sclust>>16)>>8);};					 
				tim = get_fattime();						 
				*(BYTE*)(dir+22)=(BYTE)(tim); *((BYTE*)(dir+22)+1)=(BYTE)((WORD)(tim)>>8); *((BYTE*)(dir+22)+2)=(BYTE)((DWORD)(tim)>>16); *((BYTE*)(dir+22)+3)=(BYTE)((DWORD)(tim)>>24);
				fp->flag &= ~0x20;
				fp->fs->wflag = 1;
				res = sync(fp->fs);
			}
		}
	}

	return res;
}






 
 
 

FRESULT f_close (
	FIL *fp		 
)
{
	FRESULT res;

#line 2653 "Source\\SDHC\\fatfs\\ff.c"
	res = f_sync(fp);		 
#line 2667 "Source\\SDHC\\fatfs\\ff.c"
	if (res == FR_OK) fp->fs = 0;	 
	return res;

}




 
 
 

#line 2796 "Source\\SDHC\\fatfs\\ff.c"




 
 
 

FRESULT f_lseek (
	FIL *fp,		 
	DWORD ofs		 
)
{
	FRESULT res;


	res = validate(fp->fs, fp->id);		 
	if (res != FR_OK) return res;
	if (fp->flag & 0x80)			 
		return FR_INT_ERR;

#line 2873 "Source\\SDHC\\fatfs\\ff.c"

	 
	{
		DWORD clst, bcs, nsect, ifptr;

		if (ofs > fp->fsize					 

			 && !(fp->flag & 0x02)

			) ofs = fp->fsize;

		ifptr = fp->fptr;
		fp->fptr = nsect = 0;
		if (ofs) {
			bcs = (DWORD)fp->fs->csize * 512U;	 
			if (ifptr > 0 &&
				(ofs - 1) / bcs >= (ifptr - 1) / bcs) {	 
				fp->fptr = (ifptr - 1) & ~(bcs - 1);	 
				ofs -= fp->fptr;
				clst = fp->clust;
			} else {									 
				clst = fp->sclust;						 

				if (clst == 0) {						 
					clst = create_chain(fp->fs, 0);
					if (clst == 1) { fp->flag |= 0x80; return FR_INT_ERR; };
					if (clst == 0xFFFFFFFF) { fp->flag |= 0x80; return FR_DISK_ERR; };
					fp->sclust = clst;
				}

				fp->clust = clst;
			}
			if (clst != 0) {
				while (ofs > bcs) {						 

					if (fp->flag & 0x02) {			 
						clst = create_chain(fp->fs, clst);	 
						if (clst == 0) {				 
							ofs = bcs; break;
						}
					} else

						clst = get_fat(fp->fs, clst);	 
					if (clst == 0xFFFFFFFF) { fp->flag |= 0x80; return FR_DISK_ERR; };
					if (clst <= 1 || clst >= fp->fs->n_fatent) { fp->flag |= 0x80; return FR_INT_ERR; };
					fp->clust = clst;
					fp->fptr += bcs;
					ofs -= bcs;
				}
				fp->fptr += ofs;
				if (ofs % 512U) {
					nsect = clust2sect(fp->fs, clst);	 
					if (!nsect) { fp->flag |= 0x80; return FR_INT_ERR; };
					nsect += ofs / 512U;
				}
			}
		}
		if (fp->fptr % 512U && nsect != fp->dsect) {	 


			if (fp->flag & 0x40) {			 
				if (disk_write(fp->fs->drv, fp->buf, fp->dsect, 1) != RES_OK)
					{ fp->flag |= 0x80; return FR_DISK_ERR; };
				fp->flag &= ~0x40;
			}

			if (disk_read(fp->fs->drv, fp->buf, nsect, 1) != RES_OK)	 
				{ fp->flag |= 0x80; return FR_DISK_ERR; };

			fp->dsect = nsect;
		}

		if (fp->fptr > fp->fsize) {			 
			fp->fsize = fp->fptr;
			fp->flag |= 0x20;
		}

	}

	return res;
}




 
 
 

FRESULT f_opendir (
	DIR *dj,			 
	const TCHAR *path	 
)
{
	FRESULT res;
	BYTE sfn[12];


	res = chk_mounted(&path, &dj->fs, 0);
	if (res == FR_OK) {
		(*dj). fn = sfn;
		res = follow_path(dj, path);			 
		;
		if (res == FR_OK) {						 
			if (dj->dir) {						 
				if (dj->dir[11] & 0x10) {	 
					dj->sclust = (((DWORD)(WORD)(((WORD)*((BYTE*)(dj->dir+20)+1)<<8)|(WORD)*(BYTE*)(dj->dir+20))<<16) | (WORD)(((WORD)*((BYTE*)(dj->dir+26)+1)<<8)|(WORD)*(BYTE*)(dj->dir+26)));
				} else {						 
					res = FR_NO_PATH;
				}
			}
			if (res == FR_OK) {
				dj->id = dj->fs->id;
				res = dir_sdi(dj, 0);			 
			}
		}
		if (res == FR_NO_FILE) res = FR_NO_PATH;
	}

	return res;
}




 
 
 

FRESULT f_readdir (
	DIR *dj,			 
	FILINFO *fno		 
)
{
	FRESULT res;
	BYTE sfn[12];


	res = validate(dj->fs, dj->id);			 
	if (res == FR_OK) {
		if (!fno) {
			res = dir_sdi(dj, 0);			 
		} else {
			(*dj). fn = sfn;
			res = dir_read(dj);				 
			if (res == FR_NO_FILE) {		 
				dj->sect = 0;
				res = FR_OK;
			}
			if (res == FR_OK) {				 
				get_fileinfo(dj, fno);		 
				res = dir_next(dj, 0);		 
				if (res == FR_NO_FILE) {
					dj->sect = 0;
					res = FR_OK;
				}
			}
			;
		}
	}

	return res;
}




 
 
 

FRESULT f_stat (
	const TCHAR *path,	 
	FILINFO *fno		 
)
{
	FRESULT res;
	DIR dj;
	BYTE sfn[12];


	res = chk_mounted(&path, &dj.fs, 0);
	if (res == FR_OK) {
		(dj). fn = sfn;
		res = follow_path(&dj, path);	 
		if (res == FR_OK) {				 
			if (dj.dir)		 
				get_fileinfo(&dj, fno);
			else			 
				res = FR_INVALID_NAME;
		}
		;
	}

	return res;
}




 
 
 

FRESULT f_getfree (
	const TCHAR *path,	 
	DWORD *nclst,		 
	FATFS **fatfs		 
)
{
	FRESULT res;
	DWORD n, clst, sect, stat;
	UINT i;
	BYTE fat, *p;


	 
	res = chk_mounted(&path, fatfs, 0);
	if (res == FR_OK) {
		 
		if ((*fatfs)->free_clust <= (*fatfs)->n_fatent - 2) {
			*nclst = (*fatfs)->free_clust;
		} else {
			 
			fat = (*fatfs)->fs_type;
			n = 0;
			if (fat == 1) {
				clst = 2;
				do {
					stat = get_fat(*fatfs, clst);
					if (stat == 0xFFFFFFFF) { res = FR_DISK_ERR; break; }
					if (stat == 1) { res = FR_INT_ERR; break; }
					if (stat == 0) n++;
				} while (++clst < (*fatfs)->n_fatent);
			} else {
				clst = (*fatfs)->n_fatent;
				sect = (*fatfs)->fatbase;
				i = 0; p = 0;
				do {
					if (!i) {
						res = move_window(*fatfs, sect++);
						if (res != FR_OK) break;
						p = (*fatfs)->win;
						i = 512U;
					}
					if (fat == 2) {
						if ((WORD)(((WORD)*((BYTE*)(p)+1)<<8)|(WORD)*(BYTE*)(p)) == 0) n++;
						p += 2; i -= 2;
					} else {
						if (((DWORD)(((DWORD)*((BYTE*)(p)+3)<<24)|((DWORD)*((BYTE*)(p)+2)<<16)|((WORD)*((BYTE*)(p)+1)<<8)| *(BYTE*)(p)) & 0x0FFFFFFF) == 0) n++;
						p += 4; i -= 4;
					}
				} while (--clst);
			}
			(*fatfs)->free_clust = n;
			if (fat == 3) (*fatfs)->fsi_flag = 1;
			*nclst = n;
		}
	}
	return res;
}




 
 
 

FRESULT f_truncate (
	FIL *fp		 
)
{
	FRESULT res;
	DWORD ncl;


	res = validate(fp->fs, fp->id);		 
	if (res == FR_OK) {
		if (fp->flag & 0x80) {			 
			res = FR_INT_ERR;
		} else {
			if (!(fp->flag & 0x02))		 
				res = FR_DENIED;
		}
	}
	if (res == FR_OK) {
		if (fp->fsize > fp->fptr) {
			fp->fsize = fp->fptr;	 
			fp->flag |= 0x20;
			if (fp->fptr == 0) {	 
				res = remove_chain(fp->fs, fp->sclust);
				fp->sclust = 0;
			} else {				 
				ncl = get_fat(fp->fs, fp->clust);
				res = FR_OK;
				if (ncl == 0xFFFFFFFF) res = FR_DISK_ERR;
				if (ncl == 1) res = FR_INT_ERR;
				if (res == FR_OK && ncl < fp->fs->n_fatent) {
					res = put_fat(fp->fs, fp->clust, 0x0FFFFFFF);
					if (res == FR_OK) res = remove_chain(fp->fs, ncl);
				}
			}
		}
		if (res != FR_OK) fp->flag |= 0x80;
	}

	return res;
}




 
 
 

FRESULT f_unlink (
	const TCHAR *path		 
)
{
	FRESULT res;
	DIR dj, sdj;
	BYTE *dir;
	DWORD dclst;
	BYTE sfn[12];


	res = chk_mounted(&path, &dj.fs, 1);
	if (res == FR_OK) {
		(dj). fn = sfn;
		res = follow_path(&dj, path);		 
		if (0 && res == FR_OK && (dj.fn[11] & 0x20))
			res = FR_INVALID_NAME;			 



		if (res == FR_OK) {					 
			dir = dj.dir;
			if (!dir) {
				res = FR_INVALID_NAME;		 
			} else {
				if (dir[11] & 0x01)
					res = FR_DENIED;		 
			}
			dclst = (((DWORD)(WORD)(((WORD)*((BYTE*)(dir+20)+1)<<8)|(WORD)*(BYTE*)(dir+20))<<16) | (WORD)(((WORD)*((BYTE*)(dir+26)+1)<<8)|(WORD)*(BYTE*)(dir+26)));
			if (res == FR_OK && (dir[11] & 0x10)) {	 
				if (dclst < 2) {
					res = FR_INT_ERR;
				} else {
					mem_cpy(&sdj, &dj, sizeof(DIR));	 
					sdj.sclust = dclst;
					res = dir_sdi(&sdj, 2);		 
					if (res == FR_OK) {
						res = dir_read(&sdj);
						if (res == FR_OK			 



						) res = FR_DENIED;
						if (res == FR_NO_FILE) res = FR_OK;	 
					}
				}
			}
			if (res == FR_OK) {
				res = dir_remove(&dj);		 
				if (res == FR_OK) {
					if (dclst)				 
						res = remove_chain(dj.fs, dclst);
					if (res == FR_OK) res = sync(dj.fs);
				}
			}
		}
		;
	}
	return res;
}




 
 
 

FRESULT f_mkdir (
	const TCHAR *path		 
)
{
	FRESULT res;
	DIR dj;
	BYTE *dir, n;
	DWORD dsc, dcl, pcl, tim = get_fattime();
	BYTE sfn[12];


	res = chk_mounted(&path, &dj.fs, 1);
	if (res == FR_OK) {
		(dj). fn = sfn;
		res = follow_path(&dj, path);			 
		if (res == FR_OK) res = FR_EXIST;		 
		if (0 && res == FR_NO_FILE && (dj.fn[11] & 0x20))
			res = FR_INVALID_NAME;
		if (res == FR_NO_FILE) {				 
			dcl = create_chain(dj.fs, 0);		 
			res = FR_OK;
			if (dcl == 0) res = FR_DENIED;		 
			if (dcl == 1) res = FR_INT_ERR;
			if (dcl == 0xFFFFFFFF) res = FR_DISK_ERR;
			if (res == FR_OK)					 
				res = move_window(dj.fs, 0);
			if (res == FR_OK) {					 
				dsc = clust2sect(dj.fs, dcl);
				dir = dj.fs->win;
				mem_set(dir, 0, 512U);
				mem_set(dir+0, ' ', 8+3);	 
				dir[0] = '.';
				dir[11] = 0x10;
				*(BYTE*)(dir+22)=(BYTE)(tim); *((BYTE*)(dir+22)+1)=(BYTE)((WORD)(tim)>>8); *((BYTE*)(dir+22)+2)=(BYTE)((DWORD)(tim)>>16); *((BYTE*)(dir+22)+3)=(BYTE)((DWORD)(tim)>>24);
				{*(BYTE*)(dir+26)=(BYTE)(dcl); *((BYTE*)(dir+26)+1)=(BYTE)((WORD)(dcl)>>8); *(BYTE*)(dir+20)=(BYTE)((DWORD)dcl>>16); *((BYTE*)(dir+20)+1)=(BYTE)((WORD)((DWORD)dcl>>16)>>8);};
				mem_cpy(dir+32, dir, 32); 	 
				dir[33] = '.'; pcl = dj.sclust;
				if (dj.fs->fs_type == 3 && pcl == dj.fs->dirbase)
					pcl = 0;
				{*(BYTE*)(dir+32+26)=(BYTE)(pcl); *((BYTE*)(dir+32+26)+1)=(BYTE)((WORD)(pcl)>>8); *(BYTE*)(dir+32+20)=(BYTE)((DWORD)pcl>>16); *((BYTE*)(dir+32+20)+1)=(BYTE)((WORD)((DWORD)pcl>>16)>>8);};
				for (n = dj.fs->csize; n; n--) {	 
					dj.fs->winsect = dsc++;
					dj.fs->wflag = 1;
					res = move_window(dj.fs, 0);
					if (res != FR_OK) break;
					mem_set(dir, 0, 512U);
				}
			}
			if (res == FR_OK) res = dir_register(&dj);	 
			if (res != FR_OK) {
				remove_chain(dj.fs, dcl);			 
			} else {
				dir = dj.dir;
				dir[11] = 0x10;				 
				*(BYTE*)(dir+22)=(BYTE)(tim); *((BYTE*)(dir+22)+1)=(BYTE)((WORD)(tim)>>8); *((BYTE*)(dir+22)+2)=(BYTE)((DWORD)(tim)>>16); *((BYTE*)(dir+22)+3)=(BYTE)((DWORD)(tim)>>24);		 
				{*(BYTE*)(dir+26)=(BYTE)(dcl); *((BYTE*)(dir+26)+1)=(BYTE)((WORD)(dcl)>>8); *(BYTE*)(dir+20)=(BYTE)((DWORD)dcl>>16); *((BYTE*)(dir+20)+1)=(BYTE)((WORD)((DWORD)dcl>>16)>>8);};					 
				dj.fs->wflag = 1;
				res = sync(dj.fs);
			}
		}
		;
	}

	return res;
}




 
 
 

FRESULT f_chmod (
	const TCHAR *path,	 
	BYTE value,			 
	BYTE mask			 
)
{
	FRESULT res;
	DIR dj;
	BYTE *dir;
	BYTE sfn[12];


	res = chk_mounted(&path, &dj.fs, 1);
	if (res == FR_OK) {
		(dj). fn = sfn;
		res = follow_path(&dj, path);		 
		;
		if (0 && res == FR_OK && (dj.fn[11] & 0x20))
			res = FR_INVALID_NAME;
		if (res == FR_OK) {
			dir = dj.dir;
			if (!dir) {						 
				res = FR_INVALID_NAME;
			} else {						 
				mask &= 0x01|0x02|0x04|0x20;	 
				dir[11] = (value & mask) | (dir[11] & (BYTE)~mask);	 
				dj.fs->wflag = 1;
				res = sync(dj.fs);
			}
		}
	}

	return res;
}




 
 
 

FRESULT f_utime (
	const TCHAR *path,	 
	const FILINFO *fno	 
)
{
	FRESULT res;
	DIR dj;
	BYTE *dir;
	BYTE sfn[12];


	res = chk_mounted(&path, &dj.fs, 1);
	if (res == FR_OK) {
		(dj). fn = sfn;
		res = follow_path(&dj, path);	 
		;
		if (0 && res == FR_OK && (dj.fn[11] & 0x20))
			res = FR_INVALID_NAME;
		if (res == FR_OK) {
			dir = dj.dir;
			if (!dir) {					 
				res = FR_INVALID_NAME;
			} else {					 
				*(BYTE*)(dir+22)=(BYTE)(fno->ftime); *((BYTE*)(dir+22)+1)=(BYTE)((WORD)(fno->ftime)>>8);
				*(BYTE*)(dir+24)=(BYTE)(fno->fdate); *((BYTE*)(dir+24)+1)=(BYTE)((WORD)(fno->fdate)>>8);
				dj.fs->wflag = 1;
				res = sync(dj.fs);
			}
		}
	}

	return res;
}




 
 
 

FRESULT f_rename (
	const TCHAR *path_old,	 
	const TCHAR *path_new	 
)
{
	FRESULT res;
	DIR djo, djn;
	BYTE buf[21], *dir;
	DWORD dw;
	BYTE sfn[12];


	res = chk_mounted(&path_old, &djo.fs, 1);
	if (res == FR_OK) {
		djn.fs = djo.fs;
		(djo). fn = sfn;
		res = follow_path(&djo, path_old);		 
		if (0 && res == FR_OK && (djo.fn[11] & 0x20))
			res = FR_INVALID_NAME;



		if (res == FR_OK) {						 
			if (!djo.dir) {						 
				res = FR_NO_FILE;
			} else {
				mem_cpy(buf, djo.dir+11, 21);		 
				mem_cpy(&djn, &djo, sizeof(DIR));		 
				res = follow_path(&djn, path_new);
				if (res == FR_OK) res = FR_EXIST;		 
				if (res == FR_NO_FILE) { 				 
 
					res = dir_register(&djn);			 
					if (res == FR_OK) {
						dir = djn.dir;					 
						mem_cpy(dir+13, buf+2, 19);
						dir[11] = buf[0] | 0x20;
						djo.fs->wflag = 1;
						if (djo.sclust != djn.sclust && (dir[11] & 0x10)) {		 
							dw = clust2sect(djn.fs, (((DWORD)(WORD)(((WORD)*((BYTE*)(dir+20)+1)<<8)|(WORD)*(BYTE*)(dir+20))<<16) | (WORD)(((WORD)*((BYTE*)(dir+26)+1)<<8)|(WORD)*(BYTE*)(dir+26))));
							if (!dw) {
								res = FR_INT_ERR;
							} else {
								res = move_window(djn.fs, dw);
								dir = djn.fs->win+32;	 
								if (res == FR_OK && dir[1] == '.') {
									dw = (djn.fs->fs_type == 3 && djn.sclust == djn.fs->dirbase) ? 0 : djn.sclust;
									{*(BYTE*)(dir+26)=(BYTE)(dw); *((BYTE*)(dir+26)+1)=(BYTE)((WORD)(dw)>>8); *(BYTE*)(dir+20)=(BYTE)((DWORD)dw>>16); *((BYTE*)(dir+20)+1)=(BYTE)((WORD)((DWORD)dw>>16)>>8);};
									djn.fs->wflag = 1;
								}
							}
						}
						if (res == FR_OK) {
							res = dir_remove(&djo);		 
							if (res == FR_OK)
								res = sync(djo.fs);
						}
					}
 
				}
			}
		}
		;
	}
	return res;
}








 
 
 
#line 3545 "Source\\SDHC\\fatfs\\ff.c"



#line 3856 "Source\\SDHC\\fatfs\\ff.c"




