#include <cstdlib>
#include <iostream>
#include <string>
#include <cassert>

// Обратная операция для encode():
// каждый символ шифра → (char - ' ') → двузначное число → часть десятичной строки числа v[i]
std::string decode_decimal(const std::string& cipher) {
    std::string decimal_str;
    for (unsigned char c : cipher) {
        int val = c - ' '; // диапазон 0–99
        if (val < 10) {
            decimal_str += '0';
        }
        decimal_str += std::to_string(val);
    }
    return decimal_str;
}

// Восстанавливает исходную строку из шифра.
// Предполагает, что каждое число v[i] занимает ровно 10 десятичных цифр
// (выполняется, когда первый байт каждой четвёрки >= 10,
//  т.е. первый символ группы имеет код >= 10).
std::string decrypt(const std::string& cipher) {
    std::string decimal_str = decode_decimal(cipher);

    // каждые 10 десятичных цифр — одно 32-битное число из 4 символов
    std::string result;
    for (size_t i = 0; i + 10 <= decimal_str.size(); i += 10) {
        long long v = std::stoll(decimal_str.substr(i, 10));
        result += static_cast<char>((v >> 24) & 0xFF); // байт 1 (старший)
        result += static_cast<char>((v >> 16) & 0xFF); // байт 2
        result += static_cast<char>((v >>  8) & 0xFF); // байт 3
        result += static_cast<char>( v        & 0xFF); // байт 4 (младший)
    }
    return result;
}

int main() {
    std::string cipher = "-b`gP1e8)/1SOWf1d?uo";
    std::cout << "Cipher : " << cipher << "\n";
    std::cout << "Decoded: " << decrypt(cipher) << "\n";
}