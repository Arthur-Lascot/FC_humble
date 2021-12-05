#include <stdlib.h>
#include <stdio.h>
#include <gtk/gtk.h>
#include <err.h>

#include "./OCR/xor.h"
#include "./Image_processing/main_hough.h"
#include "./Otsu/rotation.h"

// == Variables == //

char pathNet[45];
char pathImg[128];

char nameImg[128];

char *gridc;

// === GTK === //

GtkWidget *MainWindow;
GtkBuilder *builder;

GtkWidget *Menu_box;
GtkWidget *Image_chooser;
GtkWidget *Image_loader;
//Net Box
//Net_tile
GtkWidget *Net_chooser;
GtkWidget *Net_loader;
//Create_net
GtkWidget *Net_name;
GtkWidget *Net_button;
GtkWidget *Net_test;
GtkWidget *Net_check;
GtkWidget *Net_res;
//Solver
//OCR_title
//Rot_man
GtkWidget *Rot_man;
GtkWidget *Rot_spin;
//OCR_step
GtkWidget *Gauss_1;
GtkWidget *Gauss_2;
GtkWidget *Gauss_3;
GtkWidget *Filter_median;

GtkWidget *Otsu_spin;
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
    printf("Name grid enter : %s\n", nameGrid);
    FILE *f = fopen(nameGrid, "rb");
    if (f == NULL)
    {
        printf("Can not open this grid\n");
    }
    else if (f != NULL)
    {
        printf("Grid exist !\n");
        fseek(f, 0, SEEK_END);
        long fsize = ftell(f);
        fseek(f, 0, SEEK_SET);

        gridc = malloc(fsize + 1);
        fread(gridc, 1, fsize, f);
        gridc[fsize] = 0;
    
        fclose(f);
    }
    else 
    {
        printf("Can not open this grid\n");
    }
}

void extractName()
{
    int i = 0;
    int indexlast = 0;
    while (pathImg[i] != 0 && pathImg[i] != ' ')
    {
        if (pathImg[i] == '/')
            indexlast = i;
        i++;
    }
    indexlast++;
    int j = 0;
    while (pathImg[indexlast] != 0 && pathImg[indexlast] != ' ')
    {
        nameImg[j] = pathImg[indexlast];
        indexlast++;
        j++;
    }
}

void saveGrid()
{
    FILE *f = fopen(nameGrid,"w");
    fprintf(f,"%s",gridc);
    fclose(f);
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
    Image_loader = GTK_WIDGET(gtk_builder_get_object(builder,"Image_loader"));
    Net_chooser = GTK_WIDGET(gtk_builder_get_object(builder,"Net_chooser"));
    Net_loader = GTK_WIDGET(gtk_builder_get_object(builder,"Net_loader"));
    Net_name = GTK_WIDGET(gtk_builder_get_object(builder,"Net_name"));
    Net_button = GTK_WIDGET(gtk_builder_get_object(builder,"Net_button"));
    Net_test = GTK_WIDGET(gtk_builder_get_object(builder,"Net_test"));
    Net_check = GTK_WIDGET(gtk_builder_get_object(builder,"Net_check"));
    Net_res = GTK_WIDGET(gtk_builder_get_object(builder,"Net_res"));
    Rot_man = GTK_WIDGET(gtk_builder_get_object(builder,"Rot_man"));
    Rot_spin = GTK_WIDGET(gtk_builder_get_object(builder,"Rot_spin"));
    Gauss_1 = GTK_WIDGET(gtk_builder_get_object(builder,"Gauss_1"));
    Gauss_2 = GTK_WIDGET(gtk_builder_get_object(builder,"Gauss_2"));
    Gauss_3 = GTK_WIDGET(gtk_builder_get_object(builder,"Gauss_3"));
    Filter_median = GTK_WIDGET(gtk_builder_get_object(builder,"Filter_median"));
    Otsu_spin = GTK_WIDGET(gtk_builder_get_object(builder,"Otsu_spin"));
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
    
    sprintf(nameGrid,"./obj/grid_00"); 
    gtk_widget_hide(Save);

    thresh_otsu = 10;

    gtk_main();

    return EXIT_SUCCESS;

}

void exit_app()
{
    printf("Exit app\n");
    gtk_main_quit();
}

