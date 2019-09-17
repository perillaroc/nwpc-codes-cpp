#include "grib_section_3.h"

#include <grib_property/property_component.h>

#include <gsl/span>

#include <cassert>

namespace grib_coder {
GribSection3::GribSection3():
    GribSection{3} {
    init();
}

GribSection3::GribSection3(long section_length):
    GribSection{3, section_length} {
    assert(section_length_ == 72);
    init();
}

bool GribSection3::parseFile(std::FILE* file, bool header_only) {
    const auto buffer_length = section_length_ - 5;
    std::vector<std::byte> buffer(section_length_);
    const auto read_count = std::fread(&buffer[5], 1, buffer_length, file);
    if (static_cast<long>(read_count) != buffer_length) {
        return false;
    }

    auto iterator = std::cbegin(buffer) + 5;

    auto component_span = gsl::make_span(components_);
    auto sub_component_span = component_span.subspan(2);

    for (auto& component : sub_component_span) {
        component->parse(iterator);
    }

    return true;
}

bool GribSection3::decode(GribMessageHandler* container) {
    const auto result = grid_type_.decode(container);
    return result;
}

void GribSection3::init() {
    grid_definition_template_number_.setOctetCount(2);

    std::vector<std::tuple<size_t, std::string, GribProperty*>> components{
        {4, "section3Length", &section_length_},
        {1, "numberOfSection", &section_number_},
        {1, "sourceOfGridDefinition", &source_of_grid_definition_},
        {4, "numberOfDataPoints", &number_of_data_points_},
        {1, "numberOfOctectsForNumberOfPoints", &number_of_octects_for_number_of_points_},
        {1, "interpretationOfNumberOfPoints", &interpretation_of_number_of_points_},
        {2, "gridDefinitionTemplateNumber", &grid_definition_template_number_},

        {1, "shapeOfEarth", &shape_of_earth_},
        {1, "scaleFactorOfRadiusOfSphericalEarth", &scale_factor_of_radius_of_spherical_earth_},
        {4, "scaledValueOfRadiusOfSphericalEarth", &scaled_value_of_radius_of_spherical_earth_},
        {1, "scaleFactorOfEarthMajorAxis", &scale_factor_of_earth_major_axis_},
        {4, "scaledValueOfEarthMajorAxis", &scaled_value_of_earth_major_axis_},
        {1, "scaleFactorOfEarthMinorAxis", &scale_factor_of_earth_minor_axis_},
        {4, "scaledValueOfEarthMinorAxis", &scaled_value_of_earth_minor_axis_},

        {4, "ni", &ni_},
        {4, "nj", &nj_},

        {4, "basicAngleOfTheInitialProductionDomain", &basic_angle_of_the_initial_production_domain_},
        {4, "subdivisionsOfBasicAngle", &subdivisions_of_basic_angle_},

        {4, "latitudeOfFirstGridPoint", &latitude_of_first_grid_point_},
        {4, "longitudeOfFirstGridPoint", &longitude_of_first_grid_point_},
        {1, "resolutionAndComponentFlags", &resolution_and_component_flags_},
        {4, "latitudeOfLastGridPoint", &latitude_of_last_grid_point_},
        {4, "longitudeOfLastGridPoint", &longitude_of_last_grid_point_},
        {4, "iDirectionIncrement", &i_direction_increment_},
        {4, "jDirectionIncrement", &j_direction_increment_},
        {1, "scanningMode", &scanning_mode_},
    };

    for (auto& item : components) {
        components_.push_back(std::make_unique<PropertyComponent>(
            std::get<0>(item),
            std::get<1>(item),
            std::get<2>(item)));
        registerProperty(std::get<1>(item), std::get<2>(item));
    }

    grid_definition_template_number_.setOctetCount(2);

    std::vector<std::tuple<CodeTableProperty*, std::string>> tables_id{
        {&source_of_grid_definition_, "3.0"},
        {&interpretation_of_number_of_points_, "3.11"},

        {&grid_definition_template_number_, "3.1"},
        {&shape_of_earth_, "3.2"},
    };
    for (const auto& item : tables_id) {
        std::get<0>(item)->setCodeTableId(std::get<1>(item));
    }

    std::vector<std::tuple<std::string, GribProperty*>> properties_name{
        {"gridType", &grid_type_},
    };
    for (const auto& item : properties_name) {
        registerProperty(std::get<0>(item), std::get<1>(item));
    }

}

} // namespace grib_coder
