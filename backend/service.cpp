#include "service.h"

grpc::ServerWriteReactor<Notification> *
ServiceImlp::Notify(grpc::CallbackServerContext *ctx, const InitConnect *req)
{
class Notifier : public grpc::ServerWriteReactor<Notification> {
  public:
    Notifier(grpc::CallbackServerContext *, const InitConnect *)
    {
      NextWrite();
    }

    void
    OnDone() override
    {
      delete this;
    }

    void
    OnWriteDone(bool ok) override
    {
      if (ok) {
        NextWrite();
      }
    }

  private:
    void NextWrite()
    {
      StartWrite(&reply_);
    }

    Notification reply_;
  };

  return new Notifier(ctx, req);
}
