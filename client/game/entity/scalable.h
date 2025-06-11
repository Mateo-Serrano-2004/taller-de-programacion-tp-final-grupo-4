#ifndef CLIENT_GAME_ENTITY_SCALABLE_H
#define CLIENT_GAME_ENTITY_SCALABLE_H

#include <SDL2pp/Point.hh>

#include "common/definitions.h"

namespace View {
class Scalable {
protected:
    bool apply_scalation;
    bool keep_aspect_ratio;
    
    SDL2pp::Point max_bounds;
    SDL2pp::Point min_bounds;
    SDL2pp::Point max_size;
    SDL2pp::Point min_size;
    SDL2pp::Point current_size;

    void scalate(const SDL2pp::Point& viewport);

public:
    Scalable(SDL2pp::Point max_bounds,SDL2pp::Point min_bounds);

    SDL2pp::Point get_max_bounds() const;
    int get_max_bounds_height() const;
    int get_max_bounds_width() const;
    SDL2pp::Point get_min_bounds() const;
    int get_min_bounds_height() const;
    int get_min_bounds_width() const;
    SDL2pp::Point get_max_size() const;
    int get_max_height() const;
    int get_max_width() const;
    SDL2pp::Point get_min_size() const;
    int get_min_height() const;
    int get_min_width() const;
    SDL2pp::Point get_size() const;
    int get_height() const;
    int get_width() const;

    void set_apply_scalation(bool new_apply_scalation);
    void set_keep_aspect_ratio(bool new_keep_aspect_ratio);
    void set_max_bound(const SDL2pp::Point& new_bounds);
    void set_max_bounds_height(int new_height);
    void set_max_bounds_width(int new_width);
    void set_min_bound(const SDL2pp::Point& new_bounds);
    void set_min_bounds_height(int new_height);
    void set_min_bounds_width(int new_width);
    void set_max_size(const SDL2pp::Point& new_bounds);
    void set_max_height(int new_height);
    void set_max_width(int new_width);
    void set_min_size(const SDL2pp::Point& new_bounds);
    void set_min_height(int new_height);
    void set_min_width(int new_width);

    virtual ~Scalable() = default;
};
};

#endif // CLIENT_GAME_ENTITY_SCALABLE_H
