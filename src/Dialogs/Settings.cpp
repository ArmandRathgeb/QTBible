#include "pch.hpp"

#include "include/Dialogs/Settings.hpp"

Settings::Settings(QWidget* parent)
    : QDialog(parent)
{
    auto* vbox = new QVBoxLayout(this);
    setWindowTitle("QTBible - Settings");
    resize(400, 600);

    {
        auto* hbox = new QHBoxLayout();
        std_buttons = new QDialogButtonBox(
                QDialogButtonBox::Ok |
                QDialogButtonBox::Cancel |
                QDialogButtonBox::Apply,
                Qt::Horizontal,
                this
                );
        connect(std_buttons, &QDialogButtonBox::accepted, this, &Settings::accept);
        connect(std_buttons, &QDialogButtonBox::rejected, this, &Settings::reject);
        connect(std_buttons, &QDialogButtonBox::clicked, [&](auto* button) {
            if (std_buttons->buttonRole(button) == QDialogButtonBox::ApplyRole) {
                applySettings();
            }
        });
        connect(this, &Settings::accepted, this, &Settings::applySettings);

        hbox->addWidget(std_buttons, 1, Qt::AlignRight);
        vbox->addStretch(1);
        vbox->addLayout(hbox);
    }
    setLayout(vbox);
}

void Settings::applySettings() {
    qDebug() << "Applying settings";
}
