file(GLOB SOURCES test_*.cpp)

foreach(test ${SOURCES})
    get_filename_component(test_name ${test} NAME_WE)
    add_executable(${test_name} ${test})
    target_link_libraries(${test_name} ${cyber_mx})
    # 设置 RPATH 以便运行时能找到 Fast-DDS 库（包括间接依赖）
    set_target_properties(${test_name} PROPERTIES
        BUILD_RPATH "${FastDDS_INSTALL}/lib"
        INSTALL_RPATH "${FastDDS_INSTALL}/lib"
        BUILD_WITH_INSTALL_RPATH TRUE
        INSTALL_RPATH_USE_LINK_PATH TRUE
        SKIP_BUILD_RPATH FALSE
    )

endforeach()

SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin/tests)