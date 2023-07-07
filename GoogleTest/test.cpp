#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "../DeviceDriver/DeviceDriver.cpp"


using namespace testing;
using namespace std;

class FlashTestFixture : public testing::Test
{
public:

};

class FlashMock : public FlashMemoryDevice {
public:
	MOCK_METHOD(unsigned char, read, (long), (override));
	MOCK_METHOD(void, write, (long, unsigned char), (override));
};

TEST_F(FlashTestFixture, ReadTest_AllSame) {
	FlashMock flashMock;
	EXPECT_CALL(flashMock, read).Times(5);
	DeviceDriver dd(&flashMock);
	dd.read(0xA);
}
TEST_F(FlashTestFixture, ReadTest_Different) {
	FlashMock flashMock;
	EXPECT_CALL(flashMock, read).WillOnce(Return(50))
													.WillOnce(Return(50))
													.WillOnce(Return(10))
													.WillOnce(Return(50))
													.WillOnce(Return(50));
	DeviceDriver dd(&flashMock);
	EXPECT_THROW(dd.read(0xA), ReadFailException);
}