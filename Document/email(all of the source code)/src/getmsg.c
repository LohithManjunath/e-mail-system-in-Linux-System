#include "head.h"
#include "gv.h"

void getmsg(int num, int no, char *stat, void *p)
{
	do_connect();		//connect the server 
	MSG a;
	memset(&a, 0, sizeof(a));
	a.num = num;
	a.no = no; printf("before strcpy\n");
	strcpy(a.stat, stat);printf("after strcpy\n");

	printf("num: %d    no: %d\n", num, no);
	bzero(buff,sizeof(buff));
	memcpy(buff,&a,sizeof(a));

    	if(send(socket_descriptor, buff, sizeof(a), 0)==-1)
    	{
		perror("can not send message\n");
		exit(1);
  	}
	
	MSG rmsg;
	bzero(buff,sizeof(buff));
	memset(&rmsg, 0, sizeof(rmsg));

	if(recv(socket_descriptor,&buff,sizeof(rmsg),0) < 0)
	{
		perror("the client can not receive the flag from the server!\n");
		exit(1);
	}
		
	memcpy(&rmsg, buff, sizeof(MSG));                           printf("getmsg text :%s\n", rmsg.mtext);

	MSG *k;
	k = (MSG *)p;
	
	k->num = rmsg.num;
	k->no = rmsg.no;

	strcpy(k->uname, rmsg.uname);
	strcpy(k->upsw, rmsg.upsw);
	strcpy(k->utel, rmsg.utel);
	strcpy(k->sender, rmsg.sender);
	strcpy(k->receiver, rmsg.receiver);
	strcpy(k->mtime, rmsg.mtime);
	strcpy(k->mtitle, rmsg.mtitle);
	strcpy(k->mtext, rmsg.mtext);
	
	close(socket_descriptor);
}
