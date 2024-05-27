cmake_minimum_required(VERSION 3.22)

project(cf-subm)

add_executable(cf-subm main.cpp input/input.cpp commandline/commandline.cpp read_write_submissions.cpp fetch.cpp stalk.cpp savetojson.cpp code.cpp time.cpp network.cpp)

target_link_libraries(cf-subm curl)