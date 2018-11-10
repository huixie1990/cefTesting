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

namespace {
    using Points = std::vector<snake::Point>;
    // The fixture for testing class Foo.
    class SnakeTest : public ::testing::Test {
    protected:
        // You can remove any or all of the following functions if its body
        // is empty.
        
        SnakeTest() {
            // You can do set-up work for each test here.
        }
        
        ~SnakeTest() override {
            // You can do clean-up work that doesn't throw exceptions here.
        }
        
        // If the constructor and destructor are not enough for setting up
        // and cleaning up each test, you can define the following methods:
        
        void SetUp() override {
            // Code here will be called immediately after the constructor (right
            // before each test).
        }
        
        void TearDown() override {
            // Code here will be called immediately after each test (right
            // before the destructor).
        }
        
        // Objects declared here can be used by all tests in the test case for Foo.
    };
}

class SnakePointsTest :
public ::testing::TestWithParam<Points> {
    // You can implement all the usual fixture class members here.
    // To access the test parameter, call GetParam() from class
    // TestWithParam<T>.
};

TEST_P(SnakePointsTest, InvalidPointsThrow) {
    
    EXPECT_THROW(snake::Snake(GetParam(), 1 ,snake::Direction::up),
                 std::runtime_error);
    
}

INSTANTIATE_TEST_CASE_P(NonContinuousPoints,
                        SnakePointsTest,
                        ::testing::Values(Points{{1,1},{2,2}},
                                          Points{{1,1},{1,3}},
                                          Points{{1,1},{1, -1}},
                                          Points{{1,1},{1,2},{1,4}},
                                          Points{{1,1},{3,1}}));

INSTANTIATE_TEST_CASE_P(DuplicatedPoints,
                        SnakePointsTest,
                        ::testing::Values(Points{{1,1},{1,1}},
                                          Points{{1,1},{1,2},{1,1}}));
