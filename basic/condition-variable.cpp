
//
// Created by Yao on 2023/10/23.
// Description:
//

#include <condition_variable>
#include <iostream>
#include <mutex>
#include <queue>
#include <string>
#include <thread>

std::queue<int> g_queue;
std::condition_variable g_cv;
std::mutex mtx;
void Produce()
{
    for (int i = 0; i < 10; ++i)
    {
        std::unique_lock<std::mutex> lock1(mtx);
        g_queue.push(i);
        // 通知消费者来取任务
        g_cv.notify_one();
        std::cout << "Produce -> task " << i << std::endl;

        std::this_thread::sleep_for(std::chrono::microseconds(1000));
    }
}

void Consume()
{
    while (1)
    {
        std::unique_lock<std::mutex> lock2(mtx);
        g_cv.wait(lock2, []() { return !g_queue.empty(); });
        int value = g_queue.front();
        std::cout << "Consume -> task " << value << std::endl;
        g_queue.pop();
    }
}
int main()
{

    std::thread t1(Produce);
    std::thread t2(Consume);
    t1.join();
    t2.join();

    return 0;
}
