#include "EnvLoader.h"
#include <fstream>
#include <unordered_map>

std::string EnvLoader::get(const std::string& key){
    static std::unordered_map<std::string, std::string> cache;
    static bool loaded = false;

    if (!loaded) {
        std::ifstream env("config/database.env");
        if (!env.is_open()) {
            env.open("../config/database.env");
        }
        if (!env.is_open()) {
             throw std::runtime_error("Could not find config/database.env or ../config/database.env");
        }
        std::string line;

        while (std::getline(env, line)) {
            auto pos = line.find('=');
            if (pos != std::string::npos) {
                cache[line.substr(0, pos)] = line.substr(pos + 1);
            }
        }
        loaded = true;
    }
    return cache[key];
}