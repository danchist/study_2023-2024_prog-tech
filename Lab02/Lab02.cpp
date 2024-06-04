#include <iostream>
using namespace std;

class vect {
public:
    static int count;
    int dim, num;
    double* a;

    // конструктор
    vect(int k){
        dim = k;
        num = count++;
        a = new double[k];
        for (int i=0; i<dim; i++){
            a[i] = 0;
        }
        cout << "\n A " << dim << "-dimensional Vector created" << endl << "  - Vector num: " << num << endl;

    }
    // деструктор
    ~vect() {
        delete[] a;
        a = nullptr; // если бы такой строчки не было, то a потенциально мог указывать на пустые данные, такой случить обозначим nullptr
        count--;     // понижаем кол-во всех векторов
        cout << "\n Vector " << num << " destroyed" << endl;
    }
    // делаем оператор = сразу в классе, по сути так безопаснее обращаться с данными вектора, которому мы присваиваем
    vect& operator=(const vect& diff){
        if (this != &diff){
            delete[] a;
            dim = diff.dim;
            a = new double[dim];
            for (int i = 0; i < dim; i++){
                a[i] = diff.a[i];
            }
        }
        return *this;
    }
};
// Операторы векторов: +, -, *, *k:
// объявляем об операторе, задаём постоянные, над котороым производятся действия
vect operator+(const vect& v1, const vect& v2) {
    vect res(v1.dim); // делаю новый вектор - результат
    for (int i = 0; i < v1.dim; i++) {
        res.a[i] = v1.a[i] + v2.a[i]; // иду по кол-во координат вектора и задаю сумму соответствующих двух других векторов
    }
    cout << endl << "Vector " << v1.num << " + Vector " << v2.num << endl;
    return res;
}
// аналогично, как с плюсом, просто ставим минус
vect operator-(const vect& v1, const vect& v2) {
    vect res(v1.dim);
    for (int i = 0; i < v1.dim; i++) {
        res.a[i] = v1.a[i] - v2.a[i];
    }
    cout << endl << "Vector " << v1.num << " - Vector " << v2.num << endl;
    return res;
}
// аналогично, как с плюсом, только ставим умножить
vect operator*(const vect& v1, const vect& v2) {
    vect res(v1.dim);
    for (int i = 0; i < v1.dim; i++) {
        res.a[i] = v1.a[i] * v2.a[i];
    }
    cout << endl << "Vector " << v1.num << " * Vector " << v2.num << endl;
    return res;
}
// единственное уточнение: нужно рассмотреть два случая, когда вектор умножаем на k, и k умножаем на вектор;
vect operator*(const vect& v1, const int& k) {
    vect res(v1.dim);
    for (int i = 0; i < v1.dim; i++) {
        res.a[i] = v1.a[i] * k;
    }
    cout << endl << "Vector " << v1.num << " * " << k << endl;
    return res;
}

vect operator*(const int& k, const vect& v1) {
    vect res(v1.dim);
    for (int i = 0; i < v1.dim; i++) {
        res.a[i] = v1.a[i] * k;
    }
    cout << endl << k << " * Vector " << v1.num << endl;
    return res;
}

int vect::count = 1;


// теперь делаем матрицу, единственное отличие от вектора - b это список списков, теперь нужно волноваться по
// этому поводу в некоторых случаях
class matr {
public:
    static int count;
    int dim, num;
    double** b;

    // конструктор
    matr(int k){
        dim = k;
        num = count++;
        b = new double*[dim]; // делаем список
        for (int i = 0; i < k; i++){
            b[i] = new double[dim](); // идём по списку, и в каждой ячейке создаём новый список
        }
        cout << endl << dim << "-dimensional Matrix created \n   - Matrix num: " << num << endl;
    }

    // деструктор
    ~matr() {
        for (int i = 0; i < dim; ++i) {
            delete[] b[i];
        }
        delete[] b;
        cout << "\n Matrix " << count << " destroyed" << endl;
        count--;
    }
    // делаем оператор = сразу в классе
    matr& operator=(const matr& diff){
        if (this != &diff){ // проверка на присваивание самого себя, можно время сократить, если оказывается присваиваем самого себя
            for (int i = 0; i < dim; i++){
                delete[] b[i]; // очищаем списки внутри каждой ячейки первого списка
            }
            delete[] b; // удаляем сам список

            dim = diff.dim; // присваиваем данные из другой матрицы
            b = new double*[dim]; // создаём список, идём по нему,
            for (int i = 0; i < dim; i++){
                b[i] = new double[dim]; // в каждой ячейке создаём новый список,
                for (int j = 0; j < dim; j++){
                    b[i][j] = diff.b[i][j]; //  идём по этому новому списку и переносим значения из другой матрицы
                }
            }
        }
        return *this;
    }
};

