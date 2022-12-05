#include "collision.h"
#include "types.h"

//debug
#include "tonc_mgba.h"


bool AABBCollision(AABB rect1, AABB rect2){
    if(
        rect1.p1->x < rect2.p2->x &&
        rect1.p2->x > rect2.p1->x &&
        rect1.p1->y < rect2.p2->y &&
        rect1.p2->y > rect2.p1->y
    ){
        return true;

    }
    return false;
}

void colliderFromOffsets(VPos pos, AABB offsets, AABB* dest){
    // ObjectPoint p1 = (ObjectPoint) {pos.x + offsets.p1->x, pos.y + offsets.p1->y};
    // ObjectPoint p2 = (ObjectPoint) {pos.x + offsets.p2->x, pos.y + offsets.p2->y};

    dest->p1->x = pos.x + offsets.p1->x;
    dest->p1->y = pos.y + offsets.p1->y;
    dest->p2->x = pos.x + offsets.p2->x;
    dest->p2->y = pos.y + offsets.p2->y;


    // mgba_log_int_with_prefix("infunc p2x: ", dest->p2->x);
    // mgba_log_int_with_prefix("infunc p2y: ", dest->p2->y);
}