//
//  listner.hpp
//  cefclient
//
//  Created by Hui Xie on 28/10/2018.
//

#pragma once

template <typename T>
class Listner{
public:
    virtual void notify(const T&) =0;
};
