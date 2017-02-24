#include"head.h"
#include"server.h"
#include"database.h"

int openrbb(char *uname, char *sortkey, void *p)
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
			
	printf("%s\n", uname);

//select 
	sprintf(sql, "SELECT sender,receiver,rmtitle,rmtime,no,flag FROM recyclebin_table WHERE uname = '%s'", uname);
	sqlite3_get_table(db, sql, &azResult, &nrow, &ncolumn, &zErrMsg);
	printf("%d %d\n", nrow, ncolumn);
//get 
	MAILBOX *rm;
	rm = (MAILBOX *)p;

	rm->mailnum = 0;      
  
	for (i = ncolumn; i < (nrow + 1) * ncolumn; i += ncolumn)
	{	
		if ((strcmp(sortkey, "lixingxing") == 0) || (strstr(azResult[i+2], sortkey) != NULL) || (strstr(azResult[i+3], sortkey) != NULL))
		{
			printf("Mail %d: %s %s %s %s %d %s\n", rm->mailnum, azResult[i], azResult[i+1], azResult[i+2], azResult[i+3], atoi(azResult[i+4]), azResult[i+5]);
			strcpy(rm->sender[rm->mailnum], azResult[i]);                    
			strcpy(rm->receiver[rm->mailnum], azResult[i+1]);                    
			strcpy(rm->title[rm->mailnum], azResult[i+2]);	
			strcpy(rm->time[rm->mailnum], azResult[i+3]);	
			rm->no[rm->mailnum] = atoi(azResult[i+4]);	
			strcpy(rm->database_flag[rm->mailnum], azResult[i+5]);	
			rm->mailnum++;
		}
	}
//close
	sqlite3_close(db);
	return 0;
}

void openrbb_fun(MSG msg, int temp_socket_descriptor)
{
	int rc;

	char uname[18];
	MAILBOX rm;
	//MSG rmsg;

	int i = 0;

	strcpy(uname, client_name[msg.client_num]);
	printf("the username is :%s\n", uname);
	
	switch( openrbb(uname, msg.sortkey, &rm) )
	{
		case 1:
			printf("Sendbox is empty.\n");
			break;
		default:
			printf("correct\n");

			printf("%d\n", rm.mailnum);                     
			for (i = 0;i < rm.mailnum; i++)
			{ 

printf("Mail %d: %s %s %s %s %d %s\n", i, rm.sender[i], rm.receiver[i], rm.title[i], rm.time[i], rm.no[i], rm.database_flag[i]);
			}
				bzero(buffer,sizeof(buffer));
				memcpy(buffer,&rm,sizeof(MAILBOX));
			
    				if(send(temp_socket_descriptor, buffer, sizeof(rm), 0)==-1)		//send
   				{
					perror("can not send message\n");
					exit(1);
			    	}

	}

	return ;
}
