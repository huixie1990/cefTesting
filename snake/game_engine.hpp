//
//  game_engine.hpp
//  cefclient
//
//  Created by Hui Xie on 27/10/2018.
//

#pragma once

#include <chrono>
#include <vector>
#include <functional>

#include "snake.hpp"
#include "food.hpp"
#include "boarder.hpp"
namespace snake {
    enum class GameState{
        idle, running, finished
    };
    
    class GameEngine{
        // This class owns snakes, food, boarder
    public:

        explicit GameEngine(std::chrono::duration<double> sampleTime);
        GameEngine(const GameEngine&)=delete;
        GameEngine& operator=(const GameEngine&)=delete;
        
        
        // operations
        void runGameUntil(std::function<bool()> predicate);
        void sendDirectionToSnake(Direction dir, int snakeIdx);
        void gameStartRequested();
        
        std::vector<Point> getFreePoints() const;
        
        // getters
        std::vector<Snake>& getSnakes();
        const std::vector<Snake>& getSnakes() const;
        FoodGenerator& getFoodGenerator();
        const FoodGenerator& getFoodGenerator() const;
        const Boarder& getBoarder() const;
        void setState(GameState);
    private:
        std::chrono::duration<double> fSampleTime;
        std::vector<Snake> fSnakes;
        Boarder fBoarder;
        FoodGenerator fFoodGenerator;
        GameState fGameState  = GameState::idle;
        GameState fPreviousState  = GameState::idle;
        
        void step();
        void stepSnakes();
        void entry(GameState);
        void during(GameState);
        bool snakeHeadHitsObject(const Snake&);
    };
    
}
