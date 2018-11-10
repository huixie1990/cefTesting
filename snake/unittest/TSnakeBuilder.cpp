//
//  TSnakeBuilder.cpp
//  libcef_dll_wrapper
//
//  Created by Hui Xie on 09/11/2018.
//

#include "../snake.hpp"
#include "../point.hpp"
#include "gtest/gtest.h"

namespace {
    
    // The fixture for testing class Foo.
    class SnakeBuilderTest : public ::testing::Test {
    protected:
        // You can remove any or all of the following functions if its body
        // is empty.
        
        SnakeBuilderTest() = default;
        
        ~SnakeBuilderTest() override =default;
        
        void SetUp() override {
             fSnakeBuilder = snake::SnakeBuilder{};
            // Code here will be called immediately after the constructor (right
            // before each test).
        }
        
        snake::SnakeBuilder fSnakeBuilder;
    };
}


TEST_F(SnakeBuilderTest, BuilderTestBasic) {
    auto snake = fSnakeBuilder.tail({0,0}).length(1).build();
    std::vector<snake::Point> expected{{0,0}};
    EXPECT_EQ(snake.getPosition(),expected);
}

TEST_F(SnakeBuilderTest, BuilderTestTail) {
    auto tailPoint = snake::Point{5,5};
    auto snake = fSnakeBuilder.tail(tailPoint).length(5).build();
    EXPECT_EQ(*snake.getPosition().begin(),tailPoint);
}

TEST_F(SnakeBuilderTest, BuilderTestLength) {
    auto snake = fSnakeBuilder.tail({0,0}).length(6).build();
    EXPECT_EQ(static_cast<int>(snake.getPosition().size()),6);
}

TEST_F(SnakeBuilderTest, BuilderTestDirection) {
    auto snake = fSnakeBuilder.tail({0,0}).length(1).direction(snake::Direction::down).build();
    EXPECT_EQ(snake.getDirection(),snake::Direction::down);
}

TEST_F(SnakeBuilderTest, BuilderTestSpeed) {
    auto snake = fSnakeBuilder.tail({0,0}).length(1).speed(2.5).build();
    EXPECT_EQ(snake.getSpeed(),2.5);
}

TEST_F(SnakeBuilderTest, BuilderTestDefault) {
    auto snake = fSnakeBuilder.build();
    std::vector<snake::Point> expected{{0,0}};
    EXPECT_EQ(snake.getPosition(),expected);
}

TEST_F(SnakeBuilderTest, BuilderTestSystem) {
    auto snake = fSnakeBuilder.tail({3,4}).length(4).direction(snake::Direction::right).build();
    std::vector<snake::Point> expectedPostion ={
        {3,4}, {4,4}, {5,4}, {6,4}
    };
    EXPECT_EQ(snake.getPosition(),expectedPostion);
}

