#include <comet/socket.h>
#include <set>
#include <algorithm>

using namespace std;

int main()
{
	ServerSocket socket;
	socket = ServerSocket(AF_INET, SOCK_STREAM);
	socket.bind("127.0.0.1", 8080);
	socket.listen(1024);
	socket.nonblock();
	set<ServerSocket> clients;
	clients.clear();
	
	return 0;
}
