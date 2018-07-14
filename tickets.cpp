#include "tickets.h"

tickets::tickets()
{

}

tickets::tickets(QString s)
{
    str_tickets = s;
    numbers = structed_string(s, true);
    if (s != "")
    {
        count = count_tickets();
        sum = 0;
        cost = 0;
    }
    else
    {
        count = 0;
        sum = 0;
        cost = 0;
    }
}

tickets::tickets(QString s, float sm)
{
    str_tickets = s;
    numbers = structed_string(s, true);
    if (numbers != "" && sm >= 0)
    {
        sum = sm;
        count = count_tickets();
        cost = cost_tickets();
    }
    else if (numbers == "" && sm == 0)
    {
        count = 0;
        sum = 0;
        cost = 0;
    }
    else
    {
        if (sm < 0)
            add_error(111);
        else
            add_error(900);
        count = -1;
        sum = -1;
        cost = -1;
    }
}

tickets::tickets(const tickets &t) : QMainWindow()
{
    this->str_tickets = t.str_tickets;
    this->numbers = t.numbers;
    this->count = t.count;
    this->sum = t.sum;
    this->cost = t.cost;
    this->v_numbers = t.v_numbers;
}

tickets::tickets(QVector<s_num> &vn, int sm)
{
    str_tickets = struct_to_string(vn);
    numbers = structed_string(str_tickets, true);
    if (numbers != "" && sm >= 0)
    {
        sum = sm;
        count = count_tickets();
        cost = cost_tickets();
    }
    else if (numbers == "" && sm == 0)
    {
        count = 0;
        sum = 0;
        cost = 0;
    }
    else
    {
        if (sm < 0)
            add_error(111);
        else
            add_error(900);
        count = -1;
        sum = -1;
        cost = -1;
    }
}

tickets::~tickets()
{

}


// перегрузка операторов

tickets operator -(const tickets &a, const tickets &b)
{
    QVector<tickets::s_num> vn = a.v_numbers;
    for (int i = 0; i < vn.size(); i++)
    {
        for (int j = 0; j < b.v_numbers.size(); j++)
        {
            if (vn[i].s == b.v_numbers[j].s)
            {
                if (b.v_numbers[j].begin >= vn[i].begin && b.v_numbers[j].begin <= vn[i].end &&
                        b.v_numbers[j].end >= vn[i].begin && b.v_numbers[j].end <= vn[i].end)
                {
                    if (b.v_numbers[j].begin > vn[i].begin && b.v_numbers[j].end == vn[i].end)
                    {
                        vn[i].end = b.v_numbers[j].begin-1;
                    }
                    else if (b.v_numbers[j].end < vn[i].end && b.v_numbers[j].begin == vn[i].begin)
                    {
                        vn[i].begin = b.v_numbers[j].end+1;
                    }
                    else if (b.v_numbers[j].end == vn[i].end && b.v_numbers[j].begin == vn[i].begin)
                        vn[i].s = "-";
                    else
                    {
                        vn.append({vn[i].s, b.v_numbers[j].end+1, vn[i].end});
                        vn[i].end = b.v_numbers[j].begin-1;
                    }
                }
            }
        }
    }
    int i = 0;
    while (i < vn.size())
    {
        if (vn[i].s == "-")
            vn.remove(i);
        else
            i++;
    }
    qSort(vn.begin(), vn.end(), tickets::series_sorting);
    return tickets(vn, a.sum-b.sum);
}

tickets operator +(const tickets &a, const tickets &b)
{
    float sm = -1;
    if (a.is_valid() == true && b.is_valid() == true)
        sm = a.sum + b.sum;
    return tickets(a.str_tickets + ";" + b.str_tickets, sm);
}

tickets &tickets::operator =(const tickets &t)
{
    this->str_tickets = t.str_tickets;
    this->numbers = t.numbers;
    this->count = t.count;
    this->sum = t.sum;
    this->cost = t.cost;
    this->v_numbers = t.v_numbers;
    return *this;
}


// получение информации об объекте

QString tickets::get_numbers()
{
    return numbers;
}

int tickets::get_count()
{
    return count;
}

float tickets::get_sum()
{
    return sum;
}

