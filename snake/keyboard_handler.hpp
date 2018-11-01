//
//  keyboard_handler.hpp
//  cefclient
//
//  Created by Hui Xie on 30/10/2018.
//

#pragma once
#include "include/cef_keyboard_handler.h"
#include "game_engine.hpp"
#include "point.hpp"
#include <unordered_map>
#include <memory>
#include <vector>
namespace snake{
    
    struct MovementKeys{
        int up;
        int down;
        int left;
        int right;
    };
    
    extern const std::vector<MovementKeys> MOVE_KEY_SETS;
    
    class KeyPressingHandler{
    public:
        virtual bool canHandle(int key) = 0;
        virtual void handle(int key) = 0;
        virtual ~KeyPressingHandler() = default;
    };
    
    class SnakeMovementHandler : public KeyPressingHandler{
    public:
        SnakeMovementHandler(const MovementKeys& keys, GameEngine*, int snakeIndex);
        ~SnakeMovementHandler() = default;
        
        
        bool canHandle(int key) override;
        void handle(int key) override;
      
    private:
        std::unordered_map<int,Direction> fKeyMap;
        GameEngine* fGameEngine;
        int fSnakeIndex;
    };
    
    
    class KeyboardHandler : public CefKeyboardHandler{
    public:
        KeyboardHandler(GameEngine*);
        virtual bool OnPreKeyEvent(CefRefPtr<CefBrowser> browser,
                                   const CefKeyEvent& event,
                                   CefEventHandle os_event,
                                   bool* is_keyboard_shortcut) override;
        
    private:
        std::vector<std::unique_ptr<KeyPressingHandler>> fKeyPressingHandlers;
        IMPLEMENT_REFCOUNTING(KeyboardHandler);
    };
}
