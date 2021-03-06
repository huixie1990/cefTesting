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
    extern const std::string GET_STATE_FUNC_NAME;
    extern const std::string GET_FOOD_FUNC_NAME;
    extern const std::string GET_CANVAS_SIZE_FUNC_NAME;
    extern const std::string REQUEST_POS_FUNC_NAME;
    
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
    
    
    class JsSnakeStateHandler : public CefV8Handler {
    public:
        JsSnakeStateHandler(const CefRefPtr<RendererApp>& app):fApp(app){};
        ~JsSnakeStateHandler() = default;
        
        bool Execute(const CefString& name,
                     CefRefPtr<CefV8Value> object,
                     const CefV8ValueList& arguments,
                     CefRefPtr<CefV8Value>& retval,
                     CefString& exception) override;
    private:
        CefRefPtr<RendererApp> fApp;
        // Provide the reference counting implementation for this class.
        IMPLEMENT_REFCOUNTING(JsSnakeStateHandler);
    };
    
    
    class JsFoodHandler : public CefV8Handler {
    public:
        JsFoodHandler(const CefRefPtr<RendererApp>& app):fApp(app){};
        ~JsFoodHandler() = default;
        
        bool Execute(const CefString& name,
                     CefRefPtr<CefV8Value> object,
                     const CefV8ValueList& arguments,
                     CefRefPtr<CefV8Value>& retval,
                     CefString& exception) override;
    private:
        CefRefPtr<RendererApp> fApp;
        // Provide the reference counting implementation for this class.
        IMPLEMENT_REFCOUNTING(JsFoodHandler);
    };
    
    
    class JsCanvasHandler : public CefV8Handler {
    public:
        JsCanvasHandler() = default;
        ~JsCanvasHandler() = default;
        
        bool Execute(const CefString& name,
                     CefRefPtr<CefV8Value> object,
                     const CefV8ValueList& arguments,
                     CefRefPtr<CefV8Value>& retval,
                     CefString& exception) override;
    private:
        // Provide the reference counting implementation for this class.
        IMPLEMENT_REFCOUNTING(JsCanvasHandler);
    };
    
    class JsRequestHandler : public CefV8Handler {
    public:
        JsRequestHandler(CefRefPtr<CefBrowser> browser):fBrowser(browser){};
        ~JsRequestHandler() = default;
        
        bool Execute(const CefString& name,
                     CefRefPtr<CefV8Value> object,
                     const CefV8ValueList& arguments,
                     CefRefPtr<CefV8Value>& retval,
                     CefString& exception) override;
    private:
        CefRefPtr<CefBrowser> fBrowser;
        // Provide the reference counting implementation for this class.
        IMPLEMENT_REFCOUNTING(JsRequestHandler);
    };
}
