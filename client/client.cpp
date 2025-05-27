#include "client.h"

#include "game/counter_strike_app.h"
#include "game/event/event.h"
#include "game/event/create_game_event.h"
#include "game/event/join_match_event.h"
#include "game/dto_handler/event_dto_creator.h"

void Client::run() {
	Shared<Model::Event> event;

	if (join.empty()) {
		event = make_shared<Model::CreateGameEvent>("p", "p");
	} else {
		event = make_shared<Model::JoinMatchEvent>(0);
	}

	DTO::EventDTOCreator creator(event);

	protocol.send_event(creator);

	App::CounterStrikeApp cs_app(protocol);
}
