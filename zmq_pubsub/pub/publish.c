/* Hello World zmq REP server

 */
 
#include <zmq.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <assert.h>

int main (void)
{
	// Socket to talk to clients
	void *context = zmq_ctx_new();
	void *pub = zmq_socket(context, ZMQ_PUB);
	int rc = zmq_bind (pub, "tcp://*:5555");
	assert (rc == 0);
	printf ("ZMQ PUB started.\n");
	while (1) {
		//char buffer [10];
		//zmq_recv (responder, buffer, 10, 0);
		//printf ("Received Hello\n");
		
		zmq_send(pub, "Hello!", 6, 0);
		printf ("Published: Hello!\n");
		sleep (1); // Do some 'work'
	}
	return 0;
}

