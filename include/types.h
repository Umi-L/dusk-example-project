#pragma once

#include "dusk.h"

typedef struct VPos {
    short x, y;
} VPos;

typedef struct AABB {
    ObjectPoint* p1, *p2;
} AABB;