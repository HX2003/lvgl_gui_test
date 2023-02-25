cmake_minimum_required(VERSION 3.14)

project(lvgl_gui)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)

file(GLOB HEADERS_MAIN CONFIGURE_DEPENDS *.h)
file(GLOB HEADERS_COMPONENTS CONFIGURE_DEPENDS components/*.h)

set(HEADERS ${HEADERS_MAIN} ${HEADERS_COMPONENTS})

file(GLOB SOURCES_C CONFIGURE_DEPENDS *.c)
file(GLOB SOURCES_CPP CONFIGURE_DEPENDS *.cpp)
set(SOURCES ${SOURCES_C} ${SOURCES_CPP})

find_package(SDL2 REQUIRED SDL2)
find_package(Freetype REQUIRED)
include_directories(
    .
    ${FREETYPE_INCLUDE_DIRS}
    ${SDL2_INCLUDE_DIRS}
    ${SDL2_INCLUDE_DIRS}/../
)

set(INC_INSTALL_DIR include/${PROJECT_NAME})
set(BUILD_SHARED_LIBS ON)
add_subdirectory(lvgl)
add_subdirectory(lv_drivers)

add_library(${PROJECT_NAME} SHARED ${SOURCES})

target_include_directories(lvgl PRIVATE ${FREETYPE_INCLUDE_DIRS})
target_link_libraries(lvgl PRIVATE ${FREETYPE_LIBRARIES})

target_include_directories(${PROJECT_NAME} PUBLIC .)

target_link_libraries(${PROJECT_NAME} PRIVATE lvgl lvgl::examples lvgl::demos lvgl::drivers ${SDL2_LIBRARIES} m ${FREETYPE_LIBRARIES})

add_executable(${PROJECT_NAME}_executable ${SOURCES})
target_link_libraries(${PROJECT_NAME}_executable PRIVATE lvgl lvgl::examples lvgl::demos lvgl::drivers ${SDL2_LIBRARIES} m ${FREETYPE_LIBRARIES})

install(TARGETS ${PROJECT_NAME} DESTINATION lib)
# install(FILES ${HEADERS} DESTINATION include/${PROJECT_NAME})
