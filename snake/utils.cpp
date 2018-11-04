//
//  utils.cpp
//  cefclient
//
//  Created by Hui Xie on 02/11/2018.
//

#include "utils.hpp"
using namespace snake;
bool utils::isSnakeInsideBoarder(const Snake& snake, const Boarder& boarder){
    for(const auto& point: snake.getPosition()){
        if(!boarder.isPointInside(point)){
            return false;
        }
    }
    return true;
}
