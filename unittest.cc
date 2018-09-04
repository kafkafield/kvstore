#include <gtest/gtest.h>
#include "types.h"

const char *MyKvStatusStr[]={ "ok","key not found","invalid range","not implemented","rpc failure"};

TEST(Client, ValidRead)
{
	MyKvClient clt(grpc::CreateChannel(
		"127.0.0.1:35555", grpc::InsecureChannelCredentials()));

	KeyValue temp;

	int ret = MYKV_NOT_IMPLEMENTED;
	if ((ret = clt.Find("zhufan", temp)) == MYKV_OK)
	{
		std::cout << temp.key() << "\t" << temp.value() << std::endl;
	}
	else
	{
		std::cout << "Error: " << MyKvStatusStr[ret] << std::endl;
	}
	EXPECT_EQ(ret, MYKV_OK);
}

TEST(Client, InvalidRead)
{
	MyKvClient clt(grpc::CreateChannel(
		"127.0.0.1:35555", grpc::InsecureChannelCredentials()));

	KeyValue temp;

	int ret = MYKV_NOT_IMPLEMENTED;
	if ((ret = clt.Find("zican", temp)) == MYKV_OK)
	{
		// std::cout << temp.key() << "\t" << temp.value() << std::endl;
	}
	else
	{
		std::cout << "Error: " << MyKvStatusStr[ret] << std::endl;
	}
	EXPECT_EQ(ret, MYKV_KEY_NOT_FOUND);
}

TEST(Client, FindRangeWithBegin)
{
	MyKvClient clt(grpc::CreateChannel(
		"127.0.0.1:35555", grpc::InsecureChannelCredentials()));

	std::vector<KeyValue> vTemp;

	int ret = MYKV_NOT_IMPLEMENTED;
	if ((ret = clt.FindRangeWithBegin("zhufan", vTemp)) == MYKV_OK)
	{
		for (int i = 0; i < vTemp.size(); i++)
		{
			std::cout << vTemp[i].key() << "\t" << vTemp[i].value() << std::endl;
		}
	}
	else
	{
		std::cout << "Error: " << MyKvStatusStr[ret] << std::endl;
	}
	EXPECT_EQ(ret, MYKV_OK);
}

TEST(Client, FindRangeWithEnd)
{
	MyKvClient clt(grpc::CreateChannel(
		"127.0.0.1:35555", grpc::InsecureChannelCredentials()));

	KeyValue temp;
	std::vector<KeyValue> vTemp;

	int ret = MYKV_NOT_IMPLEMENTED;
	if ((ret = clt.FindRangeWithEnd("zhufan", vTemp)) == MYKV_OK)
	{
		for (int i = 0; i < vTemp.size(); i++)
		{
			// std::cout << vTemp[i].key() << "\t" << vTemp[i].value() << std::endl;
		}
	}
	else
	{
		std::cout << "Error: " << MyKvStatusStr[ret] << std::endl;
	}
	EXPECT_EQ(ret, MYKV_OK);
}

TEST(Client, FindRangeValid)
{
	MyKvClient clt(grpc::CreateChannel(
		"127.0.0.1:35555", grpc::InsecureChannelCredentials()));

	KeyValue temp;
	std::vector<KeyValue> vTemp;

	int ret = MYKV_NOT_IMPLEMENTED;
	if ((ret = clt.FindRange("a", "z", vTemp)) == MYKV_OK)
	{
		for (int i = 0; i < vTemp.size(); i++)
		{
			// std::cout << vTemp[i].key() << "\t" << vTemp[i].value() << std::endl;
		}
	}
	else
	{
		std::cout << "Error: " << MyKvStatusStr[ret] << std::endl;
	}
	EXPECT_EQ(ret, MYKV_OK);
}

TEST(Client, FindRangeInvalid)
{
	MyKvClient clt(grpc::CreateChannel(
		"127.0.0.1:35555", grpc::InsecureChannelCredentials()));

	KeyValue temp;
	std::vector<KeyValue> vTemp;

	int ret = MYKV_NOT_IMPLEMENTED;
	if ((ret = clt.FindRange("z", "a", vTemp)) == MYKV_OK)
	{
		for (int i = 0; i < vTemp.size(); i++)
		{
			// std::cout << vTemp[i].key() << "\t" << vTemp[i].value() << std::endl;
		}
	}
	else
	{
		std::cout << "Error: " << MyKvStatusStr[ret] << std::endl;
	}
	EXPECT_EQ(ret, MYKV_INVALID_RANGE);
}

/*
TEST(Client, Unimplemented)
{
}
*/

int main(int argc, char** argv)
{
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
