#include <iostream>
#include <fstream>
#include <string>
#include "netmsg.pb.h"

int main(int argc, char **argv)
{
	GOOGLE_PROTOBUF_VERIFY_VERSION;

	netmsg msg;
	netmsg result;

	msg.set_id(1);
	msg.set_data("ola q ase");

	std::string serialized_str;

	if(!msg.SerializeToString(&serialized_str))
	{
		std::cout << "error al serializar!" << std::endl;
		return EXIT_FAILURE;
	}

	result.ParseFromString(serialized_str);

	std::cout << "DATA: " << result.id() << ", " << result.data() << std::endl;

	google::protobuf::ShutdownProtobufLibrary();

	return EXIT_SUCCESS;
}
