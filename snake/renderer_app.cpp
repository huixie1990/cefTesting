//
//  rendererApp.cpp
//  cefclient
//
//  Created by Hui Xie on 24/10/2018.
//

#include "renderer_app.hpp"
#include "js_function_handler.hpp"
#include "constant.hpp"

// CefApp methods:
CefRefPtr<CefRenderProcessHandler> RendererApp::GetRenderProcessHandler() {
    return this;
}

void RendererApp::OnContextCreated(CefRefPtr<CefBrowser> browser,
                                   CefRefPtr<CefFrame> frame,
                                   CefRefPtr<CefV8Context> context) {
    
    auto window = context->GetGlobal();
    
    auto addJSFunction = [&window](CefRefPtr<CefV8Handler> handler, const std::string& name){
        auto func = CefV8Value::CreateFunction(name, handler);
        window->SetValue(name, func, V8_PROPERTY_ATTRIBUTE_NONE);
    };
    
    CefRefPtr<CefV8Handler> positionHandler = new snake::JsSnakeLocationHandler(this);
    CefRefPtr<CefV8Handler> idHandler = new snake::JsSnakeIDHandler(this);
    CefRefPtr<CefV8Handler> stateHandler = new snake::JsSnakeStateHandler(this);
    CefRefPtr<CefV8Handler> foodHandler = new snake::JsFoodHandler(this);
    CefRefPtr<CefV8Handler> canvasHandler = new snake::JsCanvasHandler();
    CefRefPtr<CefV8Handler> requestHandler = new snake::JsRequestHandler(browser);
    
    addJSFunction(positionHandler, snake::GET_POS_FUNC_NAME);
    addJSFunction(idHandler, snake::GET_ID_FUNC_NAME);
    addJSFunction(stateHandler, snake::GET_STATE_FUNC_NAME);
    addJSFunction(foodHandler, snake::GET_FOOD_FUNC_NAME);
    addJSFunction(canvasHandler, snake::GET_CANVAS_SIZE_FUNC_NAME);
    addJSFunction(requestHandler, snake::REQUEST_POS_FUNC_NAME);
}

bool RendererApp::OnProcessMessageReceived(CefRefPtr<CefBrowser> browser,
                                           CefProcessId source_process,
                                           CefRefPtr<CefProcessMessage> message) {
    
    const std::string& message_name = message->GetName();
    if (message_name.find(snake::SNAKE_MOVE_MESSAGE) == 0) {
        handleMoveMessage(browser, message);
        return true;
    } else if(message_name.find(snake::SNAKE_STATE_MESSAGE) == 0){
        handleStateMessage(browser, message);
        return true;
    } else if(message_name == snake::FOOD_CREATE_MESSAGE){
        handleFoodMessage(browser, message);
    }
    return false;
    
}


const CefRefPtr<CefV8Value>& RendererApp::getSnakePosition(std::string sid) const{
    return fSnakesInfo.at(sid).snakePoints;
 }

const CefRefPtr<CefV8Value>& RendererApp::getSnakeState(std::string sid) const{
    return fSnakesInfo.at(sid).snakeState;
}

std::vector<std::string> RendererApp::getSnakeIDs() const{
    std::vector<std::string> result;
    for(const auto& entry:fSnakesInfo){
        result.push_back(entry.first);
    }
    return result;
}

const CefRefPtr<CefV8Value> RendererApp::getFoodPositions() const{
    return fFoods;
}

//private:

void RendererApp::handleMoveMessage(
            CefRefPtr<CefBrowser> browser,
            CefRefPtr<CefProcessMessage> message){
    
    const std::string message_name = message->GetName();
    auto sid = message_name.substr(message_name.find(':') + 1);
    auto context = browser->GetMainFrame()->GetV8Context();
    context->Enter();
    
    auto args = message->GetArgumentList();
    
    auto points = createPointArrayFromArgs(args);
    fSnakesInfo[sid].snakePoints =points;
    context->Exit();
    
    // update the UI
    auto frame = browser->GetMainFrame();
    frame->ExecuteJavaScript("drawNow()", frame->GetURL(), 0);
    
}


void RendererApp::handleStateMessage(
           CefRefPtr<CefBrowser> browser,
           CefRefPtr<CefProcessMessage> message){

    const std::string message_name = message->GetName();
    auto context = browser->GetMainFrame()->GetV8Context();
    context->Enter();
    // Handle the message here...
    auto sid = message_name.substr(message_name.find(':') + 1);
    
    auto args = message->GetArgumentList();
    
    auto state = CefV8Value::CreateString(args->GetString(0));
    fSnakesInfo[sid].snakeState = state;
    context->Exit();
    
    // update the UI
    auto frame = browser->GetMainFrame();
    frame->ExecuteJavaScript("drawNow()", frame->GetURL(), 0);
    
}


void RendererApp::handleFoodMessage(CefRefPtr<CefBrowser> browser,
                                    CefRefPtr<CefProcessMessage> message){
    auto context = browser->GetMainFrame()->GetV8Context();
    context->Enter();
    auto args = message->GetArgumentList();
    
    fFoods = createPointArrayFromArgs(args);

    context->Exit();
    
    // update the UI
    auto frame = browser->GetMainFrame();
    frame->ExecuteJavaScript("drawNow()", frame->GetURL(), 0);
    
}

CefRefPtr<CefV8Value> RendererApp:: createPointArrayFromArgs(CefRefPtr<CefListValue> args){
    auto points = CefV8Value::CreateArray(args->GetSize());
    for(decltype(args->GetSize()) i = 0; i < args->GetSize(); i++){
        auto point = args->GetDictionary(i);
        auto jsonPoint = CefV8Value::CreateObject(nullptr, nullptr);
        jsonPoint->SetValue("x",CefV8Value::CreateInt(point->GetInt("x")), V8_PROPERTY_ATTRIBUTE_READONLY);
        jsonPoint->SetValue("y",CefV8Value::CreateInt(point->GetInt("y")), V8_PROPERTY_ATTRIBUTE_READONLY);
        points->SetValue(i, jsonPoint);
    }
    return points;
}
