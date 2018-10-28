//
//  snake.hpp
//  cefclient
//
//  Created by Hui Xie on 28/10/2018.
//

#pragma once
#include "point.hpp"
#include <vector>
#include <chrono>

namespace snake {
    class Snake{
    public:
        Snake():Snake({{1,1}}){};
        Snake(const std::vector<Point>& bodyPoints)
            :Snake(bodyPoints, 1.0){};
        Snake(const std::vector<Point>& bodyPoints, double speed)
            :Snake(bodyPoints,speed,Direction::up){};
        Snake(const std::vector<Point>& bodyPoints, double speed, Direction direction):
            fBodyPoints(bodyPoints), fSpeed(speed), fDirection(direction){};
        
        
        void step(std::chrono::duration<double>); //calculate tiny little movement for every time step
        void move(); //move the position if accumulated steps are big enough for a move
        void setSpeed(double);
        
        
        // compiler generated essential operations
        // do we really need to be expliticit?
        Snake(const Snake&) = default;
        Snake& operator=(const Snake&) = default;
        Snake(Snake&&) = default;
        Snake& operator=(Snake&&) = default;
        ~Snake() = default;
        
    private:
        std::vector<Point> fBodyPoints;
        double fSpeed;
        Direction fDirection;
        double fCurrentMovingDistance = 0;
        bool isBodyValid(const std::vector<Point>&);
    };
}
