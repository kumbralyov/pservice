#ifndef DIAGRAM_H
#define DIAGRAM_H

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QMainWindow>
#include <QWidget>
#include <QDebug>

#include <QApplication>
#include <QGridLayout>
#include <QDesktopWidget>
#include <QGraphicsTextItem>
#include <QScrollBar>
#include <QLabel>

class diagram : public QMainWindow
{
    Q_OBJECT
public:
    explicit diagram(QWidget *parent = 0);

    struct d_data
    {
        QString name;
        float value;
        float percent;
    };

    QVector<d_data> v_data;

    diagram(QVector<d_data> get_data, float w, float h);

    QLabel *title;
    QGraphicsTextItem *legend_title;
    QGraphicsView *pie_chart_view;
    QGraphicsView *legend_view;
    QGraphicsScene *pie_chart_field;
    QGraphicsScene *legend_field;
    QVector<QGraphicsTextItem*> legend_text;

    void enterEvent(QEvent *e);
    void leaveEvent(QEvent *e);

private:
    QString title_text = "No title";
    QString legend_title_text = "No title";
    QString unit = "";
    float d_width;
    float d_height;
    float offset;
    float diameter;

signals:

public slots:
    void set_title(QString s);
    void set_legend_title(QString s);
    void set_unit(QString s);

private slots:
    void draw_pie_chart();
    void draw_pie_chart_sectors(QVector<diagram::d_data> get_data);
    void draw_legend(QVector<diagram::d_data> get_data);
    QColor get_color(int i);
    static bool d_data_sorting(const d_data &d1, const d_data &d2);
};

#endif // DIAGRAM_H
