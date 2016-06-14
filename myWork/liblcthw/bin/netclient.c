#undef NDEBUG
#include <lcthw/ringbuffer.h>
#include <sys/select.h>
#include <lcthw/dbg.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <fcntl.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/uio.h>

struct tagbstring NL = bsStatic("\n");
struct tagbstring CRLF = bsStatic("\r\n");

int nonblock(int fd)
{
	//fcntl manipulates files
	//F_GETFL gets the file access mode and the firl status flags

	int flags = fcntl(fd, F_GETFL, 0);
	check(flags >= 0, "Invalid flags on nonblock");

	//set file status to non blocking 
	int rc = fcntl(fd, F_SETFL, flags | O_NONBLOCK);
	check(rc == 0, "Can't set nonblocking.");
	
	return 0;


error:
	return -1;
}
int client_connect(char *host, char *port)
{
	int rc = 0;
	struct addrinfo *addr = NULL;	

	//fills addr up with internet address 
	rc = getaddrinfo(host, port, NULL, &addr);
	check(rc == 0, "Failed to lookup %s:%s", host, port);

	//creates an endpoint for communication and returns
	//a descriptor
	//AF_INET => IPV4
	//SOCK_STREAM = sequenced, two-way connection-based byte stream
	//0 is protocol?
	// return is a filedescriptor
	int sock = socket(AF_INET, SOCK_STREAM, 0);
	check(sock >= 0, "Cannot create a socket");

	//initiates a connecection to the specified socket
	rc = connect(sock, addr->ai_addr, addr->ai_addrlen);
	check(rc == 0, "Connect Failed");
	
	rc = nonblock(sock);
	check (rc == 0, "Can't set nonblock");
	
	freeaddrinfo(addr);
	return sock;
	
	return 0;
error:
	freeaddrinfo(addr);
	return 1;
}
int read_some(RingBuffer *buffer, int fd, int is_socket)
{
	int rc = 0;

	if(RingBuffer_available_data(buffer) == 0)
	{
		buffer->start = buffer->end = 0;
	}

	if(is_socket){
		//used to receive msg from sockets
		rc = recv(fd, RingBuffer_starts_at(buffer), 
				RingBuffer_available_space(buffer), 0);
	}  else {
		//count bytes from fd into buffer
	rc = read(fd, RingBuffer_starts_at(buffer), 
			RingBuffer_available_space(buffer));
		}

	check(rc >= 0, "Failed to read from fd, %d", fd);
	
	RingBuffer_commit_write(buffer, rc);
	
	return rc;
error:
	return -1;
}	
int write_some(RingBuffer *buffer, int fd, int is_socket)
{
	int rc = 0;
	bstring data = RingBuffer_get_all(buffer);
	
	check(data != NULL, "Failed to get from the buffer");
	check(bfindreplace(data, &NL, &CRLF, 0) == BSTR_OK, 
			"Failed to replace NL");

	if(is_socket) {
		rc = send(fd, bdata(data), blength(data), 0);
	} else {
		rc = write(fd, bdata(data), blength(data));
	}	

	check(rc == blength(data), "Failed to write everything to fd: %d", fd);

	bdestroy(data);

	return rc;

error:
	return -1;
}
int main(int argc, char *argv[])
{
	
	fd_set allreads;
	fd_set readmask;

	int socket = 0;
	int rc = 0;

	RingBuffer *in_rb = RingBuffer_create(1024 * 10);
	RingBuffer *sock_rb = RingBuffer_create(1024 * 10);

	check(argc == 3, "USAGE: netclient host port");

	debug("Opening socket at %s:%s", argv[1], argv[2]);
	socket = client_connect(argv[1], argv[2]);
	check(socket >= 0, "connect to %s:%s failed", argv[1], argv[2]);
	debug("Connected to: %s:%s", argv[1], argv[2]);

	FD_ZERO(&allreads);
	//add socket to our set
	FD_SET(socket, &allreads);
	FD_SET(0, &allreads);

	while(1) {
		readmask = allreads;
		//tells us when readmask becomes readable?
		debug("Checking if readmask is readable");
		//why + 1?
		rc = select(socket, &readmask, NULL, NULL, NULL);
		check(rc >= 0, "select failed");	

		//is fd part o the set?
		debug("Checking is stdin 0, is part of fdset");
		if(FD_ISSET(0, &readmask)) {
			rc = read_some(in_rb, 0, 0);
			check_debug(rc != -1, "Failed to read from stdin");
		}
		
		debug("Checking if open socket,  is part of fdset");
		if(FD_ISSET(socket, &readmask)) {
			rc = read_some(sock_rb, socket, 0);
			check_debug(rc != -1, "Failed to read from socket");
		}
		
		while(!RingBuffer_empty(sock_rb)) {
			rc = write_some(sock_rb, 1, 0);
			check_debug(rc != -1, "Failed to write to stdout");
		}
	
		while(!RingBuffer_empty(in_rb)) {
			rc = write_some(in_rb, socket, 1);
			check_debug(rc != -1, "Failed to write to socket");
		}
	}
	return 0;
error:
	return 1;

}

