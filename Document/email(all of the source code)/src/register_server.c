#include"head.h"
#include"server.h"
#include"database.h"



int regist(struct user_type reg)
{		
	//regist a new user
	sqlite3 *db = NULL;
	int rc = sqlite3_open("../bin/try.db", &db);//open
	char** azResult;
	int nrow = 0, ncolumn = 0, i = 0;
	char* zErrMsg = 0;//debug
	char ctime[30];
	gettime(&ctime);
	//printf("%s\n",ctime);
	strcpy(sql,"SELECT uname FROM user_table");
	sqlite3_get_table(db, sql, &azResult, &nrow, &ncolumn, &zErrMsg);
	printf("nrow=%d, ncolumn=%d\n",nrow,ncolumn);
	
	for(i=1; i<((nrow+1)*ncolumn); i++)
	{
		printf("azResult[%d]=%s ,reg.uname=%s\n",i,azResult[i],reg.uname);
		if(strcmp(azResult[i],reg.uname) == 0)
		{
			printf("The username has been used!\n");
			printf("return 111111");
			return 1;
		}
	}
	
	sprintf(sql, "INSERT INTO user_table VALUES('%s','%s','%s','%s');",reg.uname,reg.upsw,reg.utel,ctime);	
	sqlite3_exec(db, sql, 0, 0, &zErrMsg);
#ifdef _DEBUG_
  printf ("zErrMsg = %s \n", zErrMsg);
#endif
	
	printf("Welcome to mememail!\n");		

	sqlite3_close (db);
	printf("return 0000\n");	
	return 0;
}


void register_fun(MSG msg,int temp_sock_descriptor)
{
	printf("welcome to the register_thread.\n");

	int rc;
	char flag;
	int n;

	
	struct user_type user;//char uname[18]; char upsw[18]; char utel[12];


	strcpy(user.uname,msg.uname);
	strcpy(user.upsw,msg.upsw);
	strcpy(user.utel,msg.utel);
	
	switch(regist(user))
	{
		case 0://ok
		{
			flag = 'y';
			if(send(temp_sock_descriptor,&flag,sizeof(flag),0) < 0)
			{
				perror("can not send flag!\n");
				exit(0);
			}			
			break;
		}
		default://uname can not be used
		{
			flag = 'n';
			if(send(temp_sock_descriptor,&flag,sizeof(flag),0) < 0)
			{
				perror("can not send flag!\n");
				exit(0);
			}
			break;
		}
	}
	
	return ;
/*	flag = 'n';
	while(1)
	{
		n = recv(temp_sock_descriptor, user.uname, 20, 0);	//receive
		if(n < 0)
		{
		    printf("cannnot receive username \n");
		    exit(EXIT_FAILURE);
		}
		printf("user name %s\n",user.uname);
		switch(1)
		{
			case 1:
			{
				printf("the user name can be used \n");
				flag = 'y';
				if(send(temp_sock_descriptor, &flag, 1, 0)==-1)	//send
				{
					perror("can not send flag\n");
					close(temp_sock_descriptor);
					exit(1);
				}
				break;
			}
			default:
			{
				;
			}
		}
		if(flag == 'y') break;
	}

	
	
	n = recv(temp_sock_descriptor, user.upsw, 18, 0);	//receive
	if(n < 0)
	{
		printf("cannnot receive password \n");
		exit(EXIT_FAILURE);
	}
	printf("password is %s\n",user.upsw);
	
	n = recv(temp_sock_descriptor, user.utel, 12, 0);	//receive
	if(n < 0)
	{
	    printf("cannnot receive tel number \n");
	    exit(EXIT_FAILURE);
	}
	printf("tel is %s\n",user.utel);
	
	
	printf("register_server_pthread is over!\n");
	pthread_exit("ok!");
*/
}
