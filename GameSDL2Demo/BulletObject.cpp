#include "BulletObject.h"

BulletObject::BulletObject()
{
    x_val_ = 0;
    y_val_ = 0;
    is_move_ = false;
    bullet_type_ =SPHERE_BULLET;
}

BulletObject::~BulletObject()
{

}

void BulletObject::HandleMove(const int& x_border, const int& y_border)
{
    if(bullet_dir_ == DIR_RIGHT)
    {
        rect_.x += x_val_;
        if(rect_.x > x_border)
        {
            is_move_ = false;
        }
    }
    else if(bullet_dir_ == DIR_LEFT)
    {
        rect_.x -= x_val_;
        if(rect_.x < 0)
        {
            is_move_ = false;
        }
    }
    else if(bullet_dir_ == DIR_DOWN)
    {
        rect_.y += y_val_;
        if(rect_.y > y_border)
        {
            is_move_ = false;
        }
    }
}

bool BulletObject::LoadImgBullet(SDL_Renderer* screen)
{
    bool ret = false;
    if(bullet_type_ == SPHERE_BULLET)
    {
        ret = loadImage("asset/img/sphere_bullet.png", screen);
    }
    else if(bullet_type_ == LASER_BULLET)
    {
        ret = loadImage("asset/img/laser_bullet.png", screen);
    }
    else if(bullet_type_ == CANON_BULLET)
    {
        ret = loadImage("asset/img/canon_bullet.png", screen);
    }
    else if(bullet_type_ == BOMB)
    {
        ret = loadImage("asset/img/bomb.png", screen);
    }
    else if(bullet_type_ == THREAT_BULLET)
    {
        ret = loadImage("asset/img/threat_bullet.png", screen);
    }
    return ret;
}
