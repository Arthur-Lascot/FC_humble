#include <stdlib.h>
#include <gtk/gtk.h>


GtkWidget *MainWindow;
GtkWidget *Fixed_one;
GtkWidget *Button_one;
GtkWidget *Label_one;
GtkBuilder *builder;

int main(int argc, char *argv[])
{
    gtk_init(&argc, &argv);
    
    builder = gtk_builder_new_from_file("OCR_app.glade");

    MainWindow = GTK_WIDGET(gtk_builder_get_object(builder,"MainWindow"));
    g_signal_connect(MainWindow,"destroy",G_CALLBACK(gtk_main_quit),NULL);

    gtk_builder_connect_signals(builder,NULL);
    
    Fixed_one = GTK_WIDGET(gtk_builder_get_object(builder,"Fixed_one"));
    Button_one = GTK_WIDGET(gtk_builder_get_object(builder,"Button_one"));
    Label_one = GTK_WIDGET(gtk_builder_get_object(builder,"Label_one"));

    gtk_widget_show(MainWindow);

    gtk_main();

    return EXIT_SUCCESS;

}

void on_Button_one_clicked(GtkButton *button)
{
    gtk_label_set_text(GTK_LABEL(Label_one), (const gchar*) "90.6%" );
}
