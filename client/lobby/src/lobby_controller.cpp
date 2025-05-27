#include "lobby_controller.h"

LobbyController::LobbyController(Net::ClientProtocol& protocol, QObject* parent)
    : QObject(parent), protocol(protocol) {}

void LobbyController::sendUsername(const QString& username) {
    protocol.sendUsername(username.toStdString());
}

void LobbyController::requestGameMaps() {

    //std::vector<std::string> mapas = protocol.receiveMaps();
    QStringList list;
    for (const auto& m : mapas)
        list << QString::fromStdString(m);
    emit receivedMaps(list);

}

void LobbyController::sendCreationGameRequest(const QString& name, const QString& map) {
    //protocol.createGame(nombre.toStdString(), mapa.toStdString());
    emit partidaCreada();
}

void LobbyController::sendJoinGameRequest(const QString& nombrePartida) {
    //protocol.joinGAme(nombrePartida.toStdString());
    emit joinedGame();

}
