#pragma once

#ifndef EXPLOSION_OBJECT_H_
#define EXPLOSION_OBJECT_H_

#include "CommonFunc.h"
#include "BaseObject.h"

#define NUM_FRAME_EXP 8

class ExplosionObject : public BaseObject
{
public:
    ExplosionObject();
    ~ExplosionObject();

    void set_clip();
    void set_frame(const int& fr) { frame_ = fr; }
    virtual bool loadImage(std::string path, SDL_Renderer* screen);
    void Show(SDL_Renderer* screen);
    int get_frame_width() const { return frame_width_; }
    int get_frame_height() const { return frame_height_; }
    void check_mute(const bool& im) { is_mute_ = im; }
private:
    int frame_width_;
    int frame_height_;
    unsigned int frame_;
    SDL_Rect frame_clip_[8];
    Mix_Chunk *gExp;
    bool is_mute_ = false;
};


#endif // EXPLOSION_OBJECT_H_
