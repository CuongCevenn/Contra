#include "PlayerPower.h"


PlayerPower::PlayerPower()
{
    x_pos_ = 0;
    y_pos_ = 0;
}

PlayerPower::~PlayerPower()
{

}

void PlayerPower::Init(SDL_Renderer* screen)
{
    bool ret = loadImage("asset/img/heart.png", screen);
}

void PlayerPower::Show(SDL_Renderer* screen)
{
    rect_.x = x_pos_;
    rect_.y = y_pos_;
    render(screen);
}


PlayerMoney::PlayerMoney()
{
    x_pos_ = 0;
    y_pos_ = 0;
}

PlayerMoney::~PlayerMoney()
{

}

void PlayerMoney::Init(SDL_Renderer* screen)
{
    bool ret = loadImage("asset/img/money_img.png", screen);
}

void PlayerMoney::Show(SDL_Renderer* screen)
{
    rect_.x = x_pos_;
    rect_.y = y_pos_;
    render(screen);
}







