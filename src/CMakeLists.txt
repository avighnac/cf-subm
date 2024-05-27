cmake_minimum_required(VERSION 3.22)

project(cf-subm)

add_executable(cf-subm global/global.cpp cf_subm/cf_subm.cpp main.cpp input/input.cpp cf_subm/list.cpp commandline/commandline.cpp read_write_submissions.cpp cf_subm/fetch.cpp cf_subm/stalk.cpp cf_subm/savetojson.cpp cf_subm/code.cpp time/time.cpp network/network.cpp)

target_link_libraries(cf-subm curl)