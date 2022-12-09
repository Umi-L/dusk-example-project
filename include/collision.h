#pragma once

#include "types.h"

bool AABBCollision(AABB rect1, AABB rect2);

void colliderFromOffsets(VPos pos, AABB offsets, AABB* dest);

bool pointInRect( int x1, int y1, 
                int x2, int y2, 
                //point
                int px, int py);