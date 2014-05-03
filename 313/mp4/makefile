# makefile

all: dataserver client

reqchannel.o: reqchannel.H reqchannel.C
	g++ -c -g reqchannel.C

dataserver: dataserver.C reqchannel.o 
	g++ -g -o dataserver dataserver.C reqchannel.o -lpthread

client: client.C reqchannel.o buffer.H semaphore.H timer.H person.H
	g++ -g -o client client.C reqchannel.o -lpthread
	
clean:
	rm -rf *.o 
	rm client
	rm dataserver
	rm fifo*
	
run:
	./client -n 10000 -b 250 -w 70