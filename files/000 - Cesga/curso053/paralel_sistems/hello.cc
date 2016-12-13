#include <iostream>
#include <functional>
#include <algorithm>
#include <mpi.h>

int main(int argc, char  ** argv ) {

MPI_Init(&argc,&argv) ;
double start, finish ;

int world_size ;
MPI_Comm_size(MPI_COMM_WORLD, &world_size) ;

int world_rank ;
MPI_Comm_rank(MPI_COMM_WORLD, &world_rank) ;

using namespace std ;

cout << "Hello world from processor " <<
      world_rank << " out of " << world_size << endl ;

auto x = [] ( ) {} ;
double  * pd = new double [16000000] ;

/******/
MPI_Barrier(x) ;
start = MPI_Wtime() ;
std::generate( pd, pd+16000000, [] () {return static_cast<double>(rand()) ; }) ;
std::sort( pd, pd+16000000 ) ;
MPI_Barrier(x) ;
finish = MPI_Wtime() ;
/******/

cout << "Execution time: " << finish-start << endl ;

MPI_Finalize() ;
}
