//
//  snake.cpp
//  cefclient
//
//  Created by Hui Xie on 28/10/2018.
//

#include "snake.hpp"
#include <cmath>

#include <iostream>
using namespace snake;

void Snake::timeStep(std::chrono::duration<double> timeStep){
    double oldDistance = fCurrentMovingDistance;
    fCurrentMovingDistance += timeStep.count() * fSpeed;
    
    if(int steps = std::floor(fCurrentMovingDistance) - std::floor(oldDistance)){
        move(steps);
    }
}

void Snake::move(int steps){
    for(int i=0;i<steps;i++){
        moveOneStep();
    }
    notifyListners();
  //  std::cout << "x: " << fBodyPoints.at(0).x << " . y: " << fBodyPoints.at(0).y <<std::endl;
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
    
    
}

void Snake::addListner(Listner<Snake>* listener){
    fListners.push_back(listener);
}

void Snake::notifyListners(){
    for(const auto& listner: fListners){
        listner->notify(*this);
    }
}
