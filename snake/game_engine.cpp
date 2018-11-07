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

#include <algorithm>

using namespace snake;

GameEngine::GameEngine(std::chrono::duration<double> sampleTime):
        fSampleTime(sampleTime),
        fBoarder({CANVAS_WIDTH - 1, CANVAS_HEIGHT - 1}),
        fFoodGenerator(FOOD_NUMBER){
            
        fSnakes.emplace_back(SnakeBuilder{}
                          .tail({0,0})
                          .length(3)
                          .direction(Direction::right)
                          .speed(5).build());

        fSnakes.emplace_back(SnakeBuilder{}
                          .tail({CANVAS_WIDTH - 1,CANVAS_WIDTH - 1})
                          .length(6)
                          .direction(Direction::down)
                          .speed(1).build());
            
        fStateActions = createStates();
        fTransitions = createTransitions();
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
        return;
    }
    
    if(fGameState == GameState::finished){
        setState(GameState::idle);
        return;
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
        fStateActions[fGameState].entry();
    } else{
        fStateActions[fGameState].during();
    }
    fPreviousState = fGameState;
    for (auto& transition: fTransitions){
        if(transition.source == fGameState && transition.condition()){
            fGameState = transition.destination;
        }
    }
    
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

void GameEngine::checkSnakeEatsFood(){
    for(auto& food: fFoodGenerator.getFoods()){
        for(auto& snake: fSnakes){
            const auto& bodyPoints = snake.getPosition();
            if(std::find(bodyPoints.cbegin(), bodyPoints.cend(),food.getPosition())
               != bodyPoints.cend()){
                fFoodGenerator.foodEaten(food);
                snake.grow();
                snake.setSpeed(snake.getSpeed() + SPEED_UP_RATE);
                break;
            }
        }
    }
}

std::vector<Transition> GameEngine::createTransitions(){
    std::vector<Transition> transitions;
    transitions.push_back(Transition{
                    GameState::running,
                    GameState::finished,
                    [this](){
                        for(const auto& snake: fSnakes){
                            if(snake.getState() != SnakeState::dead){
                                return false;
                            }
                        }
                        return true; // if all snakes died, game is finished
                    }});
    return transitions;
}

std::map<GameState, StateAction> GameEngine::createStates(){
    std::map<GameState, StateAction> actions;
    
    actions.emplace(GameState::idle, StateAction{
        [this](){
            for(auto& snake: fSnakes){
                snake.reset();
            }
            fFoodGenerator.reset();
        },// entry
        [](){}// during
    });
    
    actions.emplace(GameState::running, StateAction{
        [this](){
            for(auto& snake: fSnakes){
                snake.setState(SnakeState::running);
            }
            fFoodGenerator.setState(FoodGenState::running);
        }, // entry
        [this](){
            stepSnakes();
            fFoodGenerator.step([this](){return getFreePoints();});
            checkSnakeEatsFood();
        } // during
    });
    
    actions.emplace(GameState::finished, StateAction{
        [](){}, //entry
        [](){} // during
    });
    return actions;
}
