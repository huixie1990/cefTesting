//
//  js_function_handler.cpp
//  cefclient
//
//  Created by Hui Xie on 25/10/2018.
//

#include "js_function_handler.hpp"

bool snake::JsSnakeLocationHandler::Execute(const CefString& name,
                     CefRefPtr<CefV8Value> object,
                     const CefV8ValueList& arguments,
                     CefRefPtr<CefV8Value>& retval,
                     CefString& exception)  {
    if (name == snake::getJsSnakePosFuncName()) {

        // Return my string value.
        retval = CefV8Value::CreateInt(fApp->getPos());
        return true;
    }
    
    // Function does not exist.
    return false;
}


std::string snake::getJsSnakePosFuncName(){
    static std::string JS_GET_POS_FUNC_NAME = "getPositionForSnake";
    return JS_GET_POS_FUNC_NAME;
}
