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

TEST_F(FlashTestFixture, WriteTest_Success) {
	FlashMock flashMock;
	EXPECT_CALL(flashMock, write(0xA, 0xC)).WillOnce(Return());
	EXPECT_CALL(flashMock, read(0xA)).WillOnce(Return(0xFF))
															.WillOnce(Return(0xFF))
															.WillOnce(Return(0xFF))
															.WillOnce(Return(0xFF))
															.WillOnce(Return(0xFF))
															.WillRepeatedly(Return(0xC));
	DeviceDriver dd(&flashMock);
	dd.write(0xA, 0xC);
	const char ret = dd.read(0xA);
	EXPECT_EQ(ret, 0xC);
}
TEST_F(FlashTestFixture, WriteTest_Fail) {
	FlashMock flashMock;
	EXPECT_CALL(flashMock, read(0xA)).WillRepeatedly(Return(0xC));
	DeviceDriver dd(&flashMock);
	EXPECT_THROW(dd.write(0xA, 0xC), WriteFailException);
	
}

TEST_F(FlashTestFixture, AppReadAndPrint) {
	FlashMock flashMock;
	DeviceDriver dd(&flashMock);
	EXPECT_CALL(flashMock, read(0xF)).WillRepeatedly(Return(0x1));
	EXPECT_CALL(flashMock, read(0x10)).WillRepeatedly(Return(0x2));
	EXPECT_CALL(flashMock, read(0x11)).WillRepeatedly(Return(0x3));
	EXPECT_CALL(flashMock, read(0x12)).WillRepeatedly(Return(0x4));
	EXPECT_CALL(flashMock, read(0x13)).WillRepeatedly(Return(0x5));

	dd.ReadAndPrint(0xF, 0x13);
}

TEST_F(FlashTestFixture, WriteAll) {
	FlashMock flashMock;
	DeviceDriver dd(&flashMock);
	EXPECT_CALL(flashMock, read(0x00)).WillRepeatedly(Return(0xFF));
	EXPECT_CALL(flashMock, read(0x01)).WillRepeatedly(Return(0xFF));
	EXPECT_CALL(flashMock, read(0x02)).WillRepeatedly(Return(0xFF));
	EXPECT_CALL(flashMock, read(0x03)).WillRepeatedly(Return(0xFF));
	EXPECT_CALL(flashMock, read(0x04)).WillRepeatedly(Return(0xFF));
	EXPECT_CALL(flashMock, write(0x00, 0xCD)).WillOnce(Return());
	EXPECT_CALL(flashMock, write(0x01, 0xCD)).WillOnce(Return());
	EXPECT_CALL(flashMock, write(0x02, 0xCD)).WillOnce(Return());
	EXPECT_CALL(flashMock, write(0x03, 0xCD)).WillOnce(Return());
	EXPECT_CALL(flashMock, write(0x04, 0xCD)).WillOnce(Return());

	dd.WriteAll(0xCD);
}
