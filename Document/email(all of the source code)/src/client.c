#include"head.h"
#include"window.h"
#include"callback.h"
#include"gv.h"
#include<gtk/gtk.h>


int main(int argc, char* argv[])
{

	
	
	gtk_init(&argc,&argv);
	window_welcom = new_welcom_window();
	//gtk_widget_set_size_request (GTK_WIDGET (window1),220,220);
	
 	//g_signal_connect (G_OBJECT (window1), "destroy",G_CALLBACK (gtk_main_quit), NULL);
	//g_signal_connect_swapped (G_OBJECT (window1), "delete_event",G_CALLBACK (gtk_widget_destroy),window1);
	
	gtk_widget_show_all(window_welcom);
	
	gtk_main();

	return 0;
}
