#include "CommonFunc.h"
#include "BaseObject.h"
#include "game_map.h"
#include "MainObject.h"
#include "ImpTimer.h"
#include "ThreatObject.h"
#include "ExplosionObject.h"
#include "TextObject.h"
#include "PlayerPower.h"
#include "Geometric.h"
#include "Button.h"

bool init();
bool loadMedia();
void close();
std::vector<ThreatsObject*> MakeThreatList();

BaseObject g_background, g_pauseBackground, g_menuBackground, g_infoBackground, g_loseBackground, g_winBackground;
Button startButton, muteButton, unmuteButton, infoButton, backButton, exitButton, resumeButton;
TTF_Font* font_time = NULL;
int option = START;
Mix_Chunk *gLose = NULL;
Mix_Chunk *gWin = NULL;
Mix_Chunk *gIntro = NULL;

int main(int argc, char* argv[])
{
    ImpTimer fps_timer;
    if(init() == false)
        return -1;
    if(loadMedia() == false)
        return -1;
    bool is_mute = false;

    GameMap game_map;
    game_map.LoadMap("map/map01.dat");
    game_map.LoadTiles(g_screen);

    MainObject p_player_;
    p_player_.loadImage("asset/img/player_right.png", g_screen);
    p_player_.set_clips();

    PlayerPower player_power;
    player_power.Init(g_screen);
    player_power.setPos(SCREEN_WIDTH*0.5 - 600, 8);

    PlayerMoney player_money;
    player_money.Init(g_screen);
    player_money.setPos(SCREEN_WIDTH*0.5 - 300, 8);

    std::vector<ThreatsObject*> threats_list = MakeThreatList();

    ExplosionObject exp_threat;
    bool tRet = exp_threat.loadImage("asset/img/exp3.png", g_screen);
    if(!tRet) return -1;
    exp_threat.set_clip();
    ExplosionObject exp_main;
    bool mRet = exp_main.loadImage("asset/img/exp3.png", g_screen);
    if(!mRet) return -1;
    exp_main.set_clip();

    TextObject time_game;
    time_game.setColor(TextObject::WHITE_TEXT);

    TextObject mark_game;
    mark_game.setColor(TextObject::WHITE_TEXT);
    UINT mark_value = 0;

    TextObject money_game;
    money_game.setColor(TextObject::WHITE_TEXT);

    TextObject life_game;
    life_game.setColor(TextObject::WHITE_TEXT);

    bool quit = false;
    while(!quit) switch(option)
    {
    case START:
        while(SDL_PollEvent(&g_event) != 0)
        {
            if(g_event.type == SDL_QUIT)
            {
                quit = true;
                break;
            }
            startButton.handleEvent(&g_event);
            infoButton.handleEvent(&g_event);
            muteButton.handleEvent(&g_event);
            unmuteButton.handleEvent(&g_event);
            exitButton.handleEvent(&g_event);
            if(startButton.click())
            {
                Mix_FreeChunk(gIntro);
                gIntro = NULL;
                p_player_.set_option(PLAY);
                option = PLAY;
                break;
            }
            else if(infoButton.click())
            {
                option = INFO;
                break;
            }
            else if(exitButton.click())
            {
                quit = true;
                break;
            }
            else if(muteButton.click())
            {
                is_mute = true;
                Mix_FreeChunk(gIntro);
                gIntro = NULL;
            }
            else if(unmuteButton.click())
            {
                is_mute = false;
                gIntro = Mix_LoadWAV("audio/intro.wav");
            }
        }
        SDL_SetRenderDrawColor(g_screen, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);
        SDL_RenderClear(g_screen);

        g_menuBackground.render(g_screen, NULL);
        startButton.setPosition(159,457);
        startButton.Show(g_screen);
        infoButton.setPosition(493, 457);
        infoButton.Show(g_screen);
        exitButton.setPosition(821, 457);
        exitButton.Show(g_screen);
        if(!is_mute)
        {
            unmuteButton.freeB();
            muteButton.loadImage("asset/img/mute_button.png", g_screen);
            muteButton.setPosition(1171,33);
            muteButton.Show(g_screen);
        }
        else
        {
            muteButton.freeB();
            unmuteButton.loadImage("asset/img/unmute_button.png", g_screen);
            unmuteButton.setPosition(1171,122);
            unmuteButton.Show(g_screen);
        }
        if(!is_mute && option == START)
        {
            if( Mix_PlayingMusic() == 0 )
            {
                Mix_PlayChannel(-1, gIntro, 0);
            }
        }
        SDL_RenderPresent(g_screen);
        break;
    case INFO:
        while(SDL_PollEvent(&g_event) != 0)
        {
            if(g_event.type == SDL_QUIT)
            {
                quit = true;
            }
            backButton.handleEvent(&g_event);
            if(backButton.click())
            {
                option = START;
                break;
            }
        }
        SDL_SetRenderDrawColor(g_screen, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);
        SDL_RenderClear(g_screen);

        g_infoBackground.render(g_screen, NULL);
        backButton.setPosition(0, 0);
        backButton.Show(g_screen);

        SDL_RenderPresent(g_screen);
        break;
    case PLAY:
    {
        fps_timer.start();
        while(SDL_PollEvent(&g_event) != 0)
        {
            if(g_event.type == SDL_QUIT)
            {
                quit = true;
            }
            if(!is_mute)
            {
                if( Mix_PlayingMusic() == 0 )
                {
                    gMusic = Mix_LoadMUS("audio/music.wav");
                    Mix_PlayMusic( gMusic, -1 );
                }
            }
            else
            {
                Mix_FreeMusic(gMusic);
                gMusic = NULL;
            }
            p_player_.HandleInputAction(g_event, g_screen);
            option = p_player_.get_option();
        }
        SDL_SetRenderDrawColor(g_screen, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);
        SDL_RenderClear(g_screen);

        g_background.render(g_screen, NULL);
        Map map_data = game_map.getMap();

        p_player_.HandleBullet(g_screen);
        p_player_.SetMapXY(map_data.start_x_, map_data.start_y_);
        p_player_.DoPlayer(map_data);
        p_player_.Show(g_screen);
        p_player_.check_mute(is_mute);

        game_map.SetMap(map_data);
        game_map.DrawMap(g_screen);

        //Draw geometric
        GeometricFormat rectangle_size(0, 0, SCREEN_WIDTH, 40);
        ColorData color_data(36, 36, 36);
        Geometric::RenderRectangle(rectangle_size, color_data, g_screen);
        GeometricFormat outlineSize(1, 1, SCREEN_WIDTH - 1, 38);
        ColorData color_data2(255, 255, 255);
        Geometric::RenderOutline(outlineSize, color_data2, g_screen);

        player_power.Show(g_screen);
        player_money.Show(g_screen);

        for(int i = 0; i < threats_list.size(); i++)
        {
            ThreatsObject* p_threat = threats_list.at(i);
            if(p_threat != NULL)
            {
                p_threat->SetMapXY(map_data.start_x_, map_data.start_y_);
                p_threat->ImpMoveType(g_screen);
                p_threat->DoPlayer(map_data);
                p_threat->MakeBullet(g_screen, SCREEN_WIDTH, SCREEN_HEIGHT);
                p_threat->Show(g_screen);

                SDL_Rect rect_player = p_player_.getRectFrame();
                bool bCol1  = false;
                std::vector<BulletObject*> tBullet_list = p_threat->get_bullet_list();
                for(int jj = 0; jj < tBullet_list.size(); jj++)
                {
                    BulletObject* pt_bullet = tBullet_list.at(jj);
                    if(pt_bullet)
                    {
                        bCol1 = SDLCommonFunc::checkCollision(pt_bullet->getRect(), rect_player);
                        if(bCol1)
                        {
                            p_threat->RemoveBullet(jj);
                            break;
                        }
                    }
                }
                SDL_Rect rect_threat = p_threat->getRectFrame();
                bool bCol2 = SDLCommonFunc::checkCollision(rect_player, rect_threat);
                int fall = p_player_.get_fall();
                int trap = p_player_.get_trap();
                if(bCol1||bCol2||fall > 0||trap > 0)
                {
                    p_player_.reset_fall();
                    p_player_.reset_trap();
                    int width_exp_frame = exp_main.get_frame_width();
                    int height_exp_frame = exp_main.get_frame_height();
                    for(int ex = 0; ex < NUM_FRAME_EXP; ex++)
                    {
                        int x_pos = (p_player_.getRect().x + p_player_.get_frame_width()*0.5 ) - width_exp_frame*0.5;
                        int y_pos = (p_player_.getRect().y + p_player_.get_frame_height()*0.5 ) - height_exp_frame*0.5;

                        exp_main.check_mute(is_mute);
                        exp_main.set_frame(ex);
                        exp_main.setRect(x_pos, y_pos);
                        exp_main.Show(g_screen);
                        SDL_RenderPresent(g_screen);
                    }

                    p_player_.damagePlayer();
                    int life = p_player_.getPlayerLife();
                    if(life >= 0)
                    {
                        p_player_.setRect(0,448);
                        p_player_.set_comeback_time(30);
                        SDL_Delay(1000);
                        continue;
                    }
                    else
                    {
                        p_threat->free();
                        option = END;
                    }
                }
            }
        }

        int frame_exp_width = exp_threat.get_frame_width();
        int frame_exp_height = exp_threat.get_frame_height();
        std::vector<BulletObject*> bullet_arr = p_player_.get_bullet_list();
        for(int r = 0; r < bullet_arr.size(); r++)
        {
            BulletObject* p_bullet = bullet_arr.at(r);
            if(p_bullet != NULL)
            {
                for(int t = 0; t < threats_list.size(); t++)
                {
                    ThreatsObject* obj_threat = threats_list.at(t);
                    if(obj_threat != NULL)
                    {
                        SDL_Rect tRect;
                        tRect.x = obj_threat->getRect().x;
                        tRect.y = obj_threat->getRect().y;
                        tRect.w = obj_threat->get_width_frame();
                        tRect.h = obj_threat->get_height_frame();

                        SDL_Rect bRect = p_bullet->getRect();

                        bool bCol = SDLCommonFunc::checkCollision(bRect, tRect);
                        if(bCol)
                        {
                            mark_value++;
                            for(int ex = 0; ex < NUM_FRAME_EXP; ex++)
                            {
                                int x_pos = p_bullet->getRect().x - frame_exp_width*0.5;
                                int y_pos = p_bullet->getRect().y - frame_exp_height*0.5;

                                exp_threat.check_mute(is_mute);
                                exp_threat.set_frame(ex);
                                exp_threat.setRect(x_pos,y_pos);
                                exp_threat.Show(g_screen);
                            }

                            p_player_.RemoveBullet(r);
                            obj_threat->free();
                            threats_list.erase(threats_list.begin() + t);
                        }
                    }
                }
            }
        }

        //Show game time
        std::string str_time = "Time: ";
        Uint32 time_val = SDL_GetTicks() / 1000.f;
        Uint32 val_time = PLAY_TIME - time_val;
        if(val_time <= 0)
        {
            option = END;
        }
        else
        {
            std::string str_val = std::to_string(val_time);
            str_time += str_val;

            time_game.setText(str_time);
            time_game.loadFromRenderText(font_time, g_screen);
            time_game.renderText(g_screen, SCREEN_WIDTH - 200, 15);
        }

        std::string val_str_mark = std::to_string(mark_value);
        std::string strMark("Mark: ");
        strMark += val_str_mark;
        mark_game.setText(strMark);
        mark_game.loadFromRenderText(font_time, g_screen);
        mark_game.renderText(g_screen, SCREEN_WIDTH*0.5 - 50, 15);

        int money_count = p_player_.getMoneyCount();
        std::string money_str = std::to_string(money_count);
        money_game.setText(money_str);
        money_game.loadFromRenderText(font_time, g_screen);
        money_game.renderText(g_screen, SCREEN_WIDTH*0.5 - 250, 15);

        int heart_count = p_player_.getPlayerLife();
        std::string life_str = std::to_string(heart_count);
        life_game.setText(life_str);
        life_game.loadFromRenderText(font_time, g_screen);
        life_game.renderText(g_screen, SCREEN_WIDTH*0.5 - 550, 15);

        SDL_RenderPresent(g_screen);

        int real_imp_time = fps_timer.get_ticks();
        int time_one_frame = 1000/FRAME_PER_SECOND;//ms

        if(real_imp_time < time_one_frame)
        {
            int delay_time = time_one_frame - real_imp_time;
            if(delay_time >= 0)
            {
                SDL_Delay(delay_time);
            }
        }
        break;
    }
    case PAUSE:
        {
        while(SDL_PollEvent(&g_event) != 0)
        {
            if(g_event.type == SDL_QUIT)
            {
                quit = true;
                break;
            }
            resumeButton.handleEvent(&g_event);
            backButton.handleEvent(&g_event);
            muteButton.handleEvent(&g_event);
            unmuteButton.handleEvent(&g_event);
            if(resumeButton.click())
            {
                p_player_.set_option(PLAY);
                option = PLAY;
                break;
            }
            else if(backButton.click())
            {
                quit = true;
                break;
            }
            else if(muteButton.click())
            {
                is_mute = true;
            }
            else if(unmuteButton.click())
            {
                is_mute = false;
            }
        }
        SDL_SetRenderDrawColor(g_screen, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);
        SDL_RenderClear(g_screen);

        g_pauseBackground.render(g_screen, NULL);
        resumeButton.setPosition(689, 223);
        resumeButton.Show(g_screen);
        backButton.setPosition(400, 223);
        backButton.Show(g_screen);
        if(!is_mute)
        {
            unmuteButton.freeB();
            muteButton.loadImage("asset/img/mute_button.png", g_screen);
            muteButton.setPosition(1171,33);
            muteButton.Show(g_screen);
        }
        else
        {
            muteButton.freeB();
            unmuteButton.loadImage("asset/img/unmute_button.png", g_screen);
            unmuteButton.setPosition(1171,122);
            unmuteButton.Show(g_screen);
        }

        SDL_RenderPresent(g_screen);
        break;
        }
    case END:
        {
            Mix_FreeMusic( gMusic );
            gMusic = NULL;
            while(SDL_PollEvent(&g_event) != 0)
            {
                if(g_event.type == SDL_QUIT)
                {
                    quit = true;
                    break;
                }
            }
            SDL_SetRenderDrawColor(g_screen, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);
            SDL_RenderClear(g_screen);

            g_loseBackground.render(g_screen, NULL);
            Mix_PlayChannel(-1, gLose, 0);

            SDL_RenderPresent(g_screen);
            break;
        }
    case WIN:
        {
            Mix_FreeMusic( gMusic );
            gMusic = NULL;
            while(SDL_PollEvent(&g_event) != 0)
            {
                if(g_event.type == SDL_QUIT)
                {
                    quit = true;
                    break;
                }
            }
            SDL_SetRenderDrawColor(g_screen, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);
            SDL_RenderClear(g_screen);

            g_winBackground.render(g_screen, NULL);
            Mix_PlayChannel(-1, gWin, 0);

            SDL_RenderPresent(g_screen);
            break;
        }
    }

    for(int i = 0; i < threats_list.size(); i++)
    {
        ThreatsObject* p_threat = threats_list.at(i);
        if(p_threat != NULL)
        {
            p_threat->free();
            p_threat = NULL;
        }
    }
    threats_list.clear();

    close();

    return 0;
}

