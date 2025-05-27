#ifndef LOBBY_CONTROLLER_H
#define LOBBY_CONTROLLER_H

class LobbyController : public QObject {
    Q_OBJECT
private:
    Net::ClientProtocol& protocol;

signals:
    void receivedGames(const QStringList& games);
    void receivedMaps(const QStringList& maps);
    void gameJoined();
    void gameCreated();
    void sentUsername();
public:
    LobbyController(Net::ClientProtocol& protocol, QObject* parent = nullptr);

    void receiveJoinableGames();
    void requestGameMaps();
    void sendJoinGameRequest(const QString& gameName);
    void sendCreationGameRequest(const QString& gameName, const QString& mapName);
    void sendUsername(const QString& username);
}