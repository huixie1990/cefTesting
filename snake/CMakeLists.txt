# Copyright (c) 2014 The Chromium Embedded Framework Authors. All rights
# reserved. Use of this source code is governed by a BSD-style license that
# can be found in the LICENSE file.

#
# Source files.
#

# cefsimple sources.
set(SNAKE_SRCS
  simple_app.cc
  simple_app.h
  snake_client.cc
  snake_client.h
game_engine.hpp
game_engine.cpp
snake.cpp
snake.hpp
food.hpp
food.cpp
boarder.hpp
boarder.cpp
point.hpp
point.cpp
listner.hpp
listner.cpp
constant.hpp
constant.cpp
keyboard_handler.hpp
keyboard_handler.cpp
utils.hpp
utils.cpp
  )
set(SNAKE_SRCS_LINUX
  cefsimple_linux.cc
  simple_handler_linux.cc
  )
set(SNAKE_SRCS_MACOSX
  cefsimple_mac.mm
  simple_handler_mac.mm
  )
set(SNAKE_SRCS_WINDOWS
  cefsimple.exe.manifest
  cefsimple.rc
  cefsimple_win.cc
  resource.h
  simple_handler_win.cc
  )
APPEND_PLATFORM_SOURCES(SNAKE_SRCS)
source_group(cef FILES ${SNAKE_SRCS})

set(CEFSIMPLE_RES_SRCS_WINDOWS
  res/cefsimple.ico
  res/small.ico
  )
APPEND_PLATFORM_SOURCES(CEFSIMPLE_RES_SRCS)
source_group(cef\\\\res FILES ${CEFSIMPLE_RES_SRCS})


set(WEB_RESOURCES
resources/snake.html
)
list(APPEND ${WEB_RESOURCES})
source_group(cef\\\\resources FILES ${WEB_RESOURCES})

set(SNAKE_SRCS
  ${SNAKE_SRCS}
  ${CEFSIMPLE_RES_SRCS}
  ${WEB_RESOURCES}
  )



# cefsimple helper sources.
 set(CEFSIMPLE_HELPER_SRCS
js_function_handler.hpp
js_function_handler.cpp
 renderer_app.cpp
 renderer_app.hpp
constant.hpp
constant.cpp
renderer_snake_info.hpp
renderer_snake_info.cpp
 )
set(CEFSIMPLE_HELPER_SRCS_MACOSX
  process_helper_mac.cc
  )
APPEND_PLATFORM_SOURCES(CEFSIMPLE_HELPER_SRCS)
source_group(cef FILES ${CEFSIMPLE_HELPER_SRCS})

# cefsimple resources.
set(CEFSIMPLE_RESOURCES_MAC_SRCS_MACOSX
  mac/Info.plist
  mac/cefsimple.icns
  )
APPEND_PLATFORM_SOURCES(CEFSIMPLE_RESOURCES_MAC_SRCS)
source_group(cef\\\\mac FILES ${CEFSIMPLE_RESOURCES_MAC_SRCS})

set(CEFSIMPLE_RESOURCES_MAC_ENGLISH_LPROJ_SRCS_MACOSX
  mac/English.lproj/InfoPlist.strings
  mac/English.lproj/MainMenu.xib
  )
APPEND_PLATFORM_SOURCES(CEFSIMPLE_RESOURCES_MAC_ENGLISH_LPROJ_SRCS)
source_group(cef\\\\mac\\\\English.lproj FILES ${CEFSIMPLE_RESOURCES_MAC_ENGLISH_LPROJ_SRCS})

set(CEFSIMPLE_RESOURCES_SRCS
  ${CEFSIMPLE_RESOURCES_MAC_SRCS}
  ${CEFSIMPLE_RESOURCES_MAC_ENGLISH_LPROJ_SRCS}
${WEB_RESOURCES}
  )

set(SNAKE_TEST_SRCS
   unittest/main.cpp
   unittest/TSnake.cpp
    unittest/TSnakeBuilder.cpp
    unittest/TGameEngine.cpp
unittest/TFood.cpp
)
list(APPEND ${SNAKE_TEST_SRCS})
source_group(unittest FILES ${SNAKE_TEST_SRCS})

#
# Shared configuration.
#

