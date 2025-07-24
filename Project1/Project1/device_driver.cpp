#include "device_driver.h"
#include <stdexcept>
using namespace std;

class readFailException : public std::runtime_error {
public:
    readFailException(const std::string& message)
        : std::runtime_error(message) {}
};

DeviceDriver::DeviceDriver(FlashMemoryDevice* hardware) : m_hardware(hardware)
{
}

int DeviceDriver::read(long address)
{
    int returnArr[COMPARE_COUNT] = { 0, };
    for (int i = 0; i < COMPARE_COUNT; i++)
    {
        returnArr[i] = (int)(m_hardware->read(address));
    }
    checkAssert(returnArr);
    return returnArr[0];
}

void DeviceDriver::checkAssert(int* returnArr)
{
    for (int i = 0; i < COMPARE_COUNT; i++)
    {
        for (int j = 0; j < COMPARE_COUNT; j++)
        {
            if(returnArr[i]!=returnArr[j])
                throw readFailException("ReadFailException: Different Value Exists");
        }
    }
}

void DeviceDriver::write(long address, int data)
{
    // TODO: implement this method
    m_hardware->write(address, (unsigned char)data);
}