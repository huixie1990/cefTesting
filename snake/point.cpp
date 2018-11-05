//
//  point.cpp
//  cefclient
//
//  Created by Hui Xie on 28/10/2018.
//

#include "point.hpp"

using namespace snake;
bool snake::operator==(const Point& a, const Point& b){
    return a.x == b.x && a.y == b.y;
}

Point snake::getNextPoint(const Point& currentPoint, Direction dir){
    switch (dir) {
        case Direction::up:
            return Point{currentPoint.x, currentPoint.y+1};
        case Direction::down:
            return Point{currentPoint.x, currentPoint.y-1};
        case Direction::left:
            return Point{currentPoint.x - 1, currentPoint.y};
        case Direction::right:
            return Point{currentPoint.x + 1, currentPoint.y};
        default:
            break;
    }
}

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
