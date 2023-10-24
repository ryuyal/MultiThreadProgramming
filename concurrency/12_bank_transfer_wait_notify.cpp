
//
// Created by Yao on 2023/10/24.
// Description:     
//

#include <iostream>
#include<mutex>
#include<string>
#include<set>
#include<thread>
#include<condition_variable>
using namespace std;

class Account {
public:
    Account(string name, double money): mName(name), mMoney(money) {};

public:
    void changeMoney(double amount) {
        unique_lock lock1(mMoneyLock);
        mConditionVar.wait(lock1, [this, amount] {
            return mMoney + amount > 0;
        });
        mMoney += amount;
        mConditionVar.notify_all();
    }
    string getName() {
        return mName;
    }
    double getMoney() {
        return mMoney;
    }
    mutex* getLock() {
        return &mMoneyLock;
    }

private:
    string mName;
    double mMoney;
    mutex mMoneyLock;
    condition_variable mConditionVar;
};

class Bank {
public:
    void addAccount(Account* account) {
        mAccounts.insert(account);
    }

    void transferMoney(Account* accountA, Account* accountB, double amount) {
        accountA->changeMoney(-amount);
        accountB->changeMoney(amount);
    }

    double totalMoney() const {
        double sum = 0;
        for (auto a : mAccounts) {
            sum += a->getMoney();
        }
        return sum;
    }

private:
    set<Account*> mAccounts;
};

mutex sCoutLock;
void randomTransfer(Bank* bank, Account* accountA, Account* accountB) {
    while(true) {
        double randomMoney = ((double)rand() / RAND_MAX) * 100;
        {
            lock_guard guard(sCoutLock);
            cout << "Try to Transfer " << randomMoney
                 << " from " << accountA->getName() << "(" << accountA->getMoney()
                 << ") to " << accountB->getName() << "(" << accountB->getMoney()
                 << "), Bank totalMoney: " << bank->totalMoney() << endl;
        }
        bank->transferMoney(accountA, accountB, randomMoney);
    }
}

int main() {
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
