//
//  point.cpp
//  cefclient
//
//  Created by Hui Xie on 28/10/2018.
//

#include "point.hpp"


bool snake::operator==(const snake::Point& a, const snake::Point& b){
    return a.x == b.x && a.y == b.y;
}

snake::Direction snake::oposite(Direction dir){
    switch (dir) {
        case snake::Direction::up:
            return snake::Direction::down;
            break;
        case snake::Direction::down:
            return snake::Direction::up;
            break;
        case snake::Direction::left:
            return snake::Direction::right;
            break;
        case snake::Direction::right:
            return snake::Direction::left;
            break;
        default:
            break;
    }
}
