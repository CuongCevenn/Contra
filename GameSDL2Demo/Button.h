#ifndef BUTTON_H_
#define BUTTON_H_

#include "CommonFunc.h"
#include "BaseObject.h"

enum buttonStatus
{
    MOUSE_OUT = 61,
    MOUSE_IN = 62,
    MOUSE_DOWN = 63,
    MOUSE_UP = 64,
};

class Button : public BaseObject
{
public:
    Button();
    ~Button();

    void setPosition(int x, int y) { x_pos_ = x; y_pos_ = y; }
    bool loadImage(std::string path, SDL_Renderer* screen);
    void Show(SDL_Renderer* des);
    int get_width_frame() const { return width_frame_; }
    int get_height_frame() const { return height_frame_; }
    void handleEvent(SDL_Event* e);
    bool click();
    void freeB() { BaseObject::free(); }
private:
    int x_pos_, y_pos_, currentStatus;
    int width_frame_;
    int height_frame_;
};







#endif // BUTTON_H_
