#pragma once

#include "Task.h"
#include <vector>
#include <string>

class JsonStorage {
public:
    explicit JsonStorage(const std::string& filename);

    std::vector<Task> load();
    void save(const std::vector<Task>& tasks);

private:
    std::string file;
};
