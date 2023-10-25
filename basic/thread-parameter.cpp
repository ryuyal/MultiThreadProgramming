//
// Created by Yao on 2023/10/20.
// Description:
//      线程函数中数据未定义错误
//

#include <iostream>
#include <thread>

/*
 * 传递临时变量的问题—使用std::ref() 传递引用类型
 */
/*void foo(int & x){
    x += 1;
    std::cout << "In thread t : x = " << x << std::endl;
}

int main() {
    int a = 1;
//    std::thread t(foo, a); // Compile error
    std::thread t(foo, std::ref(a));
    t.join();

    std::cout << "In thread main : a = " << a << std::endl;

    return 0;
}*/

/*
 * 传递指针或引用指向局部变量的问题
 */
/*
std::thread t;

void foo(int & x){
    x += 1;
    std::cout << "In thread t : x = " << x << std::endl;
}
int a = 1;
void test(){
//    int a = 1; // a是局部变量 只在test函数中局部有效 // test执行完毕后 a被释放掉 所以t.join()找不到a的引用
    t = std::thread(foo,std::ref(a));

}
int main() {
    test();
    t.join();

    std::cout << "In thread main : a = " << a << std::endl;

    return 0;
}
*/

/*
 * 传递指针或引用指向已经释放的内存问题
 */
/* void foo(int * x){
    std::cout << "In thread t : x = " << *x << std::endl;
}

int main() {
    int * ptr = new int(1);
    std::thread t(foo, ptr);

    delete ptr; // 手动释放

    t.join();

    std::cout << "In thread main : a = " << *ptr << std::endl; // ptr野指针
    return 0;
}*/

/*
 * 类成员函数作为入口函数，类对象被提前释放——使用智能指针
 */
/*#include<memory>
class A{
public:
    void foo(){
        std::cout << "Hello" << std::endl;
    }
};

int main(){
    std::shared_ptr<A> a = std::make_shared<A>();

    std::thread t(&A::foo, a);

    t.join();
}*/

/*
 * 入口函数为类的私有成员函数
 */
#include <memory>
class A
{
  private:
    friend void thread_foo(); // 友元
    void foo()
    {
        std::cout << "Hello" << std::endl;
    }
};

void thread_foo()
{
    std::shared_ptr<A> a = std::make_shared<A>();
    std::thread t(&A::foo, a);
    t.join();
}
int main()
{
    thread_foo();
}