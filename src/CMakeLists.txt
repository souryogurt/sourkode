set (sourkode_HEADERS "${SOURKODE_SOURCE_DIR}/inc/KD/kd.h" 
					"${SOURKODE_SOURCE_DIR}/inc/KD/kdplatform.h")
if(WIN32)
	list(APPEND sourkode_SOURCES "entry_winmain.c")
else()
	list(APPEND sourkode_SOURCES "entry_main.c")
endif()

list(APPEND sourkode_SOURCES "memalloc_stdlib.c")

if (APPLE)
    # For some reason, CMake doesn't know about .m
    set_source_files_properties(${sourkode_SOURCES} PROPERTIES LANGUAGE C)
endif()

add_library(sourkode STATIC ${sourkode_SOURCES} ${sourkode_HEADERS})
set_target_properties(sourkode PROPERTIES
    VERSION ${SOURKODE_VERSION}
    SOVERSION ${SOURKODE_VERSION_MAJOR})

target_include_directories(sourkode PRIVATE "${SOURKODE_SOURCE_DIR}/inc" ${sourkode_INCLUDE_DIRS})
target_compile_definitions(sourkode PUBLIC UNICODE _UNICODE)

# HERE I CAN SET NINJA FLAGS ACTUALLY
#target_compile_options(sourkode PRIVATE
#                       "$<$<C_COMPILER_ID:Clang>:-Wall>"
#                       "$<$<C_COMPILER_ID:GNU>:-Wall>")

set_target_properties(sourkode PROPERTIES OUTPUT_NAME sourkode)
