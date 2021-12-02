#include <stdlib.h>
#include <gtk/gtk.h>


GtkWidget *MainWindow;

GtkBuilder *builder;

typedef struct Menu
{
    GtkWidget *Menu_box;
    GtkWidget *Image_chooser;
    //Net Box
    //Net_tile
    GtkWidget *Net_chooser;
    //Create_net
    GtkWidget *Net_name;
    GtkWidget *Net_button;
    GtkWidget *Net_test;
    GtkWidget *Net_res;
    //Solver
    //OCR_title
    //Rot_man
    GtkWidget *Rot_left;
    GtkWidget *Rot_right;
    //OCR_step
    GtkWidget *Auto_rot;
    GtkWidget *Print_line;
    GtkWidget *Print_case;
    GtkWidget *Print_step;
    //Solve_buttons
    GtkWidget *OCR_button;
    GtkWidget *Solver_button;
} Menu;

typedef struct MainArea
{
    GtkWidget *Name_sudoku;
    //Page 1
    GtkWidget *Image_sudoku;
    //Page 2
    GtkWidget *Sudoku_file;
} MainArea;

int main(int argc, char *argv[])
{
    gtk_init(&argc, &argv);

    builder = gtk_builder_new_from_file("OCR_app.glade");

    MainWindow = GTK_WIDGET(gtk_builder_get_object(builder,"MainWindow"));
    g_signal_connect(MainWindow,"destroy",G_CALLBACK(gtk_main_quit),NULL);

    gtk_builder_connect_signals(builder,NULL);
    
    // === MENU ===
    GtkWidget *Menu_box = GTK_WIDGET(gtk_builder_get_object(builder,"Menu_box"));
    GtkWidget *Image_chooser = GTK_WIDGET(gtk_builder_get_object(builder,"Image_chooser"));
    GtkWidget *Net_chooser = GTK_WIDGET(gtk_builder_get_object(builder,"Net_chooser"));
    GtkWidget *Net_name = GTK_WIDGET(gtk_builder_get_object(builder,"Net_name"));
    GtkWidget *Net_button = GTK_WIDGET(gtk_builder_get_object(builder,"Net_button"));
    GtkWidget *Net_test = GTK_WIDGET(gtk_builder_get_object(builder,"Net_test"));
    GtkWidget *Net_res = GTK_WIDGET(gtk_builder_get_object(builder,"Net_res"));
    GtkWidget *Rot_left = GTK_WIDGET(gtk_builder_get_object(builder,"Rot_left"));
    GtkWidget *Rot_right = GTK_WIDGET(gtk_builder_get_object(builder,"Rot_right"));
    GtkWidget *Auto_rot = GTK_WIDGET(gtk_builder_get_object(builder,"Auto_rot"));
    GtkWidget *Print_line = GTK_WIDGET(gtk_builder_get_object(builder,"Print_line"));
    GtkWidget *Print_case = GTK_WIDGET(gtk_builder_get_object(builder,"Print_case"));
    GtkWidget *Print_step = GTK_WIDGET(gtk_builder_get_object(builder,"Print_step"));
    GtkWidget *OCR_button = GTK_WIDGET(gtk_builder_get_object(builder,"OCR_button"));
    GtkWidget *Solver_button = GTK_WIDGET(gtk_builder_get_object(builder,"Solver_button"));
    /// === MENU ===

    /// === Main Area ===
    GtkWidget *Image_sudoku=GTK_WIDGET(gtk_builder_get_object(builder,"Image_sudoku"));
    GtkWidget *Name_sudoku=GTK_WIDGET(gtk_builder_get_object(builder,"Name_sudoku"));
    GtkWidget *Sudoku_file=GTK_WIDGET(gtk_builder_get_object(builder,"Sudoku_file"));

    /// === Main Area ===
 

    Menu menu = 
    {
        .Menu_box = Menu_box,
        .Image_chooser = Image_chooser,
        .Net_chooser = Net_chooser,
        .Net_name = Net_name,
        .Net_button = Net_button,
        .Net_test = Net_test,
        .Net_res = Net_res,
        .Rot_left = Rot_left,
        .Rot_right = Rot_right,
        .Auto_rot = Auto_rot,
        .Print_line = Print_line,
        .Print_case = Print_case,
        .Print_step = Print_step,
        .OCR_button = OCR_button,
        .Solver_button = Solver_button,
    };

    MainArea area =
    {
        .Image_sudoku = Image_sudoku,
    };

    gtk_widget_show(MainWindow);

    gtk_main();

    return EXIT_SUCCESS;

}

void on_Image_chooser_file_set(GtkFileChooserButton *fi)
{
    printf("File Name = %s\n",gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(fi)));
    printf("Folder Name = %s\n",gtk_file_chooser_get_current_folder(GTK_FILE_CHOOSER(fi)));
}

void on_Net_chooser_file_set(GtkFileChooserButton *fi)
{
    printf("File Name = %s\n",gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(fi)));
    printf("Folder Name = %s\n",gtk_file_chooser_get_current_folder(GTK_FILE_CHOOSER(fi)));
}

void on_Net_button_clicked(GtkButton *b)
{
    printf("Create Network\n");
}

void on_Net_test_clicked(GtkButton *b)
{
    printf("Test Network\n");
}

void on_Rot_left_clicked(GtkButton *b)
{
    printf("Rotation Left\n");
}

void on_Rot_right_clicked(GtkButton *b)
{
    printf("Rotation Right\n");
}

void on_Auto_rot_clicked(GtkButton *b)
{
    printf("Auto Rotation\n");
}

void on_Print_line_clicked(GtkButton *b)
{
    printf("Print Line\n");
}

void on_Print_case_clicked(GtkButton *b)
{
    printf("Print Case\n");
}

void on_OCR_button_clicked(GtkButton *b)
{
    printf("OCR...\n");
}

void on_Solver_button_clicked(GtkButton *b)
{
    printf("Solver...\n");
}

void on_Print_step_toggled(GtkButton *b)
{
    printf("Print Step\n");
}

void on_Case_clicked(GtkButton *b)
{
    printf("Case clicked\n");
}
