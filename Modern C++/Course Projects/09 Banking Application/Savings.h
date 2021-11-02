// Savings.h
#pragma once
#include "Account.h"
// savings inherits from Account
class Savings : public Account {
    float m_Rate;

public:
    Savings(const std::string &name, float balance, float rate);
    // Not only must we initialise the data fields of this class,
    // we have to initialise the data fields of the base class too.
    // So the constructor needs to have those fields.
    // The user will have to specify the name, balance and rate.
    ~Savings();
    float GetInterestRate() const override;
    void AccumulateInterest() override;
};
