#include <gb/gb.h>
#include <stdio.h>
#include "player.h"
void getPlayerInput();
BOOLEAN checkPlayerCollision(int x, int y);

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
    scroll_sprite(0, player.xDirection, player.yDirection);

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
    if (btn & J_A)
    {
        btn = btn ^ J_A;
        player.speed = 2;
    } else {
        player.speed = 1;
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
    for (int i = 0; i < walkebleTilesCount; i++) if (tile != playerMap.walkebleTiles[i] && tile != 0) return TRUE;
    return FALSE;
}