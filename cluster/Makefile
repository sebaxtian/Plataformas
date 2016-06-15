ex1: example1
		mpirun --mca btl_tcp_if_exclude lo,eth0 -np 4 --hostfile /shared/machinefile /shared/ex1
example1:
		mpicc example1.c -o /shared/ex1
ex2: example2
		mpirun --mca btl_tcp_if_exclude lo,eth0 -np 4 --hostfile /shared/machinefile /shared/ex2
example2:
		mpicc example2.c -o /shared/ex2
ex3: example3
		mpirun --mca btl_tcp_if_exclude lo,eth0 -np 5 --hostfile /shared/machinefile /shared/ex3
example3:
		mpicc example3.c -o /shared/ex3
ex4: example4
		mpirun --mca btl_tcp_if_exclude lo,eth0 -np 4 --hostfile /shared/machinefile /shared/ex4
example4:
		mpicc example4.c -o /shared/ex4
work1: tarea1
		mpirun --mca btl_tcp_if_exclude lo,eth0 -np 4 --hostfile /shared/machinefile /shared/work1
tarea1:
		mpicc tarea1.c -o /shared/work1
runex3:
		mpirun --mca btl_tcp_if_exclude lo,eth0 -np 5 --hostfile /shared/machinefile /shared/ex3
runwork1:
		mpirun --mca btl_tcp_if_exclude lo,eth0 -np 4 --hostfile /shared/machinefile /shared/work1
work2: riemann
		mpirun --mca btl_tcp_if_exclude lo,eth0 -np 4 --hostfile /shared/machinefile /shared/work2
riemann:
		mpicc riemann.c -o /shared/work2 -lm