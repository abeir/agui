project(game_engine_gui_test LANGUAGES CXX)

aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR} TEST_FILES)

add_executable(${PROJECT_NAME} ${TEST_FILES})
add_dependencies(${PROJECT_NAME} gui::shared)

target_include_directories(${PROJECT_NAME} PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${DIR_SRC}/gui)
target_link_libraries(${PROJECT_NAME} PUBLIC gui::shared)

set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/../bin)