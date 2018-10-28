//
//  snake_message_handler.cpp
//  cefclient
//
//  Created by Hui Xie on 24/10/2018.
//

#include "snake_message_handler.hpp"


// Called due to cefQuery execution in message_router.html.
bool snake::MessageHandler::OnQuery(CefRefPtr<CefBrowser> browser,
                             CefRefPtr<CefFrame> frame,
                             int64 query_id,
                             const CefString& request,
                             bool persistent,
                             CefRefPtr<Callback> callback) {
    // Only handle messages from the startup URL.
//    const std::string& url = frame->GetURL();
//    if (url.find(startup_url_) != 0)
//        return false;
    
    const std::string& message_name = request;
    if (message_name.find(snake::getRequestName()) == 0) {
        // Reverse the string and return.
        std::string result = message_name.substr(snake::getRequestName().length()+1);
        std::reverse(result.begin(), result.end());
        callback->Success(result);
        return true;
    }
    
    return false;
}

std::string snake::getRequestName() {
    static const std::string name("getSnakePosition");
    return name;
};
