#ifndef QTBIBLE_WORDCHART_HPP
#define QTBIBLE_WORDCHART_HPP

#include <QString>
#include <QChart>
#include <QWidget>

namespace Tools {

    class WordChart : public QWidget {
    Q_OBJECT
    public:
        WordChart(QString passage, QWidget* parent = nullptr);

    private:
        static QWidget* createChart(QtCharts::QChart& chart, QtCharts::QChartView* view, QWidget& parent);
        static QVector<std::pair<QString, int>> countWords(QStringList& words);

        QtCharts::QChartView* histogram;
        QtCharts::QChartView* pie;
        QTabWidget* tabs;
        QStringList passage_words;
        QVector<std::pair<QString, int>> counted;
    };

} // Tools

#endif // QTBIBLE_WORDCHART_HPP
