#include "properties.h"

#include "console.h"

properties& properties::get_instance() {
    static properties instance("nk-dualsense-rdr2.properties");
    return instance;
}

properties::properties(const std::string& filename) {
    std::ifstream file(filename);

    if (!file.is_open()) {
        console::write("Could not open file: " + filename);
        return;
    }
    
    std::string line;
    while (std::getline(file, line)) {
        if (line.empty() || line[0] == '#') {
            continue;
        }

        std::istringstream is_line(line);

        if (std::string key; std::getline(is_line, key, '=')) {
            if (std::string value_str; std::getline(is_line, value_str))
                data_[key] = value_str;
        }
    }

    if (file.bad()) {
        console::write("Failed to read from file: " + filename);
    } else {
        file.close();
    }
}

prop_value properties::get(const std::string& key, prop_value default_value) const {
    const auto it = data_.find(key);
    
    if (it == data_.end()) {
        return default_value;
    }

    const auto& value_str = it->second;
    if (value_str == "true") {
        return true;
    }

    if (value_str == "false") {
        return false;
    }

    char* end;
    const long value_long = std::strtol(value_str.c_str(), &end, 10);
    if (*end == '\0') {
        return value_long;
    }

    const double value_double = std::strtod(value_str.c_str(), &end);
    if (*end == '\0') {
        return value_double;
    }

    return value_str;
}
