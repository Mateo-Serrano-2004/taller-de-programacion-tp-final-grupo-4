#ifndef CLIENT_GAME_SOUND_SOUND_EFFECT_PLAYER_H
#define CLIENT_GAME_SOUND_SOUND_EFFECT_PLAYER_H

namespace Model {
class GameState;
};

namespace View {
class SoundEffectPlayer {
public:
    SoundEffectPlayer() = default;

    void play(const Model::GameState& game_state);

    ~SoundEffectPlayer() = default;
};
};

#endif // CLIENT_GAME_SOUND_SOUND_EFFECT_PLAYER_H
