#ifndef COMMON_ROUND_STATE_H
#define COMMON_ROUND_STATE_H

enum class RoundState {
    Warmup = 0x00,
    Buying = 0x01,
    Active = 0x02,
    PostRound = 0x03,
    Ended = 0x04
};
#endif  // COMMON_ROUND_STATE_H
