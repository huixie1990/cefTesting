// Copyright (c) 2013 The Chromium Embedded Framework Authors. All rights
// reserved. Use of this source code is governed by a BSD-style license that
// can be found in the LICENSE file.

#pragma once

#include "include/cef_client.h"

#include "keyboard_handler.hpp"
#include "game_engine.hpp"
#include <vector>


class SnakeClient : public CefClient, public CefDisplayHandler, public CefLifeSpanHandler, public CefRequestHandler  {
    
public:
    SnakeClient(CefRefPtr<snake::KeyboardHandler> keyboardHandler,
                snake::GameEngine* engine)
        :fKeyboardHandler(keyboardHandler), fEngine(engine){};
    SnakeClient(const SnakeClient&) = delete;
    SnakeClient(SnakeClient&&) = default;
    SnakeClient& operator=(const SnakeClient&) = delete;
    SnakeClient& operator=(SnakeClient&&) = default;
    ~SnakeClient() = default;
    
    // CefClient methods:
    CefRefPtr<CefDisplayHandler> GetDisplayHandler() override { return this; }
    CefRefPtr<CefLifeSpanHandler> GetLifeSpanHandler() override { return this; }
    CefRefPtr<CefRequestHandler> GetRequestHandler() override { return this; }
    CefRefPtr<CefKeyboardHandler> GetKeyboardHandler() override { return fKeyboardHandler; }
    
    bool OnProcessMessageReceived(CefRefPtr<CefBrowser> browser,
                                  CefProcessId source_process,
                                  CefRefPtr<CefProcessMessage> message) override;

    // CefDisplayHandler methods:
    void OnTitleChange(CefRefPtr<CefBrowser> browser,
                       const CefString& title) override;
    
    // CefLifeSpanHandler methods:
    void OnAfterCreated(CefRefPtr<CefBrowser> browser) override;
    bool DoClose(CefRefPtr<CefBrowser> browser) override;
    void OnBeforeClose(CefRefPtr<CefBrowser> browser) override;
    
//    // CefRequestHandler methods:
//    bool OnBeforeBrowse(CefRefPtr<CefBrowser> browser,
//                        CefRefPtr<CefFrame> frame,
//                        CefRefPtr<CefRequest> request,
//                        bool user_gesture,
//                        bool is_redirect) override;
    CefRefPtr<CefResourceHandler> GetResourceHandler(
                                                     CefRefPtr<CefBrowser> browser,
                                                     CefRefPtr<CefFrame> frame,
                                                     CefRefPtr<CefRequest> request) override;
//    void OnRenderProcessTerminated(CefRefPtr<CefBrowser> browser,
//                                   TerminationStatus status) override;
    
    
    std::vector<CefRefPtr<CefBrowser>> getBrowsers() const {return fBrowsers;};
    
private:
    CefRefPtr<snake::KeyboardHandler> fKeyboardHandler;
    std::vector<CefRefPtr<CefBrowser>> fBrowsers;
    snake::GameEngine* fEngine; // engine's life span longer than this class
    
    IMPLEMENT_REFCOUNTING(SnakeClient);
};

