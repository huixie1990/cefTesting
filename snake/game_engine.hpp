//
//  game_engine.hpp
//  cefclient
//
//  Created by Hui Xie on 27/10/2018.
//

#pragma once

#include <chrono>
#include "snake.hpp"

namespace snake {
    
    // This class owns snakes, food, playground
    
    class GameEngine{
        
    public:
        GameEngine():GameEngine(std::chrono::milliseconds(100)){};
        GameEngine(std::chrono::duration<double> sampleTime): fSampleTime(sampleTime){

        };
        
        void step();
        
        Snake& getSnake(){return fSnake;};
        
    private:
        std::chrono::duration<double> fSampleTime;
        Snake fSnake = Snake({{0,0},{1,0},{2,0},{3,0}},20);
    };
    
}
