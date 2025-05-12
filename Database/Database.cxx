#include "Database.hxx"

Database::Database(void) {
    this->filename = "database.txt";
    this->filename_enc = "database.enc";
    this->crypter.decrypt(this->filename_enc, this->filename);
    this->file.open(this->filename, true);
    this->file.readToList(this->data);
}

Database::Database(const std::string& filename) {
    this->filename = filename + ".txt";
    this->filename_enc = filename + ".enc";
    this->crypter.encrypt(this->filename_enc, this->filename);
    this->file.open(filename);
    this->file.readToList(this->data);
}

Database::Database(const List<TradeOperation>& unit, const std::string& filename) {
    this->data = unit;
    this->filename = filename + ".txt";
    this->filename_enc = filename + ".enc";
    this->file.open(this->filename);
}

Database::Database(const Database& unit) {
    this->data = unit.data;
    this->file.open(unit.filename);
    this->filename = unit.filename;
    this->filename_enc = unit.filename_enc;
}

Database::~Database(void) {
    this->file.rewriteFromList(this->data);
    this->crypter.encrypt(this->filename, this->filename_enc);
}

Database& Database::operator=(const Database& unit) noexcept {
    if (this == &unit) return *this;
    this->data = unit.data;
    this->filename = unit.filename;
    this->filename_enc = unit.filename_enc;
    this->file.open(unit.filename);
    return *this;
}

TradeOperation& Database::operator[](const unsigned int index) noexcept {
    return this->data[index];
}

std::ostream& operator<<(std::ostream& os, const Database& unit) {
    for (unsigned int i = 0; i < unit.data.length(); ++i) {
        os << i + 1 << ' ' << unit[i] << std::endl;
    }
    return os;
}

const TradeOperation& Database::operator[](const unsigned int index) const noexcept {
    return this->data[index];
}

void Database::append(const TradeOperation& unit) noexcept {
    this->data.append(unit);
}

void Database::remove(const unsigned int index) noexcept {
    this->data.remove(index);
}

unsigned int Database::size() noexcept {
    return this->data.length();
}

unsigned int Database::getStockQuantity(const std::string& article, const std::tm& date) const noexcept {
    unsigned int total = 0;
    
    for (unsigned int i = 0; i < this->data.length(); ++i) {
        const TradeOperation& op = this->data[i];
        
        std::tm purchaseDate = op.getPurchaseDate();
        std::tm saleDate = op.getSaleDate();
        
        if (op.getArticle() == article) {
            time_t purchaseTime = std::mktime(&purchaseDate);
            time_t queryTime = std::mktime(const_cast<std::tm*>(&date));
            
            if (purchaseTime <= queryTime) {
                if (!op.isSold()) {
                    total += op.getPurchaseQuantity();
                } else {
                    time_t saleTime = std::mktime(&saleDate);
                    if (saleTime > queryTime) {
                        total += op.getPurchaseQuantity();
                    }
                }
            }
        }
    }
    
    return total;
}

List<TradeOperation> Database::getShippedProducts(const std::tm& date) const noexcept {
    List<TradeOperation> result;
    
    for (unsigned int i = 0; i < this->data.length(); ++i) {
        const TradeOperation& op = this->data[i];
        
        std::tm saleDate = op.getSaleDate();
        
        if (op.isSold() && 
            saleDate.tm_year == date.tm_year &&
            saleDate.tm_mon == date.tm_mon &&
            saleDate.tm_mday == date.tm_mday) {
            result.append(op);
        }
    }
    
    return result;
}

double Database::calculateSupplierInventoryValue(const std::string& supplier) const noexcept {
    double totalValue = 0.0;
    
    for (unsigned int i = 0; i < this->data.length(); ++i) {
        const TradeOperation& op = this->data[i];
        
        if (op.getSupplier() == supplier) {
            totalValue += op.getPurchasePrice() * op.getPurchaseQuantity();
        }
    }
    
    return totalValue;
}