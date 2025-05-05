#include "Crypter.hxx"

void Crypter::encrypt (const std::string& filename_in, const std::string& filename_out) noexcept {
    std::string key;
    char alphabet[63] = "AaBbCcDdEeFfGgHhIiJjKkLlMmNnOoPpQqRrSsTtUuVvWwXxYyZz1234567890";
    srand(time(NULL));
    for (int i = 0; i < 16; ++i) {
        key += alphabet[rand() % 62];
    }
    this->file.open("key.txt", std::ios::out | std::ios::trunc);
    this->file << key;
    this->file.close();
    std::string commandAES = "openssl aes-128-cbc -salt -in " + filename_in + " -out " + filename_out + " -pass pass:" + key;
    std::system(commandAES.c_str());
    if (std::remove(filename_in.c_str()) != 0) {
        std::cerr << "CANNOT DELETE >>> " + filename_in << std::endl;
    }
    std::string commandRSA = "openssl rsautl -encrypt -inkey rsa.public -pubin -in key.txt -out key.txt.enc";
    std::system(commandRSA.c_str());
    if (std::remove("key.txt") != 0) {
        std::cerr << "CANNOT DELETE >>> key.txt" << std::endl;
    }
}

void Crypter::decrypt (const std::string& filename_in, const std::string& filename_out) noexcept {
    std::string commandRSA = "openssl rsautl -decrypt -inkey rsa.private -in key.txt.enc -out key.txt";
    std::system(commandRSA.c_str());
    std::string key;
    this->file.open("key.txt", std::ios::in);
    this->file >> key;
    this->file.close();
    if (std::remove("key.txt.enc") != 0) {
        std::cerr << "CANNOT DELETE >>> key.txt.enc" << std::endl;
    }
    std::string commandAES = "openssl aes-128-cbc -d -in " + filename_in + " -out " + filename_out + " -pass pass:" + key;
    std::system(commandAES.c_str());
    if (std::remove(filename_in.c_str()) != 0) {
        std::cerr << "CANNOT DELETE >>> " + filename_in << std::endl;
    }
}