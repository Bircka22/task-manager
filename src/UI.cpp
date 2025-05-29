#include "UI.h"
#include "Task.h"
#include <iostream>
#include <fstream>
#include "nlohmann/json.hpp"
#include <string>
#include <Storage.h>

UI::UI(TaskManager& manager) : manager(manager) {}

void UI::run() {
    while (true) {       
        if (!handleInput())
            break;
    }
}

void UI::clearScreen() {
#ifdef _WIN32
    std::system("cls");
#else
    std::system("clear");
#endif
}

bool UI::handleInput() {
    int choice;

    std::cout << "╔══════════════════════════════════════╗\n";
    std::cout << "║        Менеджер задач                ║\n";
    std::cout << "╠══════════════════════════════════════╣\n";
    std::cout << "║ 1. Показать все задачи               ║\n";
    std::cout << "║ 2. Добавить задачу                   ║\n";
    std::cout << "║ 3. Удалить задачу                    ║\n";
    std::cout << "║ 4. Редактировать задачу              ║\n";
    std::cout << "║ 5. Отметить задачу выполненной       ║\n";
    std::cout << "║ 6. Поиск по ключевому слову          ║\n";
    std::cout << "║ 7. Импортировать задачи из файла     ║\n";
    std::cout << "║ 8. Экспортировать задачи в файл      ║\n";
    std::cout << "║ 0. Выход                             ║\n";
    std::cout << "╚══════════════════════════════════════╝\n";


    if (!(std::cin >> choice)) {
        std::cin.clear();
        std::cin.ignore(10000, '\n');
        std::cout << "Некорректный ввод!\n";
        return true;
    }

    std::cin.ignore();

    clearScreen();

    switch (choice) {
    case 1: sortTasks(); listTasks(); break;
    case 2: addTask(); break;
    case 3: removeTask(); break;
    case 4: editTask(); break;
    case 5: markTaskCompleted(); break;
    case 6: searchTasks(); break;
    case 7: importTasks(); break;
    case 8: exportTasks(); break;
    case 0: return false;
    default: std::cout << "Неверный выбор!\n"; break;
    }

    return true;
}

void UI::importTasks() {
    std::string path;
    std::cout << "Введите путь к файлу импорта (например, import.json): ";
    std::getline(std::cin, path);

    std::ifstream in(path);
    if (!in) {
        std::cout << "❌ Не удалось открыть файл: " << path << "\n";
        return;
    }

    nlohmann::json j;
    try {
        in >> j;

        for (const auto& item : j) {
            Task t;
            t.id = item.at("id").get<int>();
            t.title = item.at("title").get<std::string>();
            t.description = item.at("description").get<std::string>();
            t.priority = static_cast<Priority>(item.at("priority").get<int>());

            std::string d = item.at("deadline").get<std::string>();
            if (!d.empty()) t.deadline = d;

            manager.addTask(t.title, t.description, t.priority, t.deadline);
        }

        std::cout << "✅ Импортировано задач: " << j.size() << "\n";
    }
    catch (const std::exception& ex) {
        std::cout << "❌ Ошибка при чтении JSON: " << ex.what() << "\n";
    }
}


void UI::addTask() {
    std::string title, description, deadlineInput;
    std::string priorityStr;

    std::cout << "╔══════════════════════════════════════╗\n";
    std::cout << "║           Добавление задачи          ║\n";
    std::cout << "╚══════════════════════════════════════╝\n";

    std::cout << "Название: ";
    std::getline(std::cin, title);

    std::cout << "Описание: ";
    std::getline(std::cin, description);

    std::cout << "Приоритет (Низкий/Средний/Высокий): ";
    std::getline(std::cin, priorityStr);

    std::cout << "Срок (ГГГГ-ММ-ДД) или пусто: ";
    std::getline(std::cin, deadlineInput);

    Priority pr = stringToPriority(priorityStr);
    std::optional<std::string> deadline = deadlineInput.empty() ? std::nullopt : std::make_optional(deadlineInput);

    int id = manager.addTask(title, description, pr, deadline);

    std::cout << "╔══════════════════════════════════════╗\n";
    std::cout << "║ Задача успешно добавлена с ID " << id;
    // Выравнивание пробелами до рамки
    int len = std::to_string(id).length();
    for (int i = 0; i < 11 - len; ++i) std::cout << " ";
    std::cout << "║\n";
    std::cout << "╚══════════════════════════════════════╝\n";
}


