#ifndef CLIENT_H
#define CLIENT_H

#include <string>
#include <utility>

#include "net/include/client_protocol.h"

class Client {
private:
    std::string join;
    Net::ClientProtocol protocol;

    Client(const Client&) = delete;
    Client& operator=(const Client&) = delete;

public:
    Client(
        const std::string& host,
        const std::string& port,
        const std::string& join
    ): join(join), protocol(host, port) {run();}

    void run();

    Client(Client&&) = default;
    Client& operator=(Client&&) = default;

    ~Client() = default;
};

#endif  // CLIENT_H
