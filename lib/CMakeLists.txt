add_library(comp_club CompClub.cpp Event.cpp TableInfo.cpp
        utils.cpp
        utils.h)

target_include_directories(comp_club PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})