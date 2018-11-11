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
    
    struct PointHash
    {
        std::size_t operator()(Point const& point) const noexcept
        {
            std::size_t h1 = std::hash<int>{}(point.x);
            std::size_t h2 = std::hash<int>{}(point.y);
            return h1 ^ (h2 << 1); // or use boost::hash_combine (see Discussion)
        }
    };
    
    enum class Direction{up, down, left, right};
    
    Point getNextPoint(const Point&, Direction);
    
    Direction oposite(Direction);
    
    bool arePointsContinuous(Point a, Point b);
    bool arePointsContinuous(const std::vector<Point>& points);
    bool hasDulicatedPoint(const std::vector<Point>& points);
}


