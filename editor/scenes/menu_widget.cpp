#include "menu_widget.h"

#include <QFileDialog>
#include <QHBoxLayout>
#include <QVBoxLayout>

#include "../widgets/styled_button.h"
#include "../widgets/styled_file_dialog.h"

MenuWidget::MenuWidget(QWidget* parent): QWidget(parent) {
    createMapBtn = new StyledButton("Crear mapa", this);
    editMapBtn = new StyledButton("Editar mapa", this);

    createMapBtn->setMinimumSize(180, 54);
    editMapBtn->setMinimumSize(180, 54);
    createMapBtn->setMaximumSize(220, 80);
    editMapBtn->setMaximumSize(220, 80);

    createMapBtn->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    editMapBtn->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    QHBoxLayout* hLayout = new QHBoxLayout();
    hLayout->addStretch();
    hLayout->addWidget(createMapBtn);
    hLayout->addSpacing(40);
    hLayout->addWidget(editMapBtn);
    hLayout->addStretch();

    QVBoxLayout* vLayout = new QVBoxLayout(this);
    vLayout->addStretch();
    vLayout->addLayout(hLayout);
    vLayout->addStretch();
    setLayout(vLayout);

    connect(createMapBtn, &QPushButton::clicked, this, &MenuWidget::createMapRequested);
    connect(editMapBtn, &QPushButton::clicked, this, [this]() {
        StyledFileDialog fileDialog(this);
        fileDialog.setNameFilter("Archivos YAML (*.yaml *.yml)");
        fileDialog.setWindowTitle("Seleccionar mapa YAML");
        if (fileDialog.exec() == QDialog::Accepted) {
            QString filePath = fileDialog.selectedFiles().first();
            if (!filePath.isEmpty())
                emit editMapRequested(filePath);
        }
    });
}
