#include"head.h"
#include"database.h"
#include"server.h"


void gettime(char* temp)
{	
	char *wday[]={"Sun","Mon","Tue","Wed","Thu","Fri","Sat"}; 
	time_t timep; 
	struct tm *p; 
	time(&timep); 
	p = gmtime(&timep); 

	sprintf(temp, "%d/%d/%d %s %02d:%02d:%02d", (1900+p->tm_year), (1+p->tm_mon), p->tm_mday, wday[p->tm_wday], p->tm_hour+8, p->tm_min, p->tm_sec); 
}
