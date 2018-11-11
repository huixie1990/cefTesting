//
//  food.cpp
//  cefclient
//
//  Created by Hui Xie on 01/11/2018.
//

#include <random>
#include <algorithm>

#include "food.hpp"
#include "constant.hpp"
using namespace snake;

Point Food::getPosition() const {
    return fPosition;
}

bool snake::operator==(const Food& a, const Food& b){
    return a.getPosition() == b.getPosition();
}

void FoodGenerator::step(std::function<std::vector<Point>()> provider){
    if(fState == FoodGenState::idle){
        return;
    }
    if(shouldGenerate()){
        generate(provider);
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

void FoodGenerator::generate(const std::function<std::vector<Point>()>& provider){
    generateFood(fSize - fFoods.size(), provider);
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


void FoodGenerator::generateFood(size_t num,
                                const std::function<std::vector<Point>()>& provider){
    auto freePoints = provider();
    num = std::min(num, freePoints.size());
    std::random_shuffle(freePoints.begin(), freePoints.end());
    
    std::transform(freePoints.begin(),
                   freePoints.begin() + num,
                   std::back_inserter(fFoods),
                   [](const Point& point){
                       return Food(point);
                   });
    
    
    notifyListners(FOOD_CREATE_MESSAGE);
}
