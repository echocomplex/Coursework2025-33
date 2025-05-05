#include "Interface.hxx"

void Interface::clearInputBuffer(void) {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

std::tm Interface::getDateFromInput(const std::string& prompt) {
    std::tm date = {};
    std::cout << prompt << " (DD.MM.YYYY): ";
    
    while (true) {
        std::string input;
        std::getline(std::cin, input);
        
        if (sscanf(input.c_str(), "%d.%d.%d", &date.tm_mday, &date.tm_mon, &date.tm_year) == 3) {
            date.tm_mon--;
            date.tm_year -= 1900; 
            break;
        }
        std::cout << "Invalid date format. Please try again (DD.MM.YYYY): ";
    }
    
    return date;
}

void Interface::getTradeOperation(TradeOperation& op) {
    std::string temp;
    double temp_price = 0;
    unsigned int temp_quantity = 0;
    unsigned short temp_age = 0;

    std::cout << "Enter Article: ";
    std::getline(std::cin, temp);
    op.setArticle(temp);
    
    std::cout << "Enter Product Name: ";
    std::getline(std::cin, temp);
    op.setProductName(temp);
    
    std::cout << "Enter Supplier: ";
    std::getline(std::cin, temp);
    op.setSupplier(temp);
    
    std::cout << "Enter Purchase Price: ";
    std::cin >> temp_price;
    this->clearInputBuffer();
    op.setPurchasePrice(temp_price);
    
    std::tm purchase_date = getDateFromInput("Enter Purchase Date");
    op.setPurchaseDate(purchase_date);
    
    std::cout << "Enter Purchase Quantity: ";
    std::cin >> temp_quantity;
    this->clearInputBuffer();
    op.setPurchaseQuantity(temp_quantity);
    
    std::cout << "Enter Store Number: ";
    std::getline(std::cin, temp);
    op.setStoreNumber(temp);
    
    std::cout << "Enter Store Address: ";
    std::getline(std::cin, temp);
    op.setStoreAddress(temp);
    
    std::tm sale_date = getDateFromInput("Enter Sale Date (or 00.00.0000 if not sold)");
    op.setSaleDate(sale_date);
    
    std::cout << "Enter Retail Price: ";
    std::cin >> temp_price;
    this->clearInputBuffer();
    op.setRetailPrice(temp_price);
}

int Interface::removeOperation(void) {
    int number;
    while (true) {
        std::cout << "Enter operation number to delete (1-" << this->db.size() << "): ";
        
        if (!(std::cin >> number)) {
            std::cin.clear();
            this->clearInputBuffer();
            std::cerr << "Error: Please enter a number\n\n";
            continue;
        }

        if (number > 0 && number <= this->db.size()) {
            return number - 1;
        }
        
        std::cerr << "Error: Number must be between 1 and " << this->db.size() << "\n\n";
    }
}

void Interface::displayMenu(void) {
    std::cout << "\n\n=== Trade Operations Database ===" << std::endl;
    std::cout << "1. Display all records" << std::endl;
    std::cout << "2. Add new operation" << std::endl;
    std::cout << "3. Remove operation" << std::endl;
    std::cout << "4. Check stock quantity by article" << std::endl;
    std::cout << "5. View shipped products by date" << std::endl;
    std::cout << "6. Calculate supplier inventory value" << std::endl;
    std::cout << "7. Exit program" << std::endl;
    std::cout << "Enter your choice (1-7): ";
}

void Interface::run(void) {
    short choice = 0;
    TradeOperation new_op;
    List<TradeOperation> collected;
    std::string temp;
    
    while (true) {
        this->displayMenu();

        while (!(std::cin >> choice) || choice < 1 || choice > 7) {
            std::cout << "Invalid input. Please enter 1-7: ";
            this->clearInputBuffer();
        }

        this->clearInputBuffer();

        switch (choice) {
            case 1:
                std::cout << "\n[All trade operations]\n";
                std::cout << this->db << std::endl;
                break;
                
            case 2:
                std::cout << "\n[Adding new trade operation]\n";
                this->getTradeOperation(new_op);
                this->db.append(new_op);
                break;
                
            case 3:
                std::cout << "\n[Removing trade operation]\n";
                this->db.remove(this->removeOperation());
                break;
                
            case 4: {
                std::cout << "Enter article to check stock: ";
                std::getline(std::cin, temp);
                std::tm date = getDateFromInput("Enter date to check stock");
                unsigned int quantity = db.getStockQuantity(temp, date);
                std::cout << "\n[Stock quantity for " << temp << " on ";
                std::cout << std::put_time(&date, "%d.%m.%Y") << "]: " << quantity << std::endl;
                break;
            }
                
            case 5: {
                std::tm date = getDateFromInput("Enter shipment date");
                collected = db.getShippedProducts(date);
                std::cout << "\n[Products shipped on " << std::put_time(&date, "%d.%m.%Y") << "]\n";
                for (int i = 0; i < collected.length(); ++i) {
                    std::cout << collected[i] << std::endl;
                }
                collected.clear();
                break;
            }
                
            case 6: {
                std::cout << "Enter supplier name: ";
                std::getline(std::cin, temp);
                double value = db.calculateSupplierInventoryValue(temp);
                std::cout << "\n[Inventory value for supplier " << temp << "]: " 
                          << value << " currency units" << std::endl;
                break;
            }
                
            case 7:
                std::cout << "\nExiting program...\n";
                return;
        }

        std::cout << "\nOperation completed. Press Enter to continue...";
        this->clearInputBuffer();
    }
}