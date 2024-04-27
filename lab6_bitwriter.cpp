#include <iostream>
#include <vector>
#include <bitset>

class BitWriter
{
public:
    BitWriter()
    : bitCount(0)
    {
    }
    
    void WriteBit(unsigned char bit)
    {
        if (bitCount % 8 == 0)
        {
            buffer.push_back(0);
        }
        if (bit)
        {
            buffer[bitCount/8] |= 1 << (7 - bitCount % 8);
        }
        bitCount++;
    }
    
    void WriteByte(unsigned char byte)
    {
        if (bitCount % 8 == 0)
        {
            buffer.push_back(byte);
        }
        else
        {
            int offset = bitCount % 8;
            buffer[bitCount/8] |= byte >> offset;
            buffer.push_back(byte << (8 - offset));
        }
        bitCount += 8;
    }
    
    const std::vector<unsigned char> &GetBuffer() const
    {
        return buffer;
    }
    
    size_t GetBitCount() const
    {
        return bitCount;
    }
    
private:
    std::vector<unsigned char> buffer;
    size_t bitCount;
};

void visualizeBuffer(const std::vector<unsigned char> &buffer)
{
    for (auto &b: buffer)
    {
        std::cout << std::bitset<8>(b) << "|";
    }
    std::cout << std::endl;
}

int main(int argc, const char * argv[]) {
    BitWriter bw;
    bw.WriteBit(1);
    visualizeBuffer(bw.GetBuffer());
    
    bw.WriteBit(0);
    bw.WriteBit(0);
    bw.WriteBit(1);
    visualizeBuffer(bw.GetBuffer());
    
    bw.WriteByte(255);
    bw.WriteBit(0);
    bw.WriteBit(1);
    visualizeBuffer(bw.GetBuffer());
    std::cout << (bw.GetBitCount() % 8) << std::endl;
    return 0;
}
