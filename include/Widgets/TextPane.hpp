#ifndef QTBIBLE_TEXTPANE_HPP
#define QTBIBLE_TEXTPANE_HPP

#include <kddockwidgets/DockWidget.h>
#include "Tools/Bible.hpp"

class TextPane : public KDDockWidgets::DockWidget {
Q_OBJECT
public:
    explicit TextPane(const QString& title);

private slots:
    void createContextMenu(const QPoint& pnt);

private:
    QTextEdit* text;

};


#endif //QTBIBLE_TEXTPANE_HPP
