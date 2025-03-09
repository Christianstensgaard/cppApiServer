cmake_minimum_required(VERSION 3.10)
project(MyBoostProject)

set(CMAKE_CXX_STANDARD 17)

find_package(Boost REQUIRED COMPONENTS system filesystem)

if(Boost_FOUND)
    message(STATUS "Boost found: ${Boost_INCLUDE_DIRS}")
    include_directories(${Boost_INCLUDE_DIRS})
    link_directories(${Boost_LIBRARY_DIRS})
else()
    message(FATAL_ERROR "Boost not found!")
endif()

add_executable(test 
  sessionManager.cpp
  mock_dataModel.cpp
  rbac.cpp
  main.cpp 
  restServer.cpp 
  routeConfig.cpp
)

set(SWAGGER_UI_SOURCE "${CMAKE_SOURCE_DIR}/root")
set(SWAGGER_UI_DESTINATION "${CMAKE_BINARY_DIR}/swagger-ui")

add_custom_command(
    TARGET test POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${SWAGGER_UI_SOURCE} ${SWAGGER_UI_DESTINATION}
)

target_link_libraries(test Boost::system Boost::filesystem)
