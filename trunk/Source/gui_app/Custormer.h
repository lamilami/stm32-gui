#ifndef CUSTORMER_H
#define CUSTORMER_H


typedef struct
{
	char custorm[30];
	char series_no[15];
	char elevator_productor[30];
	char limitor_productor[30];
	char limitor_series[15];
	char reserve1[10];
	char reserve2[10];

}TCustormer;





void Custormer(WM_MESSAGE * pMsg);

#endif 
