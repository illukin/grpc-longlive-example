#ifndef CLIENT_H
#define CLIENT_H

#include <backend.grpc.pb.h>

#include <atomic>
#include <memory>

class Client {
public:
  Client(std::shared_ptr<grpc::Channel> channel);

  Client(Client &) = delete;
  Client &operator=(Client &) = delete;

  void
  SubscribeNotifications();

  [[nodiscard]] bool
  IsSubscribed() const;

private:
  std::unique_ptr<BackendProto::RPC::Stub> stub_;
  std::atomic_bool is_subscribed_;
};

Client
MakeClient(std::string &target);

bool
TryToSubscribeNotifications(Client &);

#endif
