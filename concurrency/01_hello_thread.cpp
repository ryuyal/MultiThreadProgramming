
//
// Created by Yao on 2023/10/24.
// Description:     
//

#include <iostream>
#include<thread>
using namespace std;

void hello(){
    cout << "Hello world from new thread" << endl;
}

int main() {
    thread t(hello); // 创建线程，指定入口函数为hello
    t.join(); // 等待线程完成其执行

    return 0;
}
