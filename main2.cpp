#include <iostream>
#include <mpi.h>

using namespace std;

int main(int argc, char **argv) {
    int ierr, num_procs, my_id;

    ierr = MPI_Init(&argc, &argv);

    ierr = MPI_Comm_rank(MPI_COMM_WORLD, &my_id);
    ierr = MPI_Comm_size(MPI_COMM_WORLD, &num_procs);

    int N = num_procs;

    int data_to_send = -1;
    int send_count = 1;
    MPI_Datatype send_type = MPI_INT;
    int destination_ID = (my_id + 1) % N;
    int send_tag = my_id;

    int received_data;
    int receive_count = 1;
    MPI_Datatype receive_type = MPI_INT;
    int sender_id = (my_id - 1 + N) % N;    // id of proc from which to receive the data

    MPI_Comm comm = MPI_COMM_WORLD;
    MPI_Status status;

    MPI_Sendrecv(&data_to_send, send_count, send_type, destination_ID, send_tag,
                 &received_data, receive_count, receive_type, sender_id, MPI_ANY_TAG,
                 comm, &status);

    int received_from = status.MPI_SOURCE;
    printf("Process %d received data %d from process %d\n",
           my_id, received_data, received_from);

    ierr = MPI_Finalize();

    return 0;
}
