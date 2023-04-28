
set(GUI_LIB_NAME ${PROJECT_NAME})

aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/widgets SRC_GUI_WIDGETS_FILES)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/structures SRC_GUI_STRUCTURE_FILES)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/events SRC_GUI_EVENTS_FILES)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/platform SRC_GUI_PLATFORM_FILES)

add_library(${GUI_LIB_NAME} SHARED
        ${SRC_GUI_WIDGETS_FILES}
        ${SRC_GUI_STRUCTURE_FILES}
        ${SRC_GUI_EVENTS_FILES}
        ${SRC_GUI_PLATFORM_FILES})
add_dependencies(${GUI_LIB_NAME} imgui::static SDL2::static)
add_library(gui::shared ALIAS ${GUI_LIB_NAME})

target_include_directories(${GUI_LIB_NAME} PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${DIR_3RDPARTY}/imgui
        ${DIR_3RDPARTY}/imgui/backends
        ${DIR_3RDPARTY}/SDL/include)

target_link_libraries(${GUI_LIB_NAME} PUBLIC imgui::static SDL2::static opengl32)

set_target_properties(${GUI_LIB_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/../../bin)
