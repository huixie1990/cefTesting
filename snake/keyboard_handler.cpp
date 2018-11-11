//
//  keyboard_handler.cpp
//  cefclient
//
//  Created by Hui Xie on 30/10/2018.
//

#include "keyboard_handler.hpp"
#include <Carbon/Carbon.h>


namespace snake{
    const std::vector<snake::MovementKeys> MOVE_KEY_SETS = {
        {kVK_UpArrow, kVK_DownArrow, kVK_LeftArrow, kVK_RightArrow},
        {kVK_ANSI_W, kVK_ANSI_S, kVK_ANSI_A, kVK_ANSI_D},
        {kVK_ANSI_I, kVK_ANSI_K, kVK_ANSI_J, kVK_ANSI_L}
    };
    
    const int START_KEY = kVK_Space;
    
    KeyboardHandler::KeyboardHandler(GameEngine* engine){
        auto size = engine->getSnakes().size();
        for(decltype(size) idx = 0; idx < size; idx++){
            fKeyPressingHandlers.emplace_back(new SnakeMovementHandler(
                                MOVE_KEY_SETS[idx], engine, idx));
        }
        fKeyPressingHandlers.emplace_back(new GameStateKeyHandler(START_KEY, engine));
    }
    
    bool KeyboardHandler::OnPreKeyEvent(CefRefPtr<CefBrowser> browser,
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
    
    
    SnakeMovementHandler::SnakeMovementHandler(
                                               const MovementKeys& keys,
                                               GameEngine* engine,
                                               int snakeIndex){
        
        fGameEngine = engine;
        fSnakeIndex = snakeIndex;
        fKeyMap.emplace(keys.up, Direction::up);
        fKeyMap.emplace(keys.down, Direction::down);
        fKeyMap.emplace(keys.left, Direction::left);
        fKeyMap.emplace(keys.right, Direction::right);
    };
    
    bool SnakeMovementHandler::canHandle(int key){
        return fKeyMap.find(key) != fKeyMap.end();
    };
    
    void SnakeMovementHandler::handle(int key){
        fGameEngine->sendDirectionToSnake(fKeyMap[key], fSnakeIndex);
    };
    
    
    GameStateKeyHandler::GameStateKeyHandler(const int startKey, GameEngine* engine)
    :fStartKey(startKey), fGameEngine(engine){
    };
    
    bool GameStateKeyHandler::canHandle(int key){
        return fStartKey == key;
    };
    
    void GameStateKeyHandler::handle(int key){
        fGameEngine->gameStartRequested();
    };
    
}
