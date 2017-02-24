#include "head.h"
#include "database.h"




int main(void)
{
	char *zErrMsg = 0;//debug
	int rc;
	sqlite3 *db = NULL;

	rc = sqlite3_open("../bin/mememail.db", &db);//open database
	if ( rc )
	{
		fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
		sqlite3_close(db);
		exit(EXIT_FAILURE);
	}
	else
		printf("You have opened a sqlite3 database named mememail.db successfully!\n");
	
	
	//create user_table
	strcpy(sql, "CREATE TABLE user_table(uname VARCHAR(18) PRIMARY KEY,upsw VARCHAR(12),utel VARCHAR(12));");
	sqlite3_exec(db, sql, 0, 0, &zErrMsg);
	
#ifdef _DEBUG_
  printf ("zErrMsg = %s \n", zErrMsg);
#endif
	

	//create message_table
	strcpy(sql, "CREATE TABLE message_table(no INTEGER PRIMARY KEY,title VARCHAR(30),text VARCHAR(1000));");
	sqlite3_exec(db, sql, 0, 0, &zErrMsg);
#ifdef _DEBUG_
  printf ("zErrMsg = %s \n", zErrMsg);
#endif	


	//create sendbox_table
	strcpy(sql, "CREATE TABLE sendbox_table(no INTEGER PRIMARY KEY,uname VARCHAR(18),smtitle VARCHAR(30),smtime VARCHAR(30),receiver VARCHAR(18));");
	sqlite3_exec(db, sql, 0, 0, &zErrMsg);
#ifdef _DEBUG_ 
  printf ("zErrMsg = %s \n", zErrMsg);
#endif


	//create receivebox_table
	strcpy(sql, "CREATE TABLE receivebox_table(no INTEGER PRIMARY KEY,uname VARCHAR(18),rmtitle VARCHAR(30),rmtime VARCHAR(30),sender VARCHAR(18));");
	sqlite3_exec(db, sql, 0, 0, &zErrMsg);
#ifdef _DEBUG_
  printf ("zErrMsg = %s \n", zErrMsg);
#endif	


	//create draftbox_table
	strcpy(sql, "CREATE TABLE draftbox_table(no INTEGER PRIMARY KEY,uname VARCHAR(18),dmtitle VARCHAR(30),dmtime VARCHAR(30));");
	sqlite3_exec(db, sql, 0, 0, &zErrMsg);
#ifdef _DEBUG_
  printf ("zErrMsg = %s \n", zErrMsg);
#endif


	//create recyclebin_table
	strcpy(sql, "CREATE TABLE recyclebin_table(no INTEGER PRIMARY KEY,flag VARCHER(12), sender VARCHAR(18),receiver VARCHAR(18),rmtitle VARCHAR(30),rmtime VARCHAR(30));");
	sqlite3_exec(db, sql, 0, 0, &zErrMsg);
#ifdef _DEBUG_
  printf ("zErrMsg = %s \n", zErrMsg);
#endif


	sqlite3_close (db);        //close database
  	return 0;
}

