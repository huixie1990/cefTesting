// Copyright (c) 2013 The Chromium Embedded Framework Authors. All rights
// reserved. Use of this source code is governed by a BSD-style license that
// can be found in the LICENSE file.
#include <algorithm>
#include "snake_client.h"

#include "include/cef_app.h"
#include "include/wrapper/cef_helpers.h"

#include "examples/shared/client_util.h"
#include "examples/shared/resource_util.h"

void SnakeClient::OnTitleChange(CefRefPtr<CefBrowser> browser,
                           const CefString& title) {
    // Call the default shared implementation.
    shared::OnTitleChange(browser, title);
};

//bool SnakeClient::OnProcessMessageReceived(CefRefPtr<CefBrowser> browser,
//                                      CefProcessId source_process,
//                                      CefRefPtr<CefProcessMessage> message) {
//    CEF_REQUIRE_UI_THREAD();
//
//    return fMessageRouter->OnProcessMessageReceived(browser, source_process,
//                                                     message);
//}

void SnakeClient::OnAfterCreated(CefRefPtr<CefBrowser> browser) {
    CEF_REQUIRE_UI_THREAD();
    fBrowsers.push_back(browser);
    
    // Call the default shared implementation.
    shared::OnAfterCreated(browser);
}

bool SnakeClient::DoClose(CefRefPtr<CefBrowser> browser) {
    // Call the default shared implementation.
    return shared::DoClose(browser);
}

void SnakeClient::OnBeforeClose(CefRefPtr<CefBrowser> browser) {
    CEF_REQUIRE_UI_THREAD();
    
    for (auto bit = fBrowsers.begin(); bit != fBrowsers.end(); ++bit) {
        if ((*bit)->IsSame(browser)) {
            fBrowsers.erase(bit);
            break;
        }
    }
    
    // Call the default shared implementation.
    shared::OnBeforeClose(browser);
}

CefRefPtr<CefResourceHandler> SnakeClient::GetResourceHandler(
                                                         CefRefPtr<CefBrowser> browser,
                                                         CefRefPtr<CefFrame> frame,
                                                         CefRefPtr<CefRequest> request) {
    CEF_REQUIRE_IO_THREAD();
    
    const std::string& url = request->GetURL();
    
    // This is a minimal implementation of resource loading. For more complex
    // usage (multiple files, zip archives, custom handlers, etc.) you might want
    // to use CefResourceManager. See the "resource_manager" target for an
    // example implementation.
    const std::string& resource_path = shared::GetResourcePath(url);
    if (!resource_path.empty())
        return shared::GetResourceHandler(resource_path);
    
    return NULL;
}

// to use the shared utilities in the cef examples, I have to implement those nonsense functions
namespace shared {
    
    // This file declares methods that must be implemented in each executable
    // target. CefApp is a global singleton that controls process-specific
    // behaviors. The returned CefApp instance will be passed to CefExecuteProcess()
    // and/or CefInitialize() by the program entry point implementation. On Linux
    // and Windows a single executable is used for all processes. On macOS a
    // separate helper executable is used for sub-processes.
    
    // Called in the main browser process to create the CefApp for that process.
    
    // Called in the renderer sub-process to create the CefApp for that process.
    CefRefPtr<CefApp> CreateRendererProcessApp(){
        return nullptr;
    }
    
    // Called in other sub-processes to create the CefApp for that process.
    CefRefPtr<CefApp> CreateOtherProcessApp(){
        return nullptr;
    }
    
}  // namespace shared
