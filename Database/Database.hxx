#ifndef DATABASE_HXX
#define DATABASE_HXX


#include <List.hxx>
#include <TradeOperation.hxx>
#include <Filer.hxx>
#include <iostream>
#include <Crypter.hxx>
#include <ctime>
#include <algorithm>


class Database {
protected:
    Filer file;
    std::string filename;
    std::string filename_enc;
    List<TradeOperation> data;
    Crypter crypter;
    
public:
    Database(void);
    Database(const std::string& filename);
    Database(const List<TradeOperation>& unit, const std::string& filename);
    Database(const Database& unit);
    ~Database(void);
    
    Database& operator=(const Database& unit) noexcept;
    TradeOperation& operator[](const unsigned int index) noexcept;
    friend std::ostream& operator<<(std::ostream& os, const Database& unit);
    const TradeOperation& operator[](const unsigned int index) const noexcept;
    
    void append(const TradeOperation& unit) noexcept;
    void remove(const unsigned int index) noexcept;
    unsigned int size() noexcept;
    
    unsigned int getStockQuantity(const std::string& article, const std::tm& date) const noexcept;
    List<TradeOperation> getShippedProducts(const std::tm& date) const noexcept;
    double calculateSupplierInventoryValue(const std::string& supplier) const noexcept;
};


#endif // DATABASE_HXX