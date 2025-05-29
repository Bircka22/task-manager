#pragma once
#include "Task.h"
#include <vector>
#include <optional>

class TaskManager {
public:
    TaskManager();

    int addTask(const std::string& title,
                const std::string& description,
                Priority priority,
                const std::optional<std::string>& deadline = std::nullopt);

    bool removeTask(int id);
    bool replaceTask(int id, const Task& newTask);
    bool editTask(int id, const std::string& newTitle,
                  const std::string& newDescription,
                  Priority newPriority,
                  const std::optional<std::string>& newDeadline);

    std::optional<Task> getTask(int id) const;
    const std::vector<Task>& getAllTasks() const;

    void sortByPriority();
    void sortByDeadline();
    std::vector<Task> filterByKeyword(const std::string& keyword) const;

private:
    std::vector<Task> tasks;
    int nextId;

    static bool comparePriority(const Task& a, const Task& b);
    static bool compareDeadline(const Task& a, const Task& b);
};
