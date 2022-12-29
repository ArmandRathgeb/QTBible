#ifndef QTBIBLE_SETTINGS_HPP
#define QTBIBLE_SETTINGS_HPP

#include <QDialog>
#include <QDialogButtonBox>

class Settings : public QDialog {
Q_OBJECT
public:
    Settings(QWidget* parent = nullptr);

public slots:
    void applySettings();

private:
    QDialogButtonBox* std_buttons;
};


#endif //QTBIBLE_SETTINGS_HPP
