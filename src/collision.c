#include "collision.h"
#include "types.h"


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