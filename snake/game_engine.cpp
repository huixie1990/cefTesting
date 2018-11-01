//
//  game_engine.cpp
//  cefclient
//
//  Created by Hui Xie on 27/10/2018.
//

#include "game_engine.hpp"
#include "include/cef_process_message.h"
#include <thread>

using namespace snake;

GameEngine::GameEngine(std::chrono::duration<double> sampleTime): fSampleTime(sampleTime){
    fSnakes.emplace_back(
                         std::vector<Point>{{0,0},{1,0},{2,0},{3,0}}, 8.5, Direction::up);
    fSnakes.emplace_back(
                         std::vector<Point>{{49,49},{49,48},{49,47},{49,48}}, 1, Direction::left);
};

void GameEngine::step(){
    for(auto& snake : fSnakes){
        snake.timeStep(fSampleTime);
    }
}

void GameEngine::runGameUntil(std::function<bool()> exitPredicate){
    while(!exitPredicate()){
        step();
        std::this_thread::sleep_for(fSampleTime);
    }
}

void GameEngine::sendDirectionToSnake(Direction dir, int snakeIdx){
    if(dir == fSnakes[snakeIdx].getDirection()){
        // send the same direction, we should acclerate
        fSnakes[snakeIdx].accelerate();
        return;
    }
    fSnakes[snakeIdx].setDirection(dir);
}


std::vector<Snake>& GameEngine::getSnakes(){return fSnakes;};
const std::vector<Snake>& GameEngine::getSnakes() const{return fSnakes;};
