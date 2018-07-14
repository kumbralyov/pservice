#include "home.h"

#include <QAction>
#include <QFileDialog>
#include <QImageWriter>
#include <QScreen>
#include <QTextDocumentWriter>
#include <QToolButton>

home::home(QWidget *parent) : QMainWindow(parent)
{
    this->resize(parent->size());
    form_show();
}

home::~home()
{
    db.close();
}

int home::form_show()
{
    QGridLayout *gl = new QGridLayout;
    gl->setColumnStretch(0, 3);
    gl->setColumnStretch(1, 2);

    QWidget *wgt = new QWidget (this);

    QFile file(":/qss/te-style");
    file.open(QFile::ReadOnly);
    QString styleSheet = QLatin1String(file.readAll());
    QTextDocument *table_doc = new QTextDocument();
    table_doc->setDefaultStyleSheet(styleSheet);
    table_doc->setHtml(table_data());

    te = new QTextEdit;
    te->clear();
    te->setDocument(table_doc);
    te->setReadOnly(true);
    gl->addWidget(te, 0, 0, 2, 1);

    QVector<diagram::d_data> v_branches = branches_complete();

    d_branches = new diagram(v_branches, QApplication::desktop()->screenGeometry().width()/2, QApplication::desktop()->screenGeometry().height());
    d_branches->set_title("Доля домов культуры в общей сумме, %");
    d_branches->set_legend_title("Дома культуры");
    d_branches->set_unit("руб.");
    gl->addWidget(d_branches, 0, 1, 1, 1);

    QVector<diagram::d_data> v_kinds = kinds_complete();

    d_kinds = new diagram(v_kinds, QApplication::desktop()->screenGeometry().width()/2, QApplication::desktop()->screenGeometry().height());
    d_kinds->set_title("Доля видов услуг в общей сумме, %");
    d_kinds->set_legend_title("Виды услуг");
    d_kinds->set_unit("руб.");
    gl->addWidget(d_kinds, 1, 1, 1, 1);

    this->addToolBar(tool_bar_create());

    wgt->setLayout(gl);
    this->setCentralWidget(wgt);

    return 0;
}

QToolBar *home::tool_bar_create()
{
#ifdef Q_OS_WIN32
    QImage img_branches = d_branches->grab().toImage();
    QImage img_kinds = d_kinds->grab().toImage();
#endif

    tb = new QToolBar;

    QAction *ac_print_doc = new QAction(QIcon(), "распечатать таблицу", this);
    connect(ac_print_doc, SIGNAL(triggered()), this, SLOT(print_prev()));

#ifdef Q_OS_WIN32
    QAction *ac_print_img_branches = new QAction(QIcon(), "распечатать диаграмму (дома культуры)", this);
    connect(ac_print_img_branches, &QAction::triggered, [img_branches, this]() {print_prev(img_branches);});

    QAction *ac_print_img_kinds = new QAction(QIcon(), "распечатать диаграмму (виды услуг)", this);
    connect(ac_print_img_kinds, &QAction::triggered, [img_kinds, this]() {print_prev(img_kinds);});
#endif

    QAction *ac_save_doc = new QAction(QIcon(), "сохранить таблицу", this);
    connect(ac_save_doc, SIGNAL(triggered()), this, SLOT(save_doc()));

#ifdef Q_OS_WIN32
    QAction *ac_save_img_branches = new QAction(QIcon(), "сохранить диаграмму (дома культуры)", this);
    connect(ac_save_img_branches, &QAction::triggered, [img_branches, this]() {save_img(img_branches);});

    QAction *ac_save_img_kinds = new QAction(QIcon(), "сохранить диаграмму (виды услуг)", this);
    connect(ac_save_img_kinds, &QAction::triggered, [img_kinds, this]() {save_img(img_kinds);});
#endif

    QToolButton *tbn_save = new QToolButton();
    tbn_save->setPopupMode(QToolButton::InstantPopup);
    tbn_save->setIcon(QIcon(":/img/save-pic"));
    tbn_save->addAction(ac_save_doc);
#ifdef Q_OS_WIN32
    tbn_save->addAction(ac_save_img_branches);
    tbn_save->addAction(ac_save_img_kinds);
#endif
    tb->addWidget(tbn_save);

    QToolButton *tbn_print = new QToolButton();
    tbn_print->setPopupMode(QToolButton::InstantPopup);
    tbn_print->setIcon(QIcon(":/img/print-pic"));
    tbn_print->addAction(ac_print_doc);
#ifdef Q_OS_WIN32
    tbn_print->addAction(ac_print_img_branches);
    tbn_print->addAction(ac_print_img_kinds);
#endif
    tb->addWidget(tbn_print);

    return tb;
}

QString home::table_data()
{
    QString strsql;
    strsql.clear();
    strsql = "select T1.branch_name, sio, soo, sioc, sooc, ton, tstn, tsta, tshn, tsha, trtn, trta, tos, T5.id_location "
            "from "
                "(((select branch_name, sum(sum_in_oper) as sio "
                "from branches left outer join "
                    "(select id_branch, sum_in_oper "
                    "from in_operations "
                    "where year(date_in_oper) < year(curdate())) as io "
                "on branches.id_branch = io.id_branch "
                "group by id_location, branch_name "
                ") as T1 left outer join "
                "(select branch_name, sum(sum_out_oper) as soo "
                "from branches left outer join "
                    "(select id_branch, sum_out_oper "
                    "from out_operations "
                    "where year(date_out_oper) < year(curdate())) as oo "
                "on branches.id_branch = oo.id_branch "
                "group by id_location, branch_name "
                ") as T2 on T1.branch_name = T2.branch_name) left join "

                "((select branch_name, sum(sum_in_oper) as sioc "
                "from branches left outer join "
                    "(select id_branch, sum_in_oper "
                    "from in_operations "
                    "where year(date_in_oper) = year(curdate())) as ioc "
                "on branches.id_branch = ioc.id_branch "
                "group by id_location, branch_name "
                ") as T3 left outer join "
                "(select branch_name, sum(sum_out_oper) as sooc "
                "from branches left outer join "
                    "(select id_branch, sum_out_oper "
                    "from out_operations "
                    "where year(date_out_oper) = year(curdate())) as ooc "
                "on branches.id_branch = ooc.id_branch "
                "group by id_location, branch_name "
                ") as T4 on T3.branch_name = T4.branch_name) on T1.branch_name = T3.branch_name) left join "

                "((select branch_name, id_location, sum(tickets_out_cost*tickets_out_amount) as tos, group_concat(tickets_out_numbers separator ';') as ton "
                "from branches left outer join tickets_out on branches.id_branch = tickets_out.id_branch "
                "group by id_location, branch_name "
                ") as T5 left outer join "
                "(select branch_name, "
                        "group_concat(tickets_stub_numbers separator ';') as tstn, "
                        "sum(tickets_stub_amount * tickets_cost) as tsta, "
                        "group_concat(tickets_shortage_numbers separator ';') as tshn, "
                        "sum(tickets_shortage_amount * tickets_cost) as tsha, "
                        "group_concat(tickets_return_numbers separator ';') as trtn, "
                        "sum(tickets_return_amount * tickets_cost) as trta "
                "from branches left outer join tickets_reports on branches.id_branch = tickets_reports.id_branch "
                "group by id_location, branch_name "
                ") as T6 on T5.branch_name = T6.branch_name) on T1.branch_name = T5.branch_name ";


    QSqlQuery *quer = new QSqlQuery(db);
    quer->exec(strsql);

    int cur = 0;
    int beg = 0;
    int sum = 0;
    int spent = 0;

    int cur_s = 0;
    int beg_s = 0;
    int sum_s = 0;
    int spent_s = 0;

    int cur_t = 0;
    int beg_t = 0;
    int sum_t = 0;
    int spent_t = 0;

    int loc = -1;

    QString table;
    if (quer->isActive())
    {
        table = "<table border=\"1\" width=\"100%\" cellspacing=\"-1\" cellpadding=\"5\">"
                "<tr class=\"top\">"
                "<th rowspan=\"2\">Дом культуры</th><th rowspan=\"2\">Текущий остаток</th><th rowspan=\"2\">Остаток на начало года</th><th rowspan=\"2\">Собрано</th><th rowspan=\"2\">Израсходовано</th>"
                "<th colspan=\"3\">Билеты</th><tr class=\"top2\"><th>кол-во</th><th>сумма</th><th>номера</th></tr>"
                "</tr>";
        while (quer->next())
        {
            if (loc == -1)
            {
                loc = quer->value(13).toInt();
            }
            if (loc == quer->value(13).toInt())
            {
                cur_s += cur;
                beg_s += beg;
                sum_s += sum;
                spent_s += spent;
                cur_t += cur;
                beg_t += beg;
                sum_t += sum;
                spent_t += spent;
            }
            else
            {
                loc = quer->value(13).toInt();
                cur_s += cur;
                beg_s += beg;
                sum_s += sum;
                spent_s += spent;
                cur_t += cur;
                beg_t += beg;
                sum_t += sum;
                spent_t += spent;
                table = table + "<tr class=\"top2\">"
                        "<td>Итого:</td><td>%1</td><td>%2</td><td>%3</td><td>%4</td><td></td><td></td><td></td>"
                        "</tr>";
                table = table.arg(cur_s)
                     .arg(beg_s)
                     .arg(sum_s)
                     .arg(spent_s);
                cur_s = 0;
                beg_s = 0;
                sum_s = 0;
                spent_s = 0;
            }

            tickets t_out(quer->value(5).toString(), quer->value(12).toFloat());
            tickets t_stub(quer->value(6).toString(), quer->value(7).toFloat());
            tickets t_shortage(quer->value(8).toString(), quer->value(9).toFloat());
            tickets t_return(quer->value(10).toString(), quer->value(11).toFloat());
            tickets t = t_out - t_stub - t_shortage - t_return;
            table = table + "<tr>"
                    "<td>%1</td><td>%2</td><td>%3</td><td>%4</td><td>%5</td><td>%6</td><td>%7</td><td>%8</td>"
                    "</tr>";

            cur = quer->value(3).toInt() - quer->value(4).toInt() + quer->value(1).toInt() - quer->value(2).toInt();
            beg = quer->value(1).toInt() - quer->value(2).toInt();
            sum = quer->value(3).toInt();
            spent = quer->value(4).toInt();

            table = table.arg(quer->value(0).toString())
                 .arg(cur)
                 .arg(beg)
                 .arg(sum)
                 .arg(spent)
                 .arg(t.get_count())
                 .arg(t.get_sum())
                 .arg(t.get_numbers());
        }

        cur_s += cur;
        beg_s += beg;
        sum_s += sum;
        spent_s += spent;
        cur_t += cur;
        beg_t += beg;
        sum_t += sum;
        spent_t += spent;
        table = table + "<tr class=\"top2\">"
                "<td>Итого:</td><td>%1</td><td>%2</td><td>%3</td><td>%4</td><td></td><td></td><td></td>"
                "</tr>";
        table = table.arg(cur_s)
             .arg(beg_s)
             .arg(sum_s)
             .arg(spent_s);

        table = table + "<tr class=\"top\"><td>Итого:</td><td>%1</td><td>%2</td><td>%3</td><td>%4</td><td></td><td></td><td></td></tr>";
        table = table.arg(cur_t)
             .arg(beg_t)
             .arg(sum_t)
             .arg(spent_t);
        table = table + "</table>";
    }

    return table;
}

QVector<diagram::d_data> home::branches_complete()
{
    QVector<diagram::d_data> v;
    QString strsql;
    strsql.clear();
    strsql = "select branches.branch_name, sum(in_operations.sum_in_oper) "
            "from in_operations "
            "left join branches on in_operations.id_branch = branches.id_branch "
            "where year(in_operations.date_in_oper) = year(curdate()) "
            "group by branches.id_branch ";

    QSqlQuery *quer = new QSqlQuery(db);
    quer->exec(strsql);

    if (quer->isActive())
    {
        while (quer->next())
        {
            v.append({quer->value(0).toString(), quer->value(1).toInt()});
        }
    }
    return v;
}

QVector<diagram::d_data> home::kinds_complete()
{
    QVector<diagram::d_data> v;
    QString strsql;
    strsql.clear();
    strsql = "select paid_services.pservice_name, sum(in_operations.sum_in_oper) "
            "from in_operations "
            "left join paid_services on in_operations.id_pservice = paid_services.id_pservice "
            "where year(in_operations.date_in_oper) = year(curdate()) "
            "group by paid_services.id_pservice  ";

    QSqlQuery *quer = new QSqlQuery(db);
    quer->exec(strsql);
    qDebug() << __FILE__ << __LINE__ << quer->lastError().text();

    if (quer->isActive())
    {
        while (quer->next())
        {
            v.append({quer->value(0).toString(), quer->value(1).toInt()});
        }
    }
    return v;
}

void home::print_prev()
{
    QPrinter printer;
    printer.setPageMargins(30, 20, 15, 20, QPrinter::Millimeter);
    QPrintPreviewDialog *prev = new QPrintPreviewDialog(&printer);
    connect(prev, SIGNAL(paintRequested(QPrinter*)), this, SLOT(print(QPrinter*)));
    prev->exec();
    delete prev;
}

void home::print_prev(QImage img)
{
    QPrinter printer;
    printer.setPageMargins(30, 20, 15, 20, QPrinter::Millimeter);
    QPrintPreviewDialog *prev = new QPrintPreviewDialog(&printer);
    connect(prev, &QPrintPreviewDialog::paintRequested, [img, this](QPrinter *printer) {print(printer, img);});
    prev->exec();
    delete prev;
}

void home::print(QPrinter* printer)
{
    QTextDocument textDocument;
    textDocument.setHtml(te->toHtml());
    textDocument.setPageSize(QSizeF(printer->pageRect().size()));
    textDocument.print(printer);
}

void home::print(QPrinter *printer, QImage img)
{
    QPainter painter(printer);
    painter.drawImage(QPoint(0,0), img);
    painter.end();
}

void home::save_doc()
{
    QFileDialog fd;

#ifdef Q_OS_WIN32
    QString sfx = "doc";
#endif

#ifdef Q_OS_LINUX
    QString sfx = "odt";
#endif

    fd.setDefaultSuffix(sfx);
    QString str = fd.getSaveFileName(this, QString("Сохранить документ"), "file."+sfx, "Тестовые файлы (*."+sfx+")", nullptr);

    QTextDocument textDocument;
    textDocument.setHtml(te->toHtml());
    QTextDocumentWriter writer(str);
    writer.setFormat("html");
    writer.write(&textDocument);
}

void home::save_img(QImage img)
{
    QString str = QFileDialog::getSaveFileName(this, QString("Сохранить изображение"), QString(), QString("(*.jpg)"), nullptr);
    img.save(str);
}
