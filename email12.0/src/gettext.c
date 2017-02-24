#include <stdio.h>
#include <sys/types.h>  
#include <sys/socket.h>  
#include <netinet/in.h>  
#include <arpa/inet.h>
#include <string.h>
#include <stdlib.h>
#include "gettext.h"
#include "ipadd.h"
#define BUFFER_SIZE 1024
extern char bigbuf[4096];
extern char text_add[2048];
extern char add_name[200];

void gettext(char* textnum)
{       
        int regfd,len;
 	struct sockaddr_in serve_addr;
 	memset(&serve_addr,0,sizeof(serve_addr));
 	serve_addr.sin_family=AF_INET;
 	serve_addr.sin_addr.s_addr=inet_addr(IP);
 	serve_addr.sin_port=htons(6666);
 	if((regfd=socket(AF_INET,SOCK_STREAM,0))<0)
	{
 		perror("socket"); 
 		return ; 
	}
 	if(connect(regfd,(struct sockaddr *)&serve_addr,sizeof(struct   sockaddr))<0)
 	{
  		perror("connect"); 
  		return ;
 	}
        char  buf[40];//char *buf=(char*)malloc(size_Info) ,error
       //receive connect server waring:welcome to my server
        len=recv(regfd,buf,21,0);//receive 1th from server
        buf[len]='\0';
        printf("%s\n",buf);
        send(regfd,"ct",2,0);// send 1 th to server
        //send textnum
        send(regfd,textnum,20,0);
        memset(bigbuf,0,4096);
        len=recv(regfd,bigbuf,4000,0);//receive text
	recv(regfd,add_name,200,0);
	printf("%s\n",add_name);
	recv(regfd,text_add,2048,0);
	
        printf("receive finished !\n");
       
       // printf("topic: %s\nkind: %s\nsender: %s\n",pioe[count].topic,pioe[count].kind,pioe[count].sender);
       
        close(regfd);

}