void UI::listTasks() const {
    const auto& tasks = manager.getAllTasks();
    if (tasks.empty()) {
        std::cout << "Список задач пуст.\n";
        return;
    }
    for (const auto& t : tasks) {
        t.print();
    }
}

void UI::removeTask() {
    int id;
    std::cout << "ID задачи для удаления: ";
    std::cin >> id;
    std::cin.ignore();

    if (manager.removeTask(id))
        std::cout << "Задача удалена.\n";
    else
        std::cout << "Задача с таким ID не найдена.\n";
}

void UI::editTask() {
    int id;
    std::cout << "ID задачи для редактирования: ";
    std::cin >> id;
    std::cin.ignore();

    auto taskOpt = manager.getTask(id);
    if (!taskOpt) {
        std::cout << "Задача не найдена.\n";
        return;
    }

    std::string title, description, deadlineInput, priorityStr;
    std::cout << "Новое название: ";
    std::getline(std::cin, title);
    std::cout << "Новое описание: ";
    std::getline(std::cin, description);
    std::cout << "Новый приоритет (Низкий/Средний/Высокий): ";
    std::getline(std::cin, priorityStr);
    std::cout << "Новый срок (ГГГГ-ММ-ДД) или пусто: ";
    std::getline(std::cin, deadlineInput);

    Priority pr = stringToPriority(priorityStr);
    std::optional<std::string> deadline = deadlineInput.empty() ? std::nullopt : std::make_optional(deadlineInput);

    if (manager.editTask(id, title, description, pr, deadline))
        std::cout << "Задача обновлена.\n";
    else
        std::cout << "Ошибка обновления задачи.\n";
}

void UI::searchTasks() {
    std::string keyword;
    std::cout << "Ключевое слово для поиска: ";
    std::getline(std::cin, keyword);

    auto results = manager.filterByKeyword(keyword);
    if (results.empty()) {
        std::cout << "Ничего не найдено.\n";
        return;
    }

    for (const auto& t : results) {
        t.print();
    }
}

void UI::sortTasks() {
    std::cout << "╔══════════════════════════════════════╗\n";
    std::cout << "║            Сортировка задач          ║\n";
    std::cout << "╠══════════════════════════════════════╣\n";
    std::cout << "║ 1. Приоритету                        ║\n";
    std::cout << "║ 2. Сроку                             ║\n";
    std::cout << "╚══════════════════════════════════════╝\n";
    std::cout << "Выбор: ";

    int opt;
    std::cin >> opt;
    std::cin.ignore();

    if (opt == 1) manager.sortByPriority();
    else if (opt == 2) manager.sortByDeadline();
    else std::cout << "Неверный выбор.\n";
}

void UI::markTaskCompleted() {
    int id;
    std::cout << "Введите ID задачи для пометки как выполненной: ";
    std::cin >> id;
    std::cin.ignore();

    auto tasks = manager.getAllTasks();
    for (auto& task : tasks) {
        if (task.id == id) {
            task.completed = true;
            std::cout << "✅ Задача помечена как выполненная!\n";
            manager.replaceTask(id, task);
            return;
        }
    }
    std::cout << "❌ Задача с таким ID не найдена.\n";
}

void UI::exportTasks() {
    std::string path;
    std::cout << "Введите имя файла для экспорта (по умолчанию: export.json): ";
    std::getline(std::cin, path);

    if (path.empty())
        path = "export.json";

    std::ofstream out(path);
    if (!out) {
        std::cout << "❌ Не удалось открыть файл: " << path << "\n";
        return;
    }

    const auto& tasks = manager.getAllTasks();
    nlohmann::json j = nlohmann::json::array();

    for (const auto& t : tasks) {
        j.push_back(taskToJson(t));
    }

    out << j.dump(4);
    std::cout << "✅ Экспортировано " << tasks.size() << " задач в " << path << "\n";
}