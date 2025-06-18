#include "yaml_addresser.h"

#include <string>

YamlAddresser::YamlAddresser()
#ifdef DEBUG_MODE
        :
        yaml_config_path("server/"),
        yaml_map_path("server/maps/")
#else
        :
        yaml_config_path("/etc/cs2d/cfg/"),
        yaml_map_path("/var/cs2d/maps/")
#endif
{
}

std::string YamlAddresser::get_maps_path() { return yaml_map_path; }

std::string YamlAddresser::get_map_path(const std::string& map_name) {
    return yaml_map_path + map_name + ".yaml";
}

std::string YamlAddresser::get_config_path(const std::string& config_name) {
    return yaml_config_path + config_name;
}