# Target executable names.
set(CEF_TARGET "snake")
if(OS_MACOSX)
  set(CEF_HELPER_TARGET "snake_Helper")
  set(CEF_HELPER_OUTPUT_NAME "snake Helper")
endif()
set(TEST_TARGET "snake_unittest")

# Logical target used to link the libcef library.
ADD_LOGICAL_TARGET("libcef_lib" "${CEF_LIB_DEBUG}" "${CEF_LIB_RELEASE}")

# Determine the target output directory.
SET_CEF_TARGET_OUT_DIR()


#
# Linux configuration.
#

if(OS_LINUX)
  # Executable target.
  add_executable(${CEF_TARGET} ${SNAKE_SRCS})
  SET_EXECUTABLE_TARGET_PROPERTIES(${CEF_TARGET})
  add_dependencies(${CEF_TARGET} libcef_dll_wrapper)
  target_link_libraries(${CEF_TARGET} libcef_lib libcef_dll_wrapper ${CEF_STANDARD_LIBS})

  # Set rpath so that libraries can be placed next to the executable.
  set_target_properties(${CEF_TARGET} PROPERTIES INSTALL_RPATH "$ORIGIN")
  set_target_properties(${CEF_TARGET} PROPERTIES BUILD_WITH_INSTALL_RPATH TRUE)
  set_target_properties(${CEF_TARGET} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CEF_TARGET_OUT_DIR})

  # Copy binary and resource files to the target output directory.
  COPY_FILES("${CEF_TARGET}" "${CEF_BINARY_FILES}" "${CEF_BINARY_DIR}" "${CEF_TARGET_OUT_DIR}")
  COPY_FILES("${CEF_TARGET}" "${CEF_RESOURCE_FILES}" "${CEF_RESOURCE_DIR}" "${CEF_TARGET_OUT_DIR}")

  # Set SUID permissions on the chrome-sandbox target.
  SET_LINUX_SUID_PERMISSIONS("${CEF_TARGET}" "${CEF_TARGET_OUT_DIR}/chrome-sandbox")
endif()


#
# Mac OS X configuration.
#

if(OS_MACOSX)
  # Output paths for the app bundles.
  set(CEF_APP "${CEF_TARGET_OUT_DIR}/${CEF_TARGET}.app")
  set(CEF_HELPER_APP "${CEF_TARGET_OUT_DIR}/${CEF_HELPER_OUTPUT_NAME}.app")

  # Variable referenced from Info.plist files.
  set(PRODUCT_NAME "${CEF_TARGET}")

  # Helper executable target.
  add_executable(${CEF_HELPER_TARGET} MACOSX_BUNDLE ${CEFSIMPLE_HELPER_SRCS})
  SET_EXECUTABLE_TARGET_PROPERTIES(${CEF_HELPER_TARGET})
  add_dependencies(${CEF_HELPER_TARGET} libcef_dll_wrapper)
  target_link_libraries(${CEF_HELPER_TARGET} libcef_lib libcef_dll_wrapper ${CEF_STANDARD_LIBS})
  set_target_properties(${CEF_HELPER_TARGET} PROPERTIES
    MACOSX_BUNDLE_INFO_PLIST ${CMAKE_CURRENT_SOURCE_DIR}/mac/helper-Info.plist
    OUTPUT_NAME ${CEF_HELPER_OUTPUT_NAME}
    )

  # Fix the framework rpath in the helper executable.
  FIX_MACOSX_HELPER_FRAMEWORK_RPATH(${CEF_HELPER_TARGET})

  # Main executable target.
  add_executable(${CEF_TARGET} MACOSX_BUNDLE ${CEFSIMPLE_RESOURCES_SRCS} ${SNAKE_SRCS})
  SET_EXECUTABLE_TARGET_PROPERTIES(${CEF_TARGET})
  add_dependencies(${CEF_TARGET} libcef_dll_wrapper "${CEF_HELPER_TARGET}")
  target_link_libraries(${CEF_TARGET} libcef_lib libcef_dll_wrapper ${CEF_STANDARD_LIBS})
  add_dependencies(${CEF_TARGET} shared "${CEF_HELPER_TARGET}")
  target_link_libraries(${CEF_TARGET} shared)
  set_target_properties(${CEF_TARGET} PROPERTIES
    MACOSX_BUNDLE_INFO_PLIST ${CMAKE_CURRENT_SOURCE_DIR}/mac/Info.plist
    )

  # Copy files into the main app bundle.
  add_custom_command(
    TARGET ${CEF_TARGET}
    POST_BUILD
    # Copy the helper app bundle into the Frameworks directory.
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            "${CEF_HELPER_APP}"
            "${CEF_APP}/Contents/Frameworks/${CEF_HELPER_OUTPUT_NAME}.app"
    # Copy the CEF framework into the Frameworks directory.
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            "${CEF_BINARY_DIR}/Chromium Embedded Framework.framework"
            "${CEF_APP}/Contents/Frameworks/Chromium Embedded Framework.framework"
    VERBATIM
    )

  # Fix the framework rpath in the main executable.
  FIX_MACOSX_MAIN_FRAMEWORK_RPATH(${CEF_TARGET})

  # Manually process and copy over resource files.
  # The Xcode generator can support this via the set_target_properties RESOURCE
  # directive but that doesn't properly handle nested resource directories.
  # Remove these prefixes from input file paths.
  set(PREFIXES "mac/")
  COPY_MACOSX_RESOURCES("${CEFSIMPLE_RESOURCES_SRCS}" "${PREFIXES}" "${CEF_TARGET}" "${CMAKE_CURRENT_SOURCE_DIR}" "${CEF_APP}")

  # Add a test target

