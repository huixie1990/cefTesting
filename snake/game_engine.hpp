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

namespace snake {
    
    class GameEngine{
        // This class owns snakes, food, playground
    public:

        explicit GameEngine(std::chrono::duration<double> sampleTime);
        GameEngine(const GameEngine&)=delete;
        
        void runGameUntil(std::function<bool()> predicate);
        void step();
        
        void sendDirectionToSnake(Direction dir, int snakeIdx);
        
        std::vector<Snake>& getSnakes();
        const std::vector<Snake>& getSnakes() const;
    private:
        std::chrono::duration<double> fSampleTime;
        std::vector<Snake> fSnakes;
    };
    
}
