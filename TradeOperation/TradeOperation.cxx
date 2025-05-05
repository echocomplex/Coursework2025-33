#include "TradeOperation.hxx"
#include <iomanip>

TradeOperation::TradeOperation(void) noexcept {
    this->purchase_price = 0.0;
    this->purchase_quantity = 0;
    this->retail_price = 0.0;
    this->purchase_date = {};
    this->sale_date = {};
}

TradeOperation::TradeOperation(const std::string& article, const std::string& product_name, 
                             const std::string& supplier, double purchase_price, 
                             const std::tm& purchase_date, unsigned int purchase_quantity,
                             const std::string& store_number, const std::string& store_address,
                             const std::tm& sale_date, double retail_price) noexcept {
    this->article = article;
    this->product_name = product_name;
    this->supplier = supplier;
    this->purchase_price = purchase_price;
    this->purchase_date = purchase_date;
    this->purchase_quantity = purchase_quantity;
    this->store_number = store_number;
    this->store_address = store_address;
    this->sale_date = sale_date;
    this->retail_price = retail_price;
}

TradeOperation& TradeOperation::operator=(const TradeOperation& unit) noexcept {
    this->article = unit.article;
    this->product_name = unit.product_name;
    this->supplier = unit.supplier;
    this->purchase_price = unit.purchase_price;
    this->purchase_date = unit.purchase_date;
    this->purchase_quantity = unit.purchase_quantity;
    this->store_number = unit.store_number;
    this->store_address = unit.store_address;
    this->sale_date = unit.sale_date;
    this->retail_price = unit.retail_price;
    return *this;
}

std::ostream& operator<<(std::ostream& os, const TradeOperation& unit) {
    auto printDate = [&os](const std::tm& date) {
        os << std::setfill('0') << std::setw(2) << date.tm_mday << "."
           << std::setw(2) << (date.tm_mon + 1) << "." << (date.tm_year + 1900);
    };
    
    os << unit.article << ", " << unit.product_name << ", " << unit.supplier << ", "
       << unit.purchase_price << ", ";
    printDate(unit.purchase_date);
    os << ", " << unit.purchase_quantity << ", " << unit.store_number << ", "
       << unit.store_address << ", ";
    printDate(unit.sale_date);
    os << ", " << unit.retail_price;
    
    return os;
}

std::string TradeOperation::getArticle(void) const noexcept {
    return this->article;
}

std::string TradeOperation::getProductName(void) const noexcept {
    return this->product_name;
}

std::string TradeOperation::getSupplier(void) const noexcept {
    return this->supplier;
}

double TradeOperation::getPurchasePrice(void) const noexcept {
    return this->purchase_price;
}

std::tm TradeOperation::getPurchaseDate(void) const noexcept {
    return this->purchase_date;
}

unsigned int TradeOperation::getPurchaseQuantity(void) const noexcept {
    return this->purchase_quantity;
}

std::string TradeOperation::getStoreNumber(void) const noexcept {
    return this->store_number;
}

std::string TradeOperation::getStoreAddress(void) const noexcept {
    return this->store_address;
}

std::tm TradeOperation::getSaleDate(void) const noexcept {
    return this->sale_date;
}

double TradeOperation::getRetailPrice(void) const noexcept {
    return this->retail_price;
}

void TradeOperation::setArticle(const std::string& article) noexcept {
    this->article = article;
}

void TradeOperation::setProductName(const std::string& product_name) noexcept {
    this->product_name = product_name;
}

void TradeOperation::setSupplier(const std::string& supplier) noexcept {
    this->supplier = supplier;
}

void TradeOperation::setPurchasePrice(double purchase_price) noexcept {
    this->purchase_price = purchase_price;
}

void TradeOperation::setPurchaseDate(const std::tm& purchase_date) noexcept {
    this->purchase_date = purchase_date;
}

void TradeOperation::setPurchaseQuantity(unsigned int purchase_quantity) noexcept {
    this->purchase_quantity = purchase_quantity;
}

void TradeOperation::setStoreNumber(const std::string& store_number) noexcept {
    this->store_number = store_number;
}

void TradeOperation::setStoreAddress(const std::string& store_address) noexcept {
    this->store_address = store_address;
}

void TradeOperation::setSaleDate(const std::tm& sale_date) noexcept {
    this->sale_date = sale_date;
}

void TradeOperation::setRetailPrice(double retail_price) noexcept {
    this->retail_price = retail_price;
}

double TradeOperation::calculateProfit() const noexcept {
    if (!isSold()) return 0.0;
    return (retail_price - purchase_price) * purchase_quantity;
}

bool TradeOperation::isSold() const noexcept {
    return sale_date.tm_year != 0; 
}