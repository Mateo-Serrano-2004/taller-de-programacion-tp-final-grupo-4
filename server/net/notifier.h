#ifndef SERVER_NET_NOTIFIER_H
#define SERVER_NET_NOTIFIER_H

#include <mutex>
#include <condition_variable>

class Notifier {
private:
    std::mutex mutex;
    std::condition_variable cv;

public:
    Notifier() = default;

    void wait_for_notification();
    void notify();

    ~Notifier() = default;
};

#endif // SERVER_NET_NOTIFIER_H
