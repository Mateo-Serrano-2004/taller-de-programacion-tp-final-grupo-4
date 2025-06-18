#ifndef CLIENT_EVENT_QUIT_EVENT_H
#define CLIENT_EVENT_QUIT_EVENT_H

#include "common/DTO/event_dto.h"
#include "dto_handler/dto_creator_visitor.h"

#include "transfered_event.h"

namespace Model {
class QuitEvent: public TransferedEvent {
public:
    QuitEvent(): TransferedEvent(EventType::QUIT) {}

    DTO::EventDTO as_dto() override;

    ~QuitEvent() override = default;
};
};  // namespace Model

#endif  // CLIENT_EVENT_QUIT_EVENT_H
