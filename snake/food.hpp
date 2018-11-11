//
//  food.hpp
//  cefclient
//
//  Created by Hui Xie on 01/11/2018.
//

#pragma once
#include "point.hpp"
#include "listner.hpp"
#include <vector>
namespace snake {
    class GameEngine;
    
    class Food{
    public:
        explicit Food(const Point& point) : fPosition(point){};
        Food(const Food&) = delete;
        Food& operator=(const Food&) = delete;
        Food(Food &&) = default;
        Food& operator=(Food &&) = default;
        
        Point getPosition() const;
    private:
        Point fPosition;
    };
    
    enum class FoodGenState{
        idle, running
    };
    
    bool operator==(const Food& a, const Food& b);
    
    class FoodGenerator{
    public:
        FoodGenerator(int size) : fSize(size){};
        
        void step(std::function<std::vector<Point>()> freePointsProvider);
        void reset();
        void foodEaten(const Food&);
        
        bool shouldGenerate();
        void generate(const std::function<std::vector<Point>()>&);
        
        void addListner(Listner<FoodGenerator>*);
        
        const std::vector<Food>& getFoods() const;
        void setState(FoodGenState);
    private:
        std::vector<Food> fFoods;
        decltype(fFoods.size()) fSize;
        std::vector<Listner<FoodGenerator>*> fListners;
        FoodGenState fState = FoodGenState::idle;
        
        
        void notifyListners(const std::string&);
        void generateFood(size_t, const std::function<std::vector<Point>()>&);
    };
}
