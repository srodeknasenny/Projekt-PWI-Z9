#include <stdlib.h>
#include <stdio.h>
#include "raylib.h"
#include "hit_headers.h"

struct array_cordinals* Get_array_cordinals(){//przekształca położenie myszki na położenie statku na planszy
    struct array_cordinals* cordinal = (struct array_cordinals*)malloc(sizeof(struct array_cordinals));
    if(cordinal==NULL) return NULL;
    int x = GetMouseX();//wczytujemy położenie myszki
    int y = GetMouseY();
    x-= BEGIN_DRAW_X;//odejmujemy przestrzeń niezajętą przez statki
    y-= BEGIN_DRAW_Y;
    x = x/(SQUARE_SIZE+SPACE);//właściwe przekształcenie na współrzędną planszy
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
            DrawRectangle(x, y, SQUARE_SIZE, SQUARE_SIZE, BLUE);//zamiast makr można dodać argumenty do funkcji
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
}

void check_shot(int enemyships[10][10], struct array_cordinals* point){
    if(point==NULL || enemyships[point->y][point->x] > 1 || enemyships[point->y][point->x] < 0) return;
    if(enemyships[point->y][point->x]==0) enemyships[point->y][point->x] = 2; //oznacza pudło
    else enemyships[point->y][point->x] = 3;//oznacza trafienie (na razie w ogólności - później 3 może będzie oznaczało trafiony niezatopiony)
}