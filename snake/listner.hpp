//
//  listner.hpp
//  cefclient
//
//  Created by Hui Xie on 28/10/2018.
//

#pragma once

#include <string>
template <typename T>
class Listner{
public:
    virtual void notified(const T&, const std::string&) =0;
    virtual ~Listner() = default;
};
