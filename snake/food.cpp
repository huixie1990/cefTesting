//
//  food.cpp
//  cefclient
//
//  Created by Hui Xie on 01/11/2018.
//

#include <random>
#include "food.hpp"
#include "game_engine.hpp"
#include "constant.hpp"
using namespace snake;

Point Food::getPosition() const {
    return fPosition;
}

void FoodGenerator::step(){
    if(fState == FoodGenState::idle){
        return;
    }
    if(shouldGenerate()){
        generate();
    }
}

bool FoodGenerator::shouldGenerate(){
    return fFoods.size() < fSize;
}

void FoodGenerator::generate(){
    for(decltype(fSize) i=0; i < fSize - fFoods.size(); i++){
        generateOneFood();
    }
}

const std::vector<Food>& FoodGenerator::getFoods() const{
    return fFoods;
}

void FoodGenerator::setState(FoodGenState state){
    fState = state;
}

void FoodGenerator::addListner(Listner<FoodGenerator>* listener){
    fListners.push_back(listener);
}


// private
void FoodGenerator::notifyListners(const std::string& message){
    for(const auto& listner: fListners){
        listner->notified(*this, message);
    }
}


void FoodGenerator::generateOneFood(){
    
    auto freePoints = fGameEngine->getFreePoints();
    
    std::random_device rd;  //Will be used to obtain a seed for the random number engine
    std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
    std::uniform_int_distribution<> disX(0, freePoints.size()+1);
    
    fFoods.emplace_back(freePoints[disX(gen)]);
    
    notifyListners(FOOD_CREATE_MESSAGE);
}
