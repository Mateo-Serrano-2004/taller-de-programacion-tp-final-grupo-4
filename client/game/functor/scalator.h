#ifndef CLIENT_GAME_FUNCTOR_SCALATOR_H
#define CLIENT_GAME_FUNCTOR_SCALATOR_H

#include <SDL2pp/Point.hh>

class Scalator {
private:
    float x_factor;
    float y_factor;

public:
    Scalator();
    Scalator(float factor);
    Scalator(float x_factor, float y_factor);

    void set_x_factor(float new_x_factor);
    void set_y_factor(float new_y_factor);
    void set_factor(float new_factor);

    SDL2pp::Point operator()(const SDL2pp::Point& point) {
        return SDL2pp::Point((int) (point.GetX() * x_factor), (int) (point.GetY() * y_factor));
    }

    ~Scalator() = default;
};

#endif // CLIENT_GAME_FUNCTOR_SCALATOR_H
