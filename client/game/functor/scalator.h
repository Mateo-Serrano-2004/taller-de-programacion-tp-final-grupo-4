#ifndef CLIENT_GAME_FUNCTOR_SCALATOR_H
#define CLIENT_GAME_FUNCTOR_SCALATOR_H

#include <SDL2pp/Point.hh>

class Scalator {
private:
    SDL2pp::Point max_bounds;
    SDL2pp::Point min_bounds;
    SDL2pp::Point max_size;
    SDL2pp::Point min_size;

public:
    Scalator(
        SDL2pp::Point max_bounds,
        SDL2pp::Point min_bounds,
        SDL2pp::Point max_size,
        SDL2pp::Point min_size
    );

    void set_max_bounds(const SDL2pp::Point& new_bounds);
    void set_min_bounds(const SDL2pp::Point& new_bounds);
    void set_max_size(const SDL2pp::Point& new_size);
    void set_min_size(const SDL2pp::Point& new_size);

    SDL2pp::Point operator()(
        const SDL2pp::Point& viewport,
        bool keep_ratio
    ) {
        float x_percent = static_cast<float>(viewport.GetX() - min_bounds.GetX()) / (max_bounds.GetX() - min_bounds.GetX());
        float y_percent = static_cast<float>(viewport.GetY() - min_bounds.GetY()) / (max_bounds.GetY() - min_bounds.GetY());

        int scaled_x = min_size.GetX() + static_cast<int>(x_percent * (max_size.GetX() - min_size.GetX()));
        int scaled_y = min_size.GetY() + static_cast<int>(y_percent * (max_size.GetY() - min_size.GetY()));

        if (keep_ratio) {
            float aspect_ratio = static_cast<float>(min_size.GetX()) / min_size.GetY();
            if (x_percent > y_percent) {
                scaled_y = static_cast<int>(scaled_x / aspect_ratio);
            } else {
                scaled_x = static_cast<int>(scaled_y * aspect_ratio);
            }
        }

        scaled_x = std::clamp(scaled_x, min_size.GetX(), max_size.GetX());
        scaled_y = std::clamp(scaled_y, min_size.GetY(), max_size.GetY());

        return SDL2pp::Point(scaled_x, scaled_y);
    }

    ~Scalator() = default;
};

#endif // CLIENT_GAME_FUNCTOR_SCALATOR_H
