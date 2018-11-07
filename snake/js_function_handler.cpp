//
//  js_function_handler.cpp
//  cefclient
//
//  Created by Hui Xie on 25/10/2018.
//

#include "js_function_handler.hpp"
#include "constant.hpp"

const std::string snake::GET_POS_FUNC_NAME = "getPositionForSnake";
const std::string snake::GET_ID_FUNC_NAME = "getSnakeIDs";
const std::string snake::GET_STATE_FUNC_NAME = "getSnakeState";
const std::string snake::GET_FOOD_FUNC_NAME = "getFoodPositions";
const std::string snake::GET_CANVAS_SIZE_FUNC_NAME = "getCanvasSize";
const std::string snake::REQUEST_POS_FUNC_NAME = "requestPositions";

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

bool snake::JsSnakeStateHandler::Execute(const CefString& name,
                                      CefRefPtr<CefV8Value> object,
                                      const CefV8ValueList& arguments,
                                      CefRefPtr<CefV8Value>& retval,
                                      CefString& exception)  {
    if (name == snake::GET_STATE_FUNC_NAME) {
        if(arguments.size()!=1){
            return false;
        }
        auto arg = arguments.at(0);
        if(!arg->IsString()){
            return false;
        }
        
        auto sid = arg->GetStringValue();
        retval = fApp->getSnakeState(sid.ToString());
        return true;
    }
    // Function does not exist.
    return false;
}

bool snake::JsFoodHandler::Execute(const CefString& name,
                                      CefRefPtr<CefV8Value> object,
                                      const CefV8ValueList& arguments,
                                      CefRefPtr<CefV8Value>& retval,
                                      CefString& exception)  {
    if (name == snake::GET_FOOD_FUNC_NAME) {

        retval = fApp -> getFoodPositions();

        return true;
    }
    // Function does not exist.
    return false;
}



bool snake::JsCanvasHandler::Execute(const CefString& name,
             CefRefPtr<CefV8Value> object,
             const CefV8ValueList& arguments,
             CefRefPtr<CefV8Value>& retval,
             CefString& exception){

    if (name == GET_CANVAS_SIZE_FUNC_NAME){
        auto size = CefV8Value::CreateObject(nullptr, nullptr);
        size->SetValue("width",CefV8Value::CreateInt(CANVAS_WIDTH),
                            V8_PROPERTY_ATTRIBUTE_READONLY);
        size->SetValue("height",CefV8Value::CreateInt(CANVAS_HEIGHT),
                            V8_PROPERTY_ATTRIBUTE_READONLY);
        retval = size;
        return true;

    }
    return false;
}

bool snake::JsRequestHandler::Execute(const CefString& name,
                                     CefRefPtr<CefV8Value> object,
                                     const CefV8ValueList& arguments,
                                     CefRefPtr<CefV8Value>& retval,
                                     CefString& exception){
    
    if (name == REQUEST_POS_FUNC_NAME){
        
        
        CefRefPtr<CefProcessMessage> msg= CefProcessMessage::Create(REQUEST_POSITIONS_MESSAGE);
        
        // Send the process message to the render process.
        // Use PID_BROWSER instead when sending a message to the browser process.
        fBrowser->SendProcessMessage(PID_BROWSER, msg);
        return true;
    }
    return false;
}
