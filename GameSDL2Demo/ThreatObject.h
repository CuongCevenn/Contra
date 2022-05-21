#pragma once

#ifndef THREAT_OBJECT_H_
#define THREAT_OBJECT_H_

#include "CommonFunc.h"
#include "BaseObject.h"
#include "BulletObject.h"

#define THREAT_SPEED 3
#define THREAT_MAX_FALL_SPEED 10
#define THREAT_GRAVITY_SPEED 0.8
#define THREAT_FRAME_NUM 8

class ThreatsObject : public BaseObject
{
public:
    ThreatsObject();
    ~ThreatsObject();

    enum TypeMove
    {
        STATIC_THREAT = 0,
        MOVE_IN_SPACE_THREAT = 1,
    };

    void set_x_val(const float& xVal) { x_val_ = xVal; }
    void set_y_val(const float& yVal) { y_val_ = yVal; }
    void set_x_pos(const float& xPos) { x_pos_ = xPos; }
    void set_y_pos(const float& yPos) { y_pos_ = yPos; }
    float get_x_pos() const { return x_pos_; }
    float get_y_pos() const { return y_pos_; }
    void SetMapXY(const int& mp_x, const int& mp_y) { map_x_ = mp_x; map_y_ = mp_y; }

    void set_clips();
    bool loadImage(std::string path, SDL_Renderer* screen);
    void Show(SDL_Renderer* des);
    int get_width_frame() const { return width_frame_; }
    int get_height_frame() const { return height_frame_; }
    void DoPlayer(Map& gMap);
    void CheckToMap(Map& map_data);
    void InitThreat();

    void set_type_move(const int& typeMove) { type_move_ = typeMove; }
    void setAnimationPos(const int& pos_a, const int& pos_b) { animation_a_ = pos_a; animation_b_ = pos_b; }
    void set_input_left(const int& ipLeft) { input_type_.left_ = ipLeft; }
    void ImpMoveType(SDL_Renderer* screen);

    std::vector<BulletObject*> get_bullet_list() const { return bullet_list_; }
    void set_bullet_list(const std::vector<BulletObject*> bulletList) { bullet_list_ = bulletList; }

    void InitBullet(BulletObject* p_bullet, SDL_Renderer* screen);
    void MakeBullet(SDL_Renderer* screen, const int& x_limit, const int& y_limit);
    void RemoveBullet(const int& idx);
    SDL_Rect getRectFrame();
private:
    int map_x_;
    int map_y_;
    float x_val_;
    float y_val_;
    float x_pos_;
    float y_pos_;
    bool on_ground_;
    int come_back_time_;
    SDL_Rect frame_clip_[THREAT_FRAME_NUM];
    int width_frame_;
    int height_frame_;
    int frame_;

    int type_move_;
    int animation_a_;
    int animation_b_;
    Input input_type_;

    std::vector<BulletObject*> bullet_list_;
};



#endif // THREAT_OBJECT_H_
