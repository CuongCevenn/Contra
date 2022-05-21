#pragma once

#ifndef GAME_MAP_H_
#define GAME_MAP_H_

#include "CommonFunc.h"
#include "BaseObject.h"
#include <fstream>
#include <iostream>

#define MAX_TILES 50

class TileMat : public BaseObject
{
public:
    TileMat() {;}
    ~TileMat() {;}
};

class GameMap
{
public:
    GameMap() {;}
    ~GameMap() {;}

    void LoadMap(std::string name);
    void LoadTiles(SDL_Renderer* screen);
    void DrawMap(SDL_Renderer* screen);
    Map getMap() const {return game_map_;}
    void SetMap(Map& map_data) {game_map_ = map_data;}
private:
    Map game_map_;
    TileMat tile_mat[MAX_TILES];
};


#endif // GAME_MAP_H_
