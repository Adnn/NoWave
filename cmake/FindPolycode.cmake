## CMAKE_DOCUMENTATION_START FindPolycode.cmake
##
## Try to find Polycode.
##
## Inputs are:
##  \\li Polycode_DIR - Polycode installation directory
##  \\li Polycode_CMAKE_DIR - Polycode CMake directory, found in Polycode source tree
##
## Once done this will define :
##  \\li Polycode_FOUND - system has Polycode
##  \\li Polycode_INCLUDE_DIR - the Polycode include directory
##  \\li Polycode_DEPENDENCIES_INCLUDE_DIR - Polycode dependencies includes directories
##  \\li Polycode_LIBRARIES - The libraries needed to use Polycode
##  \\li Polycode_LIBRARY - The Polycode library
##  \\li Polycode_VIEW_DIR - The Polycode exported PolyView class directory.
##
## You can use the POLYCODE_DIR environment variable.
##
## CMAKE_DOCUMENTATION_END

##
## Use the POLYCODE_DIR environment variable
##
set(Polycode_DIR $ENV{POLYCODE_DIR} CACHE PATH "Path to Polycode installation top level directory." )

# At the root of Polycode source tree, there is a CMake/ folder containing different Find<Module>.cmake
# for most of its dependencies.
set(Polycode_CMAKE_DIR CACHE PATH "Path to Polycode CMake's folder (in Polycode's source tree)." )
list(APPEND CMAKE_MODULE_PATH ${Polycode_CMAKE_DIR})

# Approach copied from Polycode's root CMakeLists.txt
# CMAKE_PREFIX_PATH will be used by the most part of find_xxx commands
# (additionally, they willl be approriatly suffixed by the find commands)
SET(CMAKE_PREFIX_PATH 
    ${Polycode_DIR}/Framework/Core
    ${Polycode_DIR}/Framework/Core/Dependencies
    ${Polycode_DIR}/Framework/Modules/Dependencies
    ${Polycode_DIR}/Framework/Tools/Dependencies
)

##
## Look for headers and libs
##
find_path(Polycode_INCLUDE_DIR Polycode.h)

# As of today (2014-04-09) there is a PolycodeView.h exported among other headers
# We explicitely want to find the directory containing the header + the implementation
find_path(Polycode_VIEW_DIR PolycodeView.h
    ${Polycode_DIR}/Framework/Core/PolycodeView
    NO_DEFAULT_PATH
)

find_library(Polycode_LIBRARY 
    NAMES libPolycore Polycore
)

##
## Polycode Dependencies
##

# Those headers could exist in the system, avoid selecting those versions
find_path(Polycode_DEPENDENCIES_INCLUDE_DIR 
    NAMES ft2build.h zlib.h
    NO_SYSTEM_ENVIRONMENT_PATH
    NO_CMAKE_SYSTEM_PATH
)

# Gives a better chance not to catch the system wide installations of the dependencies
# when Polycode installation dir has not yet been correctly set
if(Polycode_INCLUDE_DIR)
    if(NOT Polycode_CMAKE_DIR)
        message(SEND_ERROR "Please provide Polycode_CMAKE_DIR variable to continue...")
    else()
        #POLYCODE_RELEASE_DIR is used to generate path in some of Polycode's Find<Package>.cmake
        #that are disabling the other paths
        set(POLYCODE_RELEASE_DIR ${Polycode_DIR})

        FIND_PACKAGE(OpenGL REQUIRED)
        FIND_PACKAGE(ZLIB REQUIRED)
        FIND_PACKAGE(PNG REQUIRED)
        FIND_PACKAGE(PhysFS REQUIRED)
        FIND_PACKAGE(OpenAL REQUIRED)
        FIND_PACKAGE(Freetype REQUIRED)
        FIND_PACKAGE(Ogg REQUIRED)
        FIND_PACKAGE(Vorbis REQUIRED)
        FIND_PACKAGE(VorbisFile REQUIRED)
        FIND_PACKAGE(Lua REQUIRED)
    endif()
endif()

if(APPLE)
    # Find OS X frameworks against which Polycode and its dependencies were linked
    # TODO: Is it a good idea to do that here ? What happens if those are duplicated ?
    find_library(COCOA_LIBRARY Cocoa)
    find_library(OPENGL_LIBRARY OpenGL)
    find_library(IOKIT_LIBRARY IOKit)
    find_library(OPENAL_LIBRARY OpenAL)
    mark_as_advanced(COCOA_LIBRARY OPENGL_LIBRARY IOKIT_LIBRARY OPENAL_LIBRARY)
    set(EXTRA_LIBRARIES ${COCOA_LIBRARY} ${OPENGL_LIBRARY} ${IOKIT_LIBRARY} ${OPENAL_LIBRARY})
endif(APPLE) 

##  
## handle the QUIETLY and REQUIRED arguments and set Polycode_FOUND to TRUE if 
## all listed variables are TRUE
##
INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(Polycode DEFAULT_MSG Polycode_INCLUDE_DIR Polycode_VIEW_DIR Polycode_LIBRARY)

#there seems to be a bug : xxx_FOUND is always output in upper case
IF(POLYCODE_FOUND)
    SET( Polycode_LIBRARIES ${Polycode_LIBRARY}
        ${ZLIB_LIBRARIES}
        ${LUA_LIBRARY}
        ${OPENGL_LIBRARIES}
        ${OPENAL_LIBRARY}
        ${PNG_LIBRARIES}
        ${FREETYPE_LIBRARIES}
        ${PHYSFS_LIBRARY}
        ${OGG_LIBRARY}
        ${VORBIS_LIBRARY}
        ${VORBISFILE_LIBRARY}

        ${EXTRA_LIBRARIES}
)
ELSE(POLYCODE_FOUND)
    SET( Polycode_LIBRARIES )
ENDIF(POLYCODE_FOUND)
    
MARK_AS_ADVANCED( Polycode_INCLUDE_DIR Polycode_LIBRARIES )
