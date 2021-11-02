//main.cpp
#include <iostream>
#include "Savings.h"
#include "Checkings.h"
#include "Transaction.h"
#include <typeinfo>
int main()
{
    // Savings acc("Bob", 1000, 0.5f);
    // std::cout << "Initial Balance: " << acc.GetBalance() << std::endl;
    // acc.Deposit(200);
    // acc.AccumulateInterest();
    // acc.Withdraw(380);
    // std::cout << "Balance: " << acc.GetBalance() << std::endl;
    // std::cout << "-----------------" << std::endl;
    // Checkings acc2 ("Mark", 20);
    // std::cout << "Initial Balance" << acc2.GetBalance() << std::endl;
    // acc2.Withdraw(10);
    // acc2.Deposit(10);
    // acc2.Deposit(10);
    // acc2.Deposit(10);
    // acc2.Deposit(20);
    // acc2.Withdraw(30);
    // acc2.Withdraw(10);
    // acc2.Withdraw(10);
    // acc2.Withdraw(2);
    // std::cout << "Balance: " << acc2.GetBalance() << std::endl;

    // Checkings acc ("Bob", 100);
    // Transact(&acc);
    // Savings acc2 ("Mark", 100, 0.05f);
    // Transact(&acc2);
    // std::cout << "Size of account:" << sizeof(Account) << std::endl;

    // Let's instead create an object on the Heap:
    // Savings *acc = new Savings("Bob", 100, 0.5f);
    // delete acc;
    // We also know that a base class pointer or reference can point to any of its class objects. So instead of using Savings pointer here, let's use the Account pointer.
    // Account *acc = new Savings("Bob", 100, 0.5f);
    // delete acc;

    ///// Lecture 107 - Object Slicing
    // Checkings ch("Bob", 100);
    // Account *pAccount = &ch; //pointer
    // // Let's say we would like the child class object from this account pointer.
    // Checkings* pChecking = static_cast<Checkings*> (pAccount);
    // // this work fine!

    ////// Lecture 108: The typeID operator
    //Checkings ch ("Bob", 100);
    //Transact(&ch);

    // This will work fine! It shows the minimum balance is almost 50. The minimum balance of checking is 50.
    // But what if instead, we do this:
    Checkings sav( "Bob", 100);
    // Transact(&sav);

    // RTTI in C++ gives us an operator called TypeID.
    // The typeid operator returns the information of the type as an object of the type info class, and to access that information, we have to include the header file type info.

    // Let's test it out:
    // int f {};
    // float i{};
    // const std::type_info &type_i = typeid(sav); // #include <typeinfo>
    // // Check for equality.
    // if (type_i == typeid(Savings)) std::cout << "p is pointing to Savings object." << std::endl;
    // else std::cout << "Not a savings account." << std::endl;
    // std::cout << type_i.name() << std::endl ; // this method gives us a human readable name of the types

    // so using these comparison operators we can take a decision based on the type of object that the pointer is pointing at.

    ///// Lecture 109: Dynamic cast
    // Create a checkings object and pass it into TransacT().
    Savings ch ("Bob", 100,0.01f);
    // In this case, we're passing a checkings obkect by reference into the transact function and we are performing a cast to Checkings, so this will work.
    try{
        Transact(ch);
    }catch (std::exception &ex){
        std::cout << "Exception: " << ex.what() << std::endl;
    }
    return 0;
}
