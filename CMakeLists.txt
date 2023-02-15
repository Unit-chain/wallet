cmake_minimum_required(VERSION 3.5)

project(Unit LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# QtCreator supports the following variables for Android, which are identical to qmake Android variables.
# Check http://doc.qt.io/qt-5/deployment-android.html for more information.
# They need to be set before the find_package(Qt5 ...) call.

#if(ANDROID)
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
#    if (ANDROID_ABI STREQUAL "armeabi-v7a")
#        set(ANDROID_EXTRA_LIBS
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libcrypto.so
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libssl.so)
#    endif()
#endif()

find_package(Qt5 COMPONENTS Widgets REQUIRED)

find_package(Boost)
find_package(OpenSSL REQUIRED)

#set(ROCKSDB_SHARED_LIB /usr/local/lib/librocksdb.so)

add_executable(Unit
    main.cpp
    intro.cpp
    intro.h
    intro.ui
    no_mnemonic_page.cpp
    no_mnemonic_page.h
    no_mnemonic_page.ui

    personal_cabinet.cpp
    personal_cabinet.h
    personal_cabinet.ui


    ./Unit/libdevcore/bip44/addresses.hpp
    ./Unit/libdevcore/bip44/addresses.cpp
    ./Unit/libdevcore/bip44/BIP32.hpp
    ./Unit/libdevcore/bip44/BIP32.cpp
    ./Unit/libdevcore/bip44/BIP44.hpp
    ./Unit/libdevcore/bip44/BIP44.cpp
    ./Unit/libdevcore/bip44/BIP39.hpp
    ./Unit/libdevcore/bip44/BIP39.cpp
    ./Unit/libdevcore/bip44/SHA256.cpp
    ./Unit/libdevcore/bip44/SHA256.h
    ./Unit/libdevcore/bip44/utils.hpp
    ./Unit/libdevcore/bip44/utils.cpp
#    ./Unit/libdevcore/db/DB.h
#    ./Unit/libdevcore/db/DB.cpp



)

#target_link_libraries(${PROJECT_NAME} PRIVATE ${ROCKSDB_SHARED_LIB})
target_link_libraries(${PROJECT_NAME} PRIVATE OpenSSL::SSL)

target_link_libraries(Unit PRIVATE Qt5::Widgets)
