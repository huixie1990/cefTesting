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

    class GameEngine;
    
    class GameEngineListner{
    public:
        virtual void notify(const GameEngine&) = 0;
        virtual ~GameEngineListner() = default;
    };
    
    class GameEngine{
        
    public:
        GameEngine():GameEngine(std::chrono::milliseconds(100)){
        };
        GameEngine(std::chrono::duration<double> sampleTime): fSampleTime(sampleTime){};
        
        void step();
        int getPos() const{return pos;};
        
        void setApp(GameEngineListner* app){fApp = app;};
        std::chrono::duration<double> foo() const{return fSampleTime;}
    private:
        int pos = 10;
        std::chrono::duration<double> fSampleTime;
        GameEngineListner* fApp;
        Snake fSnake = Snake({{1,1}},2.5);
    };
    
}
