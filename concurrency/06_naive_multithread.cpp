
//
// Created by Yao on 2023/10/24.
// Description:
//

#include <chrono>
#include <cmath>
#include <iostream>
#include <mutex>
#include <thread>
#include <vector>
using namespace std;

static const int MAX = 10e8; // ①
static double sum = 0;       // ②

void worker(int min, int max)
{ // ③
    for (int i = min; i <= max; i++)
    {
        sum += sqrt(i);
    }
}

/*
 * 单线程
 */
void serial_task(int min, int max)
{ // ④
    auto start_time = chrono::steady_clock::now();
    sum = 0;
    worker(0, MAX);
    auto end_time = chrono::steady_clock::now();
    auto ms = chrono::duration_cast<chrono::milliseconds>(end_time - start_time).count();
    cout << "Serial task finish, " << ms << " ms consumed, Result: " << sum << endl;
}

/*
 * 多线程
 * 错误版本：没有对临界区进行数据保护
 */
void concurrent_task(int min, int max)
{
    auto start_time = chrono::steady_clock::now();

    unsigned concurrent_count = thread::hardware_concurrency();
    cout << "hardware_concurrency: " << concurrent_count << endl;
    vector<thread> threads;
    min = 0;
    sum = 0;
    for (int t = 0; t < concurrent_count; t++)
    {
        int range = max / concurrent_count * (t + 1);
        threads.push_back(thread(worker, min, range));
        min = range + 1;
    }
    for (auto &t : threads)
    {
        t.join();
    }

    auto end_time = chrono::steady_clock::now();
    auto ms = chrono::duration_cast<chrono::milliseconds>(end_time - start_time).count();
    cout << "Concurrent task finish, " << ms << " ms consumed, Result: " << sum << endl;
}
int main()
{
    serial_task(0, MAX);

    concurrent_task(0, MAX);

    return 0;
}
