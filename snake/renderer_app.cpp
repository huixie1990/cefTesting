//
//  rendererApp.cpp
//  cefclient
//
//  Created by Hui Xie on 24/10/2018.
//

#include "renderer_app.hpp"
#include "js_function_handler.hpp"

// CefApp methods:
CefRefPtr<CefRenderProcessHandler> RendererApp::GetRenderProcessHandler() {
    return this;
}

// CefRenderProcessHandler methods:
void RendererApp::OnWebKitInitialized() {
    // Create the renderer-side router for query handling.
    CefMessageRouterConfig config;
    fMessageRouter = CefMessageRouterRendererSide::Create(config);
}

void RendererApp::OnContextCreated(CefRefPtr<CefBrowser> browser,
                                   CefRefPtr<CefFrame> frame,
                                   CefRefPtr<CefV8Context> context) {
    
    auto window = context->GetGlobal();
    

    CefRefPtr<CefV8Handler> handler = new snake::JsSnakeLocationHandler(this);
    // Create JS function that gets the position from renderer process
    auto func = CefV8Value::CreateFunction(snake::getJsSnakePosFuncName(), handler);
    window->SetValue(snake::getJsSnakePosFuncName(), func, V8_PROPERTY_ATTRIBUTE_NONE);
    
    fMessageRouter->OnContextCreated(browser, frame, context);
}

void RendererApp::OnContextReleased(CefRefPtr<CefBrowser> browser,
                                    CefRefPtr<CefFrame> frame,
                                    CefRefPtr<CefV8Context> context) {
    fMessageRouter->OnContextReleased(browser, frame, context);
}

bool RendererApp::OnProcessMessageReceived(CefRefPtr<CefBrowser> browser,
                                           CefProcessId source_process,
                                           CefRefPtr<CefProcessMessage> message) {
    
    auto context = browser->GetMainFrame()->GetV8Context();
    context->Enter();
    const std::string& message_name = message->GetName();
    if (message_name == "my_message") {
        // Handle the message here...

        auto args = message->GetArgumentList();
        
        auto points = CefV8Value::CreateArray(args->GetSize());
        for(unsigned i=0;i<args->GetSize();i++){
            auto point = args->GetDictionary(i);
            auto jsonPoint = CefV8Value::CreateObject(nullptr, nullptr);
            jsonPoint->SetValue("x",CefV8Value::CreateInt(point->GetInt("x")), V8_PROPERTY_ATTRIBUTE_READONLY);
            jsonPoint->SetValue("y",CefV8Value::CreateInt(point->GetInt("y")), V8_PROPERTY_ATTRIBUTE_READONLY);
            points->SetValue(i, jsonPoint);
        }
        fSnakePoints = points;
        context->Exit();
        
        // update the UI
        auto frame = browser->GetMainFrame();
        frame->ExecuteJavaScript("drawNow()", frame->GetURL(), 0);
        
        return true;
    }
    
    return fMessageRouter->OnProcessMessageReceived(browser, source_process,
                                                    message);
}
