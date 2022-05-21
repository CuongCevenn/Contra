#pragma once

#ifndef BASE_OBJECT_H_
#define BASE_OBJECT_H_

#include "CommonFunc.h"

class BaseObject
{
public:
    BaseObject();
    ~BaseObject();
    void setRect(const int &x, const int &y) { rect_.x = x; rect_.y = y; }
    SDL_Rect getRect() const { return rect_; }
    SDL_Texture* getObject() const { return p_object_; }
    virtual bool loadImage( std::string path, SDL_Renderer* g_screen );
    void render(SDL_Renderer* des, const SDL_Rect* clip = NULL);
    void free();

protected:
    SDL_Texture* p_object_;
    SDL_Rect rect_;
};

#endif // BASE_OBJECT_H_
