#include "sections/grib_section_4.h"
#include "sections/grib_section_0.h"
#include "templates/template_4_0.h"
#include "templates/template_4_8.h"
#include "number_convert.h"

#include <vector>
#include <sstream>
#include <cassert>

namespace GribCoder {
GribSection4::GribSection4():
	GribSection{4}
{
	init();
}

GribSection4::GribSection4(int section_length_):
	GribSection{4, section_length_}
{
	assert(section_length_ == 34 || section_length_ == 58);
	init();
}

GribSection4::~GribSection4()
{

}

bool GribSection4::parseFile(std::FILE* file)
{
	auto buffer_length = section_length_ - 5;
	std::vector<unsigned char> buffer(section_length_);
	auto read_count = std::fread(&buffer[5], 1, buffer_length, file);
	if (read_count != buffer_length) {
		return false;
	}

	nv_ = convertBytesToUint16(&buffer[5], 2);
	auto product_definition_template_number = convertBytesToUint16(&buffer[7], 2);

    // TODO: different product definition tempalte
	assert(product_definition_template_number == 0 || product_definition_template_number == 8);

	product_definition_template_number_.setLong(product_definition_template_number);

    auto template_length = section_length_ - 9;

    if (product_definition_template_number == 0) {
        product_definition_template_ = std::make_shared<Template_4_0>(template_length);
    }
    else if (product_definition_template_number == 8) {
        product_definition_template_ = std::make_shared<Template_4_8>(template_length);
    }
    else {
        throw std::exception("template not implemented");
    }
    product_definition_template_->parse(buffer);
    product_definition_template_->registerProperty(shared_from_this());

	return true;
}

bool GribSection4::decode(std::vector<std::shared_ptr<GribSection>> section_list)
{
    return product_definition_template_->decode(section_list);
}

void GribSection4::init()
{
	product_definition_template_number_.setOctetCount(2);
	product_definition_template_number_.setCodeTableId("4.0");

	property_map_["nv"] = &nv_;
	property_map_["productDefinitionTemplateNumber"] = &product_definition_template_number_;
}

} // namespace GribCoder