float tickets::get_cost()
{
    return cost;
}

bool tickets::have_errors()
{
    if (num_errors > 0)
        return true;
    else
        return false;
}

bool tickets::is_valid() const
{
    bool b;
    if (count >= 0 && cost >= 0 && sum >= 0)
    {
        if (count > 0)
        {
            if (sum == count * cost)
                b = true;
            else
                b = false;
        }
        else if (count == 0)
        {
            if (sum == 0 && cost == 0)
                b = true;
            else
                b = false;
        }
    }
    else
    {
        b = false;
    }
    return b;
}

QString tickets::get_errors()
{
    QString s = "Исходная строка: " + str_tickets + "\n";
    s += "Всего ошибок: " + QString::number(num_errors) + "\n";
    s += errors;
    s += "Отформатированная строка: " + numbers;
    return s;
}


// уставновка параметров

void tickets::set_cost(float c)
{
    if (c >= 0)
        cost = round(c * 100) / 100;
    else
    {
        add_error(111);
        cost = -1;
    }
    sum = sum_tickets();
}


// защита текстового поля

void tickets::set_le_tickets_format(QLineEdit *le)
{
    le_tickets_format = le;
    tickets(le->text());
    connect(le, SIGNAL(textChanged(QString)), this, SLOT(set_le_tickets_format_r()));
}


// форматирование строки

QString tickets::formatted_string(QString s)
{
    // функция автоматически исправляет несоответствия формату (кроме ошибки 107 "возможно, строка не дописана");
    // при обнаружении несоответствия формату в переменную errors вносится информация об ошибке,
    // а также переменная num_errors увеличивается на единицу

    // формат: серия - 1-5 букв, номер - 1-6 цифр, дипозон номеров разделяется дифисом,
    // перечисляемые номера разделяются запятой, билеты разных серий разделяются точкой с запятой
    // прочие символы недопустимы

    // состояния
    //    0     начальное состояние
    //    1-5   введена буква
    //    6-11  введена цифра
    //    12    введена запятая
    //    13    введена точка с запятой
    //    14    введён дефис
    // ошибки
    //    100	введена пустая строка
    //    101	слишком длинное название серии
    //    102	слишком длинный номер
    //    103	пропущено название серии билетов
    //    104	пропущено первое число диапозона номеров билетов
    //    105	пропущено второе число диапозона номеров билетов
    //    106	пропущен диапозон номеров билетов или введена лишняя запятая / точка с запятой
    //    107	возможно, строка не дописана
    //    108	введён недопустимый символ
    // прочее
    //    200	завершить проверку
    // для 101-106, 108	- вернуть предыдущее значение Q, для 100, 107 - завершить проверку (Q=200)

    QString f = "";
    s = s.toUpper();
    errors.clear();
    num_errors = 0;

    int a=0, i=0, q=0, qr=0;
    int TQA[15][7] = {
    //  0       1       2       3       4       5       6
    //  а..я    0..9    ,       ;       -       прочие  \0
        {1,  	103,  	106,  	106,  	104,  	108,  	100},   // 0
        {2,  	6,  	106,  	106,  	104,  	108,  	107},   // 1
        {3,  	6,  	106,  	106,  	104,  	108,  	107},   // 2
        {4,  	6,  	106,  	106,  	104,  	108,  	107},   // 3
        {5,  	6,  	106,  	106,  	104,  	108,  	107},   // 4
        {101,  	6,  	106,  	106,  	104,  	108,  	107},   // 5
        {1,  	7,  	12,  	13,  	14,  	108,  	200},   // 6
        {1,  	8,  	12,  	13,  	14,  	108,  	200},   // 7
        {1,  	9,  	12,  	13,  	14,  	108,  	200},   // 8
        {1,  	10,  	12,  	13,  	14,  	108,  	200},   // 9
        {1,  	11,  	12,  	13,  	14,  	108,  	200},   // 10
        {1,  	102,  	12,  	13,  	14,  	108,  	200},   // 11
        {1,  	6,  	106,  	106,  	104,  	108,  	107},   // 12
        {1,  	103,  	106,  	106,  	104,  	108,  	107},   // 13
        {105,  	6,  	105,  	105,  	14,  	108,  	107},   // 14
    };

    while (q != 200 && i < s.size())
    {
        if (s[i].isLetter()) a=0;
        else if (s[i] >= '0' && s[i] <= '9') a = 1;
        else if (s[i] == ',') a = 2;
        else if (s[i] == ';') a = 3;
        else if (s[i] == '-') a = 4;
        else if (s[i] == '\0') a = 6;
        else a = 5;
        qr = q;
        q = TQA[q][a];
        if ((q >= 0) && (q <= 14))
        {
            if (i > 0 && s[i-1].isNumber() && s[i].isLetter())
                f += ";";
            f += s[i];
        }

        switch (q)
        {
            case 100: /*add_error(q);*/ q = 200; break;
            case 101: add_error(q, i); q = qr; break;
            case 102: add_error(q, i); q = qr; break;
            case 103: add_error(q, i); q = qr; break;
            case 104: add_error(q, i); q = qr; break;
            case 105: add_error(q, i); q = qr; break;
            case 106: add_error(q, i); q = qr; break;
            case 107: add_error(q); q = 200; break;
            case 108: add_error(q); q = qr; break;
        }

        i++;
    }

    return f;
}

