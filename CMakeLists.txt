cmake_minimum_required(VERSION 3.22)
project(Fusion)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(LAYERS_DIR $ENV{Layers})
set(QLAYERS_DIR $ENV{QLayers})

# Find Qt modules
find_package(Qt6 6.9.1 COMPONENTS Core Gui Widgets Svg Network REQUIRED)

# Set the resource compiler path based on configuration
if (WIN32)
    set(RESOURCE_COMPILER_DEBUG "${LAYERS_DIR}/bin/Debug/LayersResourceCompilerd.exe")
    set(RESOURCE_COMPILER_RELEASE "${LAYERS_DIR}/bin/Release/LayersResourceCompiler.exe")
else()
    set(RESOURCE_COMPILER_DEBUG "${LAYERS_DIR}/bin/LayersResourceCompilerd")
    set(RESOURCE_COMPILER_RELEASE "${LAYERS_DIR}/bin/LayersResourceCompiler")
endif()

# Generate styles.cpp from styles.lrc using the Layers resource compiler
add_custom_command(
    OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/styles.cpp
    COMMAND $<$<CONFIG:Debug>:${RESOURCE_COMPILER_DEBUG}>$<$<CONFIG:Release>:${RESOURCE_COMPILER_RELEASE}>
        ${CMAKE_CURRENT_SOURCE_DIR}/styles/styles.lrc
        ${CMAKE_CURRENT_BINARY_DIR}/styles.cpp
    DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/styles/styles.lrc
    COMMENT "Generating styles.cpp from styles.lrc"
    VERBATIM
)

# Set the source files for Fusion
file(GLOB SOURCES "src/*.cpp")

# Set the header files for Fusion (public and private)
file(GLOB PUBLIC_HEADERS "include/Fusion/*.h")
file(GLOB PRIVATE_HEADERS "src/*.h")

# Combine all headers for moc generation
set(ALL_HEADERS ${PUBLIC_HEADERS} ${PRIVATE_HEADERS})

# Set the resource files
set(IMAGES "images/images.qrc")

# Generate resource files
qt6_add_resources(IMAGES_RC ${IMAGES})

# Generate moc files for all headers with Q_OBJECT
qt6_wrap_cpp(MOC_FILES ${ALL_HEADERS})

# Add the shared library target
add_library(Fusion SHARED
    ${SOURCES}
    ${CMAKE_CURRENT_BINARY_DIR}/styles.cpp
    ${MOC_FILES}
    ${IMAGES_RC}
)

# Add the FUSION_LIB definition when building the library
target_compile_definitions(Fusion PRIVATE FUSION_LIB)

# Include directories
target_include_directories(Fusion PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
    "${CMAKE_CURRENT_SOURCE_DIR}/src"
    "${LAYERS_DIR}/include"
    "${QLAYERS_DIR}/include"
)

if(WIN32)
    set(LAYERS_LIBRARY_DEBUG "${LAYERS_DIR}/lib/Debug/Layersd.lib")
    set(LAYERS_LIBRARY_RELEASE "${LAYERS_DIR}/lib/Release/Layers.lib")
    set(QLAYERS_LIBRARY_DEBUG "${QLAYERS_DIR}/lib/Debug/QLayersd.lib")
    set(QLAYERS_LIBRARY_RELEASE "${QLAYERS_DIR}/lib/Release/QLayers.lib")
else()
    set(LAYERS_LIBRARY_DEBUG "${LAYERS_DIR}/lib/libLayersd.dylib")
    set(LAYERS_LIBRARY_RELEASE "${LAYERS_DIR}/lib/libLayers.dylib")
    set(QLAYERS_LIBRARY_DEBUG "${QLAYERS_DIR}/lib/libQLayersd.dylib")
    set(QLAYERS_LIBRARY_RELEASE "${QLAYERS_DIR}/lib/libQLayers.dylib")
endif()

target_link_libraries(Fusion PRIVATE
    $<$<CONFIG:Debug>:${LAYERS_LIBRARY_DEBUG} ${QLAYERS_LIBRARY_DEBUG}>
    $<$<CONFIG:Release>:${LAYERS_LIBRARY_RELEASE} ${QLAYERS_LIBRARY_RELEASE}>
    Qt6::Core Qt6::Gui Qt6::Widgets Qt6::Svg Qt6::Network
)

# Install rules
install(TARGETS Fusion DESTINATION lib)
install(DIRECTORY include/Fusion DESTINATION include)

# Set the output directory for the built library
set_target_properties(Fusion PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin"  # for .dll
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/lib"  # for .lib
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/lib"  # for .lib
    DEBUG_POSTFIX "d"
)
