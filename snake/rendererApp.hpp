//
//  rendererApp.hpp
//  cefclient
//
//  Created by Hui Xie on 24/10/2018.
//
#pragma once

#include "include/cef_app.h"
#include "include/wrapper/cef_message_router.h"

class RendererApp : public CefApp, public CefRenderProcessHandler {
public:
    RendererApp() = default;
    RendererApp(const RendererApp&) = delete;
    RendererApp(RendererApp&&) = default;
    RendererApp& operator=(RendererApp) = delete;
    RendererApp& operator=(RendererApp&&) = default;
    ~RendererApp() = default;
    CefRefPtr<CefRenderProcessHandler> GetRenderProcessHandler() override;
    
    // CefRenderProcessHandler methods:
    void OnWebKitInitialized() override;
    
    void OnContextCreated(CefRefPtr<CefBrowser> browser,
                          CefRefPtr<CefFrame> frame,
                          CefRefPtr<CefV8Context> context) override;
    
    void OnContextReleased(CefRefPtr<CefBrowser> browser,
                           CefRefPtr<CefFrame> frame,
                           CefRefPtr<CefV8Context> context) override;
    
    bool OnProcessMessageReceived(CefRefPtr<CefBrowser> browser,
                                  CefProcessId source_process,
                                  CefRefPtr<CefProcessMessage> message) override;
    
    
private:
    // Handles the renderer side of query routing.
    CefRefPtr<CefMessageRouterRendererSide> fMessageRouter;
    IMPLEMENT_REFCOUNTING(RendererApp);
};
