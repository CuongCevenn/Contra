#pragma once

#ifndef MAIN_OBJECT_H_
#define MAIN_OBJECT_H_

#include "CommonFunc.h"
#include "BaseObject.h"
#include "BulletObject.h"
#include <vector>

#define GRAVITY_SPEED 0.8
#define MAX_FALL_SPEED 10
#define PLAYER_SPEED 8
#define PLAYER_JUMP_VALUE 18
#define PLAYER_FRAME 10

class MainObject : public BaseObject
{
public:
    MainObject();
    ~MainObject();

    enum WalkType
    {
        WALK_NONE = 0,
        WALK_RIGHT = 1,
        WALK_LEFT = 2,
    };
    bool loadImage(std::string path, SDL_Renderer* screen);
    void Show(SDL_Renderer* des);
    void HandleInputAction(SDL_Event events, SDL_Renderer* screen);
    void set_clips();
    void set_frame(const int& fr) { frame_ = fr; }
    void DoPlayer(Map& map_data);
    void CheckToMap(Map& map_data);
    void SetMapXY(const int map_x, const int map_y) {map_x_ = map_x; map_y_ = map_y;}
    void CenterEntityOnMap(Map& map_data);
    void UpdateImagePlayer(SDL_Renderer* des);
    SDL_Rect getRectFrame();
    void set_bullet_list(std::vector<BulletObject*> bullet_list)
    {
        p_bullet_list_ = bullet_list;
    }
    std::vector<BulletObject*> get_bullet_list() const { return p_bullet_list_; }
    void HandleBullet(SDL_Renderer* des);
    void RemoveBullet(const int& idx);
    void IncreaseMoney();
    int get_frame_width() const { return width_frame_; }
    int get_frame_height() const { return height_frame_; }
    void set_comeback_time(const int& cb_time)  { come_back_time_ = cb_time; }
    int getMoneyCount() const { return money_count_; }
    int getPlayerLife() const { return player_life_; }
    void damagePlayer();
    int get_fall() const { return fall_; }
    void reset_fall() { fall_ = 0; }
    int get_trap() const { return die_by_trap_; }
    void reset_trap() { die_by_trap_ = 0; }
    int get_option() const { return option_; }
    void set_option(const int& optionN) { option_ = optionN; }
    void set_checkpoint(const int& cp) { check_point_ = cp; }
    void check_mute(const bool& im) { is_mute_ = im; }
private:
    std::vector<BulletObject*> p_bullet_list_;
    int player_life_;
    float x_val_;
    float y_val_;
    float x_pos_;
    float y_pos_;
    int width_frame_;
    int height_frame_;
    SDL_Rect frame_clip_[8];
    Input input_type_;
    int frame_;
    int status_;
    bool on_ground_;
    int map_x_;
    int map_y_;
    int come_back_time_;
    int money_count_;
    int fall_;
    int die_by_trap_;
    int option_;
    unsigned int bullet_type_;
    int check_point_;
    bool check_get_damage_;
    bool check_get_damage_2_;
    int num_bomb_;
    Mix_Chunk *gBullet;
    Mix_Chunk *gCanon;
    Mix_Chunk *gLaser;
    Mix_Chunk *gGrenade;
    bool is_mute_;
};

#endif // MAIN_OBJECT_H_
