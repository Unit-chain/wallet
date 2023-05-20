cmake_minimum_required(VERSION 3.24)
project(UnitWallet VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

add_compile_definitions(LOGO_PATH="${CMAKE_CURRENT_SOURCE_DIR}/icon/logo-07-cropped.svg")

find_package(Qt5 COMPONENTS REQUIRED
        Core
        Gui
        Widgets
        Svg
        WebEngineWidgets
        )

find_package(OpenSSL REQUIRED)


#find_package(RocksDB REQUIRED)
set(ROCKSDB_SHARED_LIB /usr/local/lib/librocksdb.so)

# Set the path to the Crypto++ library
set(CRYPTOPP /usr/local/lib/libcryptopp.a)


# Locate the Crypto++ library
find_library(CRYPTOPP NAMES cryptopp PATHS ${CRYPTOPP})

# Include the Crypto++ headers
include_directories(${CRYPTOPP})



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
        aes_256_GCM.cpp
        aes_256_GCM.h
        cpuid.cpp
        cpuid.h
        sidebar.cpp
        sidebar.h

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
# Link the executable with the Crypto++ library
target_link_libraries(${PROJECT_NAME} PRIVATE ${CRYPTOPP})
target_link_libraries(${PROJECT_NAME} PRIVATE Qt5::WebEngineWidgets)
