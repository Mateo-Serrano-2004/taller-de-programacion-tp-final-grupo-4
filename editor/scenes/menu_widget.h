#ifndef MENU_WIDGET_H
#define MENU_WIDGET_H

#include <QPushButton>
#include <QWidget>

class MenuWidget: public QWidget {
    Q_OBJECT
public:
    explicit MenuWidget(QWidget* parent = nullptr);

signals:
    void createMapRequested();
    void editMapRequested(const QString& filePath);

private:
    QPushButton* createMapBtn = nullptr;
    QPushButton* editMapBtn = nullptr;
};

#endif  // MENU_WIDGET_H
