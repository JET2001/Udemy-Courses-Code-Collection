// Checkings.h
#pragma once
#include "Account.h"
class Checkings : public Account
{
    float m_minBal{50.0f}; // to query this new variable from outside the class.
public:
    // C++11 : inheriting constructors
    using Account::Account; // this will cause all the constructors of the base to be inherited in the Checking class.
    // Checkings(const std::string& name, float balance); // so we no longer need a user defined constructor.
    ~Checkings();
    void Withdraw(float amt) override;
    float GetMinimumBalance() const; // to query this new variable from outside the class.
};
