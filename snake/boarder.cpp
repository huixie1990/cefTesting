//
//  boarder.cpp
//  cefclient
//
//  Created by Hui Xie on 01/11/2018.
//

#include "boarder.hpp"
using namespace snake;
Boarder::Boarder(Point topRight, Point bottomLeft):
    fBottomLeft(bottomLeft), fTopRight(topRight),
    fAllPoints(
           [this](){
               std::vector<Point> points;
               for (int i=fBottomLeft.x; i <= fTopRight.x; i++){
                   for(int j = fBottomLeft.y; j<= fTopRight.y; j++){
                       points.emplace_back(i,j);
                   }
               }
               return points;
           }()){};

bool Boarder::isPointInside(const Point& pt) const{
    return pt.x <= fTopRight.x &&
           pt.x >= fBottomLeft.x &&
           pt.y <= fTopRight.y &&
           pt.y >= fBottomLeft.y;
}

Point Boarder::getBottomLeft() const{
    return fBottomLeft;
}

Point Boarder::getTopRight() const{
    return fTopRight;
}

int Boarder::width() const{
    return fTopRight.x - fBottomLeft.x + 1;
}

int Boarder::height() const{
    return fTopRight.y - fTopRight.y + 1;
}

std::vector<Point> Boarder::allPoints() const{
    return fAllPoints;
}
