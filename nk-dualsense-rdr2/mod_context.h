#pragma once

#include <windows.h>

#include "../inc/ds5w.h"

class mod_context {
public:
    static mod_context& get_instance() {
        static mod_context instance;
        return instance;
    }

    mod_context(const mod_context&) = delete;
    mod_context(mod_context&&) = delete;
    void operator=(const mod_context&) = delete;
    void operator=(mod_context&&) = delete;

    void zero();
    void on_detach();
    void set_device_context(const DS5W::DeviceContext& new_device_context);
    const DS5W::DeviceContext& get_device_context() const;

private:
    mod_context() = default;
    ~mod_context() = default;

    DS5W::DeviceContext device_context_;
};
