#include <gb/gb.h>
#include <gb/cgb.h>
#include <stdio.h>
#include "sprite/backgroundTiles.h"
#include "maps/backgroundMap.h"
#include "player.h"

const UWORD backgroundPallet[] = {
    backgroundTilesCGBPal0c0,    backgroundTilesCGBPal0c1,    backgroundTilesCGBPal0c2,    backgroundTilesCGBPal0c3,
    backgroundTilesCGBPal1c0,    backgroundTilesCGBPal1c1,    backgroundTilesCGBPal1c2,    backgroundTilesCGBPal1c3,
    backgroundTilesCGBPal2c0,    backgroundTilesCGBPal2c1,    backgroundTilesCGBPal2c2,    backgroundTilesCGBPal2c3,
};

const UWORD playerPallet[] = {
    RGB_WHITE,    RGB_LIGHTGRAY,    RGB_DARKGRAY,    RGB_BLACK,
};
void main() {
    set_sprite_palette(0, 1, &playerPallet[0]);
    set_sprite_prop(0,0);
    initPlayer();


    //init background
    set_bkg_data(0, 6, backgroundTiles);
    set_bkg_palette(0, 3, &backgroundPallet[0]);

    VBK_REG = 1;
    set_bkg_tiles(0, 0, backgroundMapWidth, backgroundMapHeight, backgroundMapPLN1);
    VBK_REG = 0;
    set_bkg_tiles(0, 0, backgroundMapWidth, backgroundMapHeight, backgroundMapPLN0);

    char walkebleTiles[] = {0, 4, 5, 0, 0, 0, 0, 0, 0, 0};
    setPlayerHitboxMap(backgroundMap, backgroundMapWidth, backgroundMapHeight, walkebleTiles);
    SHOW_BKG;
    DISPLAY_ON;



    while (1)
    {
        delay(50);
        updatePlayer();
    }
}