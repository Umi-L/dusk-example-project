#include <std_utils.h>

#include "dusk.h"
#include "scenes.h"
#include "tonc_mgba.h"
#include "types.h"

AABB colliders[50];
int num_colliders = 0;

Sprite* sPlayer;
VPos pPlayer;
Anim aPlayerWalk;

Map map;

BackgroundPoint shift;

const int MOVEMENT_SPEED = 1;

void logColliderLocations(){
    mgba_log("LOGGING COLLIDER LOCATIONS");

    for (int i = 0; i < map.numObjects; i++){
        MapObject obj = map.objects[i];

        mgba_log("X");
        mgba_log_int(obj.position.y);
        mgba_log("Y");
        mgba_log_int(obj.position.y); 

        mgba_log(obj.name);
    }
}

void loadMapColliders(){
    num_colliders = 0;

    for (int i = 0; i < map.numObjects; i++){
        // mgba_log_int_with_prefix("currentobj posx: ", obj.position.x);
        // mgba_log_int_with_prefix("currentobj posy: ", obj.position.y);

        // mgba_log_int_with_prefix("if 0 then even else odd: ", i % 2);

        if (i % 2 == 0){ //even
            colliders[i/2].p1 = &map.objects[i].position;

            // mgba_log("even");
        }
        else{
            colliders[i/2].p2 = &map.objects[i].position;
            num_colliders++;

            mgba_log_int_with_prefix("\n\nLoaded collider#: ", i/2);
            mgba_log_int_with_prefix("p1 x: ", colliders[i/2].p1->x);
            mgba_log_int_with_prefix("p1 y: ", colliders[i/2].p1->y);
            mgba_log_int_with_prefix("p2 x: ", colliders[i/2].p2->x);
            mgba_log_int_with_prefix("p2 y: ", colliders[i/2].p2->y);
        }

        
    }
}

void logPlayerLocation(){
    mgba_log("\nPlayerPos");

    mgba_log_int_with_prefix("Player x: ", sPlayer->x);
    mgba_log_int_with_prefix("Player y: ", sPlayer->y);
}

bool pointInRect( int x1, int y1, 
                int x2, int y2, 
                //point
                int px, int py)
{
    if (px > x1 && px < x2 && py > y1 && py < y2)
        return true;

    return false;
}

void game_start(){
    //test logging
    mgba_log("LOGGING START");

    //init vars
    shift = (BackgroundPoint){0, 0};

    //init graphics
    dusk_init_graphics_mode0();

    // set up background
    map = dusk_load_map("testmap");
    map_init_registers();
    map_set_onscreen(map);

    logColliderLocations();
    loadMapColliders();

    // load sprite atlas
    dusk_sprites_init();
    SpriteAtlas atlas = dusk_load_atlas("a_player");
    dusk_sprites_upload_atlas(&atlas);


    //init sprite
    sPlayer = dusk_sprites_make(0, 32, 32, //32 by 32 only working with 2 sprites... hm
                               (Sprite){
                                    //.x = SCREEN_WIDTH / 2 - 8,
                                    //.y = SCREEN_HEIGHT / 2 - 8,
                                    //.base_tid = 32,
                                    //.page = 0,
                                    //.flags = SPRITEFLAG_PRIORITY(3) //don't know what this does
                                });
    


    //init anim with frames 0-2
    aPlayerWalk = MAKE_ANIM(0, 2);
}

void game_update(){
    dusk_frame();


    // input
    int y_move = key_tri_vert();
    int x_move = key_tri_horz();

    VPos pPossiblePosition = pPlayer;

    //update player position
    pPossiblePosition.x += x_move * MOVEMENT_SPEED;
    pPossiblePosition.y += y_move * MOVEMENT_SPEED;

    bool validPosition = true;

    //collision
    for (int i = 0; i < num_colliders; i++){
        //mgba_log_int(i);

        AABB obj = colliders[i];

        //mgba_log_int(colliders[i].p2->y);

        if(pointInRect(obj.p1->x, obj.p1->y, obj.p2->x, obj.p2->y, pPossiblePosition.x, pPossiblePosition.y)){
            validPosition = false;
        }

        //logPlayerLocation();
    }

    if (validPosition){

        pPlayer = pPossiblePosition;

        //push to sprite
        sPlayer->x = pPlayer.x;
        sPlayer->y = pPlayer.y;
    }

    //animate sprite
    dusk_sprites_anim_play(sPlayer, &aPlayerWalk);

    // update map position
    map_shift(map, shift);

    //blit sprite data from vram
    dusk_sprites_update();
}

void game_end(){}



Scene game_scene = {
    .start = game_start,
    .update = game_update,
    .end = game_end,
};