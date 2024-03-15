cmake_minimum_required(VERSION 3.20)
if (VCPKG_TARGET_ANDROID)
    include("cmake/vcpkg_android.cmake")
endif()
set(VCPKG_ROOT "/Users/yangfan/.vcpkg-clion/vcpkg")
set(CMAKE_TOOLCHAIN_FILE "/Users/yangfan/Library/Android/sdk/ndk/25.1.8937393/build/cmake/android.toolchain.cmake")
set(CMAKE_ANDROID_NDK "/Users/yangfan/Library/Android/sdk/ndk/25.1.8937393")
set(ANDROID_NDK_HOME "/Users/yangfan/Library/Android/sdk/ndk/25.1.8937393")
set(VCPKG_CHAINLOAD_TOOLCHAIN_FILE "${ANDROID_NDK_HOME}/build/cmake/android.toolchain.cmake")
set(VCPKG_TARGET_TRIPLET "arm64-android")
set(ANDROID_ABI "arm64-v8a")
set(ANDROID_PLATFORM 23)

project(EchoOCPP)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(BIN_DIR ${CMAKE_SOURCE_DIR}/bin)
set(LIB_DIR ${CMAKE_SOURCE_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${LIB_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${LIB_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${BIN_DIR})

add_subdirectory(src)
add_subdirectory(test)
add_subdirectory(app)


add_executable(client client.cpp
        src/OCPP/201/Message/MessageManager.hpp)
add_executable(server server.cpp)



target_link_libraries(server PRIVATE AppServer)
target_link_libraries(client
       PUBLIC
        AppChargePoint
)


