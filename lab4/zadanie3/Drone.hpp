#pragma once

#include <string>

class Drone
{
private:
    std::string model;
    int battery_level;
    static int active_drones;

public:
    Drone(const std::string& model, int battery_level = 100); //CONST KONIECZNIE BOZE XD ZNOWU
    ~Drone();

    const std::string& get_model() const { return model; }
    const int get_battery_level() const { return battery_level; }
    void set_battery_level(int level) { battery_level = level; }

    void print() const;
    static int get_active_count(); //STATIC SIE DAJE, A NIE CONST
};