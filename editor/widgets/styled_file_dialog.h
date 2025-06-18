#ifndef STYLED_FILE_DIALOG_H
#define STYLED_FILE_DIALOG_H

#include <QFileDialog>

class StyledFileDialog: public QFileDialog {
    Q_OBJECT

public:
    explicit StyledFileDialog(QWidget* parent = nullptr): QFileDialog(parent) {
        this->setOption(QFileDialog::DontUseNativeDialog, true);
        this->setStyleSheet(R"(
        QFileDialog {
            background-color: #f5f5f5;
        }
        QFileDialog QWidget {
            background-color: #f5f5f5;
            color: black;
        }
        QFileDialog QListView {
            background-color: white;
            border: 1px solid #cccccc;
        }
        QFileDialog QLineEdit {
            background-color: white;
            border: 1px solid #cccccc;
            padding: 4px;
        }
        QFileDialog QPushButton {
            background-color: #4CAF50;
            color: white;
            border: none;
            border-radius: 4px;
            padding: 8px 16px;
            font-size: 14px;
            font-weight: bold;
        }
        QFileDialog QPushButton:hover {
            background-color: #45a049;
        }
        QFileDialog QPushButton:pressed {
            background-color: #3d8b40;
        }
    )");
    }
};

#endif  // STYLED_FILE_DIALOG_H
