CXX = mpicxx
CXXFLAGS = -std=c++17 -Wall -O3

all: integrate mpi_integrate_v1 mpi_integrate_v2 mpi_integrate_v3

integrate: integrate.cpp func.cpp
	$(CXX) $(CXXFLAGS) integrate.cpp func.cpp -o integrate

mpi_integrate_v1: mpi_integrate_v1.cpp func.cpp
	$(CXX) $(CXXFLAGS) mpi_integrate_v1.cpp func.cpp -o mpi_integrate_v1

mpi_integrate_v2: mpi_integrate_v2.cpp func.cpp
	$(CXX) $(CXXFLAGS) mpi_integrate_v2.cpp func.cpp -o mpi_integrate_v2

mpi_integrate_v3: mpi_integrate_v3.cpp func.cpp
	$(CXX) $(CXXFLAGS) mpi_integrate_v3.cpp func.cpp -o mpi_integrate_v3

clean:
	rm -f integrate mpi_integrate_v1 mpi_integrate_v2 mpi_integrate_v3 *.o

