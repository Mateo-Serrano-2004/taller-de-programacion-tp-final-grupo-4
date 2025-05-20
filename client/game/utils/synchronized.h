#ifndef CLIENT_GAME_UTILS_SYNCHRONIZED_H
#define CLIENT_GAME_UTILS_SYNCHRONIZED_H

#include <memory>

#include "client/game/definitions.h"

namespace Abstract {
    template <typename T>
    class Synchronized {
    protected:
        TSQueue<T>* queue;
        bool valid_message;
        TS<T> message;

        void await_for_message();
        bool is_last_message_valid();

    public:
        Synchronized(TSQueue<T>* queue) : queue(queue), valid_message(false) {}

        virtual ~Synchronized() = default;
    };

    template <typename T>
    inline void Synchronized<T>::await_for_message() {
        try {
            valid_message = queue->try_pop(message);
        } catch (ClosedQueue& error) {
            valid_message = false;
        }
    }
    template <typename T>
    inline bool Synchronized<T>::is_last_message_valid() {
        return valid_message;
    }
    };  // namespace Abstract

#endif // CLIENT_GAME_UTILS_SYNCHRONIZED_H
