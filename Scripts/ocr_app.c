#include <stdlib.h>
#include <gtk/gtk.h>
#include <err.h>

#include "./OCR/xor.h"

// == Variables == //

char pathNet[128];
char pathImg[128];

char *gridc;

// === GTK === //

GtkWidget *MainWindow;
GtkBuilder *builder;

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
GtkWidget *Filter_flou;
GtkWidget *Filter_otsu;
GtkWidget *Filter_canny;
GtkWidget *Auto_rot;
GtkWidget *Print_line;
GtkWidget *Print_case;
//Solve_buttons
GtkWidget *OCR_button;
GtkWidget *Solver_button;

GtkWidget *Save;
GtkWidget *Name_sudoku;
//Page 1
GtkWidget *Image_sudoku;
//Page 2
GtkWidget *View_Stack;
GtkWidget *Text_view;
GtkTextBuffer *TextBuffer;



void on_changed_text(GtkTextBuffer *t);


// === TOOLS === //
//Function to concat a string
char* concat(const char *s1, const char *s2)
{
    char *result = malloc(strlen(s1) + strlen(s2) + 1); 
    // +1 for the null-terminator

    if(result==NULL)                     
    {
        errx(1,"Error : Memory not allocated");
    }
    strcpy(result, s1);
    strcat(result, s2);
    return result;
}

void readgrid()
{
    FILE *f = fopen("grid_00", "rb");
    fseek(f, 0, SEEK_END);
    long fsize = ftell(f);
    fseek(f, 0, SEEK_SET);  /* same as rewind(f); */

    gridc = malloc(fsize + 1);
    fread(gridc, 1, fsize, f);
    fclose(f);

    gridc[fsize] = 0;

}

// === TOOLS === //


int main(int argc, char *argv[])
{
    gtk_init(&argc, &argv);

    builder = gtk_builder_new_from_file("OCR_app.glade");

    MainWindow = GTK_WIDGET(gtk_builder_get_object(builder,"MainWindow"));
    g_signal_connect(MainWindow,"destroy",G_CALLBACK(gtk_main_quit),NULL);

    gtk_builder_connect_signals(builder,NULL);

    // === MENU ===
    Menu_box = GTK_WIDGET(gtk_builder_get_object(builder,"Menu_box"));
    Image_chooser = GTK_WIDGET(gtk_builder_get_object(builder,"Image_chooser"));
    Net_chooser = GTK_WIDGET(gtk_builder_get_object(builder,"Net_chooser"));
    Net_name = GTK_WIDGET(gtk_builder_get_object(builder,"Net_name"));
    Net_button = GTK_WIDGET(gtk_builder_get_object(builder,"Net_button"));
    Net_test = GTK_WIDGET(gtk_builder_get_object(builder,"Net_test"));
    Net_res = GTK_WIDGET(gtk_builder_get_object(builder,"Net_res"));
    Rot_left = GTK_WIDGET(gtk_builder_get_object(builder,"Rot_left"));
    Rot_right = GTK_WIDGET(gtk_builder_get_object(builder,"Rot_right"));
    Filter_flou = GTK_WIDGET(gtk_builder_get_object(builder,"Filter_flou"));
    Filter_otsu = GTK_WIDGET(gtk_builder_get_object(builder,"Filter_otsu"));
    Filter_canny = GTK_WIDGET(gtk_builder_get_object(builder,"Filter_canny"));
    Auto_rot = GTK_WIDGET(gtk_builder_get_object(builder,"Auto_rot"));
    Print_line = GTK_WIDGET(gtk_builder_get_object(builder,"Print_line"));
    Print_case = GTK_WIDGET(gtk_builder_get_object(builder,"Print_case"));
    OCR_button = GTK_WIDGET(gtk_builder_get_object(builder,"OCR_button"));
    Solver_button = GTK_WIDGET(gtk_builder_get_object(builder,"Solver_button"));
    /// === MENU ===

    /// === Main Area ===
    Save=GTK_WIDGET(gtk_builder_get_object(builder,"Save"));
    Image_sudoku=GTK_WIDGET(gtk_builder_get_object(builder,"Image_sudoku"));
    Name_sudoku=GTK_WIDGET(gtk_builder_get_object(builder,"Name_sudoku"));
    View_Stack=GTK_WIDGET(gtk_builder_get_object(builder,"View_Stack"));
    Text_view=GTK_WIDGET(gtk_builder_get_object(builder,"Text_view"));

    /// === Main Area ===

    TextBuffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(Text_view));

    g_signal_connect(TextBuffer,"changed",G_CALLBACK(on_changed_text), NULL);

    gtk_widget_show(MainWindow);

    gtk_main();

    return EXIT_SUCCESS;

}

void exit_app()
{
    printf("Exit app\n");
    gtk_main_quit();
}

void on_Image_chooser_file_set(GtkFileChooserButton *fi)
{
    sprintf(pathImg,"%s",gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(fi)));
    printf("File Name = %s\n",pathImg);
    gtk_image_set_from_file(GTK_IMAGE(Image_sudoku),pathImg);   
}

void on_Net_chooser_file_set(GtkFileChooserButton *fi)
{
    sprintf(pathNet,"%s",gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(fi)));
    printf("File Name = %s\n",pathNet);
}

void on_Net_name_changed(GtkEntry *t)
{
    sprintf(pathNet,"./obj/%s.netOCR",gtk_entry_get_text(t));
    printf("PathNet : %s\n",pathNet); 
}


void on_Net_button_clicked(GtkButton *b)
{
    printf("Net button\n");
    if(pathNet != NULL) 
    {   
        printf("New Net %s\n",pathNet);
        //new_net(&pathNet);
    }
}

void on_Net_test_clicked(GtkButton *b)
{
    FILE *fnet = fopen(pathNet,"r");
    if (fnet != NULL)
    {
        //xr(1,fnet,NULL);
        printf("Test Network : %f\n",rate);
        char res[64];
        sprintf(res,"Resultat : %i/100",(int)rate);
        gtk_label_set_text(GTK_LABEL(Net_res), (const gchar*) res);
    }
}

void on_Rot_left_clicked(GtkButton *b)
{
    printf("Rotation Left\n");
}

void on_Rot_right_clicked(GtkButton *b)
{
    printf("Rotation Right\n");
}

void on_Filter_flou_clicked(GtkButton *b)
{
    printf("Filter Flou\n");
}

void on_Filter_otsu_clicked(GtkButton *b)
{
    printf("Filter Otsu\n");
}

void on_Filter_canny_clicked(GtkButton *b)
{
    printf("Filter Canny\n");
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
    readgrid();
    printf("%s",gridc);
    gtk_text_buffer_set_text(TextBuffer,(const gchar *) gridc,(gint) -1 );
    gtk_widget_hide(Save);

}

void on_Case_clicked(GtkButton *b)
{
    printf("Case clicked\n");
}

void on_Save_clicked(GtkButton *b)
{
    printf("Save clicked\n");
}

void on_changed_text(GtkTextBuffer *t)
{
    printf("Buffer Changed\n");
    gtk_widget_show(Save);
}
