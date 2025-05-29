#include "TaskManager.h"
#include "UI.h"
#include "JsonStorage.h"
#include <iostream>
#include <filesystem>
#include <windows.h>

const std::filesystem::path SAVE_FILE = "data/tasks.json";

int main() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    TaskManager manager;
    JsonStorage storage(SAVE_FILE.string());

    auto loaded = storage.load();
    for (const auto& t : loaded) {
        manager.addTask(t.title, t.description, t.priority, t.deadline);
    }

    UI ui(manager);
    ui.run();

    storage.save(manager.getAllTasks());
    return 0;
}
