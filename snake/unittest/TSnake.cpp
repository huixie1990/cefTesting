////
////  TSnake.cpp
////  cefclient
////
////  Created by Hui Xie on 07/11/2018.
////
//
#include "../snake.hpp"
#include "../point.hpp"
#include "gtest/gtest.h"

#include <utility>

namespace {
    using Points = std::vector<snake::Point>;
    using namespace std::chrono;
    class SnakeInitPointsTest :
    public ::testing::TestWithParam<Points> {
        // You can implement all the usual fixture class members here.
        // To access the test parameter, call GetParam() from class
        // TestWithParam<T>.
    };
    
    TEST_P(SnakeInitPointsTest, InvalidPointsThrow) {
        
        EXPECT_THROW(snake::Snake(GetParam(), 1 ,snake::Direction::up),
                     std::runtime_error);
        
    }
    
    INSTANTIATE_TEST_CASE_P(NonContinuousPoints,
                            SnakeInitPointsTest,
                            ::testing::Values(Points{{1,1},{2,2}},
                                              Points{{1,1},{1,3}},
                                              Points{{1,1},{1, -1}},
                                              Points{{1,1},{1,2},{1,4}},
                                              Points{{1,1},{3,1}}));
    
    INSTANTIATE_TEST_CASE_P(DuplicatedPoints,
                            SnakeInitPointsTest,
                            ::testing::Values(Points{{1,1},{1,1}},
                                              Points{{1,1},{1,2},{1,1}}));
    
    // The fixture for testing class Foo.
    class SnakeMoveTest : public ::testing::Test {
    protected:
        SnakeMoveTest(): fBuilder(snake::SnakeBuilder{}.speed(1).direction(snake::Direction::up).tail({5,5}).length(3)),
            fSnake(fBuilder.build()) {
        }
        
        ~SnakeMoveTest() override = default;
        
        void SetUp() override {
            fSnake = fBuilder.build();
        }
        
        snake::SnakeBuilder fBuilder;
        snake::Snake fSnake;
    };
    
    
    TEST_F(SnakeMoveTest, LengthDoesNotChange) {
        auto originalLength = fSnake.getPosition().size();
        fSnake.move(2);
        EXPECT_EQ(fSnake.getPosition().size(), originalLength);
    }
    
    TEST_F(SnakeMoveTest, MovePointsMatch) {
        fSnake.move(1);
        Points expected = {{5,6},{5,7},{5,8}};
        EXPECT_EQ(fSnake.getPosition(), expected);
    }
    
    TEST_F(SnakeMoveTest, MoveDirectionChange) {
        fSnake.setDirection(snake::Direction::right);
        fSnake.move(1);
        Points expected = {{5,6},{5,7},{6,7}};
        EXPECT_EQ(fSnake.getPosition(), expected);
    }
    
    TEST_F(SnakeMoveTest, GrowTest) {
        auto originalLength = fSnake.getPosition().size();
        
        fSnake.setDirection(snake::Direction::right);
        fSnake.move(1);
        fSnake.grow();
        
        EXPECT_EQ(fSnake.getPosition().size(), originalLength + 1);
        Points expected = {{5,5},{5,6},{5,7},{6,7}};
        EXPECT_EQ(fSnake.getPosition(), expected);
    }
    
    class TimeStepTest : public ::testing::TestWithParam<std::pair<duration<double>,Points>>{
    
        // You can implement all the usual fixture class members here.
        // To access the test parameter, call GetParam() from class
        // TestWithParam<T>.
    };
    
    TEST_P(TimeStepTest, TimeStepPointCorrect) {
        auto snake = snake::SnakeBuilder{}.speed(0.5).tail({1,1}).
                                length(3).direction(snake::Direction::right).build();
        snake.setState(snake::SnakeState::running);
        snake.moveTimeStep(GetParam().first);
        EXPECT_EQ(snake.getPosition(), GetParam().second);
    }
    
    INSTANTIATE_TEST_CASE_P(TimeStepPosTest, TimeStepTest,
            ::testing::Values(std::make_pair(milliseconds(1), Points{{1,1},{2,1},{3,1}}),
                              std::make_pair(milliseconds(1000), Points{{1,1},{2,1},{3,1}}),
                              std::make_pair(milliseconds(1900), Points{{1,1},{2,1},{3,1}}),
                              std::make_pair(milliseconds(2000), Points{{2,1},{3,1},{4,1}}),
                              std::make_pair(milliseconds(3000), Points{{2,1},{3,1},{4,1}}),
                              std::make_pair(milliseconds(4000), Points{{3,1},{4,1},{5,1}})));
}




