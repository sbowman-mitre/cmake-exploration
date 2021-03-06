# Project setup
cmake_minimum_required(VERSION 3.0)
project(myapp)
enable_language(CXX)

# set versions
include (VersionUtils.cmake)
get_version ("${PROJECT_SOURCE_DIR}/include"
        myapp_version_major myapp_version_minor myapp_version_patch myapp_version_suffix)
string(LENGTH ${myapp_version_suffix} myapp_version_suffix_length)
if(myapp_version_suffix_length EQUAL 1)
	# ignore this suffix
	set(VERSION ${myapp_version_major}.${myapp_version_minor}.${myapp_version_patch})
else()
	# use the suffix
	set(VERSION ${myapp_version_major}.${myapp_version_minor}.${myapp_version_patch}-${myapp_version_suffix})
endif()
message("-- Generating build for myapp version ${VERSION}")

# bring log4cplus includes onto our path
include_directories(/usr/local/include/log4cplus/)
include_directories(/usr/local/include/)  # still need this if the ExternalProject_Add operation is told to "install" also
include_directories(${PROJECT_SOURCE_DIR})

# bring integrator in as a dependency by using its GIT_TAG
include(ExternalProject)
#    This completely fails when offline. Need mitigation strategy.
#    GIT_TAG v1.1.1, couldn't use this, but would rather do so. Just pointing to the repo gets master!
#    Could consider using INSTALL_DIR to force a known location that matches include_directories
ExternalProject_Add(integrator
    GIT_REPOSITORY git@github.com:buffetboy2001/integrator.git
    # GIT_TAG v1.2.0
    INSTALL_COMMAND make install
    UPDATE_DISCONNECTED 1
)

# add directories that the linker should use when searching for libraries
link_directories(/usr/local/bin)

# Build executable
add_executable(myapp src/main.cpp)
target_link_libraries(myapp cyglog4cplus-1-2-5.dll integrator-1.3.0-SNAPSHOT) # grr...would like this library name to be automatic, linked to ExternalProject_Add

# installing to a separate bin directory
install(TARGETS myapp DESTINATION bin)

# Thoughts & notes:
#
# Should I want to, log4plus .7z can be downloaded at this URL: http://downloads.sourceforge.net/project/log4cplus/log4cplus-stable/1.2.0/log4cplus-1.2.0.7z?r=https%3A%2F%2Fsourceforge.net%2Fprojects%2Flog4cplus%2Ffiles%2F&ts=1457216600&use_mirror=netcologne
#
# [] Using ExternalProject_Add does not automatically tell CMake what new paths to include and what new library to link. So, there is still a lot of setup work to do. How to solve this?