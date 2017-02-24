#include<gtk/gtk.h>
#include<unistd.h>
int main()
{
	GtkWidget *window;
	GtkWidget *window2;
	gtk_init(NULL,NULL);
	window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	window2 = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	g_signal_connect (G_OBJECT (window), "destroy",G_CALLBACK (gtk_main_quit), NULL);
	g_signal_connect_swapped (G_OBJECT (window), "delete_event",G_CALLBACK (gtk_widget_destroy),window);
	gtk_widget_show(window);
	gtk_widget_show(window2);
	gtk_widget_destroy(window);
	window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	gtk_widget_show(window);
	gtk_main();
}
