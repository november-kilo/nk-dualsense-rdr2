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
    template <typename T> T get_or_default(const std::string& key, const T& default_value) const;

private:
    explicit properties(const std::string& filename);
    ~properties() = default;

    std::map<std::string, std::string> props_;
};

template <typename T>
T properties::get_or_default(const std::string& key, const T& default_value) const {
    const prop_value& value = get(key, default_value); 
    if(auto val = std::get_if<T>(&value)) {
        return *val;
    }
    return default_value;
}
