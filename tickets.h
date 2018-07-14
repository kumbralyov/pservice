#ifndef TICKETS_H
#define TICKETS_H

#include <QString>
#include <QLineEdit>
#include <QDebug>
#include <QMainWindow>
#include <QRegExp>
#include <QMessageBox>
#include <mainwindow.h>
#include <math.h>

class tickets : public QMainWindow
{
    Q_OBJECT

public:
    tickets();
    tickets(QString s);
    tickets(QString s, float sm);
    tickets(const tickets &t);
    ~tickets();

    // перегрузка операторов
    friend tickets operator -(const tickets &a, const tickets &b);
    friend tickets operator +(const tickets &a, const tickets &b);
    tickets& operator =(const tickets &t);

    // получение информации об объекте
    QString get_numbers();      // получить номера билетов
    int get_count();            // получить количество билетов
    float get_sum();            // получить сумму билетов
    float get_cost();           // получить цену (среднюю цену) билетов
    bool have_errors();         // узнать, есть ли ошибки
    bool is_valid() const;      // проверка соответствия между количеством билетов, их суммой и ценой
    QString get_errors();       // получить информацию о наличии ошибок

    // уставновка параметров
    void set_cost(float c);     // установить цену билета

    // защита текстового поля
    void set_le_tickets_format(QLineEdit *le);      // установить защиту на текстовое поле для ввода номеров билетов

    void show_state();

private:
    QString str_tickets = "";       // введённая строка
    QString numbers = "";           // номера билетов в отформатированном формате
    int count = 0;                  // количество билетов
    float sum = 0;                  // сумма билетов
    float cost = 0;                 // стоимость билетов
    QString errors = "";            // информация об ошибках
    int num_errors = 0;             // количество ошибок
    QLineEdit *le_tickets_format;   // текстовое поле для ввода номеров билетов

    struct s_num
    {
        QString s;
        int begin;
        int end;
    };

    QVector<s_num> v_numbers;

public:
    tickets(QVector<s_num> &vn, int sm);

private slots:
    // форматирование строки
    QString formatted_string(QString s);            // отформатировать строку
    QString structed_string(QString s, bool d);     // отформатировать строку (с удалением лишних символов в конце строки)
    QVector<s_num> string_to_struct(QString f);     // преобразует строку в вектор
    void remove_duplicates(QVector<s_num> &sn);     // удаляет дубликаты номеров билетов
    static QString struct_to_string(const QVector<s_num> &sn);  // преобразует вектор в строку
    static bool series_sorting(const s_num &s1, const s_num &s2);     // вспомогательная функция, сортирует серии в алфавитном порядке

    // подсчёт количества, суммы и цены билетов
    int count_tickets();                // подсчитать количество билетов
    float sum_tickets();                // вычислить сумму билетов
    float cost_tickets();               // вычислить среднюю цену билета

    // добавление информации об ошибках
    void add_error(int e);              // добавить информацию об ошибке
    void add_error(int e, int i);       // добавить информацию об ошибке (с указанием индекса ошибочного символа)
    void add_error(int e, int i, QString s);       // добавить информацию об ошибке (с указанием индекса ошибочного символа)

    // защита текстового поля
    void set_le_tickets_format_r();     // вспомогательная функция, которая осуществляет защиту текстового поля для ввода номеров билетов
};

#endif // TICKETS_H
