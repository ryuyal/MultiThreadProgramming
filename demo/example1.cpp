
//
// Created by Yao on 2023/10/23.
// Description: 计算[1, 10e8]范围内所有自然数的平方根之和
//
/*
 * 单线程模式
 */
//#include <iostream>
//#include<cmath>
//#include<chrono>
//using namespace std;
//
//static const int MAX = 10e8; // ①
//static double sum = 0; // ②
//
//void worker(int min, int max) { // ③
//    for (int i = min; i <= max; i++) {
//        sum += sqrt(i);
//    }
//}
//
//void serial_task(int min, int max) { // ④
//    auto start_time = chrono::steady_clock::now();
//    sum = 0;
//    worker(0, MAX);
//    auto end_time = chrono::steady_clock::now();
//    auto ms = chrono::duration_cast<chrono::milliseconds>(end_time - start_time).count();
//    cout << "Serail task finish, " << ms << " ms consumed, Result: " << sum << endl;
//}
//
//int main() {
//
//    serial_task(1, MAX);
//
//    return 0;
//}

/*
 * 多线程的方式
 */
#include<iostream>
#include<thread>
#include<vector>
#include<chrono>
#include<cmath>
#include<mutex>
using namespace std;

static const int MAX = 10e8;
static double sum = 0;

static mutex exclusive;

void concurrent_worker(int min, int max) {
    double tmp_sum = 0;
    for (int i = min; i <= max; i++) {

        tmp_sum += sqrt(i);

    }
    exclusive.lock(); // ①
    sum += tmp_sum;
    exclusive.unlock(); // ②
}

void concurrent_task(int min, int max) {
    auto start_time = chrono::steady_clock::now();

    unsigned concurrent_count = thread::hardware_concurrency();
    cout << "hardware_concurrency: " << concurrent_count << endl; // 获取硬件支持的并发线程数
    vector<thread> threads;
    min = 0;
    sum = 0;
    for (int t = 0; t < concurrent_count; t++) {
        int range = max / concurrent_count * (t + 1);
        threads.emplace_back(thread(concurrent_worker, min, range)); // ③
        min = range + 1;
    }
    for (int i = 0; i < threads.size(); i++) {
        threads[i].join();
    }

    auto end_time = chrono::steady_clock::now();
    auto ms = chrono::duration_cast<chrono::milliseconds>(end_time - start_time).count();
    cout << "Concurrent task finish, " << ms << " ms consumed, Result: " << sum << endl;
}

int main(){
    concurrent_task(1, MAX);
    return 0;
}

