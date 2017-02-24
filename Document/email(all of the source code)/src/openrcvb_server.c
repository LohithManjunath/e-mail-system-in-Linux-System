#include"head.h"
#include"server.h"
#include"database.h"

int openrcvb(char *uname, char *sortkey, void *p)
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
	sprintf(sql, "SELECT rmtitle,rmtime,sender,no,rmstat FROM receivebox_table WHERE uname = '%s'", uname);
	sqlite3_get_table(db, sql, &azResult, &nrow, &ncolumn, &zErrMsg);
	printf("%d %d\n", nrow, ncolumn);
//get 
	MAILBOX *rm;
	rm = (MAILBOX *)p;

	rm->mailnum = 0;         
	for (i = ncolumn; i < (nrow + 1) * ncolumn; i += ncolumn)
	{
		if ((strcmp(sortkey, "lixingxing") == 0) || (strstr(azResult[i], sortkey) != NULL) || (strstr(azResult[i+1], sortkey) != NULL) || (strstr(azResult[i+2], sortkey) != NULL))
		{		
			printf("Mail %d: %s %s %s %d %s\n", rm->mailnum, azResult[i], azResult[i+1], azResult[i+2], atoi(azResult[i+3]), azResult[i+4]);
			strcpy(rm->title[rm->mailnum], azResult[i]);                    
			strcpy(rm->time[rm->mailnum], azResult[i+1]);                    
			strcpy(rm->sender[rm->mailnum], azResult[i+2]);	
			rm->no[rm->mailnum] = atoi(azResult[i+3]);
			strcpy(rm->rmstat[rm->mailnum], azResult[i+4]);
			rm->mailnum++;
		}
	}
//close
	sqlite3_close(db);

	return 0;
}

void openrcvb_fun(MSG msg, int temp_socket_descriptor)
{

	int rc;

	char uname[18];
	MAILBOX rm;


	int i = 0;
	
	strcpy(uname, client_name[msg.client_num]);
	printf("the username is :%s\n", uname);
	
	switch( openrcvb(uname, msg.sortkey, &rm) )
	{
		case 1:
			printf("Receivebox is empty.\n");
			break;
		default:
			printf("correct\n");
	
			printf("%d\n", rm.mailnum);                     
			for (i = 0;i < rm.mailnum; i++)
			{ 

printf("Mail %d: %s %s %s %d %s\n", i, rm.title[i], rm.time[i], rm.sender[i], rm.no[i], rm.rmstat[i]);
			}
				bzero(buffer,sizeof(buffer));
				memcpy(buffer,&rm,sizeof(MAILBOX));
				printf("before send buffer:temp_socket_descriptor = %d,buffer_lenth=%d,sizeof_rm=%d\n",temp_socket_descriptor,strlen(buffer),sizeof(rm));
    				if(send(temp_socket_descriptor, buffer, sizeof(rm), 0)==-1)		//send
   				{
					perror("can not send message\n");
					exit(1);
			    	}

	}

	return ;
}
