//
//  game_engine.hpp
//  cefclient
//
//  Created by Hui Xie on 27/10/2018.
//

#pragma once

#include <chrono>
#include <vector>
#include <unordered_map>
#include <functional>

#include "snake.hpp"
#include "food.hpp"
#include "boarder.hpp"
namespace snake {
    enum class GameState{
        idle, running, finished
    };
    
    struct Transition{
        GameState source;
        GameState destination;
        std::function<bool()> condition;
    };
    
    struct StateAction{
        std::function<void()> entry;
        std::function<void()> during;
    };
    
    class GameEngine{
        // This class owns snakes, food, boarder
    public:

        explicit GameEngine(std::chrono::duration<double> sampleTime);
        GameEngine(const GameEngine&)=delete;
        GameEngine& operator=(const GameEngine&)=delete;
        
        
        // operations
        void runGameUntil(std::function<bool()> predicate);
        std::vector<Point> getFreePoints() const;
        void step();
        // possible async calls
        void sendDirectionToSnake(Direction dir, int snakeIdx);
        void gameStartRequested();
        
        // getters setters
        std::vector<Snake>& getSnakes();
        const std::vector<Snake>& getSnakes() const;
        
        FoodGenerator& getFoodGenerator();
        const FoodGenerator& getFoodGenerator() const;
        
        const Boarder& getBoarder() const;
        void setState(GameState);
        GameState getState() const;        
    private:
        std::chrono::duration<double> fSampleTime;
        std::vector<Snake> fSnakes;
        Boarder fBoarder;
        FoodGenerator fFoodGenerator;
        GameState fGameState  = GameState::idle;
        GameState fPreviousState  = GameState::idle;
        std::vector<Transition> fTransitions;
        std::unordered_map<GameState, StateAction> fStateActions;
        
        
        void stepSnakes();
        void checkSnakeEatsFood();
        

        bool snakeHeadHitsObject(const Snake&);
        
        std::vector<Snake> createSnakes();
        std::vector<Transition> createTransitions();
        std::unordered_map<GameState, StateAction> createStates();
    };
    

}
