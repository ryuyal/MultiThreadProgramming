
//
// Created by Yao on 2023/10/24.
// Description:     
//

#include <iostream>
#include <thread>
using namespace std;

void hello(string name) {
    cout << "Welcome to " << name << endl;
}

int main() {
    thread t(hello, "https://github.com/ryuyal"); // 传递参数给入口函数hello
    t.join(); // 等待线程完成其执行

    return 0;
}

