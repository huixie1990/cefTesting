//
//  js_function_handler.cpp
//  cefclient
//
//  Created by Hui Xie on 25/10/2018.
//

#include "js_function_handler.hpp"

const std::string snake::GET_POS_FUNC_NAME = "getPositionForSnake";
const std::string snake::GET_ID_FUNC_NAME = "getSnakeIDs";

bool snake::JsSnakeLocationHandler::Execute(const CefString& name,
                     CefRefPtr<CefV8Value> object,
                     const CefV8ValueList& arguments,
                     CefRefPtr<CefV8Value>& retval,
                     CefString& exception)  {
    if (name == snake::GET_POS_FUNC_NAME) {

        if(arguments.size()!=1){
            return false;
        }
        auto arg = arguments.at(0);
        if(!arg->IsString()){
            return false;
        }
        
        auto sid = arg->GetStringValue();
        retval = fApp->getSnakePosition(sid.ToString());
        return true;
    }
    // Function does not exist.
    return false;
}

bool snake::JsSnakeIDHandler::Execute(const CefString& name,
                                            CefRefPtr<CefV8Value> object,
                                            const CefV8ValueList& arguments,
                                            CefRefPtr<CefV8Value>& retval,
                                            CefString& exception)  {
    if (name == snake::GET_ID_FUNC_NAME) {
        auto sids = fApp -> getSnakeIDs();
        auto jsSids = CefV8Value::CreateArray(sids.size());
        for (decltype(sids.size()) i = 0; i < sids.size(); i++){
            auto sid = sids[i];
            auto jsSid = CefV8Value::CreateString(sid);
            jsSids->SetValue(i, jsSid);
        }
        retval = jsSids;
        return true;
    }
    // Function does not exist.
    return false;
}

