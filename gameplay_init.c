#include "raylib.h"
#include "structs.h"
#include "functions.h"
/*main do testowania gameplayu*/
int main()
{
    board *playerBoard = initboard();
    board *enemyBoard = initboard();

    //reczne dodanie statkow do debugowania (w przyszlosci zmienione na to co dostaniemy od gracza)
    ship *playerShip = initship(3);
    ship *enemyShip = initship(3);
    pair playerStart = {2, 2};
    pair enemyStart = {4, 4};
    placeStatek(playerBoard, playerShip, playerStart, 2);
    placeStatek(enemyBoard, enemyShip, enemyStart, 3);

    //funkcja od grania - wywoluje tez playagain (czyli w zasadzie reset gry, w ktorym czysci i zaczyna od poczatku)
    PlayGame(playerBoard, enemyBoard,playerShip,enemyShip);

    //sprzatam i wychodze
    delboard(playerBoard);
    delboard(enemyBoard);
    delship(playerShip);
    delship(enemyShip);

    return 0;
}