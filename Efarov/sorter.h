#ifndef SORTER_H
#define SORTER_H

#include <algorithm>
#include <QDebug>
#include <QString>


class Sorter
{
private:
    int *__arr;
    int __n;
    bool __asc;

    void __quickSort(int *arr, int low, int high);

public:
    Sorter(int *arr = nullptr, int n = 0, bool asc = true);
    void setList(int *arr, int n);
    void setDirect(bool asc);
    int* list() const;
    int size() const;
    bool direct() const;
    void bubleSort();
    void selectSort();
    void exchangeSort();
    void insertSort();
    void shellSort();
    void combSort();
    void quickSort();
    ~Sorter();

    friend void debugOutputList(const Sorter &sorter);
};

#endif // SORTER_H
