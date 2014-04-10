project(PolycodeTemplate)

##
## Start by listing platform independent files
##
set(${PROJECT_NAME}_HEADERS
    PolycodeTemplateEntryPoint.h
)

set(${PROJECT_NAME}_SOURCES
    PolycodeTemplateEntryPoint.cpp
)

##
## Append platform dependent files
##

#set(PLATFORM_ARGUMENT "")

if(APPLE)
    list(APPEND ${PROJECT_NAME}_HEADERS
        PolycodeTemplateAppDelegate.h
        PolycodeTemplate-Prefix.pch
    )
    
    list(APPEND ${PROJECT_NAME}_SOURCES
        main.m
        PolycodeTemplateAppDelegate.mm
        ${Polycode_VIEW_DIR}/PolycodeView.mm
    )

    set(${PROJECT_NAME}_SUPPORT
        PolycodeTemplate-Info.plist.in
    ) 

    set(${PROJECT_NAME}_RESOURCES
        Base.lproj/MainMenu.xib 
    ) 
   
    set(CMAKE_MACOSX_BUNDLE True)

    # This is to compile the project as objective C++
    # because there is a common file with the .cpp extension, that need obj-c++ when compiled on OS X
    # I am partial about this, it would be nice to be able to change the file "type" (as seen from Identity Inspector)
    # for PolycodeTemplateEntryPoint alone.
    set(CMAKE_CXX_FLAGS "-x objective-c++")
endif(APPLE)
# TODO: Linux and Windows platforms

add_executable(${PROJECT_NAME}
    # I do not know if it is a good idea to show the template in the IDE ?
    #${${PROJECT_NAME}_SUPPORT}
    ${${PROJECT_NAME}_SOURCES}
    ${${PROJECT_NAME}_HEADERS}
    ${${PROJECT_NAME}_RESOURCES}
)
    
# include CppUTest headers
include_directories(${Polycode_INCLUDE_DIR} ${Polycode_VIEW_DIR})
include_directories(${Polycode_DEPENDENCIES_INCLUDE_DIR})
include_directories(${Boost_INCLUDE_DIR} ${AuntEater_INCLUDE_DIR})

target_link_libraries(${PROJECT_NAME}
    NoWaveLib
    ${Polycode_LIBRARIES}
    ${AuntEater_LIBRARIES}
)

######################################################################
## Installation stuff - common to all projects
######################################################################
set_target_properties(${PROJECT_NAME} PROPERTIES
        VERSION "${VERSION}"
        SOVERSION "${SOVERSION}"
        # TODO: It would be nice to be able to just use an existing plist, instead of compulsorily 'configuring' it
        MACOSX_BUNDLE_INFO_PLIST "${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}-Info.plist.in"
        RESOURCE ${${PROJECT_NAME}_RESOURCES}
)


