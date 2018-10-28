//
//  snake.hpp
//  cefclient
//
//  Created by Hui Xie on 28/10/2018.
//

#pragma once
#include "point.hpp"
#include "listner.hpp"
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
        
        const std::vector<Point>& getPosition() const{
            return fBodyPoints;
        }
        void timeStep(std::chrono::duration<double>);
        void move(int steps);
        void setSpeed(double speed);
        void addListner(Listner<Snake>*);
        
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
        std::vector<Listner<Snake>*> fListners;
        
        
        void notifyListners();
        void moveOneStep();
        bool isBodyValid(const std::vector<Point>&);
    };
}
