#include "head.h"
#include "database.h"

int creatdatabase()
{
	sqlite3 *db = NULL;	
	char* zErrMsg = 0;//debug	
	int rc = sqlite3_open("try.db", &db);//open
	if ( rc )
	{
		fprintf (stderr, "Can't open database: %s\n", sqlite3_errmsg (db));
		sqlite3_close (db);
		return 1;
	}
	else
		printf("You have opened a sqlite3 database named shroomail.db successfully!\n");

	//create user_table
	strcpy(sql,"CREATE TABLE user_table(uname VARCHAR(18) PRIMARY KEY,upsw VARCHAR(12),utel VARCHAR(12),utime VARCHAR(30));");
	sqlite3_exec(db, sql, 0, 0, &zErrMsg);
	
#ifdef _DEBUG_
  printf ("zErrMsg = %s \n", zErrMsg);
#endif

	//create linkman_table
strcpy(sql,"CREATE TABLE linkman_table(uname VARCHAR(18),friend VARCHAR(18),ltime VARCHAR(30));");/////////////////////////xiugai
	sqlite3_exec(db, sql, 0, 0, &zErrMsg);
	
#ifdef _DEBUG_
  printf ("zErrMsg = %s \n", zErrMsg);
#endif


	//create active_user_table
	strcpy(sql,"CREATE TABLE active_user_table(uname VARCHAR(18) PRIMARY KEY,atime VARCHAR(30));");
	sqlite3_exec(db, sql, 0, 0, &zErrMsg);
	
#ifdef _DEBUG_
  printf ("zErrMsg = %s \n", zErrMsg);
#endif	


	//create sendbox_table
	strcpy(sql,"CREATE TABLE sendbox_table(no INTEGER PRIMARY KEY,uname VARCHAR(18),smtitle NVARCHAR(30),smtime VARCHAR(30),receiver VARCHAR(18));");
	sqlite3_exec(db, sql, 0, 0, &zErrMsg);
#ifdef _DEBUG_ 
  printf ("zErrMsg = %s \n", zErrMsg);
#endif


	//create message_table
	strcpy(sql,"CREATE TABLE message_table(no INTEGER PRIMARY KEY,title NVARCHAR(30),text NVARCHAR(1000),flag INTEGER);");
	sqlite3_exec(db, sql, 0, 0, &zErrMsg);
#ifdef _DEBUG_
  printf ("zErrMsg = %s \n", zErrMsg);
#endif


	//create receivebox_table
	strcpy(sql,"CREATE TABLE receivebox_table(no INTEGER PRIMARY KEY,uname VARCHAR(18),rmtitle NVARCHAR(30),rmtime VARCHAR(30),sender VARCHAR(18),rmstat VARCHAR(1));");
	//rmstat == 'y' 已读
	//rmstat == 'n' 未读
	sqlite3_exec(db, sql, 0, 0, &zErrMsg);
#ifdef _DEBUG_
  printf ("zErrMsg = %s \n", zErrMsg);
#endif


	//create draftbox_table
	strcpy(sql,"CREATE TABLE draftbox_table(no INTEGER PRIMARY KEY,uname VARCHAR(18),dmtitle NVARCHAR(30),dmtime VARCHAR(30));");
	sqlite3_exec(db, sql, 0, 0, &zErrMsg);
#ifdef _DEBUG_
  printf ("zErrMsg = %s \n", zErrMsg);
#endif


	//create recyclebin_table
	strcpy(sql,"CREATE TABLE recyclebin_table(no INTEGER,uname VARCHAR(18),sender VARCHAR(18),receiver VARCHAR(18),rmtitle NVARCHAR(30),rmtime VARCHAR(30),flag VARCHAR(1));");
	// flag == 's' from sendbox_table
	// flag == 'r' from receivebox_table
	// flag == 'd' from draftbox_table
 	sqlite3_exec(db, sql, 0, 0, &zErrMsg);
#ifdef _DEBUG_
  printf ("zErrMsg = %s \n", zErrMsg);
#endif
	sqlite3_close (db);        //关闭数据库
  	return 0;

}

int main()
{	
	count = 0;

	creatdatabase();

	return 0;
}
