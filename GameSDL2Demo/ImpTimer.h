#ifndef IMP_TIMER_H_
#define IMP_TIMER_H_

#include "CommonFunc.h"

class ImpTimer
{
public:
    ImpTimer();
    ~ImpTimer();

    void start();
    void stop();
    void pause();
    void unpause();

    Uint32 get_ticks();

    bool is_started();
    bool is_paused();
private:
    Uint32 start_tick_;
    Uint32 paused_tick_;

    bool is_paused_;
    bool is_started_;
};




#endif // IMP_TIMER_H_
