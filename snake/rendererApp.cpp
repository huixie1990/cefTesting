//
//  rendererApp.cpp
//  cefclient
//
//  Created by Hui Xie on 24/10/2018.
//

#include "rendererApp.hpp"


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
    return fMessageRouter->OnProcessMessageReceived(browser, source_process,
                                                    message);
}
