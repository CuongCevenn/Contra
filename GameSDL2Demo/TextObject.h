#ifndef TEXT_OBJECT_H_
#define TEXT_OBJECT_H_

#include "CommonFunc.h"

class TextObject
{
public:
    TextObject();
    ~TextObject();

    enum TextColor
    {
        RED_TEXT = 0,
        WHITE_TEXT = 1,
        BLACK_TEXT = 2,
    };
    bool loadFromRenderText(TTF_Font* font, SDL_Renderer* screen);
    void free();
    void setColor(Uint8 red, Uint8 green, Uint8 blue);
    void setColor(int type);
    void renderText(SDL_Renderer* screen,
                    int xp, int yp,
                    SDL_Rect* clip = NULL,
                    double angle = 0.0,
                    SDL_Point* center = NULL,
                    SDL_RendererFlip flip = SDL_FLIP_NONE);
    int getWidth() const { return width_; }
    int getHeight() const { return height_; }

    void setText(const std::string& text) { str_val_ = text; }
    std::string getText() const { return str_val_; }
private:
    std::string str_val_;
    SDL_Color text_color_;
    SDL_Texture* texture_;
    int width_;
    int height_;
};






#endif // TEXT_OBJECT_H_
