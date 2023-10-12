cmake_minimum_required(VERSION 3.21)
project(Gra)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

file(GLOB sources "*.cpp")
add_executable(Gra ${sources})
target_link_libraries(Gra PRIVATE sfml-graphics)
target_link_libraries(sfml-audio)
target_compile_features(Gra PRIVATE cxx_std_17)
if (WIN32 AND BUILD_SHARED_LIBS)
    add_custom_command(TARGET Gra POST_BUILD 
        COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_RUNTIME_DLLS:Gra> $<TARGET_FILE_DIR:Gra> COMMAND_EXPAND_LISTS)
endif()
# configure_file("${CMAKE_CURRENT_SOURCE_DIR}/arial.ttf" "$<TARGET_FILE_DIR:Gra>/arial.ttf" COPYONLY)

install(TARGETS Gra)
