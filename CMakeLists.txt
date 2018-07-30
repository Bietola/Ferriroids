# initialize project
cmake_minimum_required(VERSION 3.5)
project(Proj VERSION 1.0.0 LANGUAGES CXX)

# load packages
find_package(SFML 2.5 COMPONENTS graphics REQUIRED)
find_package(Boost 1.55 COMPONENTS filesystem REQUIRED)

# create target executable
file(GLOB_RECURSE PROJECT_SOURCES 
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp 
    ${CMAKE_CURRENT_SOURCE_DIR}/src/**/*.cpp
)
add_executable(Proj ${PROJECT_SOURCES})

# include directories
target_include_directories(Proj
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/headers
)

# compiler properties
target_compile_options(Proj PRIVATE -Wall)
target_compile_features(Proj PRIVATE cxx_std_17)

# export compilation database for YCM
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# link libraries
target_link_libraries(Proj
    PRIVATE
        Boost::boost # for optional
        Boost::filesystem
        sfml-graphics
)

# copy resources from resource directories into build directory
set(source "${CMAKE_SOURCE_DIR}/assets")
set(destination "${CMAKE_CURRENT_BINARY_DIR}/assets")
add_custom_command(
    TARGET Proj POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E create_symlink ${source} ${destination} 
    DEPENDS ${destination}
    COMMENT "Created symbolic link to assets folder at ${source} to ${destination}"
)

# copy compile commands into root directory
set(source "${CMAKE_CURRENT_BINARY_DIR}/compile_commands.json")
set(destination "${CMAKE_SOURCE_DIR}/")
add_custom_command(
    TARGET Proj POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy ${source} ${destination}
    DEPENDS ${destination}
    COMMENT "Copied compilation database from ${source} to ${destination}"
)
