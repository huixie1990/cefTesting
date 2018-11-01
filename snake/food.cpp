//
//  food.cpp
//  cefclient
//
//  Created by Hui Xie on 01/11/2018.
//

#include "food.hpp"
using namespace snake;

Point Food::getPosition() const {
    return fPosition;
}

bool FoodGenerator::shouldGenerate(){
    return fFoods.size() < fSize;
}

void FoodGenerator::generate(){}

void FoodGenerator::generateFood(int number){}
