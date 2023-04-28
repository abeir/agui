set(DIR_IMGUI ${CMAKE_CURRENT_SOURCE_DIR}/imgui)

file(GLOB IMGUI_FILES CONFIGURE_DEPENDS ${DIR_IMGUI}/*.cpp)
file(GLOB IMGUI_BACKENDS_FILES CONFIGURE_DEPENDS
        ${DIR_IMGUI}/backends/imgui_impl_sdl2.cpp
        ${DIR_IMGUI}/backends/imgui_impl_sdl2.h
        ${DIR_IMGUI}/backends/imgui_impl_opengl3.cpp
        ${DIR_IMGUI}/backends/imgui_impl_opengl3.h)

add_library(imgui STATIC ${IMGUI_FILES} ${IMGUI_BACKENDS_FILES})
add_dependencies(imgui SDL2::static)
add_library(imgui::static ALIAS imgui)

target_include_directories(imgui PUBLIC ${DIR_IMGUI})
target_link_libraries(imgui PUBLIC SDL2::static)