int matr::count = 1;
// операторы матрицы: +, -, *, *k
matr operator+(const matr& v1, const matr& v2) {
    matr res(v1.dim); // делаю новую матрицу - результат
    for (int i = 0; i < v1.dim; i++) {
        for (int j = 0; j < v1.dim; j++){
            res.b[i][j] = v1.b[i][j] + v2.b[i][j]; // иду по списку списков, ячейку результата задаю сумму соответствующих двух других ячеек
        }
    }
    cout << endl << "Matrix " << v1.num << " + " << v2.num << endl;
    return res;
}
// дальше всё то же самое, как и с плюсом, надо поменять операцию, а *k рассмотреть два случая
matr operator-(const matr& v1, const matr& v2) {
    matr res(v1.dim);
    for (int i = 0; i < v1.dim; i++) {
        for (int j = 0; j < v1.dim; j++){
            res.b[i][j] = v1.b[i][j] - v2.b[i][j];
        }
    }
    cout << endl << "Matrix " << v1.num << " - " << v2.num << endl;
    return res;
}

matr operator*(const matr& v1, const matr& v2) {
    matr res(v1.dim);
    for (int i = 0; i < v1.dim; i++) {
        for (int j = 0; j < v1.dim; j++){
            res.b[i][j] = v1.b[i][j] * v2.b[i][j];
        }
    }
    cout << endl << "Matrix " << v1.num << " * " << v2.num << endl;
    return res;
}

matr operator*(const matr& v1, const int& k) {
    matr res(v1.dim);
    for (int i = 0; i < v1.dim; i++) {
        for (int j = 0; j < v1.dim; j++){
            res.b[i][j] = v1.b[i][j] * k;
        }
    }
    cout << endl << "Matrix " << v1.num << " * " << k << endl;
    return res;
}

matr operator*(const int& k, const matr& v1) {
    matr res(v1.dim);
    for (int i = 0; i < v1.dim; i++) {
        for (int j = 0; j < v1.dim; j++){
            res.b[i][j] = v1.b[i][j] * k;
        }
    }
    cout << endl << k << "* Matrix " << v1.num << endl;
    return res;
}

// отдельная штука: умножение вектора на матрицу
vect operator*(const vect& v2, const matr& v1) {
    if (v1.dim != v2.dim){ // нельзя умножать, если матрица и вектор разных размеров, в таком случае выйдем
        cout << "\n Dimensions of matrix and vector do not match \n";
        exit(1337);
    }
    vect res(v2.dim); // делаем вектор результат
    for (int i = 0; i < v1.dim; i++) {
        res.a[i] = 0; // сначала назначаем это 0, чтобы туда можно было прибавить что-либо
        for (int j = 0; j < v1.dim; j++) {
            res.a[i] += v1.b[i][j] * v2.a[j]; // идём j раз (размерностью матрицы), прибавляем ячейку из матрицы,
                                                 // умноженную на соответствующую ячейку вектора
        }
    }
    cout << endl << "Matrix " << v1.num << " * Vector " << v2.num << endl;
    return res;
}




int main() {
    cout << "\n Vectors!!!!! \n";
    vect v1(3);
    v1.a[0] = 1;
    v1.a[1] = 2;
    v1.a[2] = 3;
    v1 = 4 * v1;
    for (int i = 0; i < 3; i++) {
        cout << v1.a[i] << " ";
    }

    vect v2(3);
    cout << endl;
    v2.a[0] = 1;
    for (int i = 1; i < 3; i++) {
        v2.a[i] = v2.a[i - 1] + 1;
    }
    for (int i = 0; i < 3; i++) {
        cout << v2.a[i] << " ";
    }
    cout << endl;
    vect v3(3);
    cout << endl;
    v3 = v2 + v1;
    cout << endl;
    for (int i = 0; i < 3; i++) {
        cout << v3.a[i] << " ";
    }
    cout << endl;
    v1 = 4 * v1;
    for (int i = 0; i < 3; i++) {
        cout << v1.a[i] << " ";
    }
    cout << endl;
    v2 = v2 * v1;
    for (int i = 0; i < 3; i++) {
        cout << v2.a[i] << " ";
    }
    cout << endl;

    cout << endl;

    cout << endl;

    cout << "Matrix!!!!!!" << endl;
    matr nice(3);

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            nice.b[i][j] = 1;
        }
    }
    cout << endl;

    vect v5(3);
    for (int i = 0; i < 3; i++) {
        v5.a[i] = 2;
    }
    for (int i = 0; i < 3; i++) {
        cout << v5.a[i] << endl;
    }
    cout << endl;
    //cout << "\n AAAAAAAAAAAA \n";
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            cout << nice.b[i][j] << " ";
        }
        cout << endl;
    }

    vect cool(3);
    cool = v5 * nice;
    for (int i = 0; i < cool.dim; i++) {
        cout << cool.a[i];
        cout << endl;
    }
    // РАБОТАЕЕЕЕЕЕЕЕЕЕЕЕЕЕЕЕЕЕЕЕЕЕЕЕЕЕЕЕЕЕЕЕЕЕЕЕЕЕЕТ
}