set(SNAKE_SRCS_FOR_TEST ${SNAKE_SRCS})
list(REMOVE_ITEM SNAKE_SRCS_FOR_TEST "cefsimple_mac.mm")

find_library(GTEST_LIB
    NAMES googletest
    PATHS "../build/snake/Frameworks"
)

message("\n\n\n\n\n\n\n\ndddddddd")
message(${GTEST_LIB})


add_executable(${TEST_TARGET} ${SNAKE_SRCS_FOR_TEST}  ${SNAKE_TEST_SRCS})
SET_EXECUTABLE_TARGET_PROPERTIES(${TEST_TARGET})
add_dependencies(${TEST_TARGET} libcef_dll_wrapper "${CEF_HELPER_TARGET}")
target_link_libraries(${TEST_TARGET} libcef_lib libcef_dll_wrapper ${CEF_STANDARD_LIBS} ${GTEST_LIB} shared)
add_dependencies(${TEST_TARGET} shared "${CEF_HELPER_TARGET}")

target_include_directories(${TEST_TARGET} PUBLIC "${GTEST_LIB}/Versions/A")
set_target_properties(${TEST_TARGET} PROPERTIES
    OUTPUT_NAME ${TEST_TARGET})

set_target_properties(${TEST_TARGET} PROPERTIES INSTALL_RPATH "@executable_path/..")
set_target_properties(${TEST_TARGET} PROPERTIES BUILD_WITH_INSTALL_RPATH TRUE)



endif()


#
# Windows configuration.
#

if(OS_WINDOWS)
  # Executable target.
  add_executable(${CEF_TARGET} WIN32 ${SNAKE_SRCS})
  add_dependencies(${CEF_TARGET} libcef_dll_wrapper)
  SET_EXECUTABLE_TARGET_PROPERTIES(${CEF_TARGET})
  target_link_libraries(${CEF_TARGET} libcef_lib libcef_dll_wrapper ${CEF_STANDARD_LIBS})

  if(USE_SANDBOX)
    # Logical target used to link the cef_sandbox library.
    ADD_LOGICAL_TARGET("cef_sandbox_lib" "${CEF_SANDBOX_LIB_DEBUG}" "${CEF_SANDBOX_LIB_RELEASE}")
    target_link_libraries(${CEF_TARGET} cef_sandbox_lib ${CEF_SANDBOX_STANDARD_LIBS})
  endif()

  # Add the custom manifest files to the executable.
  ADD_WINDOWS_MANIFEST("${CMAKE_CURRENT_SOURCE_DIR}" "${CEF_TARGET}" "exe")

  # Copy binary and resource files to the target output directory.
  COPY_FILES("${CEF_TARGET}" "${CEF_BINARY_FILES}" "${CEF_BINARY_DIR}" "${CEF_TARGET_OUT_DIR}")
  COPY_FILES("${CEF_TARGET}" "${CEF_RESOURCE_FILES}" "${CEF_RESOURCE_DIR}" "${CEF_TARGET_OUT_DIR}")
endif()


