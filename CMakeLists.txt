cmake_minimum_required(VERSION 3.26)
project(MultiThreadProgramming)

set(CMAKE_CXX_STANDARD 17)

#[[basic usage of multi-thread]]
add_executable(basic-usage basic/basic-usage.cpp)
add_executable(thread-parameter basic/thread-parameter.cpp)
add_executable(mutex-data-shared basic/mutex-data-shared.cpp)
add_executable(mutex-deadlock basic/mutex-deadlock.cpp)
add_executable(call-once basic/call-once.cpp)
add_executable(condition-variable basic/condition-variable.cpp)

#[[basic knowledge of thread-pool]]
add_executable(thread-pool-example thread-pool/thread-pool-example.cpp)
add_executable(async-future thread-pool/async-future.cpp)
add_executable(atomic thread-pool/atomic.cpp)

#[[concurrency programming blog]]
add_executable(hello_thread concurrency/01_hello_thread.cpp)
add_executable(lambda_thread concurrency/02_lambda_thread.cpp)
add_executable(thread_argument concurrency/03_thread_argument.cpp)
add_executable(thread_self_manage concurrency/04_thread_self_manage.cpp)
add_executable(call_once concurrency/05_call_once.cpp)
add_executable(naive_multithread concurrency/06_naive_multithread.cpp)
add_executable(mutex_lock concurrency/07_mutex_lock.cpp)
add_executable(improved_mutex_lock concurrency/08_improved_mutex_lock.cpp)
add_executable(deadlock_bank_transfer concurrency/09_deadlock_bank_transfer.cpp)
add_executable(improved_bank_transfer concurrency/10_improved_bank_transfer.cpp)
add_executable(lock_guard concurrency/11_lock_guard.cpp)
add_executable(bank_transfer_wait_notify concurrency/12_bank_transfer_wait_notify.cpp)
add_executable(async_task concurrency/13_async_task.cpp)
add_executable(packaged_task concurrency/14_packaged_task.cpp)
add_executable(promise_future concurrency/15_promise_future.cpp)
add_executable(parallel_algorithm concurrency/16_parallel_algorithm.cpp)