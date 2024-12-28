#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "raylib.h"
#include "structs.h"

// Declare functions for external usage
void UpdateHitbox(struct ship* s);
void mouse_drag(int key, struct ship* s, Color color);
void rotate(int key, Image* sprite, Texture2D* texture);
void UpdateShip(bool* isDragging, struct ship* s);

#endif // FUNCTIONS_H
