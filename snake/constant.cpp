//
//  constant.cpp
//  cefclient
//
//  Created by Hui Xie on 29/10/2018.
//

#include "constant.hpp"
namespace snake{
    const int CANVAS_WIDTH = 50;
    const int CANVAS_HEIGHT = 50;
    
    const int FOOD_NUMBER = 2;
    const double SPEED_UP_RATE = 1;
    
    const std::string SNAKE_MOVE_MESSAGE = "snake_move";
    const std::string SNAKE_STATE_MESSAGE = "snake_state_change";
    const std::string FOOD_CREATE_MESSAGE = "food_create";
    const std::string REQUEST_POSITIONS_MESSAGE = "request_positions";
}
