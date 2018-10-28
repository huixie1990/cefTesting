// Copyright (c) 2013 The Chromium Embedded Framework Authors. All rights
// reserved. Use of this source code is governed by a BSD-style license that
// can be found in the LICENSE file.

#include "simple_app.h"
#include "snake_client.h"
#include <string>
#include <thread>
#include <iostream>
#include "include/cef_browser.h"
#include "include/cef_command_line.h"
#include "include/views/cef_browser_view.h"
#include "include/views/cef_window.h"
#include "include/wrapper/cef_helpers.h"


#include "examples/shared/resource_util.h"
#include "examples/shared/app_factory.h"




SimpleApp::SimpleApp() {}

void SimpleApp::OnContextInitialized() {
    CEF_REQUIRE_UI_THREAD();
    
    CefRefPtr<CefCommandLine> command_line =
    CefCommandLine::GetGlobalCommandLine();
    
    // SimpleHandler implements browser-level callbacks.
    // fClient is a CEF smart pointer
    fClient = new SnakeClient();
    
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


void SimpleApp::notify(const snake::GameEngine& engine){
    auto browsers = getClient()->getBrowsers();
    if(browsers.empty()){
        return;
    }
    auto browser = browsers.at(0);
    
    CefRefPtr<CefProcessMessage> msg= CefProcessMessage::Create("my_message");
    
    // Retrieve the argument list object.
    CefRefPtr<CefListValue> args = msg->GetArgumentList();
    
    // Populate the argument values.
   // args->SetString(0, "my string");
    args->SetInt(0, engine.getPos());
    
    // Send the process message to the render process.
    // Use PID_BROWSER instead when sending a message to the browser process.
    browser->SendProcessMessage(PID_RENDERER, msg);
}

CefRefPtr<CefApp> shared::CreateBrowserProcessApp(){
    return new SimpleApp();
}
