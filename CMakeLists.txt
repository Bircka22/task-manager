cmake_minimum_required(VERSION 3.16)
project(task_manager)

# ��������� �������� C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# ���� � ���������� � ����������
include_directories(${PROJECT_SOURCE_DIR}/src)
include_directories(${PROJECT_SOURCE_DIR}/include)

set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")


# ������� ��������� (��������, nlohmann/json)
# include/ ��� �������� ���� � json.hpp ����� ���

# ���������� ������������ �����
add_executable(task-manager
    src/main.cpp
    src/Task.cpp
    src/TaskManager.cpp
    src/JsonStorage.cpp
    src/Storage.cpp
    src/UI.cpp
    )

# �� �������: ����� ���������� ����������, �������� SQLite
# find_package(SQLite3 REQUIRED)
# target_link_libraries(task-manager PRIVATE SQLite::SQLite3)
