#ifndef CLIENT_GAME_ENTITY_ALIGNER_H
#define CLIENT_GAME_ENTITY_ALIGNER_H

namespace View {
class Aligner {
protected:
    float alignment_y;
    float alignment_x;

public:
    Aligner(float alignment_y, float alignment_x);

    float get_vertical_alignment() const;
    float get_horizontal_alignment() const;

    void set_vertical_alignment(float new_alignment);
    void set_horizontal_alignment(float new_alignment);

    virtual ~Aligner() = default;
};
};  // namespace View

#endif  // CLIENT_GAME_ENTITY_ALIGNER_H
