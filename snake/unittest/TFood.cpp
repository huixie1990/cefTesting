//
//  tFood.cpp
//  libcef_dll_wrapper
//
//  Created by Hui Xie on 11/11/2018.
//

#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "../food.hpp"

#include <utility>
namespace {
    using namespace ::testing;
    using Points = std::vector<snake::Point>;
    auto fiveFreePointsProvider = [](){
        return Points{{1,1},{2,2},{3,3},{4,4},{5,5}};
    };
    // The fixture for testing class Foo.
    class FoodGeneratorTest : public ::testing::Test {
    protected:
        FoodGeneratorTest() = default;
        
        ~FoodGeneratorTest() override =default;
        
        void SetUp() override {
            fGenerator = snake::FoodGenerator{3};
            // Code here will be called immediately after the constructor (right
            // before each test).
        }
        
        snake::FoodGenerator fGenerator = snake::FoodGenerator{3};
    };
    
    TEST_F(FoodGeneratorTest, GenaratorPredicateTest){
        EXPECT_EQ(fGenerator.shouldGenerate(), true);
        
        fGenerator.generate(fiveFreePointsProvider);
        
        EXPECT_EQ(fGenerator.shouldGenerate(), false);
    }
    
    TEST_F(FoodGeneratorTest, GenaratorFoodPosTest){
        
        fGenerator.generate(fiveFreePointsProvider);
        
        auto foods = fGenerator.getFoods();
        Points foodPoints;
        std::transform(foods.begin(), foods.end(), std::back_inserter(foodPoints),
                       [](snake::Food& food){
                           return food.getPosition();
                       });
        
        for (auto& foodPoint: foodPoints){
            EXPECT_THAT(fiveFreePointsProvider(), Contains(foodPoint));
        }
        
    }
    
    
    class GeneratorLengthTest :
        public ::testing::TestWithParam<std::pair<int,int>>
       {};
    
    TEST_P(GeneratorLengthTest, GeneratorCorrectNumberOfFood) {
        int generatorSize, expectedFoodNumber;
        std::tie(generatorSize, expectedFoodNumber) = GetParam();
        
        snake::FoodGenerator foodGenerator{generatorSize};
        
        foodGenerator.generate(fiveFreePointsProvider);
        
        EXPECT_THAT(foodGenerator.getFoods(), SizeIs(expectedFoodNumber));
    }
    
    INSTANTIATE_TEST_CASE_P(DifferentSizeOfFreePoints, GeneratorLengthTest,
          ::testing::Values(std::make_tuple(3, 3),
                            std::make_tuple(5, 5),
                            std::make_tuple(6, 5)
                            ));
    
}
