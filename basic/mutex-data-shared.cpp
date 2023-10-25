
//
// Created by Yao on 2023/10/20.
// Description: 互斥量解决多线程数据共享问题
//

#include <iostream>
#include <mutex>
#include <thread>
using namespace std;

int shared_data = 0;
std::mutex mtx;

void func()
{
    for (int i = 0; i < 100000; ++i)
    {
        mtx.lock();
        shared_data += 1;
        mtx.unlock();
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
