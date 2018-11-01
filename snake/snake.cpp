//
//  snake.cpp
//  cefclient
//
//  Created by Hui Xie on 28/10/2018.
//

#include "snake.hpp"
#include "point.hpp"
#include <cmath>

using namespace snake;

Snake::Snake(const std::vector<Point>& bodyPoints,double speed,Direction direction):
        fBodyPoints(bodyPoints), fSpeed(speed), fDirection(direction), fSID(generateSID()){};


void Snake::timeStep(std::chrono::duration<double> timeStep){
    double oldDistance = fCurrentMovingDistance;
    fCurrentMovingDistance += timeStep.count() * fSpeed;
    
    if(int steps = std::floor(fCurrentMovingDistance) - std::floor(oldDistance)){
        move(steps);
    }
}

void Snake::accelerate(){
    move(1);
}

void Snake::move(int steps){
    for(int i=0;i<steps;i++){
        moveOneStep();
    }
    notifyListners();
}

void Snake::moveOneStep(){
    snake::Point nextPoint = [this](){
        auto currentPoint = fBodyPoints.back();
        switch (fDirection) {
            case Direction::up:
                return snake::Point{currentPoint.x, currentPoint.y+1};
            case Direction::down:
                return snake::Point{currentPoint.x, currentPoint.y-1};
            case Direction::left:
                return snake::Point{currentPoint.x - 1, currentPoint.y};
            case Direction::right:
                return snake::Point{currentPoint.x + 1, currentPoint.y};
            default:
                break;
        }
        return snake::Point({1,1});
    }();
    
    fBodyPoints.push_back(std::move(nextPoint));
    fBodyPoints.erase(fBodyPoints.begin());
    
    fPreviousDirection = fDirection;
}

void Snake::addListner(Listner<Snake>* listener){
    fListners.push_back(listener);
}

void Snake::notifyListners(){
    for(const auto& listner: fListners){
        listner->notify(*this);
    }
}


std::string snake::generateSID(){
    static int currentID = 0;
    currentID++;
    return std::to_string(currentID);
}


void Snake::setSpeed(double speed){
    fSpeed = speed;
}

void Snake::setDirection(Direction dir){
    if(fPreviousDirection == snake::oposite(dir)){
        // can't move backwards
        return;
    }
    fDirection = dir;
}


const std::vector<Point>& Snake::getPosition() const{
    return fBodyPoints;
}

std::string Snake::getSID() const {
    return fSID;
}
Direction Snake::getDirection() const {
    return fDirection;
}
