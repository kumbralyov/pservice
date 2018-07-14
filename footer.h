#ifndef FOOTER_H
#define FOOTER_H

#include <QMainWindow>
#include <QGridLayout>
#include <QLabel>
#include <QSqlQueryModel>

class footer : public QMainWindow
{
    Q_OBJECT
public:
    explicit footer(QSqlQueryModel *m, QWidget *parent = 0);

private:
    QSqlQueryModel *model;

    QLabel *lb_all;
    QLabel *lb_sel;

    QVector<int> cols;
    int shift;

//    int all_count = 0;
//    int sel_count = 0;
//    float all_sum = 0;
//    float sel_sum = 0;

signals:

public slots:
    void set_footer_sum(int col);
    void recount_all();
    void recount_sel(QVector<int> sels);
    void set_shift(int sh);
};

#endif // FOOTER_H
