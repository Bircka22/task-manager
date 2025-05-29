#include "TaskManager.h"
#include <algorithm>

TaskManager::TaskManager() : nextId(1) {}

int TaskManager::addTask(const std::string& title,
                         const std::string& description,
                         Priority priority,
                         const std::optional<std::string>& deadline) {
    Task t{nextId++, title, description, priority, deadline};
    tasks.push_back(std::move(t));
    return nextId - 1;
}

bool TaskManager::removeTask(int id) {
    auto it = std::remove_if(tasks.begin(), tasks.end(), [id](const Task& t) {
        return t.id == id;
    });
    if (it != tasks.end()) {
        tasks.erase(it, tasks.end());
        return true;
    }
    return false;
}

bool TaskManager::editTask(int id, const std::string& newTitle,
                           const std::string& newDescription,
                           Priority newPriority,
                           const std::optional<std::string>& newDeadline) {
    for (Task& t : tasks) {
        if (t.id == id) {
            t.title = newTitle;
            t.description = newDescription;
            t.priority = newPriority;
            t.deadline = newDeadline;
            return true;
        }
    }
    return false;
}

std::optional<Task> TaskManager::getTask(int id) const {
    for (const Task& t : tasks) {
        if (t.id == id) return t;
    }
    return std::nullopt;
}

const std::vector<Task>& TaskManager::getAllTasks() const {
    return tasks;
}

bool TaskManager::comparePriority(const Task& a, const Task& b) {
    return static_cast<int>(a.priority) > static_cast<int>(b.priority);
}

bool TaskManager::compareDeadline(const Task& a, const Task& b) {
    return a.deadline < b.deadline;
}

void TaskManager::sortByPriority() {
    std::sort(tasks.begin(), tasks.end(), comparePriority);
}

void TaskManager::sortByDeadline() {
    std::sort(tasks.begin(), tasks.end(), compareDeadline);
}

std::vector<Task> TaskManager::filterByKeyword(const std::string& keyword) const {
    std::vector<Task> result;
    for (const auto& t : tasks) {
        if (t.title.find(keyword) != std::string::npos ||
            t.description.find(keyword) != std::string::npos) {
            result.push_back(t);
        }
    }
    return result;
}

bool TaskManager::replaceTask(int id, const Task& newTask) {
    for (auto& task : tasks) {
        if (task.id == id) {
            task = newTask;
            return true;
        }
    }
    return false;
}