QString tickets::structed_string(QString s, bool d)
{
    QString f = formatted_string(s);
    QString sn = "";

    if (d == true && f != "")
    {
        int j = f.size()-1;
        while (f[j].isDigit() == false)
        {
            f.remove(j, 1);
            j--;
        }

        // перевод строки в структурированный вид
        v_numbers = string_to_struct(f);

        // сортировка билетов
        qSort(v_numbers.begin(), v_numbers.end(), series_sorting);

        // удаление дубликатов билетов
        remove_duplicates(v_numbers);

        // перевод из структурированного вида в строку
        sn = struct_to_string(v_numbers);
    }

    return sn;
}

QVector<tickets::s_num> tickets::string_to_struct(QString f)
{
    int i = 0;
    QVector<s_num> sn;
    QString ser = "", begin = "", end = "";

    while (i < f.size())
    {
        begin = "";
        end = "";
        if (f[i].isLetter())
        {
            ser = "";
            while (f[i].isLetter())
            {
                ser += f[i];
                i++;
            }
            if (f[i].isDigit())
            {
                while (f[i].isDigit())
                {
                    begin += f[i];
                    i++;
                }
                if (f[i] == ',')
                {
                    end = begin;
                }
            }
        }
        if (f[i] == '-')
        {
            i++;
            if (f[i].isDigit())
            {
                while (f[i].isDigit())
                {
                    end += f[i];
                    i++;
                }
            }
        }
        if (ser != "" && begin != "" && end != "")
            sn.append({ser, begin.toInt(), end.toInt()});
        else if (ser != "" && begin != "" && end == "")
            sn.append({ser, begin.toInt(), begin.toInt()});
        if (f[i] == ',')
        {
            begin = "";
            end = "";
            i++;
            while (f[i].isDigit())
            {
                begin += f[i];
                i++;
            }
            if (f[i] == '-')
            {
                i++;
                if (f[i].isDigit())
                {
                    while (f[i].isDigit())
                    {
                        end += f[i];
                        i++;
                    }
                }
            }
            else
            {
                end = begin;
            }
            sn.append({ser, begin.toInt(), end.toInt()});
            if (f[i] == ',')
                i--;
        }
        i++;
    }
    return sn;
}

void tickets::remove_duplicates(QVector<s_num> &sn)
{
    int i = 1;
    while (i < sn.size())
    {
        if (sn[i].s == sn[i-1].s)
        {
            if (sn[i].begin-sn[i-1].end <= 0)
            {
                if (sn[i-1].end < sn[i].end)
                {
                    add_error(109, 0, sn[i].s + QString::number(sn[i].begin) + "-" + QString::number(sn[i-1].end));
                    sn[i-1].end = sn[i].end;
                }
                else
                {
                    add_error(109, 0, sn[i].s + QString::number(sn[i].begin) + "-" + QString::number(sn[i].end));
                }
                sn.remove(i, 1);
            }
            else if (sn[i].begin-sn[i-1].end == 1)
            {
                sn[i-1].end = sn[i].end;
                sn.remove(i, 1);
            }
            else
            {
                i++;
            }
        }
        else
        {
            i++;
        }
    }
}

