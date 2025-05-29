cmake_minimum_required(VERSION 3.16)
project(task_manager)

# Установим стандарт C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Пути к исходникам и заголовкам
include_directories(${PROJECT_SOURCE_DIR}/src)
include_directories(${PROJECT_SOURCE_DIR}/include)

set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")


# Внешние заголовки (например, nlohmann/json)
# include/ уже добавлен выше — json.hpp лежит там

# Добавление исполняемого файла
add_executable(task-manager
    src/main.cpp
    src/Task.cpp
    src/TaskManager.cpp
    src/JsonStorage.cpp
    src/Storage.cpp
    src/UI.cpp
    )

# На будущее: можно подключить библиотеки, например SQLite
# find_package(SQLite3 REQUIRED)
# target_link_libraries(task-manager PRIVATE SQLite::SQLite3)
