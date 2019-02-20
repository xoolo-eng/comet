#include <iostream>
#include <comet/socket.h>
#include <set>
#include <map>
#include <sstream>
#include <stdexcept>
#include <algorithm>
#include <sys/select.h>
// #include <signal.h>
#include <unistd.h>

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
	map<int, string> requests;
	requests.clear();
	fd_set readset, writeset, exset;
	// signal(SIGINT, [](int signum)
	// {
		// socket.close();
	// });
	while (true)
	{
		FD_ZERO(&readset);
		FD_ZERO(&writeset);
		FD_ZERO(&exset);
		int maxfd = max(socket,
			*max_element(clients.begin(), clients.end()));
		FD_SET((int)socket, &readset);
		for (auto it : clients)
		{
			FD_SET((int)it, &readset);
		}
		if (select(maxfd+1, &readset, &writeset, &exset, NULL) <= 0)
		{
			throw invalid_argument("Select");
			return 1;
		}
		if (FD_ISSET((int)socket, &readset))
		{
			ServerSocket new_client = socket.accept();
			new_client.nonblock();
			clients.insert(new_client);
		}
		for (auto it : clients)
		{
			if (FD_ISSET((int)it, &exset))
			{
				it.close();;
				clients.erase(it);
				continue;
			}
			if (FD_ISSET((int)it, &writeset))
			{
				it.send(requests[it]);
				requests.erase(it);
				it.close();
				clients.erase(it);
			}
			if (FD_ISSET((int)it, &readset))
			{
				string data;
				try
				{
					data = it.recv();
				}
				catch (domain_error& err)
				{
					cout << err.what();
				}
				cout << data << '\n';
				if (data.length() == 0) {
					requests.erase(it);
					it.close();
					clients.erase(it);
					continue;
				}
				stringstream result;
				result << "<h2>" << (int)it << "</h2>";
				requests.insert(pair<int, string>(it, result.str()));
			}
		}
	}
	return 0;
}
