project (SOURKODE C)
cmake_minimum_required(VERSION 2.8.9)

set(SOURKODE_VERSION_MAJOR "0")
set(SOURKODE_VERSION_MINOR "1")
set(SOURKODE_VERSION_PATCH "0")
set(SOURKODE_VERSION_EXTRA "")
set(SOURKODE_VERSION "${SOURKODE_VERSION_MAJOR}.${SOURKODE_VERSION_MINOR}")
set(SOURKODE_VERSION_FULL "${SOURKODE_VERSION}.${SOURKODE_VERSION_PATCH}${SOURKODE_VERSION_EXTRA}")

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

#===================== Options list ===========================================
option(NINJA_MODE "Enable all warnings" ON)

#===================== Set compiler flags =====================================
if(NINJA_MODE)
    if (CMAKE_C_COMPILER_ID MATCHES "^GNU$")
        set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} --std=c89 -pedantic -Wall -Wextra -Wformat-nonliteral -Wformat-security -Wformat-y2k -Winit-self -Wmissing-include-dirs -Wswitch-default -Wswitch-enum -Wsync-nand -Wstrict-overflow=5 -Wtrampolines -Wfloat-equal -Wdeclaration-after-statement -Wundef -Wshadow -Wunsafe-loop-optimizations -Wbad-function-cast -Wc++-compat -Wcast-qual -Wcast-align -Wwrite-strings -Wconversion -Wsign-conversion -Wlogical-op -Waggregate-return -Wstrict-prototypes -Wold-style-definition -Wnormalized=nfc -Wredundant-decls -Wnested-externs -Winline -Wvla -Wdisabled-optimization -Wmissing-prototypes -Wmissing-declarations")
    elseif(CMAKE_C_COMPILER_ID MATCHES "^MSVC$")
        if(CMAKE_C_FLAGS MATCHES "/W[0-4]")
            string(REGEX REPLACE "/W[0-4]" "/Wall" CMAKE_C_FLAGS "${CMAKE_C_FLAGS}")
        else()
            set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /Wall")
        endif()
    elseif(CMAKE_C_COMPILER_ID MATCHES "^Clang$")
        set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} --std=c89 -pedantic -Weverything")
    endif()
endif()


#===================== Find all dependencies ==================================
set(sourkode_LIBRARIES "") # should contain just list of libs
set(sourkode_PKG_LIBS "") # Should contain list of -lLIBNAME
set(sourkode_PKG_DEPS "") #list of dependencies names for pkg-config
set(sourkode_INCLUDE_DIRS "") # Should contain list of all include dirs required to build library


#===================== Export library dependencies ============================
set(SOURKODE_LIBRARIES ${sourkode_LIBRARIES} CACHE STRING "Dependencies of SOURKODE")
foreach(arg ${sourkode_PKG_DEPS})
    set(SOURKODE_PKG_DEPS "${SOURKODE_PKG_DEPS} ${arg}")
endforeach()
foreach(arg ${sourkode_PKG_LIBS})
    set(SOURKODE_PKG_LIBS "${SOURKODE_PKG_LIBS} ${arg}")
endforeach()

#==================== Create generated files ==================================
include(CMakePackageConfigHelpers)

if (UNIX)
    set(SOURKODE_CONFIG_PATH "${CMAKE_INSTALL_PREFIX}/lib/cmake/sourkode/")
else()
    set(SOURKODE_CONFIG_PATH "${CMAKE_INSTALL_PREFIX}/")
endif()

configure_package_config_file("${SOURKODE_SOURCE_DIR}/src/sourkodeConfig.cmake.in"
                              "${SOURKODE_BINARY_DIR}/src/sourkodeConfig.cmake"
                              INSTALL_DESTINATION "${SOURKODE_CONFIG_PATH}"
                              PATH_VARS CMAKE_INSTALL_PREFIX
                              NO_CHECK_REQUIRED_COMPONENTS_MACRO)

write_basic_package_version_file("${SOURKODE_BINARY_DIR}/src/sourkodeConfigVersion.cmake" 
							    VERSION ${SOURKODE_VERSION_FULL}
                                 COMPATIBILITY SameMajorVersion)

configure_file("${SOURKODE_SOURCE_DIR}/src/sourkode.pc.in"
               "${SOURKODE_BINARY_DIR}/src/sourkode.pc" @ONLY)

add_subdirectory(src)
