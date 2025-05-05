#ifndef TRADEOPERATION_HXX
#define TRADEOPERATION_HXX

#include <string>
#include <iostream>
#include <ctime>

class TradeOperation {
private:
    std::string article;
    std::string product_name;
    std::string supplier;
    double purchase_price;
    std::tm purchase_date;
    unsigned int purchase_quantity;
    std::string store_number;
    std::string store_address;
    std::tm sale_date;
    double retail_price;
    
public:
    TradeOperation(void) noexcept;
    TradeOperation(const std::string& article, const std::string& product_name, 
                  const std::string& supplier, double purchase_price, 
                  const std::tm& purchase_date, unsigned int purchase_quantity,
                  const std::string& store_number, const std::string& store_address,
                  const std::tm& sale_date, double retail_price) noexcept;
    ~TradeOperation(void) noexcept = default;
    TradeOperation& operator=(const TradeOperation& unit) noexcept;
    friend std::ostream& operator<<(std::ostream& os, const TradeOperation& unit);
    std::string getArticle(void) const noexcept;
    std::string getProductName(void) const noexcept;
    std::string getSupplier(void) const noexcept;
    double getPurchasePrice(void) const noexcept;
    std::tm getPurchaseDate(void) const noexcept;
    unsigned int getPurchaseQuantity(void) const noexcept;
    std::string getStoreNumber(void) const noexcept;
    std::string getStoreAddress(void) const noexcept;
    std::tm getSaleDate(void) const noexcept;
    double getRetailPrice(void) const noexcept;
    void setArticle(const std::string& article) noexcept;
    void setProductName(const std::string& product_name) noexcept;
    void setSupplier(const std::string& supplier) noexcept;
    void setPurchasePrice(double purchase_price) noexcept;
    void setPurchaseDate(const std::tm& purchase_date) noexcept;
    void setPurchaseQuantity(unsigned int purchase_quantity) noexcept;
    void setStoreNumber(const std::string& store_number) noexcept;
    void setStoreAddress(const std::string& store_address) noexcept;
    void setSaleDate(const std::tm& sale_date) noexcept;
    void setRetailPrice(double retail_price) noexcept;
    double calculateProfit() const noexcept;
    bool isSold() const noexcept;
};

#endif // TRADEOPERATION_HXX