//
//  game_engine.cpp
//  cefclient
//
//  Created by Hui Xie on 27/10/2018.
//


#include "include/cef_process_message.h"

#include "game_engine.hpp"
#include "utils.hpp"
#include "constant.hpp"

#include <thread>
#include <memory>
#include <iostream>
using namespace snake;

GameEngine::GameEngine(std::chrono::duration<double> sampleTime):
        fSampleTime(sampleTime), fBoarder({CANVAS_WIDTH - 1, CANVAS_HEIGHT - 1}),
        fFoodGenerator(FOOD_NUMBER, this){
    fSnakes.emplace_back(
            std::vector<Point>{{0,0},{1,0},{2,0},{3,0}},2.5, Direction::up);
    fSnakes.emplace_back(
            std::vector<Point>{{49,49},{49,48},{49,47},{49,46},{49,45}}, 1, Direction::left);
};


// getters
std::vector<Snake>& GameEngine::getSnakes(){
    return fSnakes;
}

const std::vector<Snake>& GameEngine::getSnakes() const{
    return fSnakes;
}

const Boarder& GameEngine::getBoarder() const{
    return fBoarder;
}

FoodGenerator& GameEngine::getFoodGenerator(){
    return fFoodGenerator;
}

const FoodGenerator& GameEngine::getFoodGenerator() const{
    return fFoodGenerator;
}

void GameEngine::setState(GameState state){
    fGameState = state;
}

//operations:
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

void GameEngine::gameStartRequested(){
    if(fGameState == GameState::idle){
        setState(GameState::running);
    }
}

std::vector<Point> GameEngine::getFreePoints() const{
    auto allPoints = fBoarder.allPoints();
    std::vector<Point> occupied;

    for(auto& snake : fSnakes){
        const auto& pos = snake.getPosition();
        occupied.insert(occupied.end(),
                        pos.cbegin(),
                        pos.cend());
    }
    
    const auto& foods = fFoodGenerator.getFoods();
    for(const auto& food: foods){
        occupied.push_back(food.getPosition());
    }

    allPoints.erase(std::remove_if(allPoints.begin(),
                                   allPoints.end(),
                                   [&occupied](Point& p){
                                       return std::find(occupied.cbegin(), occupied.cend(), p)
                                       != occupied.cend();
                                   }),
                    allPoints.end());
    
    return allPoints;
}

// private:


void GameEngine::step(){
    if (fGameState != fPreviousState){
        entry(fGameState);
    } else{
        during(fGameState);
    }

    fPreviousState = fGameState;
}

void GameEngine::stepSnakes(){
    for(auto& snake : fSnakes){
        snake.moveTimeStep(fSampleTime);
        // check snakes are going to die
        if(snake.getState() != SnakeState::dead &&
           (!utils::isSnakeInsideBoarder(snake, fBoarder) || snakeHeadHitsObject(snake))){
            snake.setState(SnakeState::dead);
        }
    }
}

bool GameEngine::snakeHeadHitsObject(const Snake& snakeUnderCheck){
    const auto& head = snakeUnderCheck.getPosition().back();
    
    for(const auto& snake : fSnakes){
        for(const auto& bodyPoint: snake.getPosition()){
            if(std::addressof(head) != std::addressof(bodyPoint) && head==bodyPoint){
                return true;
            }
        }
    }
    return false;
}

void GameEngine::entry(GameState state){
    switch (state) {
        case GameState::running:
            for(auto& snake: fSnakes){
                snake.setState(SnakeState::running);
            }
            fFoodGenerator.setState(FoodGenState::running);
            break;
            
        default:
            break;
    }
}

void GameEngine::during(GameState state){
    switch (state) {
        case GameState::running:
            stepSnakes();
            fFoodGenerator.step();
            break;
            
        default:
            break;
    }
}
