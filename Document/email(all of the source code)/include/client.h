#ifndef _SERVER_H
#define _SERVER_H
//void *loginpthread(void *arg);	//login function
int loginpthread(int *arg);
//void *register_thread(void *arg); //register pthread
int register_thread(int *arg);
#endif
