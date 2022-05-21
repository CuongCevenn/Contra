#include "Button.h"

Button::Button()
{
    x_pos_ = 0;
    y_pos_ = 0;
    currentStatus = 0;
    width_frame_ = 0;
    height_frame_ = 0;
}

Button::~Button()
{

}

bool Button::loadImage(std::string path, SDL_Renderer* screen)
{
    bool ret = BaseObject::loadImage(path, screen);

    if(ret == true)
    {
        width_frame_ = rect_.w;
        height_frame_ = rect_.h;
    }
    return ret;
}

void Button::Show(SDL_Renderer* des)
{
    SDL_Rect renderQuad = { x_pos_, y_pos_, width_frame_, height_frame_ };
    SDL_RenderCopy(des, p_object_, NULL, &renderQuad);
}

void Button::handleEvent(SDL_Event* e)
{
    if(e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN)
    {
        int x, y;
        SDL_GetMouseState(&x, &y);
        if(x < x_pos_ || x > x_pos_ + width_frame_ || y < y_pos_ || y > y_pos_ + height_frame_) currentStatus = MOUSE_OUT;
        else switch(e->type)
        {
            case SDL_MOUSEMOTION: currentStatus = MOUSE_IN; return;
            case SDL_MOUSEBUTTONDOWN: currentStatus = MOUSE_DOWN; return;
        }
    }
}

bool Button::click()
{
    if(currentStatus == MOUSE_DOWN)
        return true;
    return false;
}
