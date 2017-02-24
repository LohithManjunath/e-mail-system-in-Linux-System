#ifndef _SERVER_H
#define _SERVER_H
char client_name[100][18];
int client_num;
char buffer[120000];

void gettime(char* temp);


void login_fun(MSG msg,int temp_sock_descriptor);		//login function
void register_fun(MSG msg,int temp_sock_descriptor);		//register thread
void send_fun(MSG msg,int temp_sock_descriptor);		//send
void save_fun(MSG msg,int temp_sock_descriptor);		//save
void change_password_fun(MSG msg,int temp_sock_descriptor);	//change password

void delete_recEbox_fun(MSG msg,int temp_sock_descriptor);	//delete email in receive box
void delete_recYbox_fun(MSG msg,int temp_sock_descriptor);	//delete email in recycle box
void delete_send_fun(MSG msg,int temp_sock_descriptor);		//delete email in send box
void delete_draft_fun(MSG msg,int temp_sock_descriptor);	//delete email in draft box
void getlinkmen_fun(MSG msg,int temp_sock_descriptor);		//Get linkmen function
void note_fun(MSG msg,int temp_sock_descriptor);		//note the email
void recover_fun(MSG msg,int temp_sock_descriptor);		//Recover the email 



void openrcvm_fun(MSG msg, int temp_sock_descriptor);  //open mail in receivebox
void opensndb_fun(MSG msg, int temp_socket_descriptor);//open send box
void opendrtfb_fun(MSG msg,int temp_socket_descriptor);// open draftbox
void openrbb_fun(MSG msg, int temp_socket_descriptor);//open recyclebinbox
void openydmb_fun(MSG msg, int temp_socket_descriptor);//open recyclebinbox
void openwdmb_fun(MSG msg, int temp_socket_descriptor);//open recyclebinbox

#endif
