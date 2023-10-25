
//
// Created by Yao on 2023/10/24.
// Description:
//

#include <iostream>
#include <thread>
using namespace std;

int main()
{
    thread t([] { cout << "Hello World from lambda thread." << endl; });

    t.join(); // 等待线程完成其执行

    return 0;
}
