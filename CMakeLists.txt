cmake_minimum_required(VERSION 3.5)
project(network_homework_1)

find_package(PCAP REQUIRED)

INCLUDE_DIRECTORIES(${PCAP_INCLUDE_DIR} INCLUDE ${PCAP_LIBRARY})


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
SET (CMAKE_EXE_LINKER_FLAGS -lpcap)
set(SOURCE_FILES get_device_info.c)
add_executable(network_homework_1 ${SOURCE_FILES})



target_link_libraries(network_homework_1 ${PCAP_LIBRARY})


# - Try to find libpcap include dirs and libraries
#
# Usage of this module as follows:
#
#     find_package(PCAP)
#
# Variables used by this module, they can change the default behaviour and need
# to be set before calling find_package:
#
#  PCAP_ROOT_DIR             Set this variable to the root installation of
#                            libpcap if the module has problems finding the
#                            proper installation path.
#
# Variables defined by this module:
#
#  PCAP_FOUND                System has libpcap, include and library dirs found
#  PCAP_INCLUDE_DIR          The libpcap include directories.
#  PCAP_LIBRARY              The libpcap library (possibly includes a thread
#                            library e.g. required by pf_ring's libpcap)
#  HAVE_PF_RING              If a found version of libpcap supports PF_RING