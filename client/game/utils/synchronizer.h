#ifndef CLIENT_GAME_UTILS_SYNCHRONIZER_H
#define CLIENT_GAME_UTILS_SYNCHRONIZER_H

#include "client/game/definitions.h"

namespace Abstract {
    template <typename T>
    class Synchronizer {
    protected:
        TSQueue<T> queue;

    public:
        void send_message(TS<T> value);

        TSQueue<T>* get_queue();

        virtual ~Synchronizer() = default;
    };

    template <typename T>
    inline void Synchronizer<T>::send_message(TS<T> value) {
        try {
            TS<T> dummy_val;
            queue.try_pop(dummy_val);
            queue.push(value);
        } catch (ClosedQueue& error) {
            // Do nothing
        }
    }

    template <typename T>
    inline TSQueue<T>* Synchronizer<T>::get_queue() {
        return &queue;
    }
    };

#endif // CLIENT_GAME_UTILS_SYNCHRONIZER_H
