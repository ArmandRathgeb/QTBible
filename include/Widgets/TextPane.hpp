#ifndef QTBIBLE_TEXTPANE_HPP
#define QTBIBLE_TEXTPANE_HPP

#include <kddockwidgets/DockWidget.h>
#include "Tools/Bible.hpp"

class TextPane : public KDDockWidgets::DockWidget {
Q_OBJECT
public:
    explicit TextPane(const QString& title, const QVector<Tools::Bible>& bibles);

private slots:
    void createContextMenu(const QPoint& pnt);
    void switchVersions(int index);

private:
    void setupToolbar();
    void setupTextArea();
    const QVector<Tools::Bible>& bibles_;
    QTextEdit* text;
    QToolBar* tools_;
    QComboBox* versions_;

};


#endif //QTBIBLE_TEXTPANE_HPP