bool init()
{
    bool success = true;
    int ret = SDL_Init(SDL_INIT_EVERYTHING);
    if(ret < 0)
        return false;
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");

    g_window = SDL_CreateWindow( "Contra", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
    if(g_window == NULL)
    {
        success = false;
    }
    else
    {
        g_screen = SDL_CreateRenderer( g_window, -1, SDL_RENDERER_ACCELERATED );
        if(g_screen == NULL)
        {
            return false;
        }
        else
        {
            SDL_SetRenderDrawColor(g_screen, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);
            int imgFlags = IMG_INIT_PNG;
            if(!(IMG_Init(imgFlags)&&imgFlags))
                success = false;
        }

        if(TTF_Init() == -1)
        {
            success = false;
        }

        font_time = TTF_OpenFont("asset/ttf/dlxfont_.ttf", 15);
        if(font_time == NULL)
        {
            success = false;
        }
        Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
    }
    return success;
}

bool loadMedia()
{
    bool ret = g_background.loadImage("asset/img/background.png", g_screen);
    bool pRet = g_pauseBackground.loadImage("asset/img/pause_background.png", g_screen);
    bool mRet = g_menuBackground.loadImage("asset/img/menu_background.png", g_screen);
    g_infoBackground.loadImage("asset/img/info_background.png", g_screen);
    g_loseBackground.loadImage("asset/img/you_lose.png", g_screen);
    g_winBackground.loadImage("asset/img/you_win.png", g_screen);
    startButton.loadImage("asset/img/start_button.png", g_screen);
    muteButton.loadImage("asset/img/mute_button.png", g_screen);
    unmuteButton.loadImage("asset/img/unmute_button.png", g_screen);
    infoButton.loadImage("asset/img/info_button.png", g_screen);
    backButton.loadImage("asset/img/back_button.png", g_screen);
    exitButton.loadImage("asset/img/exit_button.png", g_screen);
    resumeButton.loadImage("asset/img/resume_button.png", g_screen);
    gLose = Mix_LoadWAV("audio/you_lose.wav");
    gWin = Mix_LoadWAV("audio/victory.wav");
    gIntro = Mix_LoadWAV("audio/intro.wav");
    if(ret == false||pRet == false)
        return false;
    return true;
}

void close()
{
    g_background.free();
    g_pauseBackground.free();
    g_menuBackground.free();
    g_infoBackground.free();
    g_loseBackground.free();
    g_winBackground.free();
    backButton.freeB();
    startButton.freeB();
    muteButton.freeB();
    unmuteButton.freeB();
    resumeButton.freeB();
    infoButton.freeB();
    exitButton.freeB();

    SDL_DestroyRenderer(g_screen);
    g_screen = NULL;
    SDL_DestroyWindow(g_window);
    g_window = NULL;

    Mix_FreeMusic( gMusic );
    gMusic = NULL;
    Mix_FreeChunk(gLose);
    gLose = NULL;
    Mix_FreeChunk(gWin);
    gWin = NULL;
    Mix_FreeChunk(gIntro);
    gIntro = NULL;

    Mix_Quit();
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}

std::vector<ThreatsObject*> MakeThreatList()
{
    std::vector<ThreatsObject*> list_threats;

    ThreatsObject* dynamic_threats = new ThreatsObject[20];
    for(int i = 0; i < 10; i++)
    {
        ThreatsObject* p_threat = (dynamic_threats + i);
        if(p_threat != NULL)
        {
            p_threat->loadImage("asset/img/threat_left.png",g_screen);
            p_threat->set_clips();
            p_threat->set_type_move(ThreatsObject::MOVE_IN_SPACE_THREAT);
            p_threat->set_x_pos(600 + i*950);
            p_threat->set_y_pos(320);

            int pos1 = p_threat->get_x_pos() - 60;
            int pos2 = p_threat->get_x_pos() + 60;
            p_threat->setAnimationPos(pos1, pos2);
            p_threat->set_input_left(1);
            list_threats.push_back(p_threat);
        }
    }
    ThreatsObject* threats_objs = new ThreatsObject[20];
    for(int i = 0; i < 7; i++)
    {
        ThreatsObject* p_threat = (threats_objs + i);
        if(p_threat != NULL)
        {
            p_threat->loadImage("asset/img/threat_level.png", g_screen);
            p_threat->set_clips();
            p_threat->set_x_pos(900 + i*1050);
            p_threat->set_y_pos(250);
            p_threat->set_type_move(ThreatsObject::STATIC_THREAT);
            p_threat->set_input_left(0);

            BulletObject* p_bullet = new BulletObject();
            p_threat->InitBullet(p_bullet, g_screen);
            list_threats.push_back(p_threat);
        }
    }
    return list_threats;
}



