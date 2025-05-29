#pragma once
#include "TaskManager.h"
#include <string>

class UI {
public:
    UI(TaskManager& manager);
    void run();
    

private:
    TaskManager& manager;

    void showMenu() const;
    bool handleInput();
    void addTask();
    void listTasks() const;
    void removeTask();
    void editTask();
    void searchTasks();
    void sortTasks();
    void clearScreen();
    void importTasks();
    void markTaskCompleted();
    void exportTasks();
};
