#ifndef GAME_SESSION_H
#define GAME_SESSION_H

#include <QString>

class GameSession {

private:
    QString username;
    QString mapName;
    QString gameName;
    QString joinedGame;
    bool joining = false;
    
public:
    void setUsername(const QString& username);
    void setMapName(const QString& map);
    void setGameName(const QString& gameName);
    void setJoinedGame(const QString& gameName);

    QString getUsername() const;
    QString getMapName() const;
    QString getGameName() const;
    QString getJoinedGame() const;
    bool isJoining() const;


};

#endif // GAME_SESSION_H
