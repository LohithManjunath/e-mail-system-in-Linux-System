#include"head.h"
#include"server.h"
#include"database.h"
sqlite3* db = NULL;
int login(struct user_type log)
{
	printf("welcome to the login_database_activity!\n");
	sqlite3 *db = NULL; 	
	int rc = sqlite3_open("../bin/try.db", &db);//open	
	char** azResult;
	char ctime[30];
	int nrow = 0, ncolumn = 0, i = 0;
	char* zErrMsg = 0;//debug
	strcpy(sql,"SELECT uname,upsw FROM user_table");/////////
	sqlite3_get_table(db, sql, &azResult, &nrow, &ncolumn, &zErrMsg);
	
	
	for(i=0; i<((nrow+1)*ncolumn); i+=2)
	{
		if(strcmp(azResult[i],log.uname) == 0)
		{						
			if(strcmp(azResult[i+1],log.upsw) == 0)
			{
				gettime(&ctime);				
				sprintf(sql, "INSERT INTO active_user_table VALUES('%s','%s')", log.uname, ctime);
				sqlite3_exec(db, sql, 0, 0, &zErrMsg);
				printf("Welcome user:%s\n",log.uname);
				sqlite3_close (db);
				return 0;
			}
			else 	
			{
				printf("Password error!\n");
				sqlite3_close (db);				
				return 1;	
			}
		}
	}
	printf("The username has not been used!\n");	
	sqlite3_close (db);
	return 2;
}

void login_fun(MSG msg,int temp_sock_descriptor)
{
	printf("welcome to login_server_thread.\n");
	struct user_type user;
	
	int i,j,n;
	int sd;	
	

	char flag;
	int num;
	

	//main progress
			
			strcpy(user.uname,msg.uname);
			strcpy(user.upsw,msg.upsw);
			printf("the username is :%s\n",user.uname);
			printf("the passworld is :%s\n",user.upsw);

			switch( login(user) )
			{
				case 1:{
					printf("Password error!\n");
					flag = 'a';

					if(send(temp_sock_descriptor, &flag, 1, 0)==-1)	//send
					{
						perror("can not send flag\n");
						close(temp_sock_descriptor);
						exit(1);
					}
				
					break;}
				case 2:{
					printf("The username has not been used!\n");
					flag = 'b';
					if(send(temp_sock_descriptor, &flag, 1, 0)==-1)	//send
					{
						perror("can not send flag\n");
						close(temp_sock_descriptor);
						exit(1);
					}
					printf("flag = %c\n",flag);
					break;}

				default:{
					printf("correct\n");
					strcpy(client_name[client_num],msg.uname);
					client_num++;
					flag = 'c';
					num = client_num-1;
					if(send(temp_sock_descriptor, &flag, 1, 0)==-1)//send
					{
						perror("can not send flag\n");
						close(temp_sock_descriptor);
						exit(1);
					}
					if(send(temp_sock_descriptor, &num, sizeof(num), 0)==-1)//send
					{
						perror("can not send num\n");
						close(temp_sock_descriptor);
						exit(1);
					}
					goto K;}
			}
		
	//}
K:	return ;
/*	close(sd);
	pthread_exit("ok!");
*/	
}
