#include "pch.hpp"
#include <QApplication>

#include "MainDisplay.hpp"

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);
    QCoreApplication::setApplicationName("QTBible");
    QCoreApplication::setOrganizationName("QTBible");

    MainDisplay disp{};
    disp.show();
    return QApplication::exec();
}
