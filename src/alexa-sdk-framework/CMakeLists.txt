cmake_minimum_required (VERSION 2.8.11)
project(alexa-sdk-framework)

message(STATUS "Alexa-SDK-Framework: v1.0.0")

set(VERSION_MAJOR 1)
set(VERSION_MINOR 0)
set(VERSION_PATCH 0)
set(VERSION_STRING ${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH})
set(INCLUDE_DIRECTORY "/usr/include/" )
set(INSTALL_DIRECTORY "alexa")
set(ASSET_INSTALL_DIRECTORY "/etc/alexa/asset/" )
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wdeprecated-declarations ")

# Find source files
file(GLOB SOURCES amazon-client/*.cpp
                  audio/*.cpp
                  auth/*.cpp
                  directive/*.cpp
                  directive/builtin/*.cpp
                  event/*.cpp
                  event/builtin/*.cpp
                  http2/*.cpp
                  server/*.cpp
                  utils/*.cpp)

# Find header files
file(GLOB CLIENT_HEADERS include/amazon-client/*.hpp)
file(GLOB AUDIO_HEADERS include/audio/*.hpp)
file(GLOB AUTH_HEADERS include/auth/*.hpp)
file(GLOB DIRECTIVE_HEADERS include/directive/*.hpp)
file(GLOB DIRECTIVE_BUILTIN_HEADERS include/directive/builtin/*.hpp)
file(GLOB EVENT_HEADERS include/event/*.hpp)
file(GLOB EVENT_BUILTIN_HEADERS include/event/builtin/*.hpp)
file(GLOB HTTP2_HEADERS include/http2/*.hpp)
file(GLOB SERVER_HEADERS include/server/*.hpp)
file(GLOB UTILS_HEADERS include/utils/*.hpp)
file(GLOB DEFAULT_HEADERS include/*.hpp)

#Find Asset Resources files
file(GLOB ASSETS asset/*.json)

# Include header files
include_directories(include)
include_directories(/usr/include/glib-2.0/)
include_directories(/usr/lib/glib-2.0/include/)
include_directories(/usr/include/gstreamer-1.0 )

# Create shared library
add_library(${PROJECT_NAME} SHARED ${SOURCES})

set_target_properties(${PROJECT_NAME} PROPERTIES VERSION ${VERSION_STRING} SOVERSION ${VERSION_MAJOR})
target_link_libraries(${PROJECT_NAME} "-lgstapp-1.0 -lgobject-2.0 -lglib-2.0 -lgstreamer-1.0 -lmp3lame -lboost_system -lboost_thread -lboost_date_time -lasound -lcurl -lnghttp2 -lssl -lcrypto -levent -levent_openssl -levent_core")
target_include_directories(${PROJECT_NAME} PUBLIC include )
target_include_directories(${PROJECT_NAME} PUBLIC /usr/include/glib-2.0/)
target_include_directories(${PROJECT_NAME} PUBLIC /usr/lib/glib-2.0/include/ )
target_include_directories(${PROJECT_NAME} PUBLIC /usr/include/gstreamer-1.0 )

# Install library
install(TARGETS ${PROJECT_NAME} DESTINATION /usr/lib/ )

# Install library headers
install(FILES ${CLIENT_HEADERS} DESTINATION ${INCLUDE_DIRECTORY}${INSTALL_DIRECTORY}/amazon-client/)
install(FILES ${AUDIO_HEADERS} DESTINATION ${INCLUDE_DIRECTORY}${INSTALL_DIRECTORY}/audio/)
install(FILES ${AUTH_HEADERS} DESTINATION ${INCLUDE_DIRECTORY}${INSTALL_DIRECTORY}/auth/)
install(FILES ${DIRECTIVE_HEADERS} DESTINATION ${INCLUDE_DIRECTORY}${INSTALL_DIRECTORY}/directive/)
install(FILES ${DIRECTIVE_BUILTIN_HEADERS} DESTINATION ${INCLUDE_DIRECTORY}${INSTALL_DIRECTORY}/directive/builtin/)
install(FILES ${EVENT_HEADERS} DESTINATION ${INCLUDE_DIRECTORY}${INSTALL_DIRECTORY}/event/)
install(FILES ${EVENT_BUILTIN_HEADERS} DESTINATION ${INCLUDE_DIRECTORY}${INSTALL_DIRECTORY}/event/builtin/)
install(FILES ${HTTP2_HEADERS} DESTINATION ${INCLUDE_DIRECTORY}${INSTALL_DIRECTORY}/http2/)
install(FILES ${SERVER_HEADERS} DESTINATION ${INCLUDE_DIRECTORY}${INSTALL_DIRECTORY}/server/)
install(FILES ${UTILS_HEADERS} DESTINATION ${INCLUDE_DIRECTORY}${INSTALL_DIRECTORY}/utils/)
install(FILES ${DEFAULT_HEADERS} DESTINATION ${INCLUDE_DIRECTORY}${INSTALL_DIRECTORY}/)

# Install Assets
install(FILES ${ASSETS} DESTINATION ${ASSET_INSTALL_DIRECTORY} )