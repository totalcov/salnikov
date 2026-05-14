#include <iostream>
#include "vect.h"
#include "MySatun.h"

int main() {
    try {
        // Vector<double>
    Vector<double> vd(5);
    vd[0] = 1.5;
    vd.print();
    
    // Vector<int>
    Vector<int> vi(3);
    vi[0] = 12;
    vi[1] = 20;
    vi[2] = vi[0] + vi[1];
    vi.print();
    
    // Vector<MySatun>
    Vector<MySatun> vs(3);
    vs[0] = MySatun(7.0);
    vs[1] = MySatun(2.5);
    vs[2] = MySatun(100000.0);  // насыщение
    vs.print(); 
    
    Vector<Vector<int>> vv(2, 2);
    vv[0] = Vector<int>(2);
    vv[1] = Vector<int>(2);

    vv[0][0] = 1;
    vv[0][1] = 2;
    vv[1][1] = 9; 
    vv.print();

    Vector<Vector<Vector<int>>> vvv(2, 2, 2); // Создание тройного вложенного вектора размером 2x2x2

// Присваиваем значения элементам
    vvv[0][0][0] = 1;
    vvv[0][0][1] = 2;
    vvv[0][1][0] = 3;
    vvv[0][1][1] = 4;

    vvv[1][0][0] = 5;
    vvv[1][0][1] = 6;
    vvv[1][1][0] = 7;
    vvv[1][1][1] = 8;

// Печать значений (предполагается, что у вас есть метод для вывода вложенных векторов)
    vvv.print();
    }

    catch (const std::invalid_argument& e) {
        std::cout << "Ошибка: " << e.what() << std::endl;
    } catch (const std::out_of_range& e) {
        std::cout << "Ошибка: " << e.what() << std::endl;
    } catch (const std::bad_alloc& e) {
        std::cout << "Ошибка выделения памяти: " << e.what() << std::endl;
    }

    return 0;
}