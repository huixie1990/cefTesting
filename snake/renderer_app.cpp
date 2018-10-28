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
    
    const std::string& message_name = message->GetName();
    if (message_name == "my_message") {
        // Handle the message here...
        auto args = message->GetArgumentList();
        pos = args->GetInt(0);
        return true;
    }
    
    return fMessageRouter->OnProcessMessageReceived(browser, source_process,
                                                    message);
}
