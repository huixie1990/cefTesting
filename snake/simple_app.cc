// Copyright (c) 2013 The Chromium Embedded Framework Authors. All rights
// reserved. Use of this source code is governed by a BSD-style license that
// can be found in the LICENSE file.

#include "simple_app.h"
#include "snake_client.h"
#include "constant.hpp"
#include "keyboard_handler.hpp"
#include <string>
#include <thread>
#include <functional>

#include "include/cef_browser.h"
#include "include/cef_command_line.h"
#include "include/views/cef_browser_view.h"
#include "include/views/cef_window.h"
#include "include/wrapper/cef_helpers.h"


#include "examples/shared/resource_util.h"
#include "examples/shared/app_factory.h"

SimpleApp::SimpleApp(std::chrono::duration<double> sampleTime): fGameEngine(sampleTime){
    for(auto& snake :fGameEngine.getSnakes()){
        snake.addListner(this);  //app owns snakes. no need to remove listner
    }
};

void SimpleApp::OnContextInitialized() {
    CEF_REQUIRE_UI_THREAD();
    
    CefRefPtr<CefCommandLine> command_line =
    CefCommandLine::GetGlobalCommandLine();
    
    CefRefPtr<snake::KeyboardHandler> handler = new snake::KeyboardHandler(&fGameEngine);
    // SimpleHandler implements browser-level callbacks.
    // fClient is a CEF smart pointer
    fClient = new SnakeClient(handler);
    
    // Specify CEF browser settings here.
    CefBrowserSettings browser_settings;
    
    std::string url;
    // Check if a "--url=" value was provided via the command-line. If so, use
    // that instead of the default URL.
    url = command_line->GetSwitchValue("url");
    if (url.empty())
        shared::GetResourceDir(url);
    url = "file://" + url + "/resources/snake.html";
    
    // Information used when creating the native window.
    CefWindowInfo window_info;
    
    // Create the first browser window.
    CefBrowserHost::CreateBrowser(window_info, fClient, url, browser_settings,
                                  NULL);
}



void SimpleApp::notify(const snake::Snake& snake){
    auto browsers = getClient()->getBrowsers();
    if(browsers.empty()){
        return;
    }
    auto browser = browsers.at(0);
    
    auto message = snake::SNAKE_MOVE_MESSAGE + ":" + snake.getSID();
    CefRefPtr<CefProcessMessage> msg= CefProcessMessage::Create(message);
    
    // Retrieve the argument list object.
    CefRefPtr<CefListValue> args = msg->GetArgumentList();
    
    // Populate the argument values.
    const auto snakePosition = snake.getPosition();
    args->SetSize(snakePosition.size());
    
    for(decltype(snakePosition.size()) i=0; i<snakePosition.size(); i++){
        CefRefPtr<CefDictionaryValue> point = CefDictionaryValue::Create();
        point->SetInt("x", snakePosition[i].x);
        point->SetInt("y", snakePosition[i].y);
        args->SetDictionary(i, point);
    }
    
    // Send the process message to the render process.
    // Use PID_BROWSER instead when sending a message to the browser process.
    browser->SendProcessMessage(PID_RENDERER, msg);
}


snake::GameEngine& SimpleApp::getGameEngine() {
    return fGameEngine;
}

CefRefPtr<SnakeClient> SimpleApp::getClient() const {
    return fClient;
}

// non sense moethod that the cef example shared utilities forced to implement
CefRefPtr<CefApp> shared::CreateBrowserProcessApp(){
    return nullptr;
}