QString tickets::struct_to_string(const QVector<s_num> &sn)
{
    QString s = "";
    for (int i = 0; i < sn.size(); i++)
    {
//        if (QString::number(sn[i].end) != QString::number(sn[i].begin))
//        {
//            if (i == 0 || sn[i].s != sn[i-1].s)
//                s += ";" + sn[i].s + QString::number(sn[i].begin) + "-" + QString::number(sn[i].end);
//            else
//                s += "," + QString::number(sn[i].begin) + "-" + QString::number(sn[i].end);
//        }
//        else
//        {
//            s += "," + QString::number(sn[i].begin);
//        }


        if (QString::number(sn[i].end) != QString::number(sn[i].begin))
        {
            if (i == 0 || sn[i].s != sn[i-1].s)
                s += ";" + sn[i].s + QString::number(sn[i].begin) + "-" + QString::number(sn[i].end);
            else
                s += "," + QString::number(sn[i].begin) + "-" + QString::number(sn[i].end);
        }
        else
        {
            if (i == 0 || sn[i].s != sn[i-1].s)
                s += ";" + sn[i].s + QString::number(sn[i].begin);
            else
                s += "," + QString::number(sn[i].begin);
        }
    }
    s.remove(0, 1);
    return s;
}

bool tickets::series_sorting(const s_num &s1, const s_num &s2)
{
    if (s1.s == s2.s)
        return (s1.begin < s2.begin);
    else
        return (s1.s < s2.s);
}


// подсчёт количества, суммы и цены билетов

int tickets::count_tickets()
{
    int c = 0;

    for (int i = 0; i < v_numbers.size(); i++)
    {
        c += v_numbers[i].end - v_numbers[i].begin + 1;
    }

    return c;
}

float tickets::sum_tickets()
{
    if (count >= 0 && cost >= 0)
        sum = round(count * cost * 100) / 100;
    else
    {
        sum = -1;
        if (count < 0) add_error(110);
        if (cost < 0) add_error(111);
    }
    return sum;
}

float tickets::cost_tickets()
{
    if (count > 0 && sum >= 0)
        cost = round(sum / count * 100) / 100;
    else if (count == 0 && sum == 0)
        cost = 0;
    else
    {
        cost = -1;
        if (count < 0) add_error(110);
        if (sum < 0) add_error(112);
    }
    return cost;
}


// добавление информации об ошибках

void tickets::add_error(int e)
{
    add_error(e, 0);
}

void tickets::add_error(int e, int i)
{
    add_error(e, i, "");
}

void tickets::add_error(int e, int i, QString s)
{
    switch (e)
    {
        case 100: errors += "введена пустая строка\n"; break;
        case 101: errors += "слишком длинное название серии (символ " + QString::number(i+1) + ")\n"; break;
        case 102: errors += "слишком длинный номер (символ " + QString::number(i+1) + ")\n"; break;
        case 103: errors += "пропущено название серии билетов (символ " + QString::number(i+1) + ")\n"; break;
        case 104: errors += "пропущено первое число диапозона номеров билетов (символ " + QString::number(i+1) + ")\n"; break;
        case 105: errors += "пропущено второе число диапозона номеров билетов (символ " + QString::number(i+1) + ")\n"; break;
        case 106: errors += "пропущен диапозон номеров билетов или введена лишняя запятая / точка с запятой (символ " + QString::number(i+1) + ")\n"; break;
        case 107: errors += "возможно, строка не дописана\n"; break;
        case 108: errors += "введён недопустимый символ\n"; break;
        case 109: errors += "билеты " + s + " внесены дважды\n"; break;
        case 110: errors += "введено отрицательное количество билетов\n"; break;
        case 111: errors += "введена отрицательная цена\n"; break;
        case 112: errors += "введена отрицательная сумма\n"; break;
        case 900: errors += "неизвестная ошибка\n"; break;
    }
    num_errors++;
}


// защита текстового поля

void tickets::set_le_tickets_format_r()
{
    QString s = formatted_string(le_tickets_format->text());
    le_tickets_format->setText(s);
}
