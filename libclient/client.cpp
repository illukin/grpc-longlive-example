#include "client.h"

#include <condition_variable>
#include <iostream>
#include <memory>
#include <mutex>
#include <thread>

#include <grpcpp/grpcpp.h>

#include <backend.grpc.pb.h>

namespace BP = BackendProto;

using grpc::Channel;
using grpc::ClientContext;
using grpc::ClientReadReactor;
using grpc::Status;

Client
MakeClient(std::string &target)
{
  return { grpc::CreateChannel(target, grpc::InsecureChannelCredentials()) };
}

bool
TryToSubscribeNotifications(Client &client)
{
  using std::chrono_literals::operator""ms;

  std::thread(&Client::SubscribeNotifications, &client).detach();
  std::this_thread::sleep_for(500ms);

  return client.IsSubscribed();
}

Client::Client(std::shared_ptr<Channel> channel)
  : stub_(BackendProto::RPC::NewStub(channel)), is_subscribed_(false) {}

void
Client::SubscribeNotifications()
{
  class Reader : public ClientReadReactor<BP::Notification> {
  public:
    Reader(BackendProto::RPC::Stub *stub, const BP::InitConnect &req,
      std::atomic_bool &is_subscribed) : do_notify_(is_subscribed)
    {
      do_notify_ = true;
      stub->async()->Notify(&context_, &req, this);
      StartRead(&reply_);
      StartCall();
    }

    void
    OnReadDone(bool ok) override
    {
      if (ok) {
        StartRead(&reply_);
      }
    }

    void
    OnDone(const Status &s) override
    {
      do_notify_ = false;
      std::unique_lock<std::mutex> lock(mu_);
      status_ = s;
      done_ = true;
      cv_.notify_one();
    }

    Status
    Await()
    {
      std::unique_lock<std::mutex> lock(mu_);
      cv_.wait(lock, [this] { return done_; });

      return std::move(status_);
    }

  private:
    ClientContext context_;
    BP::Notification reply_;
    std::mutex mu_;
    std::condition_variable cv_;
    Status status_;
    bool done_ = false;
    std::atomic_bool &do_notify_;
  };

  BP::InitConnect request;
  Reader reader(stub_.get(), request, is_subscribed_);
  Status status = reader.Await();

  static size_t counter = 0;
  if (!status.ok()) {
    std::cout << "Notification rpc failed. Attempt #" << ++counter << std::endl;
  }
}

bool
Client::IsSubscribed() const
{
  return is_subscribed_.load();
}
