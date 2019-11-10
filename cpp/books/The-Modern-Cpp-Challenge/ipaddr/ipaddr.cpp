#include "ipaddr.h"

#include <sstream>

///*constexpr*/ IpV4::IpV4()
//    :data_{{0}}
//{
//}

constexpr IpV4::IpV4(unsigned char d1, unsigned char d2, unsigned char d3, unsigned char d4)
    :data_{{d1, d2, d3, d4}}
{
}

constexpr IpV4::IpV4(unsigned long addr)
    :data_ {{
            static_cast<unsigned char>((addr >> 24) & 0xFF),
            static_cast<unsigned char>((addr >> 16) & 0xFF),
            static_cast<unsigned char>((addr >> 8 ) & 0xFF),
            static_cast<unsigned char>((addr      ) & 0xFF)
            }}
{
}

constexpr unsigned long IpV4::toULong() const noexcept
{
    return  static_cast<unsigned long>(data_[3])       |
            static_cast<unsigned long>(data_[2] <<  8) |
            static_cast<unsigned long>(data_[1] << 16) |
            static_cast<unsigned long>(data_[0] << 24);
}

std::string IpV4::ToString() const
{
    std::stringstream ss;
    ss << static_cast<unsigned long>(data_[0]) << '.'
       << static_cast<unsigned long>(data_[1]) << '.'
       << static_cast<unsigned long>(data_[2]) << '.'
       << static_cast<unsigned long>(data_[3]);
    return ss.str();
}

const IpV4& IpV4::operator = (const IpV4& other)
{
    data_ = other.data_;
    return *this;
}

std::ostream& operator<<(std::ostream& os, const IpV4& addr)
{
    os << static_cast<unsigned long>(addr.data_[0]) << '.'
       << static_cast<unsigned long>(addr.data_[1]) << '.'
       << static_cast<unsigned long>(addr.data_[2]) << '.'
       << static_cast<unsigned long>(addr.data_[3]);
    return os;
}

std::istream& operator>>(std::istream& is, IpV4& addr)
{
    char d1, d2, d3;
    int b1, b2, b3, b4;
    is >> b1 >> d1 >> b2 >> d2 >> b3 >> d3 >> b4;
    if (d1 == '.' && d2 == '.' && d3 == '.')
       addr = IpV4(b1, b2, b3, b4);
    else
       is.setstate(std::ios_base::failbit);

    return is;
}
