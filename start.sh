if [[ $# -ne 2 ]]; then
  echo "Specify token_value and num_processes as command line arguments."
  exit 1
fi

mpic++ main.cpp
mpirun --oversubscribe -np "$2" a.out "$1"
