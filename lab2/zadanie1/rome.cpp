#include "rome.hpp"

namespace rome
{
    Province create_province(std::string name)
    {
        Province province;
        province.name=name;
        province.cities.clear();
        return province;
    }

    void add_city(Province* province, std::string city)
    {
        province->cities.push_back(city);
    }

    std::string description(Province* province)
    {
        std::string list = province->name;
        list += ": ";

        for(int i = 0; i<province->cities.size() - 1; i++)
        {
            list += province->cities[i];
            list += ", ";
        }

        list += province->cities[province->cities.size()-1];
        list += ".";
        return list;
    }
}