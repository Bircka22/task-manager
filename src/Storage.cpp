#include "Storage.h"
#include "nlohmann/json.hpp"
#include <fstream>

using json = nlohmann::json;

nlohmann::json taskToJson(const Task& t) {
    return {
        {"id", t.id},
        {"title", t.title},
        {"description", t.description},
        {"priority", static_cast<int>(t.priority)},
        {"deadline", t.deadline.value_or("")},
        {"completed", t.completed}
    };
}

Task jsonToTask(const nlohmann::json& j) {
    Task t;
    t.id = j.at("id").get<int>();
    t.title = j.at("title").get<std::string>();
    t.description = j.at("description").get<std::string>();
    t.priority = static_cast<Priority>(j.at("priority").get<int>());

    std::string d = j.value("deadline", "");
    if (!d.empty()) t.deadline = d;

    t.completed = j.value("completed", false);
    return t;
}


bool Storage::saveToFile(const std::string& path, const std::vector<Task>& tasks) {
    std::ofstream out(path);
    if (!out) return false;

    nlohmann::json j = nlohmann::json::array();

    for (const auto& t : tasks) {
        j.push_back(taskToJson(t));
    }

    out << j.dump(4);
    return true;
}


std::vector<Task> Storage::loadFromFile(const std::string& path) {
    std::ifstream in(path);
    if (!in) return {};

    nlohmann::json j = nlohmann::json::array();
    in >> j;

    std::vector<Task> tasks;
    for (const auto& item : j) {
        tasks.push_back(jsonToTask(item));
    }
    return tasks;
}
