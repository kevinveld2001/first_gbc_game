#include <gb/gb.h>
#include <stdio.h>
#include "../sprite/man.c"
#include "../sprite/backgroundTiles.c"
#include "../maps/backgroundMap.c"

void main() {
    //init background
    set_bkg_data(0, 2, backgroundTiles);
    set_bkg_tiles(0, 0, 20, 18, backgroundMap);
    
    SHOW_BKG;
    DISPLAY_ON;

    //init sprites
    set_sprite_data(0, 2, manSprite);
    set_sprite_tile(0, 0);
    move_sprite(0, 8, 16);
    SHOW_SPRITES;

    //set man vars
    int manAnimation = 0;
    int manX = 0;
    int manY = 0;
    int manSpeed = 1;
    BOOLEAN swapAnimation = FALSE;


    while (1)
    {
        delay(50);
        swapAnimation = !swapAnimation;
        if (swapAnimation) {
            set_sprite_tile(0, manAnimation);
            if (manAnimation == 0) manAnimation = 1;
            else manAnimation = 0;
        }

        uint8_t btn = joypad();

        if (btn & J_A)
        {
            btn = btn ^ J_A;
            manSpeed = 2;
        } else {
            manSpeed = 1;
        }
        

        if (btn & J_RIGHT && !(manX + manSpeed > 152))
        {
            scroll_sprite(0, manSpeed, 0);
            manX += manSpeed;
        }
        if(btn & J_LEFT && !(manX - manSpeed < 0))
        {
            scroll_sprite(0, -manSpeed, 0);
            manX -= manSpeed;
        }
        if (btn & J_UP && !(manY - manSpeed < 0))
        {
            scroll_sprite(0, 0, -manSpeed);
            manY -= manSpeed;
        }
        if (btn & J_DOWN && !(manY + manSpeed > 136))
        {
            scroll_sprite(0, 0, manSpeed);
            manY += manSpeed;
        } 
        
    }
}