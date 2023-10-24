
//
// Created by Yao on 2023/10/24.
// Description:     
//

#include <iostream>
#include<thread>
#include<mutex>

using namespace std;
void init() {
    cout << "Initialing..." << endl;
    // Do something...
}

void worker(once_flag * flag) {
    call_once(*flag, init);
}

int main() {
    once_flag flag;

    // 有些任务需要执行一次，并且只希望它执行一次，例如资源的初始化任务
    /*
     * 下面有三个线程都会使用init函数，但是只会有一个线程真正执行它。
     */
    thread t1(worker, &flag);
    thread t2(worker, &flag);
    thread t3(worker, &flag);

    t1.join();
    t2.join();
    t3.join();

    return 0;
}
