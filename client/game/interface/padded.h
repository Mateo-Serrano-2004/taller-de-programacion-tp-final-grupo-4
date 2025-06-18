#ifndef CLIENT_GAME_ENTITY_PADDED_H
#define CLIENT_GAME_ENTITY_PADDED_H

namespace View {
class Padded {
protected:
    int padding;

public:
    explicit Padded(int padding = 0);

    int get_padding() const;

    virtual void set_padding(int new_padding);

    virtual ~Padded() = default;
};
};  // namespace View

#endif  // CLIENT_GAME_ENTITY_PADDED_H
