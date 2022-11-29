#include <iostream>
#include <thread>

#include <client.h>

int
main() {
  std::string server_addr = "unix-abstract:test";
  auto client = MakeClient(server_addr);

  while (!TryToSubscribeNotifications(client));
  std::cout << "Subscribe success" << std::endl;

  size_t i = 0;
  while (true) {
    std::cout << "Do something: " << ++i << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));
  }

  return 0;
}