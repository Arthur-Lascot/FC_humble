#include <stdlib.h>
#include <gtk/gtk.h>


GtkWidget *MainWindow;

GtkWidget *Menu_box;

GtkWidget *Image_chooser;

GtkBuilder *builder;

int main(int argc, char *argv[])
{
    gtk_init(&argc, &argv);
    
    builder = gtk_builder_new_from_file("OCR_app.glade");

    MainWindow = GTK_WIDGET(gtk_builder_get_object(builder,"MainWindow"));
    g_signal_connect(MainWindow,"destroy",G_CALLBACK(gtk_main_quit),NULL);

    gtk_builder_connect_signals(builder,NULL);
    
    Menu_box = GTK_WIDGET(gtk_builder_get_object(builder,"Menu_box"));
    Image_chooser = GTK_WIDGET(gtk_builder_get_object(builder,"Image_chooser"));
    

    gtk_widget_show(MainWindow);

    gtk_main();

    return EXIT_SUCCESS;

}

void on_Image_chooser_file_set(GtkFileChooserButton *fi)
{
    printf("File Name = %s\n",gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(fi)));
    printf("Folder Name = %s\n",gtk_file_chooser_get_current_folder(GTK_FILE_CHOOSER(fi)));
}







