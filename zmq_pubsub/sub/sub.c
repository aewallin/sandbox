

// Hello World client
#include <zmq.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

int main (void) {
	printf ("Connecting to hello world server…\n");
	void *context = zmq_ctx_new ();
	void *sub = zmq_socket (context, ZMQ_SUB);
	zmq_setsockopt ( sub , ZMQ_SUBSCRIBE, "", 0);
	zmq_connect (sub, "tcp://localhost:5555");

	int request_nbr;
	for (request_nbr = 0; request_nbr != 10; request_nbr++) {
		char buffer [10];
		//printf ("Sending Hello %d…\n", request_nbr);
		//zmq_send (requester, "Hello", 5, 0);
		zmq_recv (sub, buffer, 10, 0);
		printf ("Received msg nr %d: %s\n", request_nbr, buffer);
	}
	zmq_close (sub);
	zmq_ctx_destroy (context);
	return 0;
}
