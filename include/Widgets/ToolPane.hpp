#ifndef QTBIBLE_TOOLPANE_HPP
#define QTBIBLE_TOOLPANE_HPP

#include <kddockwidgets/DockWidget.h>
#include <QString>
#include <QComboBox>

class ToolPane : public KDDockWidgets::DockWidget {
Q_OBJECT
public:
    ToolPane();

    void insertVersion(const QString& version);

private:
    QComboBox* versions_box;

};


#endif //QTBIBLE_TOOLPANE_HPP
