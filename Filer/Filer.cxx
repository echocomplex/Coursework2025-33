#include "Filer.hxx"

Filer::Filer(const std::string& path, const bool createNew) {
    if (createNew) {
        this->file.open(path, std::ios::in);
        if (!this->file.is_open()) {
            this->file.open(path, std::ios::out);
            this->file.close();
            this->file.open(path, std::ios::in);
            if (!this->file.is_open()) throw std::runtime_error("Failed to create the file.");
        }
    }
    else {
        this->file.open(path, std::ios::in);
        if (!this->file.is_open()) throw std::runtime_error("File cannot be opened or does not exists");
    }
    this->path = path;
}

Filer::~Filer(void) noexcept {
    if (this->file.is_open()) this->file.close();
}

void Filer::open(const std::string& path, const bool createNew) {
    if (createNew) {
        this->file.open(path, std::ios::in);
        if (!this->file.is_open()) {
            this->file.open(path, std::ios::out);
            this->file.close();
            this->file.open(path, std::ios::in);
            if (!this->file.is_open()) throw std::runtime_error("Failed to create the file.");
        }
    }
    else {
        this->file.open(path, std::ios::in);
        if (!this->file.is_open()) throw std::runtime_error("File cannot be opened or does not exists");
    }
    this->path = path;
}

void Filer::read(std::string& str) {
    if (!this->file.is_open()) throw std::runtime_error("File does not open now");
    
    this->mutex.lock();

    this->file.close();
    this->file.open(this->path, std::ios::in);

    this->file.seekg(0, std::ios::beg);
    std::string temp;

    this->file.seekp(0, std::ios::beg);
    while (std::getline(this->file, temp)) str += temp + '\n';
    
    this->mutex.unlock();
}

void Filer::readToList(List<TradeOperation>& unit) {
    if (!this->file.is_open()) throw std::runtime_error("File does not open now");
    
    this->mutex.lock();

    this->file.close();
    this->file.open(this->path, std::ios::in);

    this->file.seekg(0, std::ios::beg);
    std::string temp;
    TradeOperation node;
    while (std::getline(this->file, temp)) {
        node = TradeOperation();
        this->stringToOperation(node, temp);
        unit.append(node);
    }

    this->mutex.unlock();
}

void Filer::writeBack(std::string& string) {
    if (!this->file.is_open()) throw std::runtime_error("File does not open now");
    else if (string.empty()) return;

    this->mutex.lock();

    this->file.close();
    this->file.open(this->path, std::ios::out | std::ios::app);

    this->file << string << '\n';
    this->file.flush();
    this->mutex.unlock();
}

void Filer::writeBackFromOperation(const TradeOperation& unit) {
    if (!this->file.is_open()) throw std::runtime_error("File does not open now");

    this->mutex.lock();

    this->file.close();
    this->file.open(this->path, std::ios::out | std::ios::app);

    auto formatDate = [](const std::tm& date) {
        std::ostringstream oss;
        oss << std::setfill('0') << std::setw(2) << date.tm_mday << "."
            << std::setw(2) << (date.tm_mon + 1) << "." << (date.tm_year + 1900);
        return oss.str();
    };

    this->file << 
        unit.getArticle() << "$$" <<
        unit.getProductName() << "$$" <<
        unit.getSupplier() << "$$" <<
        unit.getPurchasePrice() << "$$" <<
        formatDate(unit.getPurchaseDate()) << "$$" <<
        unit.getPurchaseQuantity() << "$$" <<
        unit.getStoreNumber() << "$$" <<
        unit.getStoreAddress() << "$$" <<
        formatDate(unit.getSaleDate()) << "$$" <<
        unit.getRetailPrice() << '\n';
    
    this->file.flush();
    
    this->mutex.unlock();
}

void Filer::rewrite(std::string& string) {
    if (!this->file.is_open()) throw std::runtime_error("File does not open now");
    else if (string.empty()) return;

    this->mutex.lock();

    this->file.close();
    this->file.open(this->path, std::ios::out | std::ios::trunc);

    this->file << string << '\n';
    this->file.flush();

    this->mutex.unlock();
}

void Filer::rewriteFromList(const List<TradeOperation>& unit) {
    if (!this->file.is_open()) throw std::runtime_error("File does not open now");
    else if (unit.length() == 0) return;

    this->mutex.lock();

    this->file.close();
    this->file.open(this->path, std::ios::out | std::ios::trunc);

    this->file.seekg(0, std::ios::beg);

    auto formatDate = [](const std::tm& date) {
        std::ostringstream oss;
        oss << std::setfill('0') << std::setw(2) << date.tm_mday << "."
            << std::setw(2) << (date.tm_mon + 1) << "." << (date.tm_year + 1900);
        return oss.str();
    };

    for (unsigned int i = 0; i < unit.length(); ++i) {
        this->file << 
            unit[i].getArticle() << "$$" <<
            unit[i].getProductName() << "$$" <<
            unit[i].getSupplier() << "$$" <<
            unit[i].getPurchasePrice() << "$$" <<
            formatDate(unit[i].getPurchaseDate()) << "$$" <<
            unit[i].getPurchaseQuantity() << "$$" <<
            unit[i].getStoreNumber() << "$$" <<
            unit[i].getStoreAddress() << "$$" <<
            formatDate(unit[i].getSaleDate()) << "$$" <<
            unit[i].getRetailPrice() << '\n';
    }
    this->file.flush();

    this->mutex.unlock();
}

void Filer::stringToOperation(TradeOperation& unit, const std::string& str) {
    if (str.empty()) return;

    std::string arr[10];
    unsigned short count = 0;
    for (size_t i = 0; i < (str.size() - 1) && count < 10; ++i) {
        if (str[i] == '$' && str[i + 1] == '$') {
            ++count, ++i;
        } 
        else arr[count].push_back(str[i]);
    }
    if (count < 10) arr[count].push_back(str[str.size() - 1]);

    auto parseDate = [](const std::string& dateStr) {
        std::tm date = {};
        std::istringstream iss(dateStr);
        char dot;
        iss >> date.tm_mday >> dot >> date.tm_mon >> dot >> date.tm_year;
        date.tm_mon--;
        date.tm_year -= 1900;
        return date;
    };

    unit.setArticle(arr[0]);
    unit.setProductName(arr[1]);
    unit.setSupplier(arr[2]);
    try {
        unit.setPurchasePrice(std::stod(arr[3]));
    } 
    catch (std::exception) {
        unit.setPurchasePrice(0.0); 
    }
    unit.setPurchaseDate(parseDate(arr[4]));
    try {
        unit.setPurchaseQuantity(std::stoul(arr[5]));
    } 
    catch (std::exception) {
        unit.setPurchaseQuantity(0); 
    }
    unit.setStoreNumber(arr[6]);
    unit.setStoreAddress(arr[7]);
    unit.setSaleDate(parseDate(arr[8]));
    try {
        unit.setRetailPrice(std::stod(arr[9]));
    } 
    catch (std::exception) {
        unit.setRetailPrice(0.0); 
    }
}