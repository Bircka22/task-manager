#include "JsonStorage.h"
#include "Storage.h"
#include <filesystem>
#include <iostream>

JsonStorage::JsonStorage(const std::string& filename) : file(filename) {}

std::vector<Task> JsonStorage::load() {
    return Storage::loadFromFile(file);
}

void JsonStorage::save(const std::vector<Task>& tasks) {
    std::filesystem::path p = file;
    if (p.has_parent_path()) {
        std::filesystem::create_directories(p.parent_path());
    }


    if (!Storage::saveToFile(file, tasks)) {
        std::cerr << "❌ Ошибка при сохранении!\n";
    }
    else {
        std::cout << "✅ Сохранено в " << file << "\n";
    }
}