#include "head.h"
#include "gv.h"

void getmailbox(MSG m, int client_num, void *p)
{
	do_connect();		//connect the server 
	MSG a;
	memset(&a, 0, sizeof(a));
	a.num = m.num;
	a.client_num = client_num;
	strcpy(a.sortkey, m.sortkey);
	bzero(buff,sizeof(buff));
	memcpy(buff,&a,sizeof(a));

    	if(send(socket_descriptor, buff, sizeof(a), 0)==-1)
    	{
		perror("can not send message\n");
		exit(1);
  	}
	
	MAILBOX box;
	bzero(buff,sizeof(buff));
	memset(&box, 0, sizeof(box));

	if(recv(socket_descriptor,&buff,sizeof(box),0) < 0)
	{
		perror("the client can not receive the flag from the server!\n");
		exit(1);
	}
		
	memcpy(&box, buff, sizeof(MAILBOX));

	MAILBOX *k;
	k = (MAILBOX *)p;
	
	k->mailnum = box.mailnum;
	int i;
	for (i = 0; i < box.mailnum; i++)
	{
		k->no[i] = box.no[i];
		strcpy(k->title[i], box.title[i]);
		strcpy(k->receiver[i], box.receiver[i]);
		strcpy(k->sender[i], box.sender[i]);
		strcpy(k->rmstat[i], box.rmstat[i]);
		strcpy(k->time[i], box.time[i]);
		strcpy(k->database_flag[i], box.database_flag[i]);
	}
	close(socket_descriptor);
}
