#ifndef TYPES_H
#define TYPES_H

#include <iostream>
#include <map>
#include <string>
#include "mylist.h"
#include "cmdline.h"

#include <grpc++/grpc++.h>

#include "kvop.grpc.pb.h"
// #include "kvop.pb.h"

using grpc::Channel;
using grpc::ClientContext;

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;
using mykv::GetRequestPB;
using mykv::GetResponsePB;
using mykv::PutRequestPB;
using mykv::PutResponsePB;
using mykv::DeleteRequestPB;
using mykv::DeleteResponsePB;
using mykv::ScanRequestPB;
using mykv::ScanResponsePB;
using mykv::MyKvServer;


typedef std::string Key;
typedef std::string Value;
enum MyKvStatus
{
	MYKV_OK,
	MYKV_KEY_NOT_FOUND,
	MYKV_INVALID_RANGE,
	MYKV_NOT_IMPLEMENTED,
	MYKV_RPC_FAILURE,

	MYKV_STATUS_NUM
};

class KeyValue
{
public:
	Key key()
	{
		return key_;
	}
	Value value()
	{
		return value_;
	}
	void set_key(Key _key)
	{
		key_ = _key;
	}
	void set_value(Value _value)
	{
		value_ = _value;
	}

private:
	Key key_;
	Value value_;
};
//TODO: add all declarations here
class MyKvClient
{
public:
	MyKvClient(std::shared_ptr<Channel> channel)
	: stub(MyKvServer::NewStub(channel))
	{
	}

	int Find(const std::string& key, KeyValue& ret);
	int FindRangeWithBegin(const std::string& beginKey, 
		std::vector<KeyValue>& ret);
	int FindRangeWithEnd(const std::string& endKey, 
		std::vector<KeyValue>& ret);
	int FindRange(const std::string& beginKey, 
		const std::string& endKey, std::vector<KeyValue>& ret);

private:
	std::unique_ptr<MyKvServer::Stub> stub;
};

class MyKvServerImpl : public MyKvServer::Service
{
public:
	MyKvServerImpl()
	: MyKvServer::Service()
	{
		fillKvStore();
	}
	Status Get(ServerContext* ctx,
		const GetRequestPB* req,
		GetResponsePB* res);
	Status Put(ServerContext* ctx,
		const PutRequestPB* req,
		PutResponsePB* res);
	Status Delete(ServerContext* ctx,
		const DeleteRequestPB* req,
		DeleteResponsePB* res);
	Status Scan(ServerContext* ctx,
		const ScanRequestPB* req,
		ScanResponsePB* res);
	void fillKvStore();
	std::string genRandomString( size_t length );

private:
	std::map<Key, Value> kvStore;
};

#endif
