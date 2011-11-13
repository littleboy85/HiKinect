#/**********************************************************\ 
# Auto-generated Mac project definition file for the
# hiKinect project
#\**********************************************************/

# Mac template platform definition CMake file
# Included from ../CMakeLists.txt

# remember that the current source dir is the project root; this file is in Mac/
file (GLOB PLATFORM RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
    Mac/[^.]*.cpp
    Mac/[^.]*.h
    Mac/[^.]*.cmake
    )

# use this to add preprocessor definitions
add_definitions(
    
)

SOURCE_GROUP(Mac FILES ${PLATFORM})

set (SOURCES
    ${SOURCES}
    ${PLATFORM}
    )

set(PLIST "Mac/bundle_template/Info.plist")
set(STRINGS "Mac/bundle_template/InfoPlist.strings")
set(LOCALIZED "Mac/bundle_template/Localized.r")

add_mac_plugin(${PROJECT_NAME} ${PLIST} ${STRINGS} ${LOCALIZED} SOURCES)

# add library dependencies here; leave ${PLUGIN_INTERNAL_DEPS} there unless you know what you're doing!
target_link_libraries(${PROJECT_NAME}
    ${PLUGIN_INTERNAL_DEPS}
    )

#SET(ENV{OPEN_NI_CONFIG_PATH} ${pathToPlugin}/Contents/ni)
set (OpenNI_LIB_PATH /usr/lib)
target_link_libraries(${PROJECT_NAME} "${OpenNI_LIB_PATH}/libOpenNI.dylib")

#custom

#Copy the specified lib to the plugin directory.
function(copyLibToFrameworks libPath pathToPlugin)
    ADD_CUSTOM_COMMAND(
        TARGET ${PROJECT_NAME}
        POST_BUILD
        COMMAND mkdir -p ${pathToPlugin}/Contents/Frameworks
    )
    ADD_CUSTOM_COMMAND(
        TARGET ${PROJECT_NAME}
        POST_BUILD
        COMMAND cp ${libPath} ${pathToPlugin}/Contents/Frameworks
    )
endfunction()
 
#Update the reference to the lib from the plugin.
function(updateReferencesToLib fromPath toPath targetLib)
    ADD_CUSTOM_COMMAND(
        TARGET ${PROJECT_NAME}
        POST_BUILD
        COMMAND install_name_tool -change ${fromPath} ${toPath} ${targetLib}
    )
endfunction()
 
#Update the reference inside the target lib.
function(updateReferenceInLib toPath targetLib)
    ADD_CUSTOM_COMMAND(
        TARGET ${PROJECT_NAME}
        POST_BUILD
        COMMAND install_name_tool -id ${toPath} ${targetLib}
    )
endfunction()
 
#Copy and update references for a library.
function(changeLoaderPath pathInBinary libFolder libName pathToPlugin target)
    copyLibToFrameworks(${libFolder}/${libName} 
        ${pathToPlugin}
    )
    updateReferenceInLib(@loader_path/../Frameworks/${libName} 
        ${pathToPlugin}/Contents/Frameworks/${libName}
    )
    updateReferencesToLib(${pathInBinary} 
        @loader_path/../Frameworks/${libName} 
        ${target}
    )
endfunction()


# Build the path to the plugin binary
#get_target_property(LIBDIR ${PROJECT_NAME} LIBRARY_OUTPUT_DIRECTORY)
#get_target_property(ONAME ${PROJECT_NAME} OUTPUT_NAME)
#set(PBIN "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_CFG_INTDIR}/${PROJECT_NAME}.plugin")
#changeLoaderPath(../../Bin/Release/libOpenNI.dylib ${CMAKE_CURRENT_SOURCE_DIR}/Mac libOpenNI.dylib ${PBIN} ${PBIN}/Contents/MacOS/${PROJECT_NAME})
#changeLoaderPath(/usr/local/lib/libusb-1.0.0.dylib ${CMAKE_CURRENT_SOURCE_DIR}/Mac libusb-1.0.0.dylib ${PBIN} ${PBIN}/Contents/Frameworks/libOpenNI.dylib)

