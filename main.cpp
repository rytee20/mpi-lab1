#include <iostream>
#include <mpi.h>

void star(int ProcNum, int ProcRank, int m) {
    int message = 0;
    MPI_Status status;

    for (int i = 0; i < m; ++i) {
        if (ProcRank == 0) {
            // Центральный процесс отправляет сообщение всем остальным процессам
            for (int dest = 1; dest < ProcNum; ++dest) {
                MPI_Send(&message, 1, MPI_INT, dest, 0, MPI_COMM_WORLD);
                std::cout << "Center process send " << message << " to process " << dest << std::endl;
            }
        }
        else {
            // Крайние процессы принимают сообщение от центрального процесса
            MPI_Recv(&message, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
            std::cout << "Process " << ProcRank << " recieved " << message << " from center process" << std::endl;
        }
    }
}

int main(int argc, char** argv) {

    setlocale(LC_ALL, "RUS");

    MPI_Init(&argc, &argv);

    int ProcNum, ProcRank;
    MPI_Comm_size(MPI_COMM_WORLD, &ProcNum); // получаем количество процессов
    MPI_Comm_rank(MPI_COMM_WORLD, &ProcRank); // получаем номер текущего процесса


    int m = 3; // число повторений

    star(ProcNum, ProcRank, m);

    MPI_Finalize();
    return 0;
}
