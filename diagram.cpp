#include "diagram.h"

diagram::diagram(QWidget *parent) : QMainWindow(parent)
{
    this->show();
    draw_pie_chart();
}

diagram::diagram(QVector<diagram::d_data> get_data, float w, float h)
{
    legend_title = new QGraphicsTextItem();

    qSort(get_data.begin(), get_data.end(), diagram::d_data_sorting);

    float sum = 0;
    for (int i = 0; i < get_data.size(); i++)
    {
        sum += get_data[i].value;
    }
    for (int i = 0; i < get_data.size(); i++)
    {
        get_data[i].percent = round(get_data[i].value/sum * 1000) / 1000;
    }

    draw_pie_chart();
    w = w*0.7;
    h = h*0.7;
    d_width = w/2;
    d_height = h;
    diameter = (d_width < d_height) ? d_width : d_height;
    offset = diameter * 0.03;
    diameter = diameter - offset;
    draw_pie_chart_sectors(get_data);
    draw_legend(get_data);

    legend_view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    legend_view->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
}

void diagram::enterEvent(QEvent *e)
{
    legend_view->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    legend_view->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
}

void diagram::leaveEvent (QEvent *e)
{
    legend_view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    legend_view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

void diagram::set_title(QString s)
{
    title->setText(s);
}

void diagram::set_legend_title(QString s)
{
    legend_title_text = s;
    legend_title->setTextWidth(diameter);
    legend_title->setPos(0, 0);
    legend_title->setHtml("<p align = \"center\">" + s + "</p>");
    legend_field->addItem(legend_title);
}

void diagram::set_unit(QString s)
{
    int i = 0;
    while (i < legend_text.size())
    {
        legend_text[i]->setPlainText(legend_text[i]->toPlainText() + " " + s);
        i++;
    }
}

void diagram::draw_pie_chart()
{
    QGridLayout *gl = new QGridLayout;
    QWidget *wgt = new QWidget (this);

    title = new QLabel("");
    title->setText(title_text);
    QFont font;
    font.setBold(true);
    font.setPointSize(12);
    title->setFont(font);
    title->setAlignment(Qt::AlignCenter);
    title->setStyleSheet("background-color: white");
    gl->addWidget(title, 0, 0, 1, 2);

    QBrush brush;
    brush.setColor("black");
    brush.setStyle(Qt::SolidPattern);
    QPen pen;
    pen.setBrush(brush);

    pie_chart_field = new QGraphicsScene();
    pie_chart_view = new QGraphicsView;
    pie_chart_view->setScene(pie_chart_field);

    legend_view = new QGraphicsView;
    legend_field = new QGraphicsScene();
    legend_view->setScene(legend_field);

    gl->addWidget(pie_chart_view, 1, 0, 1, 1);
    gl->addWidget(legend_view, 1, 1, 1, 1);
    gl->setColumnStretch(0, 3);
    gl->setColumnStretch(1, 2);
    gl->setSpacing(0);
    pie_chart_view->setFrameShape(QFrame::NoFrame);
    legend_view->setFrameShape(QFrame::NoFrame);
//    qDebug() << __FILE__ << __LINE__ << gl->sizeConstraint() << gl->sizeHint();

    wgt->setLayout(gl);
    this->setCentralWidget(wgt);
}

void diagram::draw_pie_chart_sectors(QVector<diagram::d_data> get_data)
{
    float offsetX = offset;
    float offsetY = offset;
    float radius = diameter/2;
    float centerX = radius + offsetX;
    float centerY = radius + offsetY;

    float angle_p = 0;
    float rad_p = 0;
    float angle = 0;
    float rad = 0;

    QPolygon *pol = new QPolygon();
    QBrush brush;
    QPen pen;

    float p = 0;
    float d = 0;

    int b = 0;

    int i = 0;
    while (i < get_data.size() && get_data[i].percent > 0)
    {
        b = 0;
        if (get_data[i].percent > 0.5)
            b = 1;
        for (int a = 0; a <= b; a++)
        {
            brush.setColor(get_color(i));
            brush.setStyle(Qt::SolidPattern);
            pen.setBrush(brush);

            angle_p = 360 * p;
            while (angle_p >= 360)
                angle_p = angle_p - 360;
            while (angle_p < 0)
                angle_p = angle_p + 360;
            rad_p = (angle_p-90)*3.141593/180;

            if (get_data[i].percent > 0.5)
                d = get_data[i].percent/2 + p;
            else
                d = get_data[i].percent + p;

            angle = 360 * d;
            while (angle >= 360)
                angle = angle - 360;
            while (angle < 0)
                angle = angle + 360;
            rad = (angle-90)*3.141593/180;

            *pol << QPoint(centerX, centerY)
                 << QPoint(radius+10+radius*cos(rad_p), radius+10+radius*sin(rad_p))
                 << QPoint(radius+10+radius*cos(rad), radius+10+radius*sin(rad));

            pie_chart_field->addPolygon(*pol, pen, brush);
            pie_chart_field->addLine(radius+10+radius*cos(rad_p), radius+10+radius*sin(rad_p), radius+10+radius*cos(rad), radius+10+radius*sin(rad), pen);

            float step = 0.1 / diameter /*0.0005*/;
            while (p+step <= d-step)
            {
                angle_p = 360 * (p+step);
                while (angle_p >= 360)
                    angle_p = angle_p - 360;
                while (angle_p < 0)
                    angle_p = angle_p + 360;
                rad_p = (angle_p-90)*3.141593/180;

                angle = 360 * (d-step);
                while (angle >= 360)
                    angle = angle - 360;
                while (angle < 0)
                    angle = angle + 360;
                rad = (angle-90)*3.141593/180;

                pie_chart_field->addLine(radius+10+radius*cos(rad_p), radius+10+radius*sin(rad_p), radius+10+radius*cos(rad), radius+10+radius*sin(rad), pen);
                step += 0.1 / diameter /*0.0005*/;
            }

            angle_p = 360 * (p+step+100);
            while (angle_p >= 360)
                angle_p = angle_p - 360;
            while (angle_p < 0)
                angle_p = angle_p + 360;
            rad_p = (angle_p-90)*3.14159/180;

            if (a == 0)
            {
                QGraphicsTextItem *legend_note = new QGraphicsTextItem();
                legend_note->setHtml("<p align = \"center\">" + QString::number(get_data[i].percent*100) + "</p>");
                legend_note->setPos(radius+radius*cos(rad_p)*1.1-5, radius+radius*sin(rad_p)*1.1);
                pie_chart_field->addItem(legend_note);
            }


            pol->clear();
            p = d;
        }
        i++;
    }
}

void diagram::draw_legend(QVector<diagram::d_data> get_data)
{
    QBrush brush;
    QPen pen;
    float w_rect = 10;
    float h_rect = 20;

    set_legend_title(legend_title_text);

    int i = 0;
    while (i < get_data.size() && get_data[i].percent > 0)
    {
        brush.setColor(get_color(i));
        brush.setStyle(Qt::SolidPattern);
        pen.setBrush(brush);
        legend_field->addRect(offset, (offset+h_rect)*(i+1)+10, w_rect, h_rect, pen, brush);

        legend_text.append(new QGraphicsTextItem(get_data[i].name + "\n" + QString::number(get_data[i].value)));

//        legend_text = new QGraphicsTextItem(get_data[i].name + "\n" + QString::number(get_data[i].value));
        legend_text[i]->setPos(offset+5+w_rect, (offset+h_rect)*(i+1)+5);
        legend_text[i]->setBoundingRegionGranularity(0);
        legend_field->addItem(legend_text[i]);
//        qDebug() << __FILE__ << __LINE__ << i << offset+w_rect << offset+h_rect << w_rect << h_rect;
        i++;
    }
}

QColor diagram::get_color(int i)
{
    int start = 240;
    int step = 100;
    int m = i%6;
    int n = i/6;

    int r = 0, g = 0, b = 0;
    switch (m) {
    case 0:
        r = start-n*step; g = 0; b = 0; break;
    case 1:
        r = 0; g = start-n*step; b = 0; break;
    case 2:
        r = 0; g = 0; b = start-n*step; break;
    case 3:
        r = start-n*step; g = start-n*step; b = 0; break;
    case 4:
        r = start-n*step; g = 0; b = start-n*step; break;
    case 5:
        r = 0; g = start-n*step; b = start-n*step; break;
    case 6:
        r = start-n*n*step; g = start-n*step; b = 0; break;
    }

    int c[3] = {r, g, b};

    for (int j = 0; j < 3; j++)
    {
        while (c[j] > 255)
            c[j] = c[j] - 255;
    }


    for (int j = 0; j < 3; j++)
    {
        while (c[j] < 0)
            c[j] = c[j] + 255;
    }

    QColor col(c[0], c[1], c[2]);
    return col;
}

bool diagram::d_data_sorting(const diagram::d_data &d1, const diagram::d_data &d2)
{
    return d1.value > d2.value;
}
