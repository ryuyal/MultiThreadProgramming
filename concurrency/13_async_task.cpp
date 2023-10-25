
//
// Created by Yao on 2023/10/24.
// Description:
//

/*
 * 通过函数指定异步任务
 */
/*#include <iostream>
#include<cmath>
#include<future>
using namespace std;

static const int MAX = 10e8;
static double sum = 0;

void worker(int min, int max) {
    for (int i = min; i <= max; i++) {
        sum += sqrt(i);
    }
}

int main() {
    sum = 0;
    auto start = chrono::system_clock::now();
    auto f1 = async(worker, 0, MAX);
    cout << "Async task triggered" << endl;
    f1.wait(); // 等待任务执行完成
    cout << "Async task finish, result: " << sum << endl << endl;
    auto end = chrono::system_clock::now();

    auto duration =chrono::duration_cast<chrono::milliseconds>(end - start).count();
    cout << "Time duration = " << duration << "ms" << endl;
    return 0;
}*/

/*
 * 通过lambda表达式指定
 */

/*#include<iostream>
#include<chrono>
#include<cmath>
#include<future>
#include<thread>
using namespace std;

static const int MAX = 10e8;

int main(){
    auto start = chrono::system_clock::now();
    double result = 0;
    cout << "Async task with lambda triggered thread: " << this_thread::get_id() << endl;

    // launch::async明确指定要通过独立的线程来执行任务
    auto f2 = async(launch::async, [&result](){
        cout << "Lambda task in thread: " << this_thread::get_id() << endl;
        for (int i = 0; i <= MAX; ++i) {
            result += sqrt(i);
        }
    });

    f2.wait();

    cout << "Async task with lambda finish, result: " << result << endl << endl;

    auto end = chrono::system_clock::now();
    auto duration =chrono::duration_cast<chrono::milliseconds>(end - start).count();
    cout << "Time duration = " << duration << "ms" << endl;

    return 0;
}*/

/*
 * 面向对象
 */
#include <chrono>
#include <cmath>
#include <future>
#include <iostream>
#include <thread>
using namespace std;

static const int MAX = 10e8;

class Worker
{
  public:
    Worker(int min, int max) : mMin(min), mMax(max)
    {
    }
    double work()
    {
        mResult = 0;
        for (int i = mMin; i <= mMax; i++)
        {
            mResult += sqrt(i);
        }
        return mResult;
    }
    double getResult()
    {
        return mResult;
    }

  private:
    int mMin;
    int mMax;
    double mResult;
};

int main()
{
    Worker w(0, MAX);
    cout << "Task in class triggered" << endl;
    auto f3 = async(&Worker::work, &w); // 请注意这里是&w，因此传递的是对象的指针。如果不写&将传入w对象的临时复制。
    f3.wait();
    cout << "Task in class finish, result: " << w.getResult() << endl << endl;

    return 0;
}
