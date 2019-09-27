project(tool_util)

add_library(tool_util STATIC)

target_sources(tool_util
	PRIVATE
		condition.cpp
)

target_include_directories(tool_util
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/../
        )

target_link_libraries(tool_util
	PUBLIC
		NwpcCodesCpp::GribCoder
		CLI11::CLI11
)

add_library(NwpcCodesCpp::ToolUtil ALIAS tool_util)