cmake_minimum_required(VERSION 3.28)
project(Game CXX)

set(CMAKE_CXX_STANDARD 20)
set(SFML_BUILD_NETWORK OFF)

include(FetchContent)

# SFML
FetchContent_Declare(
    sfml
    URL https://github.com/SFML/SFML/archive/refs/tags/3.0.2.tar.gz
)
FetchContent_MakeAvailable(sfml)

# EnTT
FetchContent_Declare(
    entt
    GIT_REPOSITORY https://github.com/skypjack/entt.git
    GIT_TAG v3.16.0
)
FetchContent_MakeAvailable(entt)

# nlohmann
FetchContent_Declare(
    json
    URL https://github.com/nlohmann/json/releases/download/v3.12.0/json.tar.xz
)
FetchContent_MakeAvailable(json)

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS src/*.cpp)

add_executable(Game ${SOURCES})

target_include_directories(Game PRIVATE Include)

target_link_libraries(Game 
    PRIVATE 
        SFML::Graphics 
        SFML::Audio
        EnTT::EnTT
        nlohmann_json::nlohmann_json
)

#cmake -B Build -D CMAKE_BUILD_TYPE=Debug
#cmake --build Build --config Debug -j
#./build/debug/game