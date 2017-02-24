#include "head.h"
#include "server.h"
#include "database.h"

int openrcvm(int no, int checkstat, char *stat, void *p)
{
//open db
	sqlite3 *db = NULL;
	char** azResult;
	int nrow = 0, ncolumn = 0, i = 0;
	char *zErrMsg;
	int rc = sqlite3_open("../bin/try.db", &db);

	if ( rc )
	{
		fprintf(stderr, "Can't open database: %s\n",sqlite3_errmsg(db));
		exit(EXIT_FAILURE);
	}
	else 
		printf("You have opened try.db successfully!\n");
//select
	sprintf(sql, "SELECT title,text FROM message_table WHERE no = '%d'", no);
	sqlite3_get_table(db, sql, &azResult, &nrow, &ncolumn, &zErrMsg);
	printf("%d %d\n", nrow, ncolumn);
	if (nrow == 0) 
	{
		return 1;	
	}         
//get
	MSG *rmsg;
	rmsg = (MSG *)p;

	for (i = ncolumn; i < (nrow + 1) * ncolumn; i += ncolumn)
	{
		printf("title: %s\ntext: %s\n", azResult[i], azResult[i+1]);
		strcpy(rmsg->mtitle, azResult[i]);                    
		strcpy(rmsg->mtext, azResult[i+1]);                    	
	}
//change the stat
	if ((strcmp(stat,"n") == 0) && (checkstat == 121))
	{
		sprintf(sql, "UPDATE receivebox_table SET rmstat = '%c' WHERE no = '%d'", 'y', no);
		sqlite3_exec(db, sql, 0, 0, &zErrMsg);
	}	
//
	sqlite3_close(db);
	return 0;
}

void openrcvm_fun(MSG msg, int temp_sock_descriptor)
{
	MSG rcvmsg;

	int i = 0;
	
	printf("the mail no is :%d\n", msg.no);
	printf("the mail stat is %s\n", msg.stat);
	printf("mailnum: %d\n", msg.num);

	switch( openrcvm(msg.no, msg.num, msg.stat, &rcvmsg) )
	{
		case 1:
			printf("Message is empty.\n");
			break;
		default:
			printf("correct\n");

			bzero(buffer,sizeof(buffer));
			memcpy(buffer,&rcvmsg,sizeof(MSG));

    			if(send(temp_sock_descriptor, buffer, sizeof(buffer), 0)==-1)		//send
   			{
				perror("can not send message\n");
				exit(1);
			}  
	}
	
	return ;			
}
