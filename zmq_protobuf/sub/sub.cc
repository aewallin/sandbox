/* zmq SUB with protobuf test

 */
 
#include <zmq.hpp>
#include <string>
#include <iostream>
#include <cstdio> // printf
#include <unistd.h> // sleep()

#include "mymessage.pb.h"

int main (void)
{
	zmq::context_t context (1);
	zmq::socket_t socket(context, ZMQ_SUB);
	char messageType[] = { 0x0a, 0x02, 0x54, 0x54 }; 
	// 10 2 or 0x0a 0x02 is protobuf signature ?
	// "TT" = 0x54 0x54 is our specified message type string
	
	//socket.setsockopt( ZMQ_SUBSCRIBE, "", 0 );
	socket.setsockopt( ZMQ_SUBSCRIBE, messageType, 4 );
	//socket.setsockopt(ZMQ_IDENTITY, "Hello", 5);
	 
	socket.connect("tcp://localhost:5555");

	AMessage msg = AMessage(); // protobuf message
	
	zmq::message_t* zmq_msg = new zmq::message_t(); 
	
	std::cout << "ZMQ SUB started.\n";
	while (1) {

		socket.recv(zmq_msg);		
		printf("SUB[ %d ] :",  zmq_msg->size() );
		for (int n =0;n< zmq_msg->size(); n++)
			printf("%02x ", ((char *)zmq_msg->data())[n]); // raw bytes received
		std::cout << "\n";
		
		// interpret bytes with protobuf
		msg.ParseFromArray( (char *)zmq_msg->data(), zmq_msg->size() );
		std::cout << "type=" << msg.messagetype() << " a="<<msg.a() << " b=" << msg.b() << "\n";
		
		sleep (1); // Do some 'work'
	}
	return 0;
}

