cmake_minimum_required(VERSION 3.28)
project(rest_api)

#sandy
#need to install and include your json library here....
# see https://formulae.brew.sh/formula/jsoncpp for installation
INCLUDE_DIRECTORIES(  "/opt/homebrew/Cellar/jsoncpp/1.9.5/include" )
LINK_DIRECTORIES(  "/opt/homebrew/Cellar/jsoncpp/1.9.5/lib" )

#sandy
#if there is no curl library, need to install and include your curl here 
# see https://formulae.brew.sh/formula/curl for installation
#INCLUDE_DIRECTORIES(  "/opt/homebrew/Cellar/curl/8.8.0/include" )
#LINK_DIRECTORIES(  "/opt/homebrew/Cellar/curl/8.8.0/lib" )


#Sandy :
# Add a compiler command for using curl & jsoncpp
#
set(CURL_LIBRARY "-lcurl")
set(JSON_LIBRARY "-ljsoncpp")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CURL_LIBRARY}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${JSON_LIBRARY}")



set(CMAKE_CXX_STANDARD 17)
add_executable(rest_api main.cpp url_helper.h url_debug.h)
