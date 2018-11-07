// Copyright (c) 2013 The Chromium Embedded Framework Authors. All rights
// reserved. Use of this source code is governed by a BSD-style license that
// can be found in the LICENSE file.

#include "simple_app.h"
#include "snake_client.h"
#include "keyboard_handler.hpp"
#include "constant.hpp"
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
    fGameEngine.getFoodGenerator().addListner(this);
};

void SimpleApp::OnContextInitialized() {
    CEF_REQUIRE_UI_THREAD();
    
    CefRefPtr<CefCommandLine> command_line =
    CefCommandLine::GetGlobalCommandLine();
    
    CefRefPtr<snake::KeyboardHandler> handler = new snake::KeyboardHandler(&fGameEngine);
    // SimpleHandler implements browser-level callbacks.
    // fClient is a CEF smart pointer
    fClient = new SnakeClient(handler, &fGameEngine);
    
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


snake::GameEngine& SimpleApp::getGameEngine() {
    return fGameEngine;
}

CefRefPtr<SnakeClient> SimpleApp::getClient() const {
    return fClient;
}


void SimpleApp::notified(const snake::Snake& snake, const std::string& snakeMessage){
    auto browsers = getClient()->getBrowsers();
    if(browsers.empty()){
        return;
    }
    auto browser = browsers.at(0);
    auto message = snakeMessage + ":" + snake.getSID();
    
    if (snakeMessage == snake::SNAKE_MOVE_MESSAGE){
        sendSnakeMoveMessage(snake, message, browser);
    } else if (snakeMessage == snake::SNAKE_STATE_MESSAGE){
        sendSnakeStateMessage(snake, message, browser);
    }
}

void SimpleApp::notified(const snake::FoodGenerator& generator, const std::string& generatorMessage){
    auto browsers = getClient()->getBrowsers();
    if(browsers.empty()){
        return;
    }
    auto browser = browsers.at(0);

    CefRefPtr<CefProcessMessage> msg= CefProcessMessage::Create(generatorMessage);
    
    // Retrieve the argument list object.
    CefRefPtr<CefListValue> args = msg->GetArgumentList();
    
    // Populate the argument values.
    const auto& foods = generator.getFoods();
    args->SetSize(foods.size());
    
    for(decltype(foods.size()) i=0; i<foods.size(); i++){
        auto position = foods[i].getPosition();
        CefRefPtr<CefDictionaryValue> point = CefDictionaryValue::Create();
        point->SetInt("x", position.x);
        point->SetInt("y", position.y);
        args->SetDictionary(i, point);
    }
    
    // Send the process message to the render process.
    // Use PID_BROWSER instead when sending a message to the browser process.
    browser->SendProcessMessage(PID_RENDERER, msg);
    
}




//private:
void SimpleApp::sendSnakeMoveMessage(
            const snake::Snake& snake,
            const std::string& message,
            CefRefPtr<CefBrowser> browser){
    
    CefRefPtr<CefProcessMessage> msg= CefProcessMessage::Create(message);
    
    // Retrieve the argument list object.
    CefRefPtr<CefListValue> args = msg->GetArgumentList();
    
    // Populate the argument values.
    const auto& snakePosition = snake.getPosition();
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

void SimpleApp::sendSnakeStateMessage(
                    const snake::Snake& snake,
                    const std::string& message,
                    CefRefPtr<CefBrowser> browser){
    
    CefRefPtr<CefProcessMessage> msg= CefProcessMessage::Create(message);
    
    // Retrieve the argument list object.
    CefRefPtr<CefListValue> args = msg->GetArgumentList();
    
    // Populate the argument values.
    const auto snakeState = snake.getState();
    
    args->SetString(0, snake::toString(snakeState));
    
    // Send the process message to the render process.
    // Use PID_BROWSER instead when sending a message to the browser process.
    browser->SendProcessMessage(PID_RENDERER, msg);
}


// non sense moethod that the cef example shared utilities forced to implement
CefRefPtr<CefApp> shared::CreateBrowserProcessApp(){
    return nullptr;
}
