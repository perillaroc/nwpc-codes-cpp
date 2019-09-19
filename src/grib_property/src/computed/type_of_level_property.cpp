#include "grib_property/computed/type_of_level_property.h"
#include <grib_coder/grib_message_handler.h>

#include <map>

namespace grib_coder {

const std::vector<
    std::tuple<
        std::string,
        std::vector<
            std::tuple<
                std::string,
                int
            >
        >
    >
> type_of_level_list{
    {
        "surface",
        {
            {"typeOfFirstFixedSurface", 1},
            {"typeOfSecondFixedSurface", 255}
        }
    },
    {
        "cloudBase",
        {
            {"typeOfFirstFixedSurface", 2},
            {"typeOfSecondFixedSurface", 255}
        }
    },
    {
        "cloudTop",
        {
            {"typeOfFirstFixedSurface", 3},
            {"typeOfSecondFixedSurface", 255}
        }
    },
    {
        "nominalTop",
        {
            {"typeOfFirstFixedSurface", 8},
            {"typeOfSecondFixedSurface", 255}
        }
    },
    {
        "isobaricInPa",
        {
            {"typeOfFirstFixedSurface", 100},
            {"typeOfSecondFixedSurface", 255}
        }
    },
    {
        "meanSea",
        {
            {"typeOfFirstFixedSurface", 101},
            {"typeOfSecondFixedSurface", 255}
        }
    },
    {
        "heightAboveSea",
        {
            {"typeOfFirstFixedSurface", 102},
            {"typeOfSecondFixedSurface", 255}
        }
    },
    {
        "heightAboveGround",
        {
            {"typeOfFirstFixedSurface", 103},
            {"typeOfSecondFixedSurface", 255}
        }
    },
    {
        "heightAboveGroundLayer",
        {
            {"typeOfFirstFixedSurface", 103},
            {"typeOfSecondFixedSurface", 103}
        }
    },
    {
        "depthBelowLand",
        {
            {"typeOfFirstFixedSurface", 106},
            {"typeOfSecondFixedSurface", 255}
        }
    },
    {
        "depthBelowLand",
        {
            {"typeOfFirstFixedSurface", 106},
            {"typeOfSecondFixedSurface", 106}
        }
    }
};


std::string TypeOfLevelProperty::getString() {
    return type_of_level_;
}

bool TypeOfLevelProperty::decode(GribMessageHandler* container) {
    std::map<std::string, long> property_map;

    property_map["typeOfFirstFixedSurface"] = container->getLong("typeOfFirstFixedSurface");
    property_map["typeOfSecondFixedSurface"] = container->getLong("typeOfSecondFixedSurface");

    for (const auto& item : type_of_level_list) {
        auto type_name = std::get<0>(item);
        auto conditions = std::get<1>(item);
        auto flag = true;
        for (const auto& condition : conditions) {
            const auto& property_name = std::get<0>(condition);
            const auto& property_value = std::get<1>(condition);
            if (property_map[property_name] != property_value) {
                flag = false;
                break;
            }
        }
        if (flag) {
            type_of_level_ = type_name;
            break;
        }
    }

    return true;
}

} // namespace grib_coder
