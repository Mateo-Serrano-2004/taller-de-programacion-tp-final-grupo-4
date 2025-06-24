#ifndef CLIENT_GAME_SOUND_SOUND_EFFECT_PLAYER_H
#define CLIENT_GAME_SOUND_SOUND_EFFECT_PLAYER_H

namespace Model {
class GameState;
};

namespace View {
class SoundEffectPlayer {
private:
    void play_tracked_sounds(const Model::GameState& game_state);
    void play_radio_message(const Model::GameState& game_state);
    void play_bomb_state(const Model::GameState& game_state);
    void play_explosion(const Model::GameState& game_state);
    void play_winning_sound(const Model::GameState& game_state);

public:
    SoundEffectPlayer() = default;

    void play(const Model::GameState& game_state);

    ~SoundEffectPlayer() = default;
};
};  // namespace View

#endif  // CLIENT_GAME_SOUND_SOUND_EFFECT_PLAYER_H
