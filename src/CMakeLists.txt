set (sourkode_HEADERS "${SOURKODE_SOURCE_DIR}/inc/KD/kd.h" 
					"${SOURKODE_SOURCE_DIR}/inc/KD/kdplatform.h")
if(WIN32)

	list(APPEND sourkode_SOURCES "entry_winmain.c")
else()
	list(APPEND sourkode_SOURCES "entry_main.c")
endif()

if (APPLE)
    # For some reason, CMake doesn't know about .m
    set_source_files_properties(${sourkode_SOURCES} PROPERTIES LANGUAGE C)
endif()

add_library(sourkode STATIC ${sourkode_SOURCES} ${sourkode_HEADERS})
set_target_properties(sourkode PROPERTIES
    VERSION ${SOURKODE_VERSION}
    SOVERSION ${SOURKODE_VERSION_MAJOR}
    FOLDER "sourkode")
if(WIN32)
	target_compile_definitions(sourkode PRIVATE -DUNICODE -D_UNICODE)
endif()
if(WITHOUT_STANDARD_C_LIBRARY)
	target_compile_definitions(sourkode PRIVATE -DNO_STANDARD_C_LIBRARY)
endif()
if(WITH_WINDOWING)
	target_compile_definitions(sourkode PRIVATE -DKD_WINDOW_SUPPORTED)
endif()

target_include_directories(sourkode PRIVATE "${SOURKODE_SOURCE_DIR}/inc" ${sourkode_INCLUDE_DIRS})

# HERE I CAN SET NINJA FLAGS ACTUALLY
#target_compile_options(sourkode PRIVATE
#                       "$<$<C_COMPILER_ID:Clang>:-Wall>"
#                       "$<$<C_COMPILER_ID:GNU>:-Wall>")

set_target_properties(sourkode PROPERTIES OUTPUT_NAME sourkode)
