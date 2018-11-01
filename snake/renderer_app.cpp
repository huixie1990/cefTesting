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

// CefRenderProcessHandler methods:
//void RendererApp::OnWebKitInitialized() {
//    // Create the renderer-side router for query handling.
//    CefMessageRouterConfig config;
//    fMessageRouter = CefMessageRouterRendererSide::Create(config);
//}

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
    addJSFunction(positionHandler, snake::GET_POS_FUNC_NAME);
    addJSFunction(idHandler, snake::GET_ID_FUNC_NAME);
    
   // fMessageRouter->OnContextCreated(browser, frame, context);
}

//void RendererApp::OnContextReleased(CefRefPtr<CefBrowser> browser,
//                                    CefRefPtr<CefFrame> frame,
//                                    CefRefPtr<CefV8Context> context) {
//    fMessageRouter->OnContextReleased(browser, frame, context);
//}

bool RendererApp::OnProcessMessageReceived(CefRefPtr<CefBrowser> browser,
                                           CefProcessId source_process,
                                           CefRefPtr<CefProcessMessage> message) {
    
    auto context = browser->GetMainFrame()->GetV8Context();
    context->Enter();
    const std::string& message_name = message->GetName();
    if (message_name.find(snake::SNAKE_MOVE_MESSAGE) == 0) {
        // Handle the message here...
        auto sid = message_name.substr(message_name.find(':') + 1);
        
        auto args = message->GetArgumentList();
        
        auto points = CefV8Value::CreateArray(args->GetSize());
        for(decltype(args->GetSize()) i = 0; i < args->GetSize(); i++){
            auto point = args->GetDictionary(i);
            auto jsonPoint = CefV8Value::CreateObject(nullptr, nullptr);
            jsonPoint->SetValue("x",CefV8Value::CreateInt(point->GetInt("x")), V8_PROPERTY_ATTRIBUTE_READONLY);
            jsonPoint->SetValue("y",CefV8Value::CreateInt(point->GetInt("y")), V8_PROPERTY_ATTRIBUTE_READONLY);
            points->SetValue(i, jsonPoint);
        }
        fSnakesPoints[sid] =points;
        context->Exit();
        
        // update the UI
        auto frame = browser->GetMainFrame();
        frame->ExecuteJavaScript("drawNow()", frame->GetURL(), 0);
        
        return true;
    }
    return false;
    
//    return fMessageRouter->OnProcessMessageReceived(browser, source_process,
//                                                    message);
}


 const CefRefPtr<CefV8Value>& RendererApp::getSnakePosition(std::string sid) const{
    return fSnakesPoints.at(sid);
 }

std::vector<std::string> RendererApp::getSnakeIDs() const{
    std::vector<std::string> result;
    for(const auto& entry:fSnakesPoints){
        result.push_back(entry.first);
    }
    return result;
}
