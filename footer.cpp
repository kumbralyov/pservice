#include "footer.h"

footer::footer(QSqlQueryModel *m, QWidget *parent) : QMainWindow(parent)
{
    model = m;

    QGridLayout *gl = new QGridLayout;

    QWidget *wgt = new QWidget (this);

    lb_all = new QLabel;
    gl->addWidget(lb_all, 0, 0, 1, 1);

    lb_sel = new QLabel;
    gl->addWidget(lb_sel, 0, 1, 1, 1);

    wgt->setLayout(gl);
    this->setCentralWidget(wgt);
}

void footer::set_footer_sum(int col)
{
    cols.append(col);
    recount_all();
}

void footer::recount_all()
{
    lb_all->clear();
    lb_all->setText(lb_all->text() + "\nВсего записей: " + QString::number(model->rowCount()));

    for (int icols = 0; icols < cols.size(); icols++)
    {
        int all_sum = 0;

        for (int i = 0; i < model->rowCount(); i++)
        {
            all_sum += model->data(model->index(i, cols[icols]+shift)).toFloat();
        }

        QString col_header = model->headerData(cols[icols]+shift, Qt::Horizontal).toString();
        col_header = col_header.replace("\n", " ");
        lb_all->setText(lb_all->text() + "\n" + col_header + " (все записи): " + QString::number(all_sum));
    }
}

void footer::recount_sel(QVector<int> sels)
{
    lb_sel->clear();
    lb_sel->setText(lb_sel->text() + "\nВыделено записей: " + QString::number(sels.size()));

    for (int icols = 0; icols < cols.size(); icols++)
    {
        int sel_sum = 0;

        for (int i = 0; i < sels.size(); i++)
        {
            sel_sum += model->data(model->index(sels[i], cols[icols]+shift)).toFloat();
        }

        QString col_header = model->headerData(cols[icols]+shift, Qt::Horizontal).toString();
        col_header = col_header.replace("\n", " ");
        lb_sel->setText(lb_sel->text() + "\n" + col_header + " (выделенные записи): " + QString::number(sel_sum));
    }
}

void footer::set_shift(int sh)
{
    shift = sh;
}
