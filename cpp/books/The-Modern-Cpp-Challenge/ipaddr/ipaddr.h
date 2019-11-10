#ifndef IpV4_H
#define IpV4_H

#include <iostream>
#include <array>

class IpV4
{
public:
    constexpr IpV4()
        :data_{{0}}
    {}

    constexpr IpV4(unsigned char d1, unsigned char d2, unsigned char d3, unsigned char d4);
    explicit constexpr IpV4(unsigned long addr);
    constexpr IpV4(const IpV4& other) noexcept
        : data_(other.data_)
    {}
    std::string ToString() const;
    constexpr unsigned long toULong() const noexcept;
    const IpV4& operator = (const IpV4& other);
    friend std::ostream& operator<<(std::ostream& os, const IpV4& addr);
    friend std::istream& operator>>(std::istream& is, IpV4& addr);

private:
    std::array<unsigned char, 4>data_;
};

#endif // IpV4_H
