// Выбрать функцию из предложенных sinx cosx x x^2
// Выбрать метод интегрирования
// Выбрать шаг интегрирования и диапазона
// Интегрировать
// Выход

#include <iostream>
#include <limits>
#include <string>
#include <math.h>
#include <map>


using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::pair;
using std::map;

enum function
{
    func_sin_x, func_cos_x, func_x, func_x2
};

enum method
{
    meth_tr, meth_rec
};

struct interval_data
{
    double begin;
    double end;
    double step;
};

struct data
{
    interval_data interval;
    method meth;
    function func;
};

double x (double a) {return a;}

double x2 (double x) {return x*x;}

double calculateIntRec(const interval_data &d, double(*f) (double))
{
    double res = 0;
    double local_begin =  d.begin;
    double local_end =  d.begin + d.step;
    while (local_begin < d.end)
    {
        if (local_end > d.end)
            local_end = d.end;
        res += (local_end - local_begin) * f((local_begin + local_end) * 0.5);
        local_begin += d.step;
        local_end = local_begin + d.step;
    }
    return res;
}

double calculateIntTr(const interval_data &d, double(*f) (double))
{
    double res = 0;
    double local_begin =  d.begin;
    double local_end =  d.begin + d.step;
    while (local_begin < d.end)
    {
        if (local_end > d.end)
            local_end = d.end;
        res += (local_end - local_begin) * (f(local_begin) + f(local_end)) * 0.5;
        local_begin += d.step;
        local_end = local_begin + d.step;
    }
    return res;
}

