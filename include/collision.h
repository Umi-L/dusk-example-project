#pragma once

#include "types.h"

bool AABBCollision(AABB rect1, AABB rect2);

void colliderFromOffsets(VPos pos, AABB offsets, AABB* dest);