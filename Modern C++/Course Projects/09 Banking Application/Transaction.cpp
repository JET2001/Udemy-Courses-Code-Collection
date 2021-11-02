// Transaction.cpp
#include <iostream> // to log transactions
#include "Transaction.h"
// We want to first check what is the Minimum balance of the checking account, for this - we'll have to invoke the GetMinimumBalance() of Checkings.
// If we try to invoke that from Account ptr, we cannot because the function GetMinimumBalance() is not part of the Account class, that is why we will have to apply a down cast on the account_ptr and get the checking pointer, then through that pointer we can invoke GetMinimumBalance() function.

// Let's create a pointer of checkings: and for this to work we'll have to include the header filde for Checkings:
#include "Checkings.h"
#include <typeinfo>
// So you see a dependency on the checking header file is created here, and this Transact() function is exposed to the child classes. And from a Design perspective, this violates the DIP.
void Transact(Account *pAccount)
{
    std::cout << "Transaction started" << std::endl;
    std::cout << "Initial Balance:" << pAccount->GetBalance() << std::endl;
    pAccount->Deposit(100);
    pAccount->AccumulateInterest();
    // Checkings * pChecking = static_cast<Checkings*> (pAccount);
    // Suppose we write some code to check minimum balance before we start withdrawal:
    // if (typeid(*pAccount) == typeid(Checkings))
    // {
    //     Checkings* pChecking = static_cast<Checkings*> (pAccount);
    //     std::cout << "Minimum Balance of Checking: " << pChecking->GetMinimumBalance() << std::endl;
    // } // so these lines of code will only be executed if this was a Checking object. // Replaced with Dynamic cast in lecture 110
    Checkings *pChecking = dynamic_cast<Checkings*> (pAccount);
    if (pChecking != nullptr){
        std::cout << "Minimum Balance of Checking: " << pChecking->GetMinimumBalance() << std::endl;
    }
    pAccount->Withdraw(170);
    std::cout << "Interest Rate: " << pAccount->GetInterestRate() << std::endl;
    std::cout << "Final Balance: " << pAccount->GetBalance() << std::endl;
}

void Transact(Account &pAccount)
{
    std::cout << "Transaction started" << std::endl;
    std::cout << "Initial Balance:" << pAccount.GetBalance() << std::endl;
    pAccount.Deposit(100);
    pAccount.AccumulateInterest();
    // Checkings * pChecking = static_cast<Checkings*> (pAccount);
    // Suppose we write some code to check minimum balance before we start withdrawal:
    // if (typeid(*pAccount) == typeid(Checkings))
    // {
    //     Checkings* pChecking = static_cast<Checkings*> (pAccount);
    //     std::cout << "Minimum Balance of Checking: " << pChecking->GetMinimumBalance() << std::endl;
    // } // so these lines of code will only be executed if this was a Checking object. // Replaced with Dynamic cast in lecture 110
    Checkings &pChecking = dynamic_cast<Checkings&> (pAccount);
    std::cout << "Minimum Balance of Checking: " << pChecking.GetMinimumBalance() << std::endl;
    pAccount.Withdraw(170);
    std::cout << "Interest Rate: " << pAccount.GetInterestRate() << std::endl;
    std::cout << "Final Balance: " << pAccount.GetBalance() << std::endl;
}
