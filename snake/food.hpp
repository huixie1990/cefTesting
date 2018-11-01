//
//  food.hpp
//  cefclient
//
//  Created by Hui Xie on 01/11/2018.
//

#pragma once
#include "point.hpp"
#include <vector>
namespace snake {
    class Food{
    public:
        explicit Food(const Point& point) : fPosition(point){};
        Food(const Food&) = delete;
        Food& operator=(const Food&) = delete;
        
        Point getPosition() const;
    private:
        Point fPosition;
    };
    
    class FoodGenerator{
    public:
        explicit FoodGenerator(int size) : fSize(size){};
        bool shouldGenerate();
        void generate();
    private:
        std::vector<Food> fFoods;
        decltype(fFoods.size()) fSize;
        
        void generateFood(int number);
    };
}
