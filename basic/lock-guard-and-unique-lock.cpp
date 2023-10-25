
//
// Created by Yao on 2023/10/20.
// Description:
//

/*
 * lock_guard()
 */

/*
#include <iostream>
#include<mutex>
#include<thread>

int shared_data = 0;
std::mutex mtx;

void func(){
    for (int i = 0; i < 100000; ++i) {
        std::lock_guard<std::mutex> lg(mtx);
        shared_data ++;
    }
}
int main() {

    std::thread t1(func);
    std::thread t2(func);

    t1.join();
    t2.join();

    std::cout << shared_data << std::endl;
}
*/

/*
 * unique_lock()
 */
#include <iostream>
#include <mutex>
#include <thread>

int shared_data = 0;

// std::mutex mtx;
std::timed_mutex mtx;

void func()
{
    for (int i = 0; i < 2; ++i)
    {
        //        std::unique_lock<std::mutex> lg(mtx); // 构造函数中自动加锁 析构函数自动解锁
        std::unique_lock<std::timed_mutex> lg1(mtx, std::defer_lock); // 构造函数中没有自动加锁
                                                                      //        lg1.lock();
        if (lg1.try_lock_for(std::chrono::seconds(2)))
        {                                                         // 延迟加锁，阻塞2s
            std::this_thread::sleep_for(std::chrono::seconds(2)); // 休眠 1s
            shared_data++;
        }
    }
}
int main()
{

    std::thread t1(func);
    std::thread t2(func);

    t1.join();
    t2.join();

    std::cout << shared_data << std::endl;
}
