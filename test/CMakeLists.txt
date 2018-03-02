# xxHash_cx test

cmake_minimum_required(VERSION 3.8)

project(xxhash_cx_test)

if (MSVC)
    add_definitions(-D_UNICODE)
    add_definitions(-DXXH_ACCEPT_NULL_INPUT_POINTER=1)
    string(REPLACE "/MD" "/MT" CMAKE_C_FLAGS_DEBUG            ${CMAKE_C_FLAGS_DEBUG})
    string(REPLACE "/MD" "/MT" CMAKE_C_FLAGS_MINSIZEREL       ${CMAKE_C_FLAGS_MINSIZEREL})
    string(REPLACE "/MD" "/MT" CMAKE_C_FLAGS_RELEASE          ${CMAKE_C_FLAGS_RELEASE})
    string(REPLACE "/MD" "/MT" CMAKE_C_FLAGS_RELWITHDEBINFO   ${CMAKE_C_FLAGS_RELWITHDEBINFO})
    string(REPLACE "/MD" "/MT" CMAKE_CXX_FLAGS_DEBUG          ${CMAKE_CXX_FLAGS_DEBUG})
    string(REPLACE "/MD" "/MT" CMAKE_CXX_FLAGS_MINSIZEREL     ${CMAKE_CXX_FLAGS_MINSIZEREL})
    string(REPLACE "/MD" "/MT" CMAKE_CXX_FLAGS_RELEASE        ${CMAKE_CXX_FLAGS_RELEASE})
    string(REPLACE "/MD" "/MT" CMAKE_CXX_FLAGS_RELWITHDEBINFO ${CMAKE_CXX_FLAGS_RELWITHDEBINFO})
endif ()


add_subdirectory(extlib/googletest)

include_directories(../include)
include_directories(./extlib/xxhash)
include_directories(${googletest_BINARY_DIR}/include)
link_directories(${googletest_BINARY_DIR}/lib)

set(HEADER
)

set(SOURCE
	xxhash_test.cpp
)

set(EXTLIB
	../include/xxhash_cx.h
	./extlib/xxhash/xxhash.h
	./extlib/xxhash/xxhash.c
)

add_executable(
	xxhash_cx_test 
	${HEADER}
	${SOURCE}
	${EXTLIB}
)

target_link_libraries(xxhash_cx_test gtest)
target_link_libraries(xxhash_cx_test gtest_main)

