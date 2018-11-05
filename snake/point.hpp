//
//  point.hpp
//  cefclient
//
//  Created by Hui Xie on 28/10/2018.
//

#pragma once
#include <vector>
namespace snake {
    
    struct Point{
        int x;
        int y;
        
        Point(int ix, int iy): x(ix), y(iy){};
    };
    
    bool operator==(const snake::Point&, const snake::Point&);
    
    enum class Direction{up, down, left, right};
    
    Point getNextPoint(const Point&, Direction);
    
    Direction oposite(Direction);
}


