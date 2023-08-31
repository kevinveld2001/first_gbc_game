#include <gb/gb.h>
#include <stdio.h>
#include "sprite/backgroundTiles.h"
#include "maps/backgroundMap.h"
#include "player.h"

void main() {
    initPlayer();

    //init background
    set_bkg_data(0, 2, backgroundTiles);
    set_bkg_tiles(0, 0, 20, 18, backgroundMap);
    char walkebleTiles[] = {0x00};
    setPlayerHitboxMap(backgroundMap, 20, 18, walkebleTiles);

    SHOW_BKG;
    DISPLAY_ON;


    while (1)
    {
        delay(50);
        updatePlayer();
    }
}