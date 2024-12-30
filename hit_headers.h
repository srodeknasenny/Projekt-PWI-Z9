#include <stdlib.h>
#include <stdio.h>
#include "raylib.h"

#define WIDTH 550//szerokość ekranu
#define HEIGHT 550//wysokość ekranu
#define SPACE 10//przerwa między kafelkami
#define SQUARE_SIZE 44 //a imię jego czterdzieści i cztery
#define BEGIN_DRAW_X 10//współrzędne od których zaczynamy rysować kafelki
#define BEGIN_DRAW_Y 10

struct array_cordinals{//współrzędne w sensie trafiania statku
    int x;//od 0 do 9
    int y;//od 0 do 9
};

struct real_cordinals{//współrzędne statku w okienku RayLiba (lewego górnego rogu)
    int x;//od zera do WIDTH
    int y;//od zera do HEIGHT
};

/*dwa takie same structy i do tego identyczne jak pair w structs.h 
do tego coordinals powinno być przez dwa o, ale ja to naprawię w najbliższej przyszłości.
Mimo że to głupota, to jednak array_cordinals oraz real_cordinals wygląda czytelniej, kiedy analizuje się god
*/
struct array_cordinals* Get_array_cordinals();//przekształca położenie myszki na położenie statku na planszy
struct real_cordinals* Arrays_to_real(struct array_cordinals* cordinal);/*przekształca współrzędne statku 
na planszy na wpółrzędne lewego górnego rogu w okienku w RayLib
*/
void draw_squares();//rysuje kafelki
struct real_cordinals* colour_square(Color colour);/*koloruje aktualnie wskazywany przez myszkę kafelek 
na dany kolor i zwraca współrzędne lewego górnego rogu kafelka (niewykorzystana w hit.c)*/
void recolour_square(struct real_cordinals* point, Color colour);/*koloruje kafelek o danych współrzędnych 
lewego górnego rogu na dany kolor*/
void check_shot(int enemyships[10][10], struct array_cordinals* point); //sprawdza, czy trafiliśmy w okręt wroga