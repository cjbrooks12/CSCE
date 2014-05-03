# makefile

all: dataserver client

NetworkRequestChannel.o: NetworkRequestChannel.C NetworkRequestChannel.H
	clear
	g++ -g -c NetworkRequestChannel.C 

dataserver: dataserver.C NetworkRequestChannel.o
	clear
	g++ -g -o dataserver dataserver.C NetworkRequestChannel.o -lpthread

client: client.C buffer.H semaphore.H timer.H person.H NetworkRequestChannel.o
	clear
	g++ -g -o client client.C NetworkRequestChannel.o -lpthread	
	
clean:
	clear
	rm -rf *.o 
	rm client
	rm dataserver
	rm fifo*
	
run_client:
	clear
	./client -n 10000 -b 25 -w 10 -h compute.cse.tamu.edu -p 6258

run_dataserver:
	clear
	./dataserver -p 6258 -b 15