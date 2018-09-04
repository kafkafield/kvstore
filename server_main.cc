#include "types.h"

void RunServer(int argc, char** argv)
{
	std::string server_address("0.0.0.0:35555");
	MyKvServerImpl server;

	ServerBuilder builder;
	builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
	builder.RegisterService(&server);

	std::unique_ptr<Server> daemon_server(builder.BuildAndStart());
	daemon_server->Wait();
}

int main(int argc, char** argv)
{
	RunServer(argc, argv);
	return 0;
}
