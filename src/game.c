#include <std_utils.h>

#include "dusk.h"
#include "scenes.h"
#include "tonc_mgba.h"
#include "types.h"
#include "collision.h"

AABB colliders[50];
int num_colliders = 0;

Sprite* sPlayer;
VPos pPlayer;
Anim aPlayerWalk;
const AABB playerColliderOffsets = {&(ObjectPoint){0,0},&(ObjectPoint){32,32}};

AABB mapBounds = {&(ObjectPoint){0,0}, &(ObjectPoint){256, 256}}; 

Map map;

BackgroundPoint shift;

const float MOVEMENT_SPEED = 3;

void logColliderLocations(){
    mgba_log("LOGGING COLLIDER LOCATIONS");

    for (int i = 0; i < map.numObjects; i++){
        MapObject obj = map.objects[i];

        mgba_log("\n");

        mgba_log(obj.name);

        mgba_log_int_with_prefix("x: ", obj.position.y);
        mgba_log_int_with_prefix("y: ", obj.position.y);
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

/** update background and sprite from pos */
void adjust_background_to_sprite(VPos pos, Sprite *sprite) {
    shift.x = pPlayer.x;
    shift.y = pPlayer.y;


    //offset to middle
    shift.x -= SCREEN_WIDTH/2 - 16;
    shift.y -= SCREEN_HEIGHT/2 - 16;

    //min bounds
    if (shift.x < mapBounds.p1->x){
        shift.x = mapBounds.p1->x;
    }
    if (shift.y < mapBounds.p1->y){
        shift.y = mapBounds.p1->y;
    }


    //max bounds
    if (shift.x > mapBounds.p2->x){
        shift.x = mapBounds.p2->x;
    }
    if (shift.y > mapBounds.p2->y){
        shift.y = mapBounds.p2->y;
    }


    sPlayer->x = (SCREEN_WIDTH/2 - 16) - ((shift.x + SCREEN_WIDTH/2 - 16) - pPlayer.x);
    sPlayer->y = (SCREEN_HEIGHT/2 - 16) - ((shift.y + SCREEN_HEIGHT/2 - 16) - pPlayer.y);


    map_shift(map, shift);
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

void playerMovement(int xAxis, int yAxis){
    VPos pPossiblePosition = pPlayer;

    short xMovement = xAxis * MOVEMENT_SPEED;
    short yMovement = yAxis * MOVEMENT_SPEED;

    VPos xPossiblePosition = pPossiblePosition;
    xPossiblePosition.x += xMovement;

    VPos yPossiblePosition = pPossiblePosition;
    yPossiblePosition.y += yMovement;

    AABB playerCollider = (AABB){&(ObjectPoint){0,0},&(ObjectPoint){0,0}};
    AABB playerColliderX = (AABB){&(ObjectPoint){0,0},&(ObjectPoint){0,0}};
    AABB playerColliderY = (AABB){&(ObjectPoint){0,0},&(ObjectPoint){0,0}};

    pPossiblePosition.x += xMovement;
    pPossiblePosition.y += yMovement;

    //make colliders
    colliderFromOffsets(xPossiblePosition, playerColliderOffsets, &playerColliderX);
    colliderFromOffsets(yPossiblePosition, playerColliderOffsets, &playerColliderY);
    colliderFromOffsets(pPossiblePosition, playerColliderOffsets, &playerCollider);

    //collision
    bool xValidPosition = true;
    bool yValidPosition = true;

    bool validPosition = true;
    for (int i = 0; i < num_colliders; i++){
        //mgba_log_int(i);

        AABB obj = colliders[i];

        //logPlayerLocation();

        if (AABBCollision(playerCollider, obj)){
            validPosition = false;

            if (AABBCollision(playerColliderX, obj)){
                xValidPosition = false;
            }
            if (AABBCollision(playerColliderY, obj)){
                yValidPosition = false;
            }
        }
    }

    if (validPosition){
        pPlayer = pPossiblePosition;
        adjust_background_to_sprite(pPlayer, sPlayer);
    }
    else if (xValidPosition){
        pPlayer = xPossiblePosition;
        adjust_background_to_sprite(pPlayer, sPlayer);
    }
    else if (yValidPosition){
        pPlayer = yPossiblePosition;
        adjust_background_to_sprite(pPlayer, sPlayer);
    }
}

void game_update(){
    dusk_frame();

    // input
    int yAxis = key_tri_vert();
    int xAxis = key_tri_horz();

    //player movement
    playerMovement(xAxis, yAxis);

    //animate sprite
    dusk_sprites_anim_play(sPlayer, &aPlayerWalk);

    //blit sprite data from vram
    dusk_sprites_update();
}

void game_end(){}



Scene game_scene = {
    .start = game_start,
    .update = game_update,
    .end = game_end,
};