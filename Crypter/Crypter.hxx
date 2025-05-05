#ifndef CRYPTER_HXX
#define CRYPTER_HXX


#include <fstream>
#include <iostream>


class Crypter {
private:
    std::fstream file;
public:
    Crypter (void) noexcept = default;
    Crypter (const Crypter& unit) = delete;
    Crypter& operator= (const Crypter& unit) = delete;
    ~Crypter (void) noexcept = default;
    void encrypt (const std::string& filename_in, const std::string& filename_out) noexcept;
    void decrypt (const std::string& filename_in, const std::string& filename_out) noexcept;
};


#endif // CRYPTER_HXX