//
//  boarder.hpp
//  cefclient
//
//  Created by Hui Xie on 01/11/2018.
//

#pragma once
#include "point.hpp"
#include <vector>

namespace snake {
    class Boarder{
    public:
        Boarder(Point topRight, Point bottomLeft = {0,0});
        Point getBottomLeft() const;
        Point getTopRight() const;
        int width() const;
        int height() const;
        std::vector<Point> allPoints() const;
        
        bool isPointInside(const Point& pt) const;
    private:
        const Point fBottomLeft;
        const Point fTopRight;
        const std::vector<Point> fAllPoints;
    };
}
