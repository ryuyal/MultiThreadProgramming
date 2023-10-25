
//
// Created by Yao on 2023/10/20.
// Description:
//

#include <iostream>
#include <mutex>
#include <thread>

std::mutex m1, m2;

void func1()
{
    for (int i = 0; i < 5000; ++i)
    {
        m1.lock();
        m2.lock();
        m1.unlock();
        m2.unlock();
    }
}

void func2()
{
    // 循环等待 产生死锁
    /*    for (int i = 0; i < 5000; ++i) {
            m2.lock();
            m1.lock();
            m2.unlock();
            m1.unlock();
        }*/

    // 解决死锁，改成
    for (int i = 0; i < 5000; ++i)
    {
        m1.lock();
        m2.lock();
        m1.unlock();
        m2.unlock();
    }
}

int main()
{
    std::thread t1(func1);
    std::thread t2(func2);

    t1.join();
    t2.join();

    std::cout << "finish" << std::endl;
}
