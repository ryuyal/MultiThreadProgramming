
//
// Created by Yao on 2023/10/23.
// Description:     
//

#include <atomic>
#include <iostream>
#include <thread>
std::atomic<int> count = 0; // 相比于加锁的方式，atomic更高效
void increment() {
    for (int i = 0; i < 1000000; ++i) {
        count++;
    }
}
int main() {
    std::thread t1(increment);
    std::thread t2(increment);
    t1.join();
    t2.join();
    std::cout << count << std::endl;
    return 0;
}
