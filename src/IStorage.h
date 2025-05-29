#pragma once

#include "Task.h"
#include <vector>

class IStorage {
public:
    virtual ~IStorage() = default;

    virtual std::vector<Task> load() = 0;
    virtual void save(const std::vector<Task>& tasks) = 0;
};
