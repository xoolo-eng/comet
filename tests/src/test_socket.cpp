#include <comet/socket>
#include <set>
#include <algorithm>
#include <sys/select>
#include <unistd>

using namespace std;

int main()
{
	short result;
	ServerSocket socket;
	socket = ServerSocket(AF_INET, SOCK_STREAM);
	socket.bind("127.0.0.1", 8080);
	socket.listen(1024);
	socket.nonblock();
	set<ServerSocket> clients;
	clients.clear();
	fd_set readset, writeset, exset;
	while (true)
	{
		FD_ZERO(&readset);
		FD_ZERO(&writeset);
		FD_ZERO(&exset);
		unsigned int maxfd = socket;
		FD_SET(socket, &readset);

	}
	return 0;
}
