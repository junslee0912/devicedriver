#include "gmock/gmock.h"
#include <stdexcept>
#include <iostream>
#include "device_driver.h"

class FlashMock : public FlashMemoryDevice {
public:
	MOCK_METHOD(unsigned char, read, (long address), (override));
	MOCK_METHOD(void, write, (long address, unsigned char data), (override));
};

class DeviceDriverTestFixture : public testing::Test
{
public:
	FlashMock mock;
	DeviceDriver driver{ &mock };
};

TEST_F(DeviceDriverTestFixture, IsFiveRead)
{
	EXPECT_CALL(mock, read((long)0xB)).Times(DeviceDriver::COMPARE_COUNT);

	int data = driver.read((long)0xB);
}

TEST_F(DeviceDriverTestFixture, ReadFromHW)
{
	EXPECT_CALL(mock, read((long)0xFF)).Times(DeviceDriver::COMPARE_COUNT).WillRepeatedly(testing::Return(5));

	int expectedVal = driver.read((long)0xFF);
	EXPECT_EQ(expectedVal, 5);
}

TEST_F(DeviceDriverTestFixture, ReadFailExceptionCase) 
{
	EXPECT_CALL(mock, read((long)0xFF)).Times(2).WillOnce(testing::Return(5));
	
	try
	{
		driver.read(0xFF);
		FAIL();
	}
	catch (std::exception e)
	{
		std::cout << e.what() << std::endl;
	}

}

int main() {
	::testing::InitGoogleMock();
	return RUN_ALL_TESTS();
}