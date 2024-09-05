#pragma once

#include <fstream>
#include <map>
#include <sstream>
#include <string>
#include <variant>

using prop_value = std::variant<std::string, long, double, bool>;

class properties
{
public:
    static properties& get_instance();

    properties(const properties&) = delete;
    properties(properties&&) = delete;
    void operator=(const properties&) = delete;
    void operator=(properties&&) = delete;

    [[nodiscard]] prop_value get(const std::string& key, prop_value default_value = std::string()) const;

private:
    explicit properties(const std::string& filename);

    std::map<std::string, std::string> props_;
};
