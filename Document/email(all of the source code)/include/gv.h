#ifndef _GV_H
#define _GV_H
#include<gtk/gtk.h>
int rc,sd;
int client_num;
int socket_descriptor;		//socked number
struct sockaddr_in pin;		//server address
int lxxlzyqdsdsb;
char buff[120000];
void do_connect(void);
void getmailbox(MSG m, int client_num, void *p);
void getmsg(int num, int no, char *stat, void *p);
int port;
GtkWidget * window_login;
GtkWidget * window_welcom;
GtkWidget * window_register;
GtkWidget * window_main;
GtkWidget * window_send;
GtkWidget * window_change_psw;

GtkWidget * entry_login_user;
GtkWidget * entry_login_psw;

GtkWidget * entry_change_psw_user;
GtkWidget * entry_change_psw_re;
GtkWidget * entry_change_psw_new;
GtkWidget * entry_change_psw_new2;

GtkWidget * entry_reg_user;
GtkWidget * entry_reg_psw;
GtkWidget * entry_reg_psw2;
GtkWidget * entry_reg_tel;

GtkWidget * entry_rec;
GtkWidget * entry_name;
GtkWidget * entry_copy;
GtkWidget * entry_secret;
GtkWidget * entry_select;

GtkTextBuffer* buffer;
GtkClipboard* clipboard;

GdkColor color;
PangoFontDescription *desc_info;
GtkWidget *view_text;

GtkWidget *list;

int Delete_flag;
GtkWidget *main_label;

enum LEFT
{
	COLUMN=0,
	N_COLUMNS
};
enum RIGHT
{

   // LIST_ONE = 0,
    LIST_TWO,
    LIST_THREE,
    LIST_FOUR,
    LIST_FIVE,
    LIST_SIX,
    LIST_SEVEN,
    R_COLUMNS
};

char U_ID[50];

MSG M;
GtkWidget *main_textview;/////////////////yidongle

#endif
