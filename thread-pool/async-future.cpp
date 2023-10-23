
//
// Created by Yao on 2023/10/23.
// Description:     
//

#include <iostream>
#include <future>
#include<thread>
int calculate() {
    int i = 0;
    for (i = 0; i < 1000; ++i) {
        i++;
    }
    return i;
    /*// 模拟一个耗时的计算
    std::this_thread::sleep_for(std::chrono::seconds(1));
    return 42;*/
}
/*
 * async-future
 */
/*int main() {
    std::future<int> future_result
            = std::async(std::launch::async, calculate);
    std::cout << calculate << std::endl;
    // 在这里可以做其他的事情
    int result = future_result.get(); // 获取异步操作的结果
    std::cout << result << std::endl; // 输出42
    return 0;
}*/

/*
 * packaged_task
 */
/*int main(){
    std::packaged_task<int()> task(calculate);

    auto future_result = task.get_future();
    std::thread t1(std::move(task));
    t1.join();
    std::cout << future_result.get() << std::endl;

    return 0;
}*/

/*
 * promise
 */
void func(std::promise<int>& f){
    f.set_value(1999);

}
int main(){
    std::promise<int> f;
    auto future_result = f.get_future();
    std::thread t1(func, std::ref(f));
    t1.join();
    std::cout << future_result.get() << std::endl;

    return 0;
}

