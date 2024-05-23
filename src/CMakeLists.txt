project(cf-subm)

add_executable(cf-subm main.cpp read_write_submissions.cpp fetch.cpp stalk.cpp savetojson.cpp code.cpp network.cpp)

target_link_libraries(cf-subm curl)