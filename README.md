Distributed Numerical Integration using MPI

This project implements **numerical integration** using both a **serial version** and multiple **parallel MPI-based versions**.  
The main goal is to approximate the definite integral of a mathematical function using distributed computation to improve performance and scalability.

The project includes:
- A **serial integration program** (`integrate.cpp`)
- A **function definition** (`func.cpp`)
- Three **MPI parallel implementations**:
  - `mpi_integrate_v1.cpp`
  - `mpi_integrate_v2.cpp`
  - `mpi_integrate_v3.cpp`
- A `Makefile` for building all versions
- Documentation files (`integrate.txt`, `integrate_en.txt`)

---

## 📂 Project Structure

project/
│── func.cpp # Contains the mathematical function to integrate
│── integrate.cpp # Serial (non-MPI) integration implementation
│── mpi_integrate_v1.cpp # MPI version 1 - basic parallelization
│── mpi_integrate_v2.cpp # MPI version 2 - improved load distribution
│── mpi_integrate_v3.cpp # MPI version 3 - optimized communication & performance
│── Makefile # Build instructions
│── integrate.txt # Documentation (Arabic)
│── integrate_en.txt # Documentation (English)

---

## 🧠 How It Works

### **1. Serial Version**
The serial implementation uses:
- Numerical integration (e.g., midpoint or trapezoidal rule)
- A fixed number of intervals
- A loop to accumulate partial sums

### **2. MPI Parallel Versions**
Each MPI version divides the integration range among available processes:

- **Version 1**  
  Basic decomposition of the integration interval among processes.

- **Version 2**  
  Improved load balancing and better handling of non-even interval distribution.

- **Version 3**  
  Optimized communication, reduced synchronization, and maximized speedup.

All versions:
- Use `func.cpp` as the function to evaluate
- Compute local integrals on each process
- Use `MPI_Reduce` or similar methods to gather results

---

## 🛠️ Build Instructions

Run the following commands inside the project directory:

### **Build the serial version**
```bash`
make serial


Build all MPI versions:
make mpi

Build a specific MPI version:
make v1
make v2
make v3

Clean compiled files:
make clean

▶️ Running the Programs

Serial Execution:
./integrate

Parallel MPI Execution:

Version 1
mpirun -np 4 ./mpi_integrate_v1

Version 2
mpirun -np 4 ./mpi_integrate_v2

Version 3
mpirun -np 4 ./mpi_integrate_v3

Replace 4 with any desired number of MPI processes.


📈 Performance Notes
The MPI implementations demonstrate significant performance improvement compared to the serial version, especially when:
The integration interval is large
The number of processes increases
The load is well-balanced (v2, v3)
Communication overhead is minimized (v3)
Version 3 is typically the fastest and most optimized.


📄 Function Definition
The function to integrate is defined in func.cpp.
You can modify it freely to experiment with different integrals.


🚀 Possible Extensions
You can expand the project by adding:
Dynamic interval assignment strategies
Adaptive numerical integration
Additional MPI optimizations
Support for parallel I/O
Benchmark plotting using Python


📜 License
This project is part of a distributed systems and parallel computing assignment.
You may modify or extend it for educational or research purposes.
