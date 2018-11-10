//
//  rendererApp.hpp
//  cefclient
//
//  Created by Hui Xie on 24/10/2018.
//
#pragma once

#include "include/cef_app.h"

#include "renderer_snake_info.hpp"

#include <unordered_map>
#include <string>

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
//    void OnWebKitInitialized() override;
    
    void OnContextCreated(CefRefPtr<CefBrowser> browser,
                          CefRefPtr<CefFrame> frame,
                          CefRefPtr<CefV8Context> context) override;
    
//    void OnContextReleased(CefRefPtr<CefBrowser> browser,
//                           CefRefPtr<CefFrame> frame,
//                           CefRefPtr<CefV8Context> context) override;
    
    bool OnProcessMessageReceived(CefRefPtr<CefBrowser> browser,
                                  CefProcessId source_process,
                                  CefRefPtr<CefProcessMessage> message) override;
    
    const CefRefPtr<CefV8Value>& getSnakePosition(std::string sid) const;
    const CefRefPtr<CefV8Value>& getSnakeState(std::string sid) const;
    const CefRefPtr<CefV8Value> getFoodPositions() const;
    std::vector<std::string> getSnakeIDs() const;
    
private:
    std::unordered_map<std::string, snake::SnakeInfo> fSnakesInfo;
    CefRefPtr<CefV8Value> fFoods;
    IMPLEMENT_REFCOUNTING(RendererApp);
    
    void handleMoveMessage(CefRefPtr<CefBrowser>, CefRefPtr<CefProcessMessage>);
    void handleStateMessage(CefRefPtr<CefBrowser>, CefRefPtr<CefProcessMessage>);
    void handleFoodMessage(CefRefPtr<CefBrowser>, CefRefPtr<CefProcessMessage>);
    
    CefRefPtr<CefV8Value> createPointArrayFromArgs(CefRefPtr<CefListValue>);
};
