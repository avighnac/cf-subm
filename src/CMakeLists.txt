cmake_minimum_required(VERSION 3.22)
project(cf-subm)

set(SOURCES 
    main.cpp 

    cf_subm/list.cpp 
    cf_subm/fetch.cpp 
    cf_subm/stalk.cpp 
    cf_subm/savetojson.cpp 
    cf_subm/cf_subm.cpp 
    cf_subm/code.cpp 

    commandline/commandline.cpp 
    global/global.cpp 
    input/input.cpp 
    network/network.cpp
    time/time.cpp 

    read_write_submissions.cpp 
)

add_executable(cf-subm ${SOURCES})

if (WIN32)
    execute_process(
        COMMAND cmd /c "echo %VCPKG_ROOT%"
        OUTPUT_VARIABLE VCPKG_ROOT
        OUTPUT_STRIP_TRAILING_WHITESPACE
    )
    message("VCPKG_ROOT is set to: ${VCPKG_ROOT}")

    set(VCPKG_TRIPLET "x64-windows-static")

    set(CURL_INCLUDE_DIR "${VCPKG_ROOT}/installed/${VCPKG_TRIPLET}/include")
    set(CURL_LIBRARY "${VCPKG_ROOT}/installed/${VCPKG_TRIPLET}/lib/libcurl.lib")
    set(ZLIB_LIBRARY "${VCPKG_ROOT}/installed/${VCPKG_TRIPLET}/lib/zlib.lib")

    include_directories(${CURL_INCLUDE_DIR})
endif()

if (WIN32)
    find_package(CURL REQUIRED)
    target_link_libraries(cf-subm PRIVATE ${CURL_LIBRARY} ${ZLIB_LIBRARY} ws2_32 crypt32)
else()
    target_link_libraries(cf-subm curl)
endif()
target_compile_features(cf-subm PUBLIC cxx_std_20)