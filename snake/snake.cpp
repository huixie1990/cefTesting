//
//  snake.cpp
//  cefclient
//
//  Created by Hui Xie on 28/10/2018.
//

#include "snake.hpp"
#include "point.hpp"
#include "constant.hpp"
#include <cmath>
#include <algorithm>

using namespace snake;

Snake::Snake(const std::vector<Point>& bodyPoints,double speed,Direction direction):
        fBodyPoints(bodyPoints),
        fSpeed(speed),
        fDirection(direction),
        fInitialPoints(bodyPoints),
        fInitialSpeed(speed),
        fInitialDirection(direction),
        fPreviousDirection(direction),  
        fPreviousTail(*bodyPoints.begin()),
        fSID(generateSID()){
            
            if(!arePointsContinuous(bodyPoints)){
                throw std::runtime_error("non continuous initial points");
            }
            
            if(hasDulicatedPoint(bodyPoints)){
                throw std::runtime_error("duplicated initial points");
            }
        };


void Snake::moveTimeStep(std::chrono::duration<double> timeStep){
    if( fState!= SnakeState::running){
        return;
    }
    double oldDistance = fCurrentMovingDistance;
    fCurrentMovingDistance += timeStep.count() * fSpeed;
    
    if(int steps = std::floor(fCurrentMovingDistance) - std::floor(oldDistance)){
        move(steps);
    }
}

void Snake::accelerate(){
    if( fState!= SnakeState::running){
        return;
    }
    move(1);
}

void Snake::reset(){
    fBodyPoints = fInitialPoints;
    fSpeed = fInitialSpeed;
    fDirection = fInitialDirection;
    fPreviousDirection = fInitialDirection;
    
    fState = SnakeState::waiting;
    notifyListners(snake::SNAKE_MOVE_MESSAGE);
    notifyListners(snake::SNAKE_STATE_MESSAGE);
}

void Snake::setState(SnakeState state){
    fState = state;
    notifyListners(snake::SNAKE_STATE_MESSAGE);
}

SnakeState Snake::getState() const{
    return fState;
}


void Snake::move(int steps){
    for(int i=0;i<steps;i++){
        moveOneStep();
    }
    notifyListners(snake::SNAKE_MOVE_MESSAGE);
}

// private

void Snake::moveOneStep(){
    
    auto nextPoint = getNextPoint(fBodyPoints.back(), fDirection);
    
    fBodyPoints.push_back(std::move(nextPoint));
    fPreviousTail = *fBodyPoints.begin();
    fBodyPoints.erase(fBodyPoints.begin());
    
    fPreviousDirection = fDirection;
}

void Snake::grow(){
    fBodyPoints.insert(fBodyPoints.begin(), fPreviousTail);
}

void Snake::addListner(Listner<Snake>* listener){
    fListners.push_back(listener);
}

void Snake::notifyListners(const std::string& message) const{
    for(const auto& listner: fListners){
        listner->notified(*this, message);
    }
}

double Snake::getSpeed() const{
    return fSpeed;
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

// free functions

std::string snake::toString(SnakeState state){
    switch (state) {
        case SnakeState::waiting:
            return "waiting";
            break;
        case SnakeState::running:
            return "running";
            break;
        case SnakeState::dead:
            return "dead";
            break;
        default:
            break;
    }
}

std::string snake::generateSID(){
    static int currentID = 0;
    currentID++;
    return std::to_string(currentID);
}


SnakeBuilder& SnakeBuilder::tail(const Point& tail){
    fTail = tail;
    return *this;
}

SnakeBuilder& SnakeBuilder::length(int length){
    fLength = length;
    return *this;
}

SnakeBuilder& SnakeBuilder::speed(double speed){
    fSpeed = speed;
    return *this;
}

SnakeBuilder& SnakeBuilder::direction(Direction dir){
    fDirection = dir;
    return *this;
}

Snake SnakeBuilder::build() const{
    std::vector<Point> points;
    points.push_back(fTail);
    auto currentPoint = fTail;
    for(int i = 0; i< fLength - 1; i++){
        auto nextPoint = getNextPoint(currentPoint, fDirection);
        points.push_back(nextPoint);
        currentPoint = nextPoint;
    }
    return Snake{points, fSpeed, fDirection};
}
