// Checkings.cpp
// Constructor
#include <iostream>
#include "Checkings.h"
// Constructor
// Checkings::Checkings(const std::string& name, float balance): Account(name,balance){
//     std::cout << "Checkings(const std::string&, float)" << std::endl;
// } --> No longer needed, since we inherited the base :D
// Destructor
Checkings::~Checkings(){
    std::cout << "~Checkings()" << std::endl;
}

// Overrided methods
void Checkings::Withdraw(float amt)
{
    if (m_Balance - amt >= m_minBal)
        Account::Withdraw(amt); // Depend on your base class!!
        // In this way, a child class can call any of its base class member functions.
        // If the child class also contains a similar member function, we have to state the fully qualified name of the member function.
        // if we remove the scope resolution from Account, it may become a recursive call and it would result in undefined behaviour.
        // Don't repeat yourself.
    else {
        //Throw an exception instead of printing a message
        std::cout << "Invalid Amount" << std::endl;
    }
}
// Other methods
float Checkings::GetMinimumBalance() const {
    return m_minBal;
}
