// Copyright (c) 2013 The Chromium Embedded Framework Authors. All rights
// reserved. Use of this source code is governed by a BSD-style license that can
// be found in the LICENSE file.

#include "include/cef_app.h"
#include "renderer_app.hpp"

// Entry point function for sub-processes.
int main(int argc, char* argv[]) {
  
   
  // Provide CEF with command-line arguments.
  CefMainArgs main_args(argc, argv);

    // can't used std::make_unique can't compile with c++14 for some reasons
  CefRefPtr<CefApp> app = new RendererApp();
  // Execute the sub-process.
  return CefExecuteProcess(main_args, app, NULL);
}
