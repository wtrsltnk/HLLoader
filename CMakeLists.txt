cmake_minimum_required(VERSION 3.1)

project(HLLoader)

find_package(OpenGL REQUIRED)

add_executable(HLLoader

	)

target_link_libraries(HLLoader
    ${OPENGL_LIBRARIES}
    comctl32
    winmm
    )

target_compile_features(HLLoader
	PRIVATE cxx_auto_type
	PRIVATE cxx_nullptr
	PRIVATE cxx_range_for
	)
