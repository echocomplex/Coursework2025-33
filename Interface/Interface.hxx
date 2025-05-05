#ifndef INTERFACE_HXX
#define INTERFACE_HXX

#include <iostream>
#include <TradeOperation.hxx>
#include <List.hxx>
#include <Database.hxx>
#include <ctime>
#include <stdio.h>

class Interface {
private:
    Database db;
    void displayMenu(void);
    void getTradeOperation(TradeOperation& op);
    int removeOperation(void);
    void clearInputBuffer(void);
    std::tm getDateFromInput(const std::string& prompt);
    
public:
    Interface(void) = default;
    Interface(const Interface&) = delete;
    Interface& operator=(const Interface&) = delete;
    ~Interface(void) noexcept = default;
    void run(void);
};

#endif // INTERFACE_HXX