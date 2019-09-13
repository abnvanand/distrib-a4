#include <iostream>
#include <mpi.h>

using namespace std;

int main(int argc, char **argv) {
    int ierr, N, my_id;

    ierr = MPI_Init(&argc, &argv);

    ierr = MPI_Comm_rank(MPI_COMM_WORLD, &my_id);
    ierr = MPI_Comm_size(MPI_COMM_WORLD, &N);

    int send_to = (my_id + 1) % N;
    int receive_from = (my_id - 1 + N) % N;    // id of proc from which to receive the data

    MPI_Status status;
    int received_data;

    if (my_id == 0) {
        // send then receive
        int data_to_send = -1;
        if (argc > 1)
            data_to_send = stoi(argv[1]);

        ierr = MPI_Send(&data_to_send, 1, MPI_INT, send_to, my_id, MPI_COMM_WORLD);
        ierr = MPI_Recv(&received_data, 1, MPI_INT, receive_from, MPI_ANY_TAG,
                        MPI_COMM_WORLD, &status);
    } else {
        // receive then send
        ierr = MPI_Recv(&received_data, 1, MPI_INT, receive_from, MPI_ANY_TAG,
                        MPI_COMM_WORLD, &status);
        // send the data that this process received
        ierr = MPI_Send(&received_data, 1, MPI_INT, send_to, my_id, MPI_COMM_WORLD);
    }

    int received_from = status.MPI_SOURCE;
    printf("Process %d received data %d from process %d\n",
           my_id, received_data, received_from);

    ierr = MPI_Finalize();

    return 0;
}
