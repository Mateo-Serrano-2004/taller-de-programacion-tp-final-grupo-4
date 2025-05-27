#ifndef CLIENT_NET_PROTOCOL_H
#define CLIENT_NET_PROTOCOL_H

#include <cstdint>

#include "common/DTO/match_dto.h"
#include "common/DTO/event_dto_creator.h"

namespace Net {
    class ClientProtocol {
    private:
    public:
        uint8_t receive_match_state();
        MatchDTO receive_reference_player_id();
        void send_event(EventDTOCreator& event_dto_creator);
    };
};

#endif // CLIENT_NET_PROTOCOL_H
