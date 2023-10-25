//
// Created by Yao on 2023/10/20.
// Description:
//      线程库的基本使用
//
#include <iostream>
#include <string>
#include <thread>

void printHelloWorld()
{
    std::cout << "Hello World" << std::endl;
}

void printMessage(std::string message)
{
    std::cout << message << std::endl;
}

int main()
{
    // 1. 创建线程
    std::thread thread1(printHelloWorld);
    //    thread1.join();
    //    thread1.detach();
    bool isJoin = thread1.joinable(); // 更严谨的判断线程是否可以使用join
    if (isJoin)
    {
        thread1.join();
    }

    // 给线程函数传递参数
    std::thread thread2(printMessage, "Hello Thread");
    //    thread2.join();
    //    thread2.detach();
    isJoin = thread2.joinable();
    if (isJoin)
    {
        thread2.join();
    }

    return 0;
}
