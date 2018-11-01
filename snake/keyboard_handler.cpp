//
//  keyboard_handler.cpp
//  cefclient
//
//  Created by Hui Xie on 30/10/2018.
//

#include "keyboard_handler.hpp"
#include <Carbon/Carbon.h>


const std::vector<snake::MovementKeys> snake::MOVE_KEY_SETS = {
    {kVK_UpArrow, kVK_DownArrow, kVK_LeftArrow, kVK_RightArrow},
    {kVK_ANSI_W, kVK_ANSI_S, kVK_ANSI_A, kVK_ANSI_D},
    {kVK_ANSI_I, kVK_ANSI_K, kVK_ANSI_J, kVK_ANSI_L}
};

snake::KeyboardHandler::KeyboardHandler(GameEngine* engine){
    auto size = engine->getSnakes().size();
    for(decltype(size) idx = 0; idx < size; idx++){
        fKeyPressingHandlers.emplace_back(new SnakeMovementHandler(
                    MOVE_KEY_SETS[idx], engine, idx));
    }
}

bool snake::KeyboardHandler::OnPreKeyEvent(CefRefPtr<CefBrowser> browser,
                           const CefKeyEvent& event,
                           CefEventHandle os_event,
                           bool* is_keyboard_shortcut){
    bool handled = false;
    auto keyCode = event.native_key_code;
    for (auto& handler : fKeyPressingHandlers){
        if(handler->canHandle(keyCode)){
            handler->handle(keyCode);
            handled = true;
        }
    }
    return handled;
    
}


snake::SnakeMovementHandler::SnakeMovementHandler(
       const MovementKeys& keys, GameEngine* engine, int snakeIndex){
    
    fGameEngine = engine;
    fSnakeIndex = snakeIndex;
    fKeyMap.emplace(keys.up, Direction::up);
    fKeyMap.emplace(keys.down, Direction::down);
    fKeyMap.emplace(keys.left, Direction::left);
    fKeyMap.emplace(keys.right, Direction::right);
};

bool snake::SnakeMovementHandler::canHandle(int key){
    return fKeyMap.find(key) != fKeyMap.end();
};

void snake::SnakeMovementHandler::handle(int key){
    fGameEngine->sendDirectionToSnake(fKeyMap[key], fSnakeIndex);
};