void on_Image_chooser_changed(GtkEntry *t)
{
    sprintf(pathImg,"./Ressources/%s",gtk_entry_get_text(t));
    printf("File Image Name = %s\n",pathImg);
    //extractName();
    //printf("Name : %s\n",nameImg);
}

void on_Image_loader_clicked(GtkButton *b)
{
    printf("Image loader...\n");
    int pb = mainHough(-2,&pathImg);
    if (pb)
    {
        printf("ERROR LOADING IMAGE\n");
    }
    sprintf(pathImg,"./Temp/image.bmp");
    gtk_image_set_from_file(GTK_IMAGE(Image_sudoku),pathImg);
}

void on_Net_chooser_changed(GtkEntry *t)
{
    sprintf(pathNet,"./obj/%s",gtk_entry_get_text(t));
    printf("File Net Name = %s\n",pathNet);
}

void on_Net_loader_clicked(GtkButton *b)
{
    printf("Net loader...\n");
    char res[64];
    sprintf(res,"Réseau utilisé : %s",pathNet);
    gtk_label_set_text(GTK_LABEL(Net_check), (const gchar*) res);
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
        new_net(&pathNet);
    }
}

void on_Net_test_clicked(GtkButton *b)
{
    FILE *fnet = fopen(pathNet,"r");
    if (fnet != NULL)
    {
        xr(1,fnet,NULL);
        printf("Test Network : %f\n",rate);
        char res[64];
        sprintf(res,"Resultat : %i/100",(int)rate);
        gtk_label_set_text(GTK_LABEL(Net_res), (const gchar*) res);
    }
}

void on_Rot_man_clicked(GtkButton *b)
{
    printf("Manual Rotation\n");
    gdouble valrot = gtk_spin_button_get_value(GTK_SPIN_BUTTON(Rot_spin));
    degrot = (int)valrot;
    sprintf(pathImg,"./Temp/image.bmp");

    int res = mainHough(-1,&pathImg);
    if (res)
    {
        printf("ERROR MANUAL ROTATE\n");
    }
    sprintf(pathImg,"./Temp/imagerot.bmp");
    gtk_image_set_from_file(GTK_IMAGE(Image_sudoku),pathImg);
    
}

void on_Gauss_1_clicked(GtkButton *b)
{
    printf("Gauss 1\n");
    sprintf(pathImg,"./Temp/use.bmp");
    int res = mainHough(2,&pathImg);
    if (res)
    {
        printf("ERROR GAUSS 1\n");
    }
    sprintf(pathImg,"./Temp/gauss3.bmp");
    gtk_image_set_from_file(GTK_IMAGE(Image_sudoku),pathImg);

}

void on_Gauss_2_clicked(GtkButton *b)
{
    printf("Gauss 2\n");
    sprintf(pathImg,"./Temp/use.bmp");
    int res = mainHough(3,&pathImg);
    if (res)
    {
        printf("ERROR GAUSS 2\n");
    }
    sprintf(pathImg,"./Temp/gauss5.bmp");
    gtk_image_set_from_file(GTK_IMAGE(Image_sudoku),pathImg);

}

void on_Gauss_3_clicked(GtkButton *b)
{
    printf("Gauss 3\n");
    sprintf(pathImg,"./Temp/use.bmp");
    int res = mainHough(4,&pathImg);
    if (res)
    {
        printf("ERROR GAUSS 3");
    }
    sprintf(pathImg,"./Temp/gauss7.bmp");
    gtk_image_set_from_file(GTK_IMAGE(Image_sudoku),pathImg);

}
void on_Filter_median_clicked(GtkButton *b)
{
    printf("Filter Median\n");
    sprintf(pathImg,"./Temp/use.bmp");
    int res = mainHough(5,&pathImg);
    if (res)
    {
        printf("ERROR FILTER MEDIAN\n");
    }
    sprintf(pathImg,"./Temp/median.bmp");
    gtk_image_set_from_file(GTK_IMAGE(Image_sudoku),pathImg);
}

