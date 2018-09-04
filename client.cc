#include "types.h"

// It only forwards all the reqeusts to server. 
int MyKvClient::Find(const std::string& key, KeyValue& ret)
{
	ClientContext context;
	GetRequestPB req;
	GetResponsePB res;

	req.set_key(key);

	std::cout << "begin rpc" << std::endl;		
	Status status = stub->Get(&context, req, &res);
	std::cout << "end rpc" << std::endl;		

	if (status.ok() && res.errorcode() == MYKV_OK)
	{
		ret.set_key(key);
		ret.set_value(res.value());
	}
	return res.errorcode();
}

int MyKvClient::FindRangeWithBegin(const std::string& beginKey, 
	std::vector<KeyValue>& ret)
{
	return FindRange(beginKey, "", ret);
}

int MyKvClient::FindRangeWithEnd(const std::string& endKey, 
	std::vector<KeyValue>& ret)
{
	return FindRange("", endKey, ret);
}

int MyKvClient::FindRange(const std::string& beginKey, 
	const std::string& endKey, std::vector<KeyValue>& ret)
{
	ClientContext context;
	ScanRequestPB req;
	ScanResponsePB res;

	if (beginKey == "")
		req.set_has_begin_key(false);
	else
	{
		req.set_has_begin_key(true);
		req.set_begin_key(beginKey);
	}
	if (endKey == "")
		req.set_has_end_key(false);
	else
	{
		req.set_has_end_key(true);
		req.set_end_key(endKey);
	}
	
	Status status = stub->Scan(&context, req, &res);

	ret.clear();
	if (status.ok() && res.errorcode() == MYKV_OK)
	{
		for (int i = 0; i < res.keys_size(); i++)
		{
			KeyValue oneIns;
			oneIns.set_key(res.keys(i));
			oneIns.set_value(res.values(i));
			ret.push_back(oneIns);
		}
	}
	return res.errorcode();
}
