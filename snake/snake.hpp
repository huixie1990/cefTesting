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
#include <string>




namespace snake {
    
    enum class SnakeState{
        waiting, running, dead
    };
    std::string toString(SnakeState);
    
    std::string generateSID();
    
    class Snake{
    public:
 
        Snake(const std::vector<Point>& bodyPoints,
              double speed = 1.0,
              Direction direction = Direction::up);
        
        // compiler generated essential operations
        Snake(const Snake&) = delete;
        Snake& operator=(const Snake&) = delete;
        Snake(Snake&&) = default;
        Snake& operator=(Snake&&) = default;
        ~Snake() = default;
        
        // getter and setter
        const std::vector<Point>& getPosition() const;
        std::string getSID() const;
        Direction getDirection() const;
        SnakeState getState() const;
        void setState(SnakeState);
        void setSpeed(double speed);
        void setDirection(Direction dir);
        
        // operations
        void moveTimeStep(std::chrono::duration<double>);
        void accelerate();
        void reset();
        void addListner(Listner<Snake>*);
        

        
    private:
        std::vector<Point> fBodyPoints;
        double fSpeed;
        Direction fDirection;
        
        const std::vector<Point> fInitialPoints;
        const double fInitialSpeed;
        const Direction fInitialDirection;
        
        Direction fPreviousDirection;
        const std::string fSID;
        double fCurrentMovingDistance = 0;
        SnakeState fState = SnakeState::waiting;
        std::vector<Listner<Snake>*> fListners;
        
        void notifyListners(const std::string&);
        void move(int steps);
        void moveOneStep();
        bool isBodyValid(const std::vector<Point>&);
    };
    
    
    class SnakeBuilder{
    public:
        SnakeBuilder() = default;
        ~SnakeBuilder() = default;
        
        SnakeBuilder& tail(const Point&);
        SnakeBuilder& length(int);
        SnakeBuilder& speed(double);
        SnakeBuilder& direction(Direction);
        
        Snake build() const;
    private:
        double fSpeed = 1.0;
        Direction fDirection = Direction::up;
        Point fTail = {0,0};
        int fLength = 1;
    };
   
    
}
