#include "dusk.h"
#include "scenes.h"

/** virtual position */
typedef struct VPos {
    short x, y;
} VPos;

Sprite* sPlayer;
VPos pPlayer;
Anim aPlayerWalk;

const int MOVEMENT_SPEED = 1;

void game_start(){
    dusk_init_graphics_mode0();


    // load sprite atlas
    dusk_sprites_init();
    SpriteAtlas atlas = dusk_load_atlas("a_player");
    dusk_sprites_upload_atlas(&atlas);

    //init sprite
    sPlayer = dusk_sprites_make(0, 32, 32, //32 by 32 only working with 2 sprites... hm
                               (Sprite){
                                    //.x = SCREEN_WIDTH / 2 - 8,
                                    //.y = SCREEN_HEIGHT / 2 - 8,
                                    //.base_tid = 0,
                                    .page = 0,
                                    .flags = SPRITEFLAG_PRIORITY(3) //don't know what this does
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

    //push to sprite
    sPlayer->x = pPlayer.x;
    sPlayer->y = pPlayer.y;

    //animate sprite
    dusk_sprites_anim_play(sPlayer, &aPlayerWalk);

    //blit sprite data from vram
    dusk_sprites_update();
}

void game_end(){

}

Scene game_scene = {
    .start = game_start,
    .update = game_update,
    .end = game_end,
};