cmake_minimum_required (VERSION 3.8)

project (anthill-game-engine-core)

set(engine_core
 "engine-core/ATEngineCore.cpp"
 "engine-core/core/windows/ATWindowsCore.cpp"
  
  
 "gui-system/window-system/ATWindow.hpp" 
 "gui-system/window-system/ATWindowInitializeSettings.cpp" 
 "gui-system/window-system/ATWindowInitializeSettings.hpp" 
 "gui-system/window-system/ATWindowManager.cpp" 
 "gui-system/window-system/ATWindowManager.hpp"
  "gui-system/render-system/ATRenderProvider.hpp"
  "gui-system/render-system/ATRenderProviderBuilder.hpp" 
  #"gui-system/render-system/directx12-render-provider/ATDirectX12RenderProvider.cpp" 
  #"gui-system/render-system/directx12-render-provider/ATDirectX12RenderProvider.hpp"
   #"gui-system/render-system/directx12-render-provider/dx-call-wrappers/DXExceptions.hpp" 
   #"gui-system/render-system/directx12-render-provider/dx-call-wrappers/DXExtensions.cpp" 
   #"gui-system/render-system/directx12-render-provider/dx-call-wrappers/DXExtensions.hpp" 
   #"gui-system/render-system/directx12-render-provider/dx-call-wrappers/DXGIExtensions.cpp" 
   #"gui-system/render-system/directx12-render-provider/dx-call-wrappers/DXGIExtensions.hpp" 
   #"gui-system/render-system/directx12-render-provider/dx-call-wrappers/DXShared.cpp" 
   #"gui-system/render-system/directx12-render-provider/dx-call-wrappers/DXShared.hpp" 
   "gui-system/widgets/ATWidget.hpp"
   "gui-system/widgets/ATWidgetsTreeBuilder.hpp" 
   "gui-system/widgets/ATFrameWidget.hpp" 
   "gui-system/widgets/ATFrameWidget.cpp" 
   "gui-system/widgets/ATWidgetExceptions.hpp" 
   "gui-system/widgets/ATWidgetShared.hpp" 
   "gui-system/window-system/ATWindowSystemExceptions.hpp" 
   "engine-core/ATEngineCoreContext.hpp" 
   "gui-system/window-system/ATWindowSystemConfig.hpp" 
   "gui-system/widgets/ATWidgetCallback.hpp" 
   "gui-system/render-system/opengl-render-provider/ATOpenglRenderProvider.cpp" 
   "gui-system/render-system/opengl-render-provider/ATOpenglRenderProvider.hpp" 
   "gui-system/draw-types/ATImage.cpp" "gui-system/draw-types/ATImage.hpp"
 "gui-system/draw-types/ATRect.hpp" 
 "gui-system/draw-types/ATArea.hpp" 
 "gui-system/render-system/opengl-render-provider/ATOpenglExceptions.hpp" 
 "gui-system/widgets/ATImageWidget.hpp" 
 "gui-system/widgets/ATImageWidget.cpp"
 "gui-system/widgets/ATWidgetAttributes.hpp")

set (STBI 
"../third-party-libs/stb/stb_image.h")

set (GL3W 
"../third-party-libs/gl3w/include/GL/gl3w.h"
"../third-party-libs/gl3w/src/gl3w.c"
"../third-party-libs/gl3w/include/GL/glcorearb.h"
"../third-party-libs/gl3w/include/KHR/khrplatform.h")

include_directories("engine-core/core/windows/" "engine-core/")

include_directories("../third-party-libs/json/single_include/nlohmann/")
include_directories("../third-party-libs/pugixml/src/")

add_library(anthill-game-engine-core STATIC ${engine_core} ${STBI} ${GL3W})

include_directories("../third-party-libs/boost_1_75_0/")

macro (add_and_link_sdl2)
    set (SDL2_DIR "../third-party-libs/SDL2-2.0.14")
    find_package (SDL2 REQUIRED)

    set(SDL2_INCLUDE_DIRS "${CMAKE_CURRENT_LIST_DIR}/../third-party-libs/SDL2-2.0.14/include")

    if (${CMAKE_SIZEOF_VOID_P} MATCHES 8)
        set (SDL2_ALL_LIBS_PATH "${CMAKE_CURRENT_LIST_DIR}/../third-party-libs/SDL2-2.0.14/lib/x64/")
        set (SDL2_LIBRARY_NAME "SDL2.lib;")
        set (SDL2_MAIN_LIBRARY_NAME "SDL2main.lib")
    else ()
        set (SDL2_ALL_LIBS_PATH "${CMAKE_CURRENT_LIST_DIR}/../third-party-libs/SDL2-2.0.14/lib/x86/")
        set (SDL2_LIBRARY_NAME "SDL2.lib;")
        set (SDL2_MAIN_LIBRARY_NAME "SDL2main.lib")
    endif ()

    include_directories (${SDL2_INCLUDE_DIRS})
    target_link_libraries (anthill-game-engine-core ${SDL2_ALL_LIBS_PATH}${SDL2_LIBRARY_NAME})
    target_link_libraries (anthill-game-engine-core ${SDL2_ALL_LIBS_PATH}${SDL2_MAIN_LIBRARY_NAME})

    MESSAGE ("SDL2 include path:" ${SDL2_INCLUDE_DIRS})
    MESSAGE ("SDL2 library path:" ${SDL2_ALL_LIBS_PATH}${SDL2_LIBRARY_NAME})
    MESSAGE ("SDL2 library path:" ${SDL2_ALL_LIBS_PATH}${SDL2_MAIN_LIBRARY_NAME})
endmacro ()

add_and_link_sdl2()

target_link_libraries(anthill-game-engine-core anthill-game-engine-utils)

set_target_properties (anthill-game-engine-core PROPERTIES
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO
)