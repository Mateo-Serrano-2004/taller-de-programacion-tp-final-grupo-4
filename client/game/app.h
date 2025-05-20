#ifndef CLIENT_GAME_APP_H
#define CLIENT_GAME_APP_H

namespace App {
    class App {
    public:
        virtual void run() = 0;

        virtual ~App() = default;
    };
};

#endif // CLIENT_GAME_APP_H
