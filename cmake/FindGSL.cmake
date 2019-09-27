if(GSL_INSTALL_PREFIX)
    set(GSL_INCLUDE_HINTS ${ECCODES_INSTALL_PREFIX}/include)
endif()

find_path(
    GSL_INCLUDE_DIR
    NAMES gsl
    PATHS ${GSL_INCLUDE_PATH} ${GSL_INCLUDE_HINTS}
    PATH_SUFFIXES include/gsl
)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(GSL
	REQUIRED_VARS GSL_INCLUDE_DIR
)

message("GSL_INCLUDE_DIR ${GSL_INCLUDE_DIR}")
message("GSL_FOUND ${GSL_FOUND}")

if(GSL_FOUND AND NOT TARGET GSL::GSL)
	add_library(GSL::GSL UNKNOWN IMPORTED)
	set_target_properties(GSL::GSL PROPERTIES
		IMPORTED_LINK_INTERFACE_LANGUAGES "CXX"
		INTERFACE_INCLUDE_DIRECTORIES "${GSL_INCLUDE_DIR}")

	mark_as_advanced(
		GSL_INCLUDE_DIR
	)
endif()