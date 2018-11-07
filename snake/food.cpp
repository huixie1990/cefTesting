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

bool snake::operator==(const Food& a, const Food& b){
    return a.getPosition() == b.getPosition();
}

void FoodGenerator::step(){
    if(shouldGenerate()){
        generate();
    }
}

void FoodGenerator::reset(){
    fFoods.clear();
    fState = FoodGenState::idle;
    notifyListners(FOOD_CREATE_MESSAGE);
}

void FoodGenerator::foodEaten(const Food& food){
    fFoods.erase(std::find(fFoods.begin(),fFoods.end(),food));
    notifyListners(FOOD_CREATE_MESSAGE);
}

bool FoodGenerator::shouldGenerate(){
    return fFoods.size() < fSize;
}

void FoodGenerator::generate(){
    generateFood(fSize - fFoods.size());
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


void FoodGenerator::generateFood(int num){
    
    auto freePoints = fGameEngine->getFreePoints();
    std::random_shuffle(freePoints.begin(), freePoints.end());
//    std::random_device rd;  //Will be used to obtain a seed for the random number engine
//    std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
//    std::uniform_int_distribution<> disX(0, freePoints.size()+1);
//
    //fFoods.emplace_back(freePoints[disX(gen)]);
    
    for (int i =0; i< num;i++){
        fFoods.emplace_back(freePoints[i]);
    }
    
    notifyListners(FOOD_CREATE_MESSAGE);
}
