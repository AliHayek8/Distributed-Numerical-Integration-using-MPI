#include <iostream>
#include <iomanip>
#include <chrono>
#include <mpi.h>
#include <cstdlib> // For atof and atoi

// الدالة المراد تكاملها
extern double f(double x);

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int n;
    double a, b;

    if (rank == 0) {
        if (argc != 4) {
            std::cerr << "Usage: " << argv[0] << " <n> <a> <b>" << std::endl;
            MPI_Abort(MPI_COMM_WORLD, 1);
        }

        n = atoi(argv[1]); // عدد أشباه المنحرفات (خطوات التكامل)
        a = atof(argv[2]); // الحد الأدنى للتكامل
        b = atof(argv[3]); // الحد الأعلى للتكامل

        if (n <= 0) {
            std::cerr << "Error: Number of trapezoids (n) must be positive." << std::endl;
            MPI_Abort(MPI_COMM_WORLD, 1);
        }
        if (a >= b) {
            std::cerr << "Error: Lower bound (a) must be less than upper bound (b)." << std::endl;
            MPI_Abort(MPI_COMM_WORLD, 1);
        }
    }

    // بث القيم n, a, b من العملية 0 إلى جميع العمليات الأخرى
    MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(&a, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    MPI_Bcast(&b, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    // قياس زمن البدء الكلي
    auto start_total_time = std::chrono::high_resolution_clock::now();

    double h = (b - a) / n; // عرض كل شبه منحرف

    // تحديد نطاق التكامل لكل عملية
    int local_n = n / size;
    double local_a = a + rank * local_n * h;
    double local_b = local_a + local_n * h;

    // حساب الجزء المحلي من التكامل
    double local_integral = (f(local_a) + f(local_b)) / 2.0;
    for (int i = 1; i < local_n; ++i) {
        local_integral += f(local_a + i * h);
    }
    local_integral *= h;

    if (rank == 0) {
        double total_integral = local_integral;
        for (int i = 1; i < size; ++i) {
            double received_integral;
            MPI_Status status;
            // استقبال النتائج من أي عملية أخرى
            MPI_Recv(&received_integral, 1, MPI_DOUBLE, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, &status);
            total_integral += received_integral;
        }

        // قياس زمن الانتهاء الكلي
        auto end_total_time = std::chrono::high_resolution_clock::now();
        auto duration_total = std::chrono::duration_cast<std::chrono::microseconds>(end_total_time - start_total_time);

        std::cout << std::fixed << std::setprecision(10);
        std::cout << "MPI v2 (Any Source) Integral Result: " << total_integral << std::endl;
        std::cout << "Time taken: " << duration_total.count() << " microseconds" << std::endl;
    } else {
        // إرسال النتائج المحلية إلى العملية 0
        MPI_Send(&local_integral, 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD);
    }

    MPI_Finalize();

    return 0;
}

