#include "service.h"

#include <grpcpp/grpcpp.h>

void
RunServer(const std::string &server_addr)
{
  ServiceImlp service;
  grpc::ServerBuilder builder;

  builder.AddListeningPort(server_addr, grpc::InsecureServerCredentials());
  builder.RegisterService(&service);

  std::unique_ptr<grpc::Server> server(builder.BuildAndStart());
  server->Wait();
}

int
main()
{
  std::string server_addr = "unix-abstract:test";
  RunServer(server_addr);

  return 0;
}
