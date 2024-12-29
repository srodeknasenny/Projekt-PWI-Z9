#include <stdlib.h>
#include <stdio.h>
#include "raylib.h"
#include "hit_headers.h"

/*
hit_functions.c oraz hit_headers.h (później usunę ten komentarz, ale na razie wolę mieć zawartość w pogotowiu)
#define WIDTH 550//szerokość ekranu
#define HEIGHT 550//wysokość ekranu
#define SPACE 10//przerwa między kafelkami
#define SQUARE_SIZE 44 //a imię jego czterdzieści i cztery
#define BEGIN_DRAW_X 10
#define BEGIN_DRAW_Y 10

struct array_cordinals{//współrzędne w sensie trafiania statku
    int x;//od 0 do 9
    int y;//od 0 do 9
};

struct real_cordinals{//współrzędne statku w okienku RayLiba (lewego górnego rogu)
    int x;//od zera do WIDTH
    int y;//od zera do HEIGHT
};

struct array_cordinals* Get_array_cordinals(){//przekształca położenie myszki na położenie statku na planszy
    struct array_cordinals* cordinal = (struct array_cordinals*)malloc(sizeof(struct array_cordinals));
    if(cordinal==NULL) return NULL;
    int x = GetMouseX();
    int y = GetMouseY();
    x-= BEGIN_DRAW_X;//odejmujemy przestrzeń niezajętą przez statki
    y-= BEGIN_DRAW_Y;
    x = x/(SQUARE_SIZE+SPACE);
    y = y/(SQUARE_SIZE+SPACE);
    cordinal->x=x;
    cordinal->y=y;
    return cordinal;
};

struct real_cordinals* Arrays_to_real(struct array_cordinals* cordinal){
    if(cordinal->x>9 || cordinal->y>9) return NULL;
    struct real_cordinals* point = (struct real_cordinals*)malloc(sizeof(struct real_cordinals));
    if(point==NULL) return NULL;
    point->x = BEGIN_DRAW_X + (cordinal->x * (SQUARE_SIZE + SPACE));
    point->y = BEGIN_DRAW_Y + (cordinal->y * (SQUARE_SIZE + SPACE));
    return point;
};

void draw_squares(){
    for(int x = BEGIN_DRAW_X; x< SPACE + ((SPACE + SQUARE_SIZE)*10); x = x + SQUARE_SIZE+SPACE){
        for(int y = BEGIN_DRAW_Y; y < SPACE + ((SPACE + SQUARE_SIZE)*10); y = y + SQUARE_SIZE+SPACE){
            BeginDrawing();
            DrawRectangle(x, y, SQUARE_SIZE, SQUARE_SIZE, BLUE);
            EndDrawing();
        }
    }
}

struct real_cordinals* colour_square(Color colour){
    struct array_cordinals* ArPoint = Get_array_cordinals();
    if(ArPoint->x < 0 || ArPoint->y < 0 || ArPoint->x > 9 || ArPoint->y > 9) return NULL;
    struct real_cordinals* point = Arrays_to_real(ArPoint);
    if(point!=NULL){
        BeginDrawing();
        DrawRectangle(point->x, point->y, SQUARE_SIZE, SQUARE_SIZE, colour);
        EndDrawing();
    }
    free(ArPoint);
    return point;
}

void recolour_square(struct real_cordinals* point, Color colour){
    if(point!=NULL){
        BeginDrawing();
        DrawRectangle(point->x, point->y, SQUARE_SIZE, SQUARE_SIZE, colour);
        EndDrawing();
    }
}*/
/*Ogólnie efekt działania funkcji z hit_functions.h ma być taki, że kafelki (które drukują się na ekranie),
mają się zabarwiać na kolor magenta, gdy się na nie najedzie (jasnofioletowy). Inne informacje - lektura hit_headers.h*/
int main(){
    //Przyjmuję, że przerw będzie 11 (dwie na zewnątrz kafelków i 9 między kafelkami)
    bool drawed = false;
    struct real_cordinals* prev = NULL;
    struct real_cordinals* cur = NULL;
    SetTargetFPS(60);
    if(SPACE >= WIDTH/ 11&& SPACE >= WIDTH/ 11){
        puts("Please decrease the space or increase the screen height in code");
        return 1;
    }
    InitWindow(WIDTH, HEIGHT, "Traf");
    while(!WindowShouldClose()){
        struct array_cordinals* ArPoint = Get_array_cordinals();
        if(ArPoint->x>=0 && ArPoint->y>=0 && ArPoint->x<=WIDTH && ArPoint){
            cur = Arrays_to_real(ArPoint);
        }
        free(ArPoint);
        //printf("%i %i\n", RlPoint->x, RlPoint->y);
        //free(ArPoint);
        //free(RlPoint);
        BeginDrawing();
        if(drawed==false){
            ClearBackground(WHITE);
            draw_squares();
            drawed = true;
        }
        if(prev==NULL || (cur->x!=prev->x || cur->y!=prev->y)){
            recolour_square(cur, MAGENTA);
            if(prev!=NULL) recolour_square(prev, BLUE);
            prev = cur;
        }
        EndDrawing();
    }
    if(prev!=NULL) free(prev);
    if(cur!=NULL) free(cur);
    CloseWindow();
}