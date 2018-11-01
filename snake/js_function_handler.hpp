//
//  js_function_handler.hpp
//  cefclient
//
//  Created by Hui Xie on 25/10/2018.
//

#pragma once

#include "include/cef_v8.h"
#include "renderer_app.hpp"
namespace snake {

    extern const std::string GET_POS_FUNC_NAME;
    extern const std::string GET_ID_FUNC_NAME;
    
    class JsSnakeLocationHandler : public CefV8Handler {
    public:
        JsSnakeLocationHandler(const CefRefPtr<RendererApp>& app):fApp(app){};
        ~JsSnakeLocationHandler() = default;
        
        bool Execute(const CefString& name,
                     CefRefPtr<CefV8Value> object,
                     const CefV8ValueList& arguments,
                     CefRefPtr<CefV8Value>& retval,
                     CefString& exception) override;
    private:
        CefRefPtr<RendererApp> fApp;
        // Provide the reference counting implementation for this class.
        IMPLEMENT_REFCOUNTING(JsSnakeLocationHandler);
    };
    
    
    class JsSnakeIDHandler : public CefV8Handler {
    public:
        JsSnakeIDHandler(const CefRefPtr<RendererApp>& app):fApp(app){};
        ~JsSnakeIDHandler() = default;
        
        bool Execute(const CefString& name,
                     CefRefPtr<CefV8Value> object,
                     const CefV8ValueList& arguments,
                     CefRefPtr<CefV8Value>& retval,
                     CefString& exception) override;
    private:
        CefRefPtr<RendererApp> fApp;
        // Provide the reference counting implementation for this class.
        IMPLEMENT_REFCOUNTING(JsSnakeIDHandler);
    };
}
