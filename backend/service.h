#ifndef BACKEND_H
#define BACKEND_H

#include <condition_variable>
#include <map>
#include <vector>

#include <backend.grpc.pb.h>

using namespace BackendProto;

class ServiceImlp final : public RPC::CallbackService {
public:
  grpc::ServerWriteReactor<Notification> *
  Notify(grpc::CallbackServerContext *, const InitConnect *) override;
};

#endif
