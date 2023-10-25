
//
// Created by Yao on 2023/10/24.
// Description:
//

#include <iostream>
#include <mutex>
#include <set>
#include <string>
#include <thread>
using namespace std;

class Account
{
  public:
    Account(string name, double money) : mName(name), mMoney(money){};

  public:
    void changeMoney(double amount)
    {
        mMoney += amount;
    }
    string getName()
    {
        return mName;
    }
    double getMoney()
    {
        return mMoney;
    }
    mutex *getLock()
    {
        return &mMoneyLock;
    }

  private:
    string mName;
    double mMoney;
    mutex mMoneyLock;
};

class Bank
{
  public:
    void addAccount(Account *account)
    {
        mAccounts.insert(account);
    }

    // 转账操作
    /*
     * 1 2 3的操作是等价的
     */
    bool transferMoney(Account *accountA, Account *accountB, double amount)
    {
        /*
         */
        /*
         * 1. 使用lock_guard
         *//*

        // lock函数来获取两把锁，标准库的实现会保证不会发生死锁
        lock(*accountA->getLock(), *accountB->getLock());

        // lock_guard会在自身对象生命周期的范围内锁定互斥体即可
        lock_guard lg1(*accountA->getLock(), adopt_lock);
        lock_guard lg2(*accountB->getLock(), adopt_lock);

        */
        /*
         * 2. unique_lock等价写法
         *//*

        unique_lock ul1(*accountA->getLock(), defer_lock);
        unique_lock ul2(*accountB->getLock(), defer_lock);
        lock(*accountA->getLock(), *accountB->getLock());
*/

        /*
         * 3. scoped_lock 等价写法
         */
        scoped_lock lockAll(*accountA->getLock(), *accountB->getLock());

        if (amount > accountA->getMoney())
        {
            return false;
        }

        accountA->changeMoney(-amount);
        accountB->changeMoney(amount);
        return true;
    }

    double totalMoney() const
    {
        double sum = 0;
        for (auto a : mAccounts)
        {
            sum += a->getMoney();
        }
        return sum;
    }

  private:
    set<Account *> mAccounts;
};

mutex sCoutLock;
void randomTransfer(Bank *bank, Account *accountA, Account *accountB)
{
    while (true)
    {
        double randomMoney = ((double)rand() / RAND_MAX) * 100;
        if (bank->transferMoney(accountA, accountB, randomMoney))
        {
            sCoutLock.lock();
            cout << "Transfer " << randomMoney << " from " << accountA->getName() << " to " << accountB->getName()
                 << ", Bank totalMoney: " << bank->totalMoney() << endl;
            sCoutLock.unlock();
        }
        else
        {
            sCoutLock.lock();
            cout << "Transfer failed, " << accountA->getName() << " has only $" << accountA->getMoney() << ", but "
                 << randomMoney << " required" << endl;
            sCoutLock.unlock();
        }
    }
}

int main()
{
    Account a("yao", 100);
    Account b("elena", 200);

    Bank aBank;
    aBank.addAccount(&a);
    aBank.addAccount(&b);

    // 创建两个线程，互相在两个账号之间来回转账
    thread t1(randomTransfer, &aBank, &a, &b);
    thread t2(randomTransfer, &aBank, &b, &a);

    t1.join();
    t2.join();

    return 0;
}
