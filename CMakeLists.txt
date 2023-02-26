cmake_minimum_required(VERSION 3.24)
project(UnitWallet)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

add_compile_definitions(LOGO_PATH="${CMAKE_CURRENT_SOURCE_DIR}/icon/logo-07-cropped.svg")

find_package(Qt5 COMPONENTS
        Core
        Gui
        Widgets
        Svg
        REQUIRED)

find_package(OpenSSL REQUIRED)
#find_package(RocksDB REQUIRED)
set(ROCKSDB_SHARED_LIB /usr/local/lib/librocksdb.so)





add_executable(${PROJECT_NAME}
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
        Unit/libdevcore/bip44/addresses.hpp
        Unit/libdevcore/bip44/addresses.cpp
        Unit/libdevcore/bip44/BIP32.hpp
        Unit/libdevcore/bip44/BIP32.cpp
        Unit/libdevcore/bip44/BIP44.hpp
        Unit/libdevcore/bip44/BIP44.cpp
        Unit/libdevcore/bip44/BIP39.hpp
        Unit/libdevcore/bip44/BIP39.cpp
        Unit/libdevcore/bip44/SHA256.cpp
        Unit/libdevcore/bip44/SHA256.h
        Unit/libdevcore/bip44/utils.hpp
        Unit/libdevcore/bip44/utils.cpp
        Unit/libdevcore/db/DB.h
        Unit/libdevcore/db/DB.cpp
        ${LOGO}
        )
target_link_libraries(${PROJECT_NAME} PRIVATE
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
        Qt5::Svg
        )

target_link_libraries(${PROJECT_NAME} PRIVATE OpenSSL::SSL)
#target_link_libraries(${PROJECT_NAME} PRIVATE RocksDB::rocksdb)
target_link_libraries(${PROJECT_NAME} PRIVATE ${ROCKSDB_SHARED_LIB})
target_link_libraries(${PROJECT_NAME} PRIVATE Qt5::Widgets)
