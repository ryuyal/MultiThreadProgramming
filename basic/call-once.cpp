
//
// Created by Yao on 2023/10/23.
// Description:
//
/*
 * 饿汉模式：类产生的时候就创建好实例对象
 */
// #include<iostream>
// class Singleton {
// public:
//     static Singleton * GetInstance() {
//         return singleton_;
//     }
//
//     static void DestroyInstance() {
//         if (!singleton_ ) {
//             delete singleton_;
//         }
//     }
//
// private:
//     // 防止外部构造。
//     Singleton() = default;
//
//     // 防止拷贝和赋值。
//     Singleton& operator=(const Singleton&) = delete;
//     Singleton(const Singleton& singleton2) = delete;
//
// private:
//     static Singleton* singleton_;
// };
//
// Singleton* Singleton::singleton_ = new Singleton;
//
// int main() {
//     Singleton* s1 = Singleton::GetInstance();
//     std::cout << s1 << std::endl;
//
//     Singleton* s2 = Singleton::GetInstance();
//     std::cout << s2 << std::endl;
//
//     Singleton::DestroyInstance();
//
//     return 0;
// }

/*
 * 懒汉模式：在需要的时候，才创建对象
 * 延迟构造对象，在第一次使用该对象的时候才进行new该对象
 * Double-Checked Locking Pattern (DCLP)
 */
// #include <iostream>
// #include <mutex>
//
// class Singleton {
// public:
//     static Singleton* GetInstance() {
//         // Double-Checked Locking Pattern (DCLP)
//         if (instance_ == nullptr) {
//             std::lock_guard<std::mutex> lock(mutex_);
//             if (instance_ == nullptr) {
//                 instance_ = new Singleton;
//             }
//         }
//
//         return instance_;
//     }
//
//     ~Singleton() = default;
//
//     // 释放资源。
//     void Destroy() {
//         if (instance_ != nullptr) {
//             delete instance_;
//             instance_ = nullptr;
//         }
//     }
//
//     void PrintAddress() const {
//         std::cout << this << std::endl;
//     }
//
// private:
//     Singleton() = default;
//
//     Singleton(const Singleton&) = delete;
//     Singleton& operator=(const Singleton&) = delete;
//
// private:
//     static Singleton* instance_;
//     static std::mutex mutex_;
// };
//
// Singleton* Singleton::instance_ = nullptr;
// std::mutex Singleton::mutex_;
//
// int main() {
//     Singleton* s1 = Singleton::GetInstance();
//     s1->PrintAddress();
//
//     Singleton* s2 = Singleton::GetInstance();
//     s2->PrintAddress();
//
//     return 0;
// }

/*
 * call_once实现单例
 */
#include <iostream>
#include <memory>
#include <mutex>

class Singleton
{
  public:
    static Singleton &GetInstance()
    {
        static std::once_flag s_flag;
        std::call_once(s_flag, [&]() { instance_.reset(new Singleton); });

        return *instance_;
    }

    ~Singleton() = default;

    void PrintAddress() const
    {
        std::cout << this << std::endl;
    }

  private:
    Singleton() = default;

    Singleton(const Singleton &) = delete;
    Singleton &operator=(const Singleton &) = delete;

  private:
    static std::unique_ptr<Singleton> instance_;
};

std::unique_ptr<Singleton> Singleton::instance_;

int main()
{
    Singleton &s1 = Singleton::GetInstance();
    s1.PrintAddress();

    Singleton &s2 = Singleton::GetInstance();
    s2.PrintAddress();

    return 0;
}
