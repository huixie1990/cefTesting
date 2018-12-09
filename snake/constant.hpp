//
//  constant.hpp
//  cefclient
//
//  Created by Hui Xie on 29/10/2018.
//

#pragma once
#include <string>
namespace snake{
    constexpr int CANVAS_WIDTH = 50;
    constexpr int CANVAS_HEIGHT = 50;
    
    constexpr double SPEED_UP_RATE = 1.0;
    
    extern const std::string SNAKE_MOVE_MESSAGE;
    extern const std::string SNAKE_STATE_MESSAGE;
    extern const std::string FOOD_CREATE_MESSAGE;
    extern const std::string REQUEST_POSITIONS_MESSAGE;
}
