#ifndef _HEAD_H
#define _HEAD_H

#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<netdb.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/time.h>
#include<pthread.h> 
#include"sqlite3.h"
#include<sys/stat.h>
#include<fcntl.h>
#include<time.h>
#include<wchar.h>
#define U_MSG 15
typedef struct msg		//data bag
{
	int num;
	int no;
	int client_num;	
	char sortkey[30];
	char database_flag;
	char stat[2];
	char uname[18];
	char upsw[18];
	char utel[12];
	char sender[18];
	char receiver[200];
	char mtime[30];
	wchar_t mtitle[30];
	wchar_t mtext[1000];
}MSG;

typedef struct mailbox 
{
	int mailnum;
	char receiver[100][18];
	wchar_t title[100][30];
	char time[100][30];
	char sender[100][18];
	int no[100];
	char rmstat[100][2];
	char database_flag[100][2];
}MAILBOX;

#endif
