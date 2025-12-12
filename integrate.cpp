#include <iostream>
#include <iomanip>
#include <chrono>
#include <cstdlib> // For atof and atoi

// الدالة المراد تكاملها
extern double f(double x);

int main(int argc, char** argv) {
    if (argc != 4) {
        std::cerr << "Usage: " << argv[0] << " <n> <a> <b>" << std::endl;
        return 1;
    }

    int n = atoi(argv[1]); // عدد أشباه المنحرفات (خطوات التكامل)
    double a = atof(argv[2]); // الحد الأدنى للتكامل
    double b = atof(argv[3]); // الحد الأعلى للتكامل

    if (n <= 0) {
        std::cerr << "Error: Number of trapezoids (n) must be positive." << std::endl;
        return 1;
    }
    if (a >= b) {
        std::cerr << "Error: Lower bound (a) must be less than upper bound (b)." << std::endl;
        return 1;
    }

    // قياس زمن البدء
    auto start_time = std::chrono::high_resolution_clock::now();

    double h = (b - a) / n; // عرض كل شبه منحرف
    double integral = (f(a) + f(b)) / 2.0; // قيمة التكامل الأولية

    for (int i = 1; i < n; ++i) {
        integral += f(a + i * h);
    }
    integral *= h;

    // قياس زمن الانتهاء
    auto end_time = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);

    std::cout << std::fixed << std::setprecision(10);
    std::cout << "Sequential Integral Result: " << integral << std::endl;
    std::cout << "Time taken: " << duration.count() << " microseconds" << std::endl;

    return 0;
}

