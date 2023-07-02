#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <math.h>
#include <cmath>
#include <time.h>

using namespace std;

class SimpleFloatArray {
public:
    SimpleFloatArray(int n);     // init to size n
    SimpleFloatArray();		 // init to zero size
    SimpleFloatArray(const SimpleFloatArray&);
    SimpleFloatArray(int n, float x);
    ~SimpleFloatArray(); 	// destroy
    float& operator[ ](int i);  // subscript (вызывается при использовании оператор [])
    int numElems();
    SimpleFloatArray& operator=(const SimpleFloatArray&); //вызывается при операции присвоения
    SimpleFloatArray& operator=(float); // set values
    void setSize(int n);
private:
    int num_elems;
    float *ptr_to_data;
    void copy(const SimpleFloatArray& a);
};

SimpleFloatArray::SimpleFloatArray(int n) {
    num_elems = n;
    ptr_to_data = new float[n];
}

SimpleFloatArray::SimpleFloatArray() {
    num_elems = 0;
    ptr_to_data = 0; // set pointer to null
}

SimpleFloatArray::SimpleFloatArray(const SimpleFloatArray& a) {
    num_elems = a.num_elems;
    ptr_to_data = new float[num_elems];
    copy(a); // copy a elements
}


SimpleFloatArray::SimpleFloatArray(int n, float array) {
    num_elems = n;
    ptr_to_data = new float[n];
    for (int i = 0; i < num_elems; i++){
        ptr_to_data[i] = array;
    }
}


void SimpleFloatArray::copy(const SimpleFloatArray& a){  // copy elements of ‘a’ into the elements of *this
    for (int i = 0; i < num_elems; i++){
        ptr_to_data[i] = a.ptr_to_data[i];
    }
}

SimpleFloatArray::~SimpleFloatArray() { //реализация деструктора
    delete [] ptr_to_data;
}

float& SimpleFloatArray::operator [] (int i){
    return ptr_to_data[i];
}

SimpleFloatArray& SimpleFloatArray::operator=(const SimpleFloatArray& rhs) {
    if (ptr_to_data != rhs.ptr_to_data){ //проверяет, что объект не присваивается сам себе
        setSize (rhs.num_elems);
        copy (rhs);
    }
    return *this; //указатель на объект, с которым этот метод класса был вызван
}

SimpleFloatArray& SimpleFloatArray::operator=(float rhs) { //пример функции присвоения значений всем элементам массива
    float* p = ptr_to_data + num_elems;
    while (p > ptr_to_data)
        *--p = rhs;
    return *this;
}

int SimpleFloatArray::numElems(){
    return num_elems;
}

void SimpleFloatArray::setSize(int n){
    SimpleFloatArray x(n);
    if (n < num_elems){
        for (int i = 0; i < n; i++){
            x[i] = ptr_to_data[i];
        }
        delete [] ptr_to_data;
        num_elems = n;
        ptr_to_data = new float[n];
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
        ptr_to_data = new float[n];
        for (int i = 0; i < num_elems; i++){
            ptr_to_data[i] = x[i];
            //cout << ptr_to_data[i] << endl;
        }
    }
}

int main() {
cout << "Введите размер массива: ";
            int n_1;
            cin >> n_1;
            cout << endl;
            SimpleFloatArray x(n_1);
            for (int i = 0; i < n_1; i++){
                x[i] = i+1;
                cout << x[i] << endl;
            }
            cout << endl;
            cout << "Количество элементов массива: " << x.numElems() << endl;
            cout << endl << endl;
            SimpleFloatArray y(x);
            for (int i = 0; i < n_1; i++){
                cout << y[i] << endl;
            }
            cout << endl << endl;
            int n_2;
            cout << "Введите новый размер массива: ";
            cin >> n_2;
            x.setSize(n_2);
            for (int i = 0; i < n_2; i++){
                cout << x[i] << endl;
            }
            cout << endl << endl;
            //cout << "Введите новый размер массива: ";
            //cin >> s;
            y.setSize(n_2);
            for (int i = 0; i < n_2; i++){
                cout << y[i] << endl;
            }
            cout << endl << endl;
            cout << "Задать размер массива: ";
            int m;
            cin >> m;
            cout << "Присвоение определенного значения: ";
            float z;
            cin >> z;
            SimpleFloatArray c(m, z);
            for (int i = 0; i < m; i++){
                cout << c[i] << endl;
            }
return 0;
}
