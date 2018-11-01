// Copyright (c) 2013 The Chromium Embedded Framework Authors. All rights
// reserved. Use of this source code is governed by a BSD-style license that
// can be found in the LICENSE file.

#ifndef CEF_TESTS_CEFSIMPLE_SIMPLE_APP_H_
#define CEF_TESTS_CEFSIMPLE_SIMPLE_APP_H_


#include "include/cef_app.h"
#include "snake_client.h"
#include "game_engine.hpp"
#include "snake.hpp"
#include "listner.hpp"

#include <chrono>
// Implement application-level callbacks for the browser process.
class SimpleApp : public CefApp, public CefBrowserProcessHandler, public  Listner<snake::Snake>{
public:
    SimpleApp(std::chrono::duration<double> sampleTime);
    
    SimpleApp(const SimpleApp&) = delete;
    SimpleApp& operator=(const SimpleApp&) = delete;
    
    // CefApp methods:
    virtual CefRefPtr<CefBrowserProcessHandler> GetBrowserProcessHandler()
    OVERRIDE {
        return this;
    }
    
    // CefBrowserProcessHandler methods:
    virtual void OnContextInitialized() OVERRIDE;
    
    // Listner interface
    virtual void notify(const snake::Snake&) override;
    
    snake::GameEngine& getGameEngine();
    CefRefPtr<SnakeClient> getClient() const;
    
private:
    snake::GameEngine fGameEngine;
    CefRefPtr<SnakeClient> fClient;
    // Include the default reference counting implementation.
    IMPLEMENT_REFCOUNTING(SimpleApp);
};

#endif  // CEF_TESTS_CEFSIMPLE_SIMPLE_APP_H_

