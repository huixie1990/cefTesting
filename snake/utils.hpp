//
//  utils.hpp
//  cefclient
//
//  Created by Hui Xie on 02/11/2018.
//

#pragma once
#include "snake.hpp"
#include "boarder.hpp"
namespace snake{
    namespace  utils{
        bool isSnakeInsideBoarder(const Snake&, const Boarder&);
    }
}
