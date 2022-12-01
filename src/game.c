#include "dusk.h"
#include "scenes.h"
#include "tonc_mgba.h"

/** virtual position */
typedef struct VPos {
    short x, y;
} VPos;

Sprite* sPlayer;
VPos pPlayer;
Anim aPlayerWalk;

Map map;

BackgroundPoint shift;


const int MOVEMENT_SPEED = 1;

void logColliderLocations(){
    mgba_log("LOGGING COLLIDER LOCATIONS", LOG_ERR);

    for (int i = 0; i < map.numObjects; i++){
        MapObject obj = map.objects[i];

        mgba_log("x: " + obj.position.x, LOG_ERR);
    }
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
    //test log
    mgba_log("LOGGING START", LOG_ERR);
    mgba_log("unfortunately all logs show as errors even if not, LOG_INFO doesn't work", LOG_ERR);

    //init vars
    shift = (BackgroundPoint){0, 0};

    //init graphics
    dusk_init_graphics_mode0();

    // set up background
    map = dusk_load_map("testmap");
    map_init_registers();
    map_set_onscreen(map);

    logColliderLocations();

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

    //update player position
    pPlayer.x += x_move * MOVEMENT_SPEED;
    pPlayer.y += y_move * MOVEMENT_SPEED;

    bool validPosition = true;

    //collision
    for (int i = 0; i < map.numObjects; i++){
        MapObject obj = map.objects[i];

        if (obj.position.x == pPlayer.x && obj.position.y == pPlayer.y){
            pPlayer.x = 50;
        }

        //if(pointInRect())
    }

    if (validPosition){

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