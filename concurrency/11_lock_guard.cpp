
//
// Created by Yao on 2023/10/24.
// Description:
//

#include <iostream>
#include <mutex>
#include <thread>

int g_i = 0;
std::mutex g_i_mutex;

void safe_increment()
{
    // 在safe_increment方法结束的时候，局部变量std::lock_guard<std::mutex> aLock会被销毁，它对互斥体的锁定也就解除了
    std::lock_guard<std::mutex> aLock(g_i_mutex);
    ++g_i;

    std::cout << "thread " << std::this_thread::get_id() << ": " << g_i << std::endl;
}

int main()
{
    std::cout << "main: " << g_i << std::endl;

    std::thread t1(safe_increment);
    std::thread t2(safe_increment);

    t1.join();
    t2.join();

    std::cout << "main: " << g_i << std::endl;
}
