#include "notifier.h"

#include <mutex>
#include <condition_variable>

void Notifier::wait_for_notification() {
    std::unique_lock<std::mutex> lock(mutex);
    cv.wait(lock);
}

void Notifier::notify() {
    std::unique_lock<std::mutex> lock(mutex);
    cv.notify_all();
}
