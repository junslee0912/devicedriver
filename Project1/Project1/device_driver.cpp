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
    int retBefore = 0;
    int retNow = 0;
    for (int i = 0; i < COMPARE_COUNT; i++)
    {
        if (i == 0) { 
            retBefore = (int)(m_hardware->read(address)); 
            continue;
        }

        retNow = (int)(m_hardware->read(address));

        if(retBefore != retNow)
            throw readFailException("ReadFailException: Different Value Exists");
        
        retBefore = retNow;
    }

    return retNow;
}

void DeviceDriver::write(long address, int data)
{
    // TODO: implement this method
    m_hardware->write(address, (unsigned char)data);
}