cmake_minimum_required(VERSION 3.26)
project(MultiThreadProgramming)

set(CMAKE_CXX_STANDARD 17)


add_executable(basic-usage basic/basic-usage.cpp)
add_executable(thread-parameter basic/thread-parameter.cpp)
add_executable(mutex-data-shared basic/mutex-data-shared.cpp)
add_executable(mutex-deadlock basic/mutex-deadlock.cpp)
add_executable(call-once basic/call-once.cpp)
add_executable(condition-variable basic/condition-variable.cpp)

add_executable(thread-pool-example thread-pool/thread-pool-example.cpp)
add_executable(async-future thread-pool/async-future.cpp)
add_executable(atomic thread-pool/atomic.cpp)