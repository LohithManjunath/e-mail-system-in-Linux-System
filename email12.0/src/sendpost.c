#include "sendpost.h"
#include <stdio.h>
#include <sys/types.h>  
#include <sys/socket.h>  
#include <netinet/in.h>  
#include <arpa/inet.h>
#include <string.h>
#include <stdlib.h>
#include "ipadd.h"
extern char name[20];
typedef struct email
{
	char topic[50];
	char kind[10];
	char sender[20];
	char reciever[200];
	char time[20];
	char text[2048];//
	char info[50];
}Email;

void sendpost(char *_topic, char *_kind , char *file_name, char *_reciever, char *_time, char *_text, char *_info)
{
	int regfd,n;
 	char ch[1024];
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
 	Email *myemail=(Email*)malloc(sizeof(Email));
 	strcpy(myemail->topic,_topic);
 	strcpy(myemail->kind,_kind);
	strcpy(myemail->sender,name);
	strcpy(myemail->reciever,_reciever);
	strcpy(myemail->time,_time);
	strcpy(myemail->text,_text);
	strcpy(myemail->info,_info);
 	int size_Email=sizeof(Email);
        send(regfd,"ss",2,0);
 	char *buf=(char*)malloc(size_Email);
 	memcpy(buf,myemail,size_Email);
 	int len=0;
 	int pos=0;
  	while(pos<size_Email) 
  	{
  		len=send(regfd,buf+pos,size_Email,0);  
  		if(len<0)
  		{perror("data  send error \n");break;}
  		pos+=len;
  	}
	char filename[20]={0};
	int flenth;
	int filen = 0;
	for(flenth=strlen(file_name);flenth>0;flenth--)
	{	
		if(file_name[flenth] !='/')
		filen ++;
		if(file_name[flenth] == '/')
		break;
		
	}
	printf("filen=%d\n",filen);
	filename[filen]='\0';
	for(flenth=strlen(file_name);;flenth--)
	{	
		if(file_name[flenth] !='/')
		{
		filename[filen-1] = file_name[flenth];
		filen --;
		}
		if(file_name[flenth-1] == '/')
		break;
	}
	send(regfd,filename,20,0);
	FILE * fp = fopen(file_name,"rb");
        if(NULL == fp )
        {
            printf("File:\t%s Not Found\n", file_name);
        }
        else
        {
            char file_txt[2048] = {0};
            int file_block_length = 0;
//            while( (file_block_length = read(fp,buffer,BUFFER_SIZE))>0)
            while( (file_block_length = fread(file_txt,sizeof(char),sizeof(file_txt),fp))>0)
            {
                printf("file_block_length = %d\n",file_block_length);
                //发送buffer中的字符串到new_server_socket,实际是给客户端
                if(send(regfd,file_txt,file_block_length,0)<0)
                {
                    printf("Send File:\t%s Failed\n", file_name);
                    break;
                }
                bzero(file_txt, sizeof(file_txt));
            }
//            close(fp);
            fclose(fp);
	  bzero(file_name,sizeof(file_name));
	}
 //judge it is to check
  //
 // receive success register warning 
  	free(buf);
  	free(myemail);
	printf("sendpost.c  aaaaaa\n");
 	close(regfd);
}

