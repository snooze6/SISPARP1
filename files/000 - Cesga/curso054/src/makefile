all: pingpong.out sendrecv.out scatter.out reduce.out gather.out bcast.out barrier.out alltoall.out

CC=mpicc
CFLAGS= -lm
EXECUTABLES_PATH=executables/

OBJ=pingpong.c
pingpong.out:$(OBJ)
	$(CC) -o $(EXECUTABLES_PATH)$@ $^ $(CFLAGS)

OBJ=sendrecv.c
sendrecv.out:$(OBJ)
	$(CC) -o $(EXECUTABLES_PATH)$@ $^ $(CFLAGS)

OBJ=scatter.c
scatter.out:$(OBJ)
	$(CC) -o $(EXECUTABLES_PATH)$@ $^ $(CFLAGS)

OBJ=reduce.c
reduce.out:$(OBJ)
	$(CC) -o $(EXECUTABLES_PATH)$@ $^ $(CFLAGS)

OBJ=gather.c
gather.out:$(OBJ)
	$(CC) -o $(EXECUTABLES_PATH)$@ $^ $(CFLAGS)

OBJ=bcast.c
bcast.out:$(OBJ)
	$(CC) -o $(EXECUTABLES_PATH)$@ $^ $(CFLAGS)

OBJ=barrier.c
barrier.out:$(OBJ)
	$(CC) -o $(EXECUTABLES_PATH)$@ $^ $(CFLAGS)

OBJ=alltoall.c
alltoall.out:$(OBJ)
	$(CC) -o $(EXECUTABLES_PATH)$@ $^ $(CFLAGS)

CLEAN=*.out
clean:
	rm $(EXECUTABLES_PATH)$(CLEAN)

CLEAN=*/*.out .DS_Store */.DS_Store
cleanall:
	rm $(CLEAN)
