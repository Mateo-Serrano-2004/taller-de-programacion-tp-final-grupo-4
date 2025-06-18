#ifndef CLIENT_GAME_ENTITY_GAPPED_H
#define CLIENT_GAME_ENTITY_GAPPED_H

namespace View {
class Gapped {
protected:
    int gap_y;
    int gap_x;

public:
    explicit Gapped(int gap_y, int gap_x);

    int get_gap_y() const;
    int get_gap_x() const;

    void set_gap_y(int new_gap);
    void set_gap_x(int new_gap);

    virtual ~Gapped() = default;
};
};  // namespace View

#endif  // CLIENT_GAME_ENTITY_GAPPED_H
