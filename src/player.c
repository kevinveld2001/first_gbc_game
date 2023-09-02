#include <gb/gb.h>
#include <stdio.h>
#include "player.h"
void getPlayerInput();
BOOLEAN checkPlayerCollision(int x, int y);
void screenShake(int times);

struct Player {
    int animation;
    int x;
    int y;
    int speed;
    int xDirection;
    int yDirection;
};
struct Player player = {0, 0, 0, 1, 0, 0};

#define walkebleTilesCount 10
struct Map {
    unsigned char* map;
    int width;
    int height;
    char walkebleTiles[walkebleTilesCount];
};
struct Map playerMap;

void initPlayer() 
{
    set_sprite_data(0, 2, manSprite);
    set_sprite_tile(0, 0);
    move_sprite(0, 8, 16);
    SHOW_SPRITES;
}


void updatePlayer() 
{

    set_sprite_tile(0, player.animation);
    if (player.animation == 0) player.animation = 1;
    else player.animation = 0;

    player.x += player.xDirection * player.speed;
    player.y += player.yDirection * player.speed;
    scroll_sprite(0, player.xDirection * player.speed, player.yDirection * player.speed);

    if (player.x % 8 == 0 && player.y % 8 == 0) 
    {
        player.xDirection = 0;
        player.yDirection = 0;
    }
    if (player.xDirection == 0 && player.yDirection == 0)
    {
        getPlayerInput();
    }

}
void getPlayerInput() 
{
    uint8_t btn = joypad();
    BOOLEAN isCutting = FALSE;
    if (btn & J_A)
    {
        btn = btn ^ J_A;
        player.speed = 2;
    } else {
        player.speed = 1;
    }
    if (btn & J_B)
    {
        btn = btn ^ J_B;
        isCutting = TRUE;
    }

    switch (btn)
    {
    case J_DOWN:
        player.yDirection = 1;
        break;
    case J_UP:
        player.yDirection = -1;
        break;    
    case J_LEFT:
        player.xDirection = -1;
        break;
    case J_RIGHT:
        player.xDirection = 1;
        break;
    default:
        break;
    }
    if (isCutting) {
        int cuttingXPosition = (player.x + player.xDirection * 8) / 8;
        int cuttingYPosition = (player.y + player.yDirection * 8) / 8;
        if (playerMap.map[cuttingXPosition + cuttingYPosition * playerMap.width] == 2) {
            playerMap.map[cuttingXPosition + cuttingYPosition * playerMap.width] = 5;

            screenShake(5);
            VBK_REG = 1;
            set_bkg_tile_xy(cuttingXPosition, cuttingYPosition, 0);
            VBK_REG = 0;
            set_bkg_tile_xy(cuttingXPosition, cuttingYPosition, 5);
        }
    }

    if (checkPlayerCollision(player.x + player.xDirection * 8, player.y + player.yDirection * 8)) 
    {
        player.xDirection = 0;
        player.yDirection = 0;
    }
}

void setPlayerHitboxMap(unsigned char* map, int width, int height, char walkebleTiles[]) 
{
    playerMap.map = map;
    playerMap.width = width;
    playerMap.height = height;
    for (int i = 0; i < walkebleTilesCount; i++) playerMap.walkebleTiles[i] = walkebleTiles[i];
}

BOOLEAN checkPlayerCollision(int x, int y) 
{
    if (x < 0 || x > playerMap.width * 8 - 8 || y < 0 || y > playerMap.height * 8 - 8) return TRUE;
    int tile = playerMap.map[(x/8) + (y/8) * playerMap.width];
    for (int i = 0; i < walkebleTilesCount; i++) if (tile == playerMap.walkebleTiles[i] ) return FALSE;
    return TRUE;
}

void screenShake(int times) {
    for (int i = 0; i < times; i++) {
        wait_vbl_done();
        scroll_bkg(1, 0);
        delay(20);
        scroll_bkg(-2, 0);
        delay(20);
        scroll_bkg(1, 0);
        delay(20);
    }
}