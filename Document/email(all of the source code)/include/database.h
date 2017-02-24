#ifndef _DATABASE_H
#define _DATABASE_H

#define _DEBUG_
#define N 5000
#define M 20

char sql[N];
int count;
struct user_type
{
	char uname[18];
	char upsw[18];
	char utel[18];
};
struct message_type
{
	//int no;	
	char sender[18];
	char receiver[50];
	char mtime[30];
	wchar_t mtitle[30];
	wchar_t mtext[1000];
};


#endif
