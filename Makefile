CXX = g++
CXXFLAGS += -g -std=c++11
CPPFLAGS += `pkg-config --cflags protobuf grpc` 
LDFLAGS += -L/usr/local/lib `pkg-config --libs protobuf grpc++ grpc`\
		   -Wl,--no-as-needed -lgrpc++_reflection -Wl,--as-needed -ldl
GTESTLDFLAGS += -lgtest

PROTOC = protoc
GRPC_CPP_PLUGIN = grpc_cpp_plugin
GRPC_CPP_PLUGIN_PATH ?= `which $(GRPC_CPP_PLUGIN)`

PROTOS_PATH = ./proto

vpath %.proto $(PROTOS_PATH)

all: server_main unittest

unittest: kvop.pb.o kvop.grpc.pb.o client.o unittest.o
	$(CXX) $^ $(GTESTLDFLAGS) $(LDFLAGS) -o $@

server_main: kvop.pb.o kvop.grpc.pb.o server.o server_main.o
	$(CXX) $^ $(LDFLAGS) -o $@

.PRECIOUS: %.grpc.pb.cc
%.grpc.pb.cc: %.proto
	$(PROTOC) -I $(PROTOS_PATH) --grpc_out=. --plugin=protoc-gen-grpc=$(GRPC_CPP_PLUGIN_PATH) $<

.PRECIOUS: %.pb.cc
%.pb.cc: %.proto
	$(PROTOC) -I $(PROTOS_PATH) --cpp_out=. $< 

clean:
	rm -f *.o *.pb.cc *.pb.h unittest server_main
