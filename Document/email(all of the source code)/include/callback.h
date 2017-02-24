#ifndef _CALLBACK_H
#define _CALLBACK_H
#include<gtk/gtk.h>
void on_button_clicked_welcom(GtkWidget*,gpointer );
void login_create_User(GtkWidget*,gpointer );
void login_get_User(GtkWidget*,gpointer );
void login_change_psw(GtkWidget*,gpointer );
void change_psw_ok(GtkWidget*,gpointer );
void change_psw_return(GtkWidget*,gpointer );
void Reg( GtkWidget*,gpointer data);
void reg_Clean( GtkWidget*,gpointer );
void on_button_clicked(GtkButton* ,gpointer );
void on_edit_cut_activate(GtkButton* ,gpointer  );
void on_edit_copy_activate(GtkButton* ,gpointer  );
void on_edit_paste_activate(GtkButton* ,gpointer  );
void send_creat_new_file(GtkButton* ,gpointer );
void send_save_mail(GtkButton* ,gpointer  );
void send_file_ok_sel( GtkWidget *,GtkFileSelection * );
void send_attach_button(GtkWidget *,gpointer );
void send_send_button(GtkWidget *,gpointer );
gint send_area_event( GtkWidget *, GtkWidget * );
void send_color_changed_cb( GtkWidget *,GtkColorSelection * );
void send_toggle_button_callback (GtkWidget *, GtkWidget* );
int  send_CHECK_REF(GtkWidget *,GtkWidget * *);
void send_font_select_ok(GtkWidget *,GtkFontSelectionDialog *);
void send_changefont(GtkWidget *,GtkWidget *);
void callback_xinjian( GtkWidget *,gpointer  );
void callback_huifu( GtkWidget *,gpointer    );
void callback_zhuanfa( GtkWidget *,gpointer    );
void callback_fasong( GtkWidget *,gpointer    );
void callback_jieshou( GtkWidget *,gpointer    );
void add_to_list(GtkWidget * list, const gchar * str,const gchar * str1,const gchar * str2,const gint * str3,const gchar * str4,const gchar * str5);
void on_changed(GtkWidget* ,gpointer );
void Ton_changed(GtkWidget * , gpointer );
void remove_item(GtkWidget * , gpointer );
void send_return(GtkWidget * , gpointer );
void callback_sort( GtkWidget *,gpointer  );
void send_button_rec(GtkWidget * , gpointer );
void send_button_copy(GtkWidget * , gpointer );
void send_button_secret(GtkWidget * , gpointer );
void recover_item(GtkWidget * , gpointer );
#endif
