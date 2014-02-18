/* zmq PUB with protobuf test

 */
 
#include <zmq.hpp>
#include <string>
#include <iostream>
#include <cstdio> // printf()
#include <unistd.h> // sleep()

#include "mymessage.pb.h"

int main (void)
{
	zmq::context_t context (1);
	zmq::socket_t socket (context, ZMQ_PUB);

	socket.bind("tcp://*:5555");
	
	// protobuf message
	AMessage msg = AMessage();
	msg.set_a( 42 );
	msg.set_b( 3 );
	msg.set_messagetype( "TT"); 
	
	// zmq message
	 // need to know max size beforehand?
	
	std::cout << "ZMQ PUB started.\n";
	int count=0;
	while (1) {
		// serialize protobuf message to bytes in the zmq message
		//zmq_msg.init( msg.ByteSize() );
		msg.set_a( count );
		zmq::message_t zmq_msg( msg.ByteSize() );
		msg.SerializeToArray( (void *)zmq_msg.data(), msg.ByteSize() );
		
		
		// actual send , , msg.ByteSize()
		socket.send( zmq_msg );
		
		// print out what we sent on the wire:
		printf("MSG       : a=%d b=%d \n", msg.a(), msg.b() );
		printf("%d PUB[ %d ] :", count, msg.ByteSize() );
		for (int n =0;n< msg.ByteSize(); n++)
			printf("%02x ", ((char *)zmq_msg.data())[n]);
		std::cout << "\n";
		
		sleep (1); // Do some 'work'
		count++;
	}
	return 0;
}

