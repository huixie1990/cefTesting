//
//  point.cpp
//  cefclient
//
//  Created by Hui Xie on 28/10/2018.
//

#include "point.hpp"
using namespace snake;
Direction snake::oposite(Direction dir){
    switch (dir) {
        case Direction::up:
            return Direction::down;
            break;
        case Direction::down:
            return Direction::up;
            break;
        case Direction::left:
            return Direction::right;
            break;
        case Direction::right:
            return Direction::left;
            break;
        default:
            break;
    }
}
