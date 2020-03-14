#fisier folosit pentru compilarea serverului concurent & clientului TCP

all:
	gcc server.c -o servTcpConc
	gcc client.c -o cliTcpConc
clean:
	rm -f *~ cliTcpConc servTcpConc