#ifndef YAML_ADDRESSER_H
#define YAML_ADDRESSER_H

#include <string>

class YamlAddresser {
private:
    std::string yaml_config_path;
    std::string yaml_map_path;

public:
    YamlAddresser();

    std::string get_maps_path();
    std::string get_map_path(const std::string& map_name);
    std::string get_config_path(const std::string& config_name);
};

#endif  // YAML_ADDRESSER_H