void on_Filter_otsu_clicked(GtkButton *b)
{
    printf("Filter Otsu\n");
    sprintf(pathImg,"./Temp/use.bmp");
    gdouble valotsu = gtk_spin_button_get_value(GTK_SPIN_BUTTON(Rot_spin));
    thresh_otsu = (int)valotsu;
    int res = mainHough(6,&pathImg);
    if (res)
    {
        printf("ERROR FILTER OTSU\n");
    }
    sprintf(pathImg,"./Temp/otsu.bmp");
    gtk_image_set_from_file(GTK_IMAGE(Image_sudoku),pathImg);

}

void on_Filter_canny_clicked(GtkButton *b)
{
    printf("Filter Canny\n");
    sprintf(pathImg,"./Temp/use.bmp");
    int res = mainHough(7,&pathImg);
    if (res)
    {
        printf("ERROR FILTER CANNY\n");
    }
    sprintf(pathImg,"./Temp/canny.bmp");
    gtk_image_set_from_file(GTK_IMAGE(Image_sudoku),pathImg);

}

void on_Auto_rot_clicked(GtkButton *b)
{
    printf("Auto Rotation\n");
    sprintf(pathImg,"./Temp/use.bmp");
    int res = mainHough(8,&pathImg);
    if (res)
    {
        printf("ERROR AUTO ROTATION\n");
    }
    sprintf(pathImg,"./Temp/auto_rotate.bmp");
    gtk_image_set_from_file(GTK_IMAGE(Image_sudoku),pathImg);

}

void on_Print_line_clicked(GtkButton *b)
{
    printf("Print Line\n");
    sprintf(pathImg,"./Temp/use.bmp");
    int res = mainHough(9,&pathImg);
    if (res)
    {
        printf("ERROR PRINT LINE\n");
    }
    sprintf(pathImg,"./Temp/hough.bmp");
    gtk_image_set_from_file(GTK_IMAGE(Image_sudoku),pathImg);

}

void on_Print_case_clicked(GtkButton *b)
{
    printf("Print Case\n");
    sprintf(pathImg,"./Temp/use.bmp");
    int res = mainHough(10,&pathImg);
    if (res)
    {
        printf("ERROR PRINT CASE\n");
    }
    sprintf(pathImg,"./Temp/square.bmp");
    gtk_image_set_from_file(GTK_IMAGE(Image_sudoku),pathImg);

}

void on_OCR_button_clicked(GtkButton *b)
{
    printf("OCR...\n");
    sprintf(pathImg,"./Temp/use.bmp");
    int res = mainHough(11,&pathImg);
    if (res)
    {
        printf("ERROR TRAITMENT\n");
    }
    sprintf(pathImg,"./Temp/square.bmp");
    gtk_image_set_from_file(GTK_IMAGE(Image_sudoku),pathImg);
    readgrid();
    printf("%s",gridc);
    gtk_text_buffer_set_text(TextBuffer,(const gchar *) gridc,(gint) -1 );
   

}

void on_Solver_button_clicked(GtkButton *b)
{
    printf("Solver...\n");
       
    gtk_widget_hide(Save);
    sprintf(pathImg,"./Temp/use.bmp");
    int res = mainHough(0,&pathImg);
    if (res)
    {
        printf("ERROR SOLVE\n");
    }
    sprintf(pathImg,"./Temp/solved.bmp");
    gtk_image_set_from_file(GTK_IMAGE(Image_sudoku),pathImg);
}

/*
void on_Case_clicked(GtkButton *b)
{
    printf("Case clicked\n");
}
*/

void on_Name_sudoku_changed(GtkEntry *t)
{
    sprintf(nameGrid,"./obj/%s",gtk_entry_get_text(t));
    printf("PathNet : %s\n",nameGrid); 

}

void on_Save_clicked(GtkButton *b)
{
    printf("Save clicked\n");
    GtkTextIter begin, end;
    gchar *grid;

    gtk_text_buffer_get_iter_at_offset(GTK_TEXT_BUFFER(TextBuffer),&begin,(gint) 0);
    gtk_text_buffer_get_iter_at_offset(GTK_TEXT_BUFFER(TextBuffer),&end,(gint) -1);

    grid = gtk_text_buffer_get_text(GTK_TEXT_BUFFER(TextBuffer),&begin,&end,TRUE);
    gridc = grid;
    saveGrid();
    printf("\n%s\n",gridc);
    gtk_widget_hide(Save);

}

void on_changed_text(GtkTextBuffer *t)
{
    printf("Buffer Changed\n");
    gtk_widget_show(Save);
}
