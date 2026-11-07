cmake_minimum_required(VERSION 3.16)

project(Shogi VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SFML 3 REQUIRED COMPONENTS Graphics Window System Audio)

add_library(shogi_core
    core/Piece.cpp
    core/Board.cpp
    core/Move.cpp
    core/MoveGenerator.cpp
    core/Game.cpp
    core/Renderer.cpp
)

target_include_directories(shogi_core PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/core/include/core
)

target_link_libraries(shogi_core PUBLIC
    SFML::Graphics
    SFML::Window
    SFML::System
    SFML::Audio
)

add_executable(shogi MACOSX_BUNDLE
    src/main.cpp
    core/ResourcePath.cpp
)


target_link_libraries(shogi PRIVATE
    shogi_core
)

if(APPLE)

    target_link_libraries(shogi PRIVATE
        "-framework CoreFoundation"
    )

    set(MACOSX_BUNDLE_ICON_FILE AppIcon.icns)

    set_source_files_properties(
        "${CMAKE_SOURCE_DIR}/AppIcon.icns"
        PROPERTIES MACOSX_PACKAGE_LOCATION Resources
    )

    target_sources(shogi PRIVATE
        "${CMAKE_SOURCE_DIR}/AppIcon.icns"
    )

    set_target_properties(shogi PROPERTIES
        MACOSX_BUNDLE_BUNDLE_NAME "Shogi"
        MACOSX_BUNDLE_GUI_IDENTIFIER "com.deinname.shogi"
        MACOSX_BUNDLE_BUNDLE_VERSION "${PROJECT_VERSION}"
        MACOSX_BUNDLE_SHORT_VERSION_STRING "${PROJECT_VERSION}"
    )

    add_custom_command(TARGET shogi POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_SOURCE_DIR}/assets"
        "$<TARGET_BUNDLE_CONTENT_DIR:shogi>/Resources/assets"
    )

    install(TARGETS shogi
        BUNDLE DESTINATION .
    )

    install(CODE [[
        include(BundleUtilities)

        set(app "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/shogi.app")

        fixup_bundle(
            "${app}"
            ""
            "/opt/homebrew/opt/sfml/lib"
        )

        execute_process(
            COMMAND codesign --force --deep --sign - --timestamp=none "${app}"
            RESULT_VARIABLE SIGN_RESULT
        )

        if(NOT SIGN_RESULT EQUAL 0)
            message(FATAL_ERROR "Code signing failed!")
        endif()
    ]])

    set(CPACK_GENERATOR "DragNDrop")
    set(CPACK_PACKAGE_NAME "Shogi")
    set(CPACK_PACKAGE_VERSION "${PROJECT_VERSION}")
    set(CPACK_PACKAGE_FILE_NAME "Shogi-${PROJECT_VERSION}-macOS")

    include(CPack)

endif()
