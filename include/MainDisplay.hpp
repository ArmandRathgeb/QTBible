#ifndef QTBIBLE_MAINDISPLAY_HPP
#define QTBIBLE_MAINDISPLAY_HPP

#include <kddockwidgets/MainWindow.h>
#include <QToolBar>
#include <QVector>
#include <QDockWidget>
#include "Tools/Bible.hpp"
#include "Widgets/TextPane.hpp"
#include "Utils/Download.hpp"

class MainDisplay : public KDDockWidgets::MainWindow {
Q_OBJECT
public:
    MainDisplay();
    ~MainDisplay() override;

private slots:
    void showSettings();
#ifndef Q_OS_MAC
    void keyReleaseEvent(QKeyEvent* evt) override;
#endif

private:
    void createMenus();
    void createToolbars();
    void createShortcuts();
    void loadVersions();
    void readVersionsFromJson(const QJsonDocument& doc);
    void loadSettings();
    void writeSettings();
    void addNewText();

    Utils::Download* down;
    QVector<Tools::Bible> bibles_;
    QSettings settings_;
    QAction* settings_menu;
    QAction* showMenu;
    QAction* quit;
    QToolBar* toolbar;
    QVector<TextPane*> open_texts;
};


#endif //QTBIBLE_MAINDISPLAY_HPP