bool collectData(data &input_data) //возвращает false, если сбор данных не завершен
{
    string exit_string = "q";
    string input_string;

    cout << "Выберите функцию из предложенных: " << endl << "1. sin(x)\n"
                                                            "2. cos(x)\n"
                                                            "3. x\n"
                                                            "4. x^2\n";
    cout << "Для выхода введите " << exit_string << endl;
    map<string, int> functions_strings = {{"1.", func_sin_x}, {"1", func_sin_x}, {"sin(x)", func_sin_x}, {"sinx", func_sin_x},
                                         {"2.", func_cos_x}, {"2", func_cos_x}, {"cos(x)", func_cos_x}, {"cosx", func_cos_x},
                                         {"3.", func_x}, {"3", func_x}, {"x", func_x},
                                         {"4.", func_x2}, {"4", func_x2}, {"x^2", func_x2}, {"x2", func_x2}};
    while(true)
    {
        getline(cin, input_string);
        if (input_string == exit_string)
            return false;
        map<string, int>::iterator iter = functions_strings.find(input_string);
        if (iter == functions_strings.end())
            cout << "Некорректный ввод! Попробуйте еще раз" << endl;
        else
        {
            input_data.func = function(iter->second);
            break;
        }
    }
    cout << "Выберите метод интегрирования:" << endl << "1. Метод трапеций\n"
                                                         "2. Метод прямоугольников\n";
    cout << "Для выхода введите " << exit_string << endl;
    map<string, int> methods_strings = {{"1.", meth_tr}, {"1", meth_tr}, {"Метод трапеций", meth_tr}, {"метод трапеций", meth_tr},
                                       {"2.", meth_rec}, {"2", meth_rec}, {"Метод прямоугольников", meth_rec}, {"метод прямоугольников", meth_rec}};
    while(true)
    {
        getline(cin, input_string);
        if (input_string == exit_string)
            return false;
        map<string, int>::iterator iter = methods_strings.find(input_string);
        if (iter == methods_strings.end())
            cout << input_string << "Некорректный ввод! Попробуйте еще раз" << endl;
        else
        {
            input_data.meth = method(iter->second);
            break;
        }
    }

    double a, b, step;
    double max_value = 10000, min_value = -10000;
    double max_step = 20, min_step = 0.001;

    cout << "Интервал интегрирования должен лежать в пределах от " << min_value << " до " << max_value << endl;
    cout << "Шаг интегрирования должен лежать в пределах от " << min_step << " до " << max_step << endl;
    cout << "Введите интервал интегрирования и шаг интегрирования (a b step)" << endl;
    if (cin >> a >> b >> step && a >= min_value && b <= max_value && a < b && step <= max_step && step >= min_step)
    {
        input_data.interval = {a, b, step};
        return true;
    }
    cin.clear();
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    cout << "Некорректный ввод! Выберите начало интервала интегрирования из предложенных:" << endl << "1. -10000\n"
                                                                                                      "2. -1000\n"
                                                                                                      "3. -100\n"
                                                                                                      "4. -10\n"
                                                                                                      "5. -1\n"
                                                                                                      "6. 0\n";
    cout << "Для выхода введите " << exit_string << endl;
    map<string, double> begin_strings = {{"1.", -10000}, {"1", -10000}, {"-10000", -10000},
                                         {"2.", -1000}, {"2", -1000}, {"-1000", -1000},
                                         {"3.", -100}, {"3", -100}, {"-100", -100},
                                         {"4.", -10}, {"4", -10}, {"-10", -10},
                                         {"5.", -1}, {"5", -1}, {"-1", -1},
                                         {"6.", 0}, {"6", 0}, {"0", 0}};
    while(true)
    {
        getline(cin,input_string);
        if (input_string == exit_string)
            return false;
        map<string, double>::iterator iter = begin_strings.find(input_string);
        if (iter == begin_strings.end())
            cout << input_string << "Некорректный ввод! Попробуйте еще раз" << endl;
        else
        {
            input_data.interval.begin = iter->second;
            break;
        }
    }

    cout << "Выберите конец интервала интегрирования из предложенных: "<< endl << "1. 10000\n"
                                                                                  "2. 1000\n"
                                                                                  "3. 100\n"
                                                                                  "4. 10\n"
                                                                                  "5. 1.0\n"
                                                                                  "6. 0\n";
    cout << "Для выхода введите " << exit_string << endl;
    map<string, double> end_strings = {{"1.", 10000}, {"1", 10000}, {"1000", 10000},
                                       {"2.", 1000}, {"2", 1000}, {"1000", 1000},
                                       {"3.", 100}, {"3", 100}, {"100", 100},
                                       {"4.", 10}, {"4", 10}, {"10", 10},
                                       {"5.", 1}, {"5", 1}, {"1.0", 1},
                                       {"6.", 0}, {"6", 0}, {"0", 0}};
    while(true)
    {
        getline(cin,input_string);
        if (input_string == exit_string)
            return false;
        map<string, double>::iterator iter = end_strings.find(input_string);
        if (iter == end_strings.end())
            cout << "Некорректный ввод! Попробуйте еще раз" << endl;
        else
        {
            input_data.interval.end = iter->second;
            break;
        }
    }

    cout << "Выберите шаг интегрирования из предложенных:" << endl << "1. 0.01\n"
                                                                                         "2. 0.1\n"
                                                                                         "3. 1.0\n"
                                                                                         "4. 5.0\n"
                                                                                         "5. 15\n";
    cout << "Для выхода введите " << exit_string << endl;
    map<string, double> step_strings = {{"1.", 0.01}, {"1", 0.01}, {"0.01", 0.01},
                                        {"2.", 0.1}, {"2", 0.1}, {"0.1", 0.1},
                                        {"3.", 1}, {"3", 1}, {"1.0", 1},
                                        {"4.", 5}, {"4", 5}, {"5.0", 5},
                                        {"5.", 5}, {"5", 5}, {"15", 5}};
    while(true)
    {
        cin >> input_string;
        if (input_string == exit_string)
            return false;
        map<string, double>::iterator iter = step_strings.find(input_string);
        if (iter == step_strings.end())
            cout << "Некорректный ввод! Попробуйте еще раз" << endl;
        else
        {
            input_data.interval.step = iter->second;
            break;
        }
    }

    return true;
}

int main()
{
    data input_data;
    if (collectData(input_data))
    {
        double (*f) (double);
        switch (input_data.func)
        {
        case func_sin_x:
            f = sin;
            break;
        case func_cos_x:
            f = cos;
            break;
        case func_x:
            f = x;
            break;
        case func_x2:
            f = x2;
            break;
        default:
            cout << "Ошибка считывания из входных данных функции интегрирования";
            return 0;
        }
        switch (input_data.meth)
        {
        case meth_tr:
            cout << "Результат: " << calculateIntTr(input_data.interval, f) << endl;
            break;
        case meth_rec:
            cout << "Результат: " << calculateIntRec(input_data.interval, f) << endl;
            break;
        default:
            cout << "Ошибка считывания из входных данных метода интегрирования";
            return 0;
        }
    }

    return 0;
}
