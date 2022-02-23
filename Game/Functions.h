#pragma once

#include "framework.h"

void moveToLeft();
void moveToRight();
void moveUp();
void moveDown();
void DrawField(HDC hdc);
void newWallLeft();
void newWallRight();
void newWallUp();
void newWallDown();
void destroyWallRight();
void destroyWallLeft();
void destroyWallAround();