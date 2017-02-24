#include"head.h"
#include"server.h"
#include"database.h"

int opensndb(char *uname, char *sortkey, void *p)
{
//open db
	printf("welcome to the openSNDb_fun_database!\n");
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
	sprintf(sql, "SELECT smtitle,smtime,receiver,no FROM sendbox_table WHERE uname = '%s'", uname);
	sqlite3_get_table(db, sql, &azResult, &nrow, &ncolumn, &zErrMsg);
	printf("%d %d\n", nrow, ncolumn);
	//if (nrow == 0) 
	//{
	//	return 1;	
	//}
//get 
	MAILBOX *rm;
	rm = (MAILBOX *)p;

	rm->mailnum = 0;      

	//printf("%s\n",azResult[(nrow + 1) * ncolumn - 1]);   
	for (i = ncolumn; i < (nrow + 1) * ncolumn; i += ncolumn)
	{	
		if ((strcmp(sortkey, "lixingxing") == 0) || (strstr(azResult[i], sortkey) != NULL) || (strstr(azResult[i+1], sortkey) != NULL) || (strstr(azResult[i+2], sortkey) != NULL))
		{
			printf("i = %d\n",i);
			printf("Mail %d: %s %s %s %d\n", rm->mailnum, azResult[i], azResult[i+1], azResult[i+2], atoi(azResult[i+3]));
			strcpy(rm->title[rm->mailnum], azResult[i]);                    
			strcpy(rm->time[rm->mailnum], azResult[i+1]);                    
			strcpy(rm->receiver[rm->mailnum], azResult[i+2]);	
			rm->no[rm->mailnum] = atoi(azResult[i+3]);
			rm->mailnum++;
		}
	}
//close
	sqlite3_close(db);
	printf("the openSNDb_fun_database is over!\n");
	return 0;
}

void opensndb_fun(MSG msg, int temp_socket_descriptor)
{
	printf("welcome to the openSNDb_fun!\n");
	int rc;

	char uname[18];
	MAILBOX rm;
	//MSG rmsg;

	int i = 0;
	
	strcpy(uname, client_name[msg.client_num]);
	printf("the username is :%s\n", uname);
	
	switch( opensndb(uname, msg.sortkey, &rm) )
	{
		case 1:
			printf("Sendbox is empty.\n");
			break;
		default:
			printf("correct\n");
			//if (send(temp_socket_descriptor, &rm.mailnum, sizeof(rm.mailnum), 0) == -1)     //send num
			//{
			//	perror("can not send rm.mailnum\n");
			//	close(temp_socket_descriptor);
			//	exit(1);
			//}   
			printf("%d\n", rm.mailnum);                     
			for (i = 0;i < rm.mailnum; i++)
			{ 

printf("Mail %d: %s %s %s %d\n", i, rm.title[i], rm.time[i], rm.receiver[i], rm.no[i]);
			}
				bzero(buffer,sizeof(buffer));
				memcpy(buffer,&rm,sizeof(MAILBOX));
				
				printf("before send buffer:temp_socket_descriptor = %d,buffer_lenth=%d,sizeof_rm=%d\n",temp_socket_descriptor,strlen(buffer),sizeof(rm));
    				if(send(temp_socket_descriptor, buffer, sizeof(rm), 0)==-1)		//send
   				{
					perror("can not send message\n");
					exit(1);
			    	}
				printf("After send buffer:temp_socket_descriptor = %d,buffer_lenth=%d,sizeof_rm=%d\n",temp_socket_descriptor,strlen(buffer),sizeof(rm));

/*				memset(&rmsg, 0, sizeof(MSG));
				strcpy(rmsg.title, rm.title[i]);
				strcpy(rmsg.time, rm.time[i]);
				strcpy(rmsg.sender, rm.sender[i]);
				rmsg.no = rm.no[i];
				strcpy(rmsg.rmstat, rm.rmstat[i]);
				bzero(buffer,sizeof(buffer));
				memcpy(buffer,&rmsg,sizeof(MSG));

    				if(send(temp_socket_descriptor, buffer, sizeof(buffer), 0)==-1)		//send
   				{
					perror("can not send message\n");
					exit(1);
			    	}
*/
			//}
	}
	printf("the openSNDb_fun is over!\n");
	return ;
}
