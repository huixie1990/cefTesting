//
//  TGameEngine.cpp
//  libcef_dll_wrapper
//
//  Created by Hui Xie on 14/11/2018.
//

#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "../game_engine.hpp"

#include <chrono>
namespace {
     using Points = std::vector<snake::Point>;
    // The fixture for testing class Foo.
    class GameEngineTest : public ::testing::Test {
    protected:
        GameEngineTest():fGameEngine(std::chrono::milliseconds(100)) {};
        
        ~GameEngineTest() override =default;
        
        void SetUp() override {
            
            // Code here will be called immediately after the constructor (right
            // before each test).
        }
        snake::GameEngine fGameEngine;
    };
    
    TEST_F(GameEngineTest, StepTest){
        fGameEngine.setState(snake::GameState::running);
        std::vector<Points> positions;
        for(const auto& snake: fGameEngine.getSnakes()){
            positions.push_back(snake.getPosition());
        }
        for (int i = 0; i <30; i++){
            fGameEngine.step();
        }
        const auto& snakes = fGameEngine.getSnakes();
        for(decltype(snakes.size()) i=0; i<snakes.size(); i++){
            EXPECT_NE(snakes[i].getPosition(), positions[i]);
        }
    }
    
    TEST_F(GameEngineTest, OneSnakeDead){
        fGameEngine.setState(snake::GameState::running);
        fGameEngine.step();
        auto& snakes =  fGameEngine.getSnakes();
        if(snakes.size() > 1){
            snakes[0].setState(snake::SnakeState::dead);
        }
        fGameEngine.step();
        
        EXPECT_EQ(fGameEngine.getState(), snake::GameState::running);
    }
    
    TEST_F(GameEngineTest, SnakeAllDead){
        fGameEngine.setState(snake::GameState::running);
        fGameEngine.step();
        for(auto& snake: fGameEngine.getSnakes()){
            snake.setState(snake::SnakeState::dead);
        }
        fGameEngine.step();
        
        EXPECT_EQ(fGameEngine.getState(), snake::GameState::finished);
    }
    
    TEST_F(GameEngineTest, ChangeSnakeDirection){
        fGameEngine.setState(snake::GameState::running);
        fGameEngine.step();
        auto& snakes =  fGameEngine.getSnakes();
        fGameEngine.sendDirectionToSnake(snake::Direction::up, 0);
        fGameEngine.step();
        
        EXPECT_EQ(snakes[0].getDirection(), snake::Direction::up);
    }
    
    TEST_F(GameEngineTest, ChangeSnakeDirectionInvalid){
        fGameEngine.setState(snake::GameState::running);
        fGameEngine.step();
        auto& snakes =  fGameEngine.getSnakes();
        auto originalDirection = snakes[0].getDirection();
        fGameEngine.sendDirectionToSnake(snake::oposite(originalDirection), 0);
        fGameEngine.step();
        
        EXPECT_EQ(snakes[0].getDirection(), originalDirection);
    }
    
    TEST_F(GameEngineTest, ChangeSnakeDirectionSameDir){
        fGameEngine.setState(snake::GameState::running);
        fGameEngine.step();
        auto& snakes =  fGameEngine.getSnakes();
        auto originalPos = snakes[0].getPosition();
        fGameEngine.sendDirectionToSnake(snakes[0].getDirection(), 0);
        
        EXPECT_NE(snakes[0].getPosition(), originalPos);
    }
}
