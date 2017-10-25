cmake_minimum_required ( VERSION 3.0.2 )

project ( Raytracer )

# Fetch all source and header files
file(GLOB_RECURSE source_list RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}" "*.cpp" "*.hpp" "*.h" "*.c")
file(GLOB_RECURSE resource_list RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}" "*.vert" "*.frag" "*.glsl")

message(STATUS "Bin dir ${CMAKE_CURRENT_BINARY_DIR}")
foreach(item IN LISTS resource_list)
    message(STATUS ${item})
    add_custom_command(
        OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/${item}"
        COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_SOURCE_DIR}/${item}" "${CMAKE_CURRENT_BINARY_DIR}/${item}"
        DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/${item}"
    )
endforeach()

# Remove specific files
#list(FILTER source_list EXCLUDE REGEX "binary_to_compressed_c.cpp") 

add_executable ( Raytracer ${source_list} ${resource_list})

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 11)
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD_REQUIRED ON)

# Make the Raytracer project the start project in the solution
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT Raytracer)

file(COPY "shaders/simple.vert.glsl" DESTINATION "shaders")
file(COPY "shaders/simple.frag.glsl" DESTINATION "shaders")

# assign_source_group(${SOURCE_CODE})
assign_source_group(${source_list})
assign_source_group(${resource_list})

target_link_libraries(${PROJECT_NAME} glfw)
# target_link_libraries(${PROJECT_NAME} tbb)
