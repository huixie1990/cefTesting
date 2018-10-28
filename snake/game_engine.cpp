//
//  game_engine.cpp
//  cefclient
//
//  Created by Hui Xie on 27/10/2018.
//

#include "game_engine.hpp"
#include "include/cef_process_message.h"
void snake::GameEngine::step(){
    fSnake.step(fSampleTime);
    pos += 1;
    fApp->notify(*this);
}
