CMAKE_MINIMUM_REQUIRED(VERSION 3.31.6)

PROJECT(Cursework2025-16)

SET(CMAKE_CXX_STANDARD 23)
SET(CMAKE_CXX_STANDARD_REQUIRED ON)

INCLUDE_DIRECTORIES(
    ${CMAKE_CURRENT_SOURCE_DIR}/List
    ${CMAKE_CURRENT_SOURCE_DIR}/Database
    ${CMAKE_CURRENT_SOURCE_DIR}/Filer
    ${CMAKE_CURRENT_SOURCE_DIR}/TradeOperation
    ${CMAKE_CURRENT_SOURCE_DIR}/Interface
    ${CMAKE_CURRENT_SOURCE_DIR}/Crypter
)

ADD_EXECUTABLE(
    Program src/main.cxx
    Database/Database.cxx
    Filer/Filer.cxx
    TradeOperation/TradeOperation.cxx
    Interface/Interface.cxx
    Crypter/Crypter.cxx
)
