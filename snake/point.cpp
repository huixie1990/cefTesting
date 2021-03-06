//
//  point.cpp
//  cefclient
//
//  Created by Hui Xie on 28/10/2018.
//

#include "point.hpp"
#include <unordered_set>
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

bool snake::arePointsContinuous(Point a, Point b){
    if ((a.x == b.x) && (std::abs(a.y - b.y) == 1)){
        return true;
    }
    
    if ((a.y == b.y) && (std::abs(a.x - b.x) == 1)){
        return true;
    }
    return false;
}


bool snake::arePointsContinuous(const std::vector<Point>& points){
    return points.end() == std::adjacent_find(points.begin(), points.end(),
                                                 [](auto p1, auto p2){
                                                     return !arePointsContinuous(p1, p2);
                                                 });
}


bool snake::hasDulicatedPoint(const std::vector<Point>& points){
    std::unordered_set<Point,PointHash> pointSet(points.begin(), points.end());
    return pointSet.size() < points.size();
}
