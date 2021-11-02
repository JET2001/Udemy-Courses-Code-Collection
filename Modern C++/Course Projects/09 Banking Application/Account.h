#pragma once
#include <string>
class Account{
    // Attributes
    std::string m_Name;
    // float m_Balance; // shouldn't be private because we cannot access it in the child class.
    int m_AccNo;
    static int s_ANGenerator;
protected:
    float m_Balance;
public:
    Account(const std::string &name, float balance); // Constructor
    virtual ~Account();// Destructor
    // Base classes should always have a VIRTUAL destructor.
    // Get methods
    const std::string GetName() const;
    float GetBalance() const;
    int GetAccountNo() const;
    // Note that all the getter functions are qualified by the const keyword, and you already know that any function that does not modify the state of the class object should ALWAYS be marked as const.
    // Let's add the rest of the functions, and we'll generate the definitions of these functions.
    // Set methods

    // methods
    // Account.h
    virtual void AccumulateInterest();
    virtual void Withdraw(float amt);
    void Deposit(float amt);
    virtual float GetInterestRate() const;
    // This function would return the interest rate of the Account.
    // We will also modify the constructor to accept the arguments from outside. So first, would be the name of the Account holder, the second
};
