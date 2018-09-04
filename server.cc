#include "types.h"

Status MyKvServerImpl::Get(ServerContext* ctx,
	const GetRequestPB* req,
	GetResponsePB* res)
{
	std::cout << "In Get" << std::endl;
	auto it = kvStore.find(req->key());
	if (it != kvStore.end())
	{
		res->set_value(it->second);	
		res->set_errorcode(MYKV_OK);
	}
	else
	{
		res->set_errorcode(MYKV_KEY_NOT_FOUND);
		return Status::OK;
	}
	return Status::OK;
}

Status MyKvServerImpl::Put(ServerContext* ctx,
	const PutRequestPB* req,
	PutResponsePB* res)
{
	res->set_errorcode(MYKV_NOT_IMPLEMENTED);
	return Status::OK;
}

Status MyKvServerImpl::Delete(ServerContext* ctx,
	const DeleteRequestPB* req,
	DeleteResponsePB* res)
{
	res->set_errorcode(MYKV_NOT_IMPLEMENTED);
	return Status::OK;
}

Status MyKvServerImpl::Scan(ServerContext* ctx,
	const ScanRequestPB* req,
	ScanResponsePB* res)
{
	auto beginIt = kvStore.begin();
	auto endIt = kvStore.end();
	
	if (req->has_begin_key())
	{
		beginIt = kvStore.lower_bound(req->begin_key());
	}
	if (req->has_end_key())
	{
		endIt = kvStore.lower_bound(req->end_key());
	}

	if (req->has_begin_key() && req->has_end_key())
	{
		std::cout << "both side" << std::endl;
		if (req->begin_key() > req->end_key())
		{
			std::cout << "invalid_range" << std::endl;
			res->set_errorcode(MYKV_INVALID_RANGE);
			return Status::OK;
		}
	}
	for (auto it = beginIt; it != endIt; it++)
	{
		// set_value
		res->add_keys(it->first);
		res->add_values(it->second);
	}
	res->set_errorcode(MYKV_OK);
	return Status::OK;
}

void MyKvServerImpl::fillKvStore()
{
	kvStore["zhufan"] = "wang";
	for (int i = 0; i < 200; i++)
	{
		Key key = genRandomString(10);
		Value value = genRandomString(20);
		kvStore[key] = value;
		std::cout << key << "\t" << value << std::endl;
	}
}

std::string MyKvServerImpl::genRandomString( size_t length )
{
	auto randchar = []() -> char
	{
		const char charset[] =
		"0123456789"
		"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
		"abcdefghijklmnopqrstuvwxyz";
		const size_t max_index = (sizeof(charset) - 1);
		return charset[ rand() % max_index ];
	};
	std::string str(length,0);
	std::generate_n(str.begin(), length, randchar);
	return str;
}
