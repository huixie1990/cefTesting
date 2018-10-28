//
//  snake_message_handler.hpp
//  cefclient
//
//  Created by Hui Xie on 24/10/2018.
//

#pragma once

#include "include/wrapper/cef_message_router.h"
namespace snake{
    std::string getRequestName();
    
    class MessageHandler : public CefMessageRouterBrowserSide::Handler {
    public:
        
        MessageHandler() = default;
        MessageHandler(const MessageHandler&) = delete;
        MessageHandler(MessageHandler&&) = default;
        MessageHandler& operator=(const MessageHandler&) = delete;
        MessageHandler& operator=(MessageHandler&&) = default;
        ~MessageHandler() = default;
        // Called due to cefQuery execution in message_router.html.
        bool OnQuery(CefRefPtr<CefBrowser> browser,
                     CefRefPtr<CefFrame> frame,
                     int64 query_id,
                     const CefString& request,
                     bool persistent,
                     CefRefPtr<Callback> callback) override;
    };
}
