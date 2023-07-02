#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <math.h>
#include <cmath>
#include <time.h>

using namespace std;
template <class T>

class SimpleArray {
public:
    SimpleArray(int n);     // init to size n
    SimpleArray();		     // init to zero size
    SimpleArray(const SimpleArray<T>&);
    SimpleArray(int n, T x);
    ~SimpleArray(); 	// destroy
    T& operator[ ](int i);  // subscript (вызывается при использовании оператор [])
    int numElems();
    SimpleArray<T>& operator=(const SimpleArray<T>&); //вызывается при операции присвоения
    SimpleArray<T>& operator=(T); // set values
    void setSize(int n);
private:
    int num_elems;
    T *ptr_to_data;
    void copy(const SimpleArray<T>& a);
};

template <class T>
SimpleArray<T>::SimpleArray(int n) {
    num_elems = n;
    ptr_to_data = new T[n];
}

template <class T>
SimpleArray<T>::SimpleArray() {
    num_elems = 0;
    ptr_to_data = 0; // set pointer to null
}

template <class T>
SimpleArray<T>::SimpleArray(const SimpleArray<T>& a) {
    num_elems = a.num_elems;
    ptr_to_data = new T[num_elems];
    copy(a); // copy a elements
}

template <class T>
SimpleArray<T>::SimpleArray(int n, T array) {
    num_elems = n;
    ptr_to_data = new T[n];
    for (int i = 0; i < num_elems; i++){
        ptr_to_data[i] = array;
    }
}

template <class T>
void SimpleArray<T>::copy(const SimpleArray<T>& a){  // copy elements of ‘a’ into the elements of *this
    for (int i = 0; i < num_elems; i++){
        ptr_to_data[i] = a.ptr_to_data[i];
    }
}

template <class T>
SimpleArray<T>::~SimpleArray() { //реализация деструктора
    delete [] ptr_to_data;
}

template <class T>
T& SimpleArray<T>::operator [] (int i){
    return ptr_to_data[i];
}

template <class T>
SimpleArray<T>& SimpleArray<T>::operator=(const SimpleArray<T>& rhs) {
    if (ptr_to_data != rhs.ptr_to_data){    //проверяет, что объект не присваивается сам себе
        setSize (rhs.num_elems);
        copy (rhs);
    }
    return *this;                           //указатель на объект, с которым этот метод класса был вызван
}

template <class T>
SimpleArray<T>& SimpleArray<T>::operator=(T rhs) { //пример функции присвоения значений всем элементам массива
    T* p = ptr_to_data + num_elems;
    while (p > ptr_to_data)
        *--p = rhs;
    return *this;
}

template <class T>
int SimpleArray<T>::numElems(){
    return num_elems;
}

template <class T>
void SimpleArray<T>::setSize(int n){
    SimpleArray<T> x(n);
    if (n < num_elems){
        for (int i = 0; i < n; i++){
            x[i] = ptr_to_data[i];
        }
        delete [] ptr_to_data;
        num_elems = n;
        ptr_to_data = new T[n];
        for (int i = 0; i < num_elems; i++){
            ptr_to_data[i] = x[i];
        }
    }
    else {
        for (int i = 0; i < n; i++){
            if (i < num_elems)
                x[i] = ptr_to_data[i];
            else
                x[i] = 0;
            //cout << x[i] << endl;
        }
        delete [] ptr_to_data;
        num_elems = n;
        ptr_to_data = new T[n];
        for (int i = 0; i < num_elems; i++){
            ptr_to_data[i] = x[i];
            //cout << ptr_to_data[i] << endl;
        }
    }
}

int main() {
cout << "Задать размер массива: ";
            int n_1;
            cin >> n_1;
            cout << endl;
            SimpleArray<double> x(n_1);
            for (int i = 0; i < n_1; i++){
                cin >> x[i];
                cout << x[i] << endl;
            }
            cout << endl;
            cout << "Количество элементов массива: " << x.numElems() << endl;
            cout << endl;
            int n_2;
            cout << "Задать новый размер массива: ";
            cin >> n_2;
            x.setSize(n_2);
            for (int i = 0; i < n_2; i++){
                cout << x[i] << endl;
            }
            cout << endl;
            cout << "Задать размер массива: ";
            int dim;
            cin >> dim;
            cout << "Присвоение определенного значения: ";
            short z;
            cin >> z;
            SimpleArray<short> arr(dim, z);
            for (int i = 0; i < dim; i++){
                cout << arr[i] <<endl;
            }
return 0;
}
