#pragma once
#include <iostream>
#include <string>
#include <optional>
#include <stdexcept>

enum class Priority {
    Low = 1,
    Medium = 2,
    High = 3,
    ERror = -1
};

inline std::string priorityColor(Priority p) {
    switch (p) {
    case Priority::High:   return "\033[31m"; // Красный
    case Priority::Medium: return "\033[33m"; // Жёлтый
    case Priority::Low:    return "\033[32m"; // Зелёный
    case Priority::ERror:  return "\033[34m";
    }
    return "\033[0m";
}

struct Task {
    int id = 0;
    std::string title;
    std::string description;
    Priority priority = Priority::Low;
    std::optional<std::string> deadline = std::nullopt;
    bool completed = false;

    void print() const {
        std::cout << "ID: " << id << "\n"
            << "Заголовок: " << title << "\n"
            << "Описание: " << description << "\n"
            << "Приоритет: " << priorityColor(priority)
            << static_cast<int>(priority) << "\033[0m\n";
        if (deadline.has_value())
            std::cout << "Срок: " << *deadline << "\n";
        else
            std::cout << "Срок: не задан\n";
    }
};

inline std::string priorityToString(Priority p) {
    switch (p) {
        case Priority::Low: return "Низкий(1)";
        case Priority::Medium: return "Средний(2)";
        case Priority::High: return "Высокий(3)";
    }
    return "Неизвестно";
}

inline Priority stringToPriority(const std::string& str) {
    if (str == "Низкий" || str == "1") return Priority::Low;
    else if (str == "Средний" || str == "2") return Priority::Medium;
    else if (str == "Высокий" || str == "3") return Priority::High;
    else { return Priority::ERror; }
}