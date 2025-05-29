#pragma once

#include "Task.h"
#include <vector>
#include <string>
#include "nlohmann/json.hpp"

class Storage {
public:
    static bool saveToFile(const std::string& path, const std::vector<Task>& tasks);
    static std::vector<Task> loadFromFile(const std::string& path);
};

nlohmann::json taskToJson(const Task& t);
Task jsonToTask(const nlohmann::json& j);
