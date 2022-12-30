#include "pch.hpp"

#include "Dialogs/Settings.hpp"
#include "Utils/Download.hpp"
#include "Utils/Utils.hpp"
#include "Tools/WordChart.hpp"
#include "Widgets/TextPane.hpp"
#include "MainDisplay.hpp"

MainDisplay::MainDisplay()
    : kdd::MainWindow("QTBible", kdd::MainWindowOption_HasCentralFrame)
    , down(new Utils::Download(QUrl(VERSION_HEADER), this))
    , settings_()
    , toolbar(nullptr)
    , showMenu(nullptr)
    , quit(nullptr)
    , settings_menu(nullptr)
{
    kdd::MainWindow::showMaximized();

    qDebug() << "Loading...";
    createMenus();
    createToolbars();
    createShortcuts();
    loadVersions();
    loadSettings();

}

MainDisplay::~MainDisplay() {
    writeSettings();
}

void MainDisplay::showSettings() {
    Settings(this).exec();
}

void MainDisplay::createMenus() {
    settings_menu = new QAction(QIcon::fromTheme("settings"), "&Settings", this);
    showMenu = new QAction("&Show menu", this);
    showMenu->setCheckable(true);
    quit = new QAction(QIcon::fromTheme("exit"), "&Quit", this);

    auto* file = menuBar()->addMenu("&File");
    file->addAction(settings_menu);
    file->addAction(showMenu);
    file->addAction(quit);

    connect(settings_menu, &QAction::triggered, this, &MainDisplay::showSettings);
    connect(quit, &QAction::triggered, qApp, &QApplication::quit);
    connect(showMenu, &QAction::triggered, [&] {
        auto val = showMenu->isChecked();
        menuBar()->setVisible(val);
        settings_.setValue("MainWindow/ShowMenuBar", val);
    });

}

void MainDisplay::createToolbars() {
    toolbar = addToolBar("Main");

    toolbar->addAction(quit);
    toolbar->addAction(settings_menu);
    toolbar->addSeparator();

}

void MainDisplay::createShortcuts() {
    using QSC = QShortcut;
    using QKS = QKeySequence;
    connect(new QSC(QKS("CTRL+Q"), this), &QShortcut::activated, qApp, &QApplication::quit);
    connect(new QSC(QKS("CTRL+ALT+S"), this), &QShortcut::activated, this, &MainDisplay::showSettings);
    connect(new QSC(QKS("CTRL+T"), this), &QShortcut::activated, this, &MainDisplay::addNewText);
}

void MainDisplay::loadVersions() {
    connect(down, &Utils::Download::downloaded, [&] {
        readVersionsFromJson(QJsonDocument::fromJson(down->getData()));
    });
    connect(down, &Utils::Download::error, [] {
        qFatal("Failed to get versions. Check your internet connection");
    });
}

void MainDisplay::readVersionsFromJson(const QJsonDocument& doc) {
    qDebug() << "Started parsing versions";
    for (const auto& value : doc.object()["data"].toArray()) {
        const auto& obj = value.toObject();
        bibles_.push_back({
            obj["name"].toString(),
            obj["id"].toString(),
            obj["abbreviation"].toString(),
            obj["description"].toString(),
            obj["language"].toString()
        });
    }
    std::sort(bibles_.begin(), bibles_.end());
    if (bibles_.isEmpty()) {
        qFatal("Error occurred getting versions!");
    }
    qDebug() << "Parsed " << bibles_.size() << " versions";
    addNewText();
}

void MainDisplay::loadSettings() {
    auto checked = settings_.value("MainWindow/ShowMenuBar").toBool();
    menuBar()->setVisible(checked);
    showMenu->setChecked(checked);
}

void MainDisplay::writeSettings() {

}

#ifndef Q_OS_MAC
void MainDisplay::keyReleaseEvent(QKeyEvent* evt) {
    if (evt->key() == Qt::Key_Alt && !settings_.value("MainWindow/ShowMenuBar").toBool()) {
        menuBar()->setVisible(!menuBar()->isVisible());
    } else {
        QMainWindow::keyReleaseEvent(evt);
    }
}
#endif

void MainDisplay::addNewText() {
    if (!bibles_.isEmpty()) {
        open_texts.push_back(new TextPane(bibles_.front().name(), bibles_));
        addDockWidget(open_texts.back(), kdd::Location_OnLeft);
        addDockWidgetAsTab(open_texts.back());
    }
}

