//
//  renderer_snake_info.hpp
//  cefclient
//
//  Created by Hui Xie on 03/11/2018.
//

#pragma once
#include "include/cef_v8.h"
namespace snake{
    struct SnakeInfo{
        CefRefPtr<CefV8Value> snakePoints;
        CefRefPtr<CefV8Value> snakeState;
    };
}
