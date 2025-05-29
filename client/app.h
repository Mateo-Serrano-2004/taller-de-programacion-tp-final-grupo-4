#ifndef CLIENT_APP_H
#define CLIENT_APP_H

namespace App {
class App {
public:
    virtual void run() = 0;

    virtual ~App() = default;
};
};  // namespace App

#endif  // CLIENT_APP_H
