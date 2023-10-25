
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

static const int MAX = 10e8;
static double sum = 0;

static mutex exclusive;

void concurrent_worker(int min, int max)
{
    double temp_sum = 0;
    for (int i = min; i <= max; i++)
    {

        temp_sum += sqrt(i);
    }

    exclusive.lock();
    sum += temp_sum;
    exclusive.unlock();
}

/*
 * 多线程
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
        threads.emplace_back(concurrent_worker, min, range);
        min = range + 1;
    }
    for (auto &t : threads)
    {
        t.join(); // ④
    }

    auto end_time = chrono::steady_clock::now();
    auto ms = chrono::duration_cast<chrono::milliseconds>(end_time - start_time).count();
    cout << "Concurrent task finish, " << ms << " ms consumed, Result: " << sum << endl;
}
int main()
{

    concurrent_task(0, MAX);

    return 0;
}
