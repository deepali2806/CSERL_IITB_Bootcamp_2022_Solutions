
CC = gcc
CLIENT_FILE = simple-client.c
MULTI_THREADED_SERVER = multithreaded-server.c

all: client multithreaded_server

client: $(CLIENT_FILE)
	$(CC) $(CLIENT_FILE) -o client
	
multithreaded_server: $(MULTI_THREADED_SERVER)
	$(CC) $(MULTI_THREADED_SERVER) -o multithreaded_server -lpthread

clean:
	rm -f client multithreaded_server
