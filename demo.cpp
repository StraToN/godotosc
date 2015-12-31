/*
  This is a lame ping-ping demo for oscpkt
 */
/*
#define OSCPKT_OSTREAM_OUTPUT
#include "osc.h"
#include "io/packet_peer_udp.h"

using std::cout;
using std::cerr;

using namespace oscpkt;

const int PORT_NUM = 9109;
*/


/*
void runServer() {
	PacketPeerUDP* sock = PacketPeerUDP::create();

	if (sock->listen(PORT_NUM) != OK) {
		cerr << "Error opening port " << PORT_NUM << ": " << "\n";
	} else {
		cout << "Server started, will listen to packets on port " << PORT_NUM << std::endl;
		OSCPacketReader pr;
		OSCPacketWriter pw;
		Variant v;

		//if (sock.receiveNextPacket(30)) { // timeout, in ms
		if (sock->get_var(v) == OK) {
			pr.init(v._data._ptr, (size_t) sock->get_max_packet_size());
			OSCMessage *msg;
			while (pr.isOk() && (msg = pr.popMessage()) != 0) {
				int iarg;
				if (msg->match("/ping").popInt32(iarg).isOkNoMoreArgs()) {
					cout << "Server: received /ping " << iarg << " from " << sock->get_packet_address() << "\n";
					OSCMessage repl; repl.init("/pong").pushInt32(iarg+1);
					pw.init().addMessage(repl);
					//sock.put_packet(pw.packetData(), pw.packetSize());
				} else {
					cout << "Server: unhandled message: " << *msg << "\n";
				}
			}
		}
	}
}
*/

/*

void runClient() {
	PacketPeerUDP* sock = PacketPeerUDP::create();

	sock->set_send_address(IP_Address("localhost"), PORT_NUM);

	if (sock->listen(PORT_NUM) != OK) {
		cerr << "Error connection to port " << PORT_NUM << "\n";
	} else {
		cout << "Client started, will send packets to port " << PORT_NUM << std::endl;
		int iping = 1;
		while (sock->is_listening()) {
			OSCMessage msg("/ping");
			msg.pushInt32(iping);

			OSCPacketWriter pw;
			pw.startBundle().startBundle().addMessage(msg).endBundle().endBundle();

			Error err = sock->put_var(msg.get_variant());
			if (err != OK) {
				cout << "Client: impossible d'envoyer le packet /ping !! " << "\n";
			}
			else {
				cout << "Client: sent /ping " << iping++ << ", ok=" << err << "\n";

				/*
				// wait for a reply ?
				if (sock.receiveNextPacket(30 )) { // timeout, in ms
					PacketReader pr(sock.packetData(), sock.packetSize());
					Message *incoming_msg;
					while (pr.isOk() && (incoming_msg = pr.popMessage()) != 0) {
						cout << "Client: received " << *incoming_msg << "\n";
					}
				}
				*/
/*
			}

		}
	}
}
*/


/*
int main(int argc, char **argv) {
	if (argc > 1 && strcmp(argv[1], "--cli") == 0) {
		runClient();
	} else if (argc > 1 && strcmp(argv[1], "--serv") == 0) {
		//runServer();
	} else {
		cout << "syntax: --serv to run as server, --cli to run as client\n";
	}
}
*/
