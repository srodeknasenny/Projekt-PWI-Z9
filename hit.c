#include <stdlib.h>
#include <stdio.h>
#include "raylib.h"

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
}

void check_shot(int enemyships[10][10], struct array_cordinals* point){
    if(point==NULL || enemyships[point->y][point->x] > 1 || enemyships[point->y][point->x] < 0) return;
    if(enemyships[point->y][point->x]==0) enemyships[point->y][point->x] = 2; //oznacza pudło
    else enemyships[point->y][point->x] = 3;//oznacza trafienie (na razie w ogólności - później 3 może będzie oznaczało trafiony niezatopiony)
}
/*
                                                ***ZMIANY W TYM COMMICIE***
Dodałem przykładową planszę (oczywiście jest ona tylko do testów) oraz (co najważniejsze) pudłowanie i trafianie 
(bez rozróżnienia na zatapianie i niezatapianie). Oznaczenia kolorystyczne:
NIEBIESKI - plansza w stanie nienaruszonym
MAGENTA (jasnofioletowy) - kafelek, na który wskazuje myszka
FIOLETOWY (ciemniejszy niż magenta) - pudło (oczywiście, żeby strzelić, trzeba nacisnąć lewy przycisk myszy)
ŻÓŁTY - trafienie
Oznaczenia tablicowe:
0 - brak okrętów
1 - obecność okrętu
2 - pudło
3 - trafienie
Proszę zwracać uwagę na pozostałości po agresywnym, wulgarnym debugingu, ale raczej je wyeliminowałem.
Na pierwszy rzut oka ten commit dodaje tylko głupią funkcję, co jest niewielkim postępem, ale warto zapoznać się z logiką
działania funkcji main (w szczególności z mechaniką kolorowania kafelków), bo nie jest ona oczywista i kosztowała mnie wiele
trudu. Nawet Chatgpt ogłupiał.
*/
int main(){
    //Przyjmuję, że przerw będzie 11 (dwie na zewnątrz kafelków i 9 między kafelkami)
    int enemyships[10][10] = {
        {1, 0, 1, 0, 1, 0, 1, 0, 1, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 1, 1, 0, 1, 1, 0, 1, 1, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {1, 1, 0, 1, 1, 1, 0, 1, 1, 1},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {1, 1, 1, 0, 1, 1, 1, 1, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {1, 1, 1, 1, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
    };
    bool drawed = false;
    struct real_cordinals* prev = NULL;
    struct array_cordinals* prev_array = NULL;
    struct real_cordinals* cur = NULL;
    SetTargetFPS(60);
    if(SPACE >= WIDTH/ 11&& SPACE >= WIDTH/ 11){
        puts("Please decrease the space or increase the screen height in code");
        return 1;
    }
    InitWindow(WIDTH, HEIGHT, "Traf");
    while(!WindowShouldClose()){
        struct array_cordinals* ArPoint = Get_array_cordinals();
        if(ArPoint->x>=0 && ArPoint->y>=0 && ArPoint->x<=9 && ArPoint->y<=9){
            cur = Arrays_to_real(ArPoint);
            if(IsMouseButtonDown(MOUSE_BUTTON_LEFT)){
                if(ArPoint->x>=0 && ArPoint->y>=0 && ArPoint->x<=9 && ArPoint->y<=9){
                    //puts("Kiwi, JESLI BEDZIE TERAZ SEGFAULT TO Cytryna, BO NIE WYCHODZE POZA Jagodziana TABLICE");
                    check_shot(enemyships, ArPoint);
                    //printf("%i\n", enemyships[ArPoint->y][ArPoint->x]);
                }
            }
        }
        BeginDrawing();
        if(drawed==false){
            ClearBackground(WHITE);
            draw_squares();
            drawed = true;
        }
        if(ArPoint->x>=0 && ArPoint->y>=0 && ArPoint->x<=9 && ArPoint->y<=9 && enemyships[ArPoint -> y][ArPoint -> x]==2){
            recolour_square(cur, VIOLET);//pudło oznaczam fioletowym
        }
        else if(ArPoint->x>=0 && ArPoint->y>=0 && ArPoint->x<=9 && ArPoint->y<=9 && enemyships[ArPoint -> y][ArPoint -> x]==3){
            recolour_square(cur, YELLOW);//pudło oznaczam fioletowym
        }
        else if(ArPoint->x>=0 && ArPoint->y>=0 && ArPoint->x<=9 && ArPoint->y<=9 && enemyships[ArPoint -> y][ArPoint -> x]<2){
            recolour_square(cur, MAGENTA);
            if((prev!=NULL && prev_array!=NULL)
            && (prev_array->x>=0 && prev_array->y>=0 && prev_array->x<=9 && prev_array->y<=9)
            && (prev->x!=cur->x || prev->y!=cur->y) && (enemyships[prev_array->y][prev_array->x]<2)){
                recolour_square(prev, BLUE);
            }
            
                if (prev != NULL) {
    free(prev);
    prev = NULL;
}

prev = cur;  // Teraz przypisanie do prev

if (prev_array != NULL) {
    free(prev_array);
    prev_array = NULL;  // Poprawnie ustawiamy prev_array na NULL
}

prev_array = ArPoint;  // Teraz przypisujemy ArPoint do prev_array

        }
        EndDrawing();
    }
    //if(prev!=NULL) free(prev);
    if(cur!=NULL) free(cur);
    //if(prev_array!=NULL) free(prev_array);
    CloseWindow();
}