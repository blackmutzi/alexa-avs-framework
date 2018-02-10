cmake_minimum_required (VERSION 2.8.11)
project(AlexaAmazonClient)

message(STATUS "Alexa Amazon Client: v1.0.0")

set(VERSION_MAJOR 1)
set(VERSION_MINOR 0)
set(VERSION_PATCH 0)
set(VERSION_STRING ${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH})
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wdeprecated-declarations ")
set(CONFIG_DIRECTORY "/etc/alexa/" )

# Find source files
file(GLOB SOURCES *.cpp)

# Find header files
file(GLOB HEADERS *.hpp)

# Find config files
file(GLOB CONFIG config-example.json)

# Create
add_executable(${PROJECT_NAME} ${SOURCES} )
target_link_libraries (${PROJECT_NAME} alexa-sdk-framework )

# Install executable
install(TARGETS ${PROJECT_NAME} DESTINATION "/usr/bin/" )

# Install Config File
install(FILES ${CONFIG} DESTINATION ${CONFIG_DIRECTORY} )





