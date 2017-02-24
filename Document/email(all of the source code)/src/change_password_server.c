#include"head.h"
#include"server.h"
#include"database.h"

int changepsw(char uname[18], char opsw[18], char npsw[18])
{
	sqlite3 *db = NULL;	
	char** azResult;
	int nrow = 0, ncolumn = 0, i = 0;
	char* zErrMsg = 0;//debug
	int rc= sqlite3_open("../bin/try.db", &db);//open database
	sprintf(sql, "SELECT uname FROM user_table WHERE (uname='%s' AND upsw='%s')", uname, opsw);
	sqlite3_get_table(db, sql, &azResult, &nrow, &ncolumn, &zErrMsg);

	if(nrow == 0)
	{
		printf("username and password dose not match!\n");
		sqlite3_close (db);
		return 1;
	}
	else 
	{	
		sprintf(sql, "UPDATE user_table SET upsw='%s' WHERE uname='%s'" ,npsw, uname);
		sqlite3_exec(db, sql, 0, 0, &zErrMsg);
		printf("Password has been changed\n");
		sqlite3_close (db);
		return 0;
	}
	
}





void change_password_fun(MSG msg,int temp_sock_descriptor)
{
	char flag;

	printf("the msg.uname is %s\nthe msg.upsw is %s\nthe msg.utel is %s\n",msg.uname,msg.upsw, msg.utel);
	switch(changepsw(msg.uname, msg.upsw, msg.utel))
	{
		case 0:
		{
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
			flag ='n';
			if(send(temp_sock_descriptor, &flag, 1, 0)==-1)	//send
			{
				perror("can not send flag\n");
				close(temp_sock_descriptor);
				exit(1);
			}			
			break;
		}
	}
	
	return ;	
}
