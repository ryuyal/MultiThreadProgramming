
//
// Created by Yao on 2023/10/24.
// Description:     
//

#include <iostream>
#include<mutex>
#include<string>
#include<set>
#include<thread>
using namespace std;

class Account {
public:
    Account(string name, double money): mName(name), mMoney(money) {};

public:
    void changeMoney(double amount) {
        mMoney += amount;
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
};

class Bank {
public:
    void addAccount(Account* account) {
        mAccounts.insert(account);
    }

    // 转账操作
    bool transferMoney(Account* accountA, Account* accountB, double amount) {
        lock_guard guardA(*accountA->getLock());
        lock_guard guardB(*accountB->getLock());

        if (amount > accountA->getMoney()) {
            return false;
        }

        accountA->changeMoney(-amount);
        accountB->changeMoney(amount);
        return true;
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

void randomTransfer(Bank* bank, Account* accountA, Account* accountB) {
    while(true) {
        double randomMoney = ((double)rand() / RAND_MAX) * 100;
        if (bank->transferMoney(accountA, accountB, randomMoney)) {
            cout << "Transfer " << randomMoney << " from " << accountA->getName()
                 << " to " << accountB->getName()
                 << ", Bank totalMoney: " << bank->totalMoney() << endl;
        } else {
            cout << "Transfer failed, "
                 << accountA->getName() << " has only $" << accountA->getMoney() << ", but "
                 << randomMoney << " required" << endl;
        }
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
    thread t2(randomTransfer, &aBank, &a, &b);

    t1.join();
    t2.join();

    return 0;
}
