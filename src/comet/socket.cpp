#include <comet/socket.h>
#include <arpa/inet.h>
#include <stdexcept>
#include <cstdio>
#include <sstream>
#include <cstring>
#include <cerrno>

using namespace std;


ServerSocket::ServerSocket() :
connect (false),
created (false)
{}

ServerSocket::ServerSocket(int domain, __socket_type type) :
ServerSocket(domain, type, 0)
{}

ServerSocket::ServerSocket(int domain, __socket_type type, int protocol) :
connect (false)
{
	this->socket_fd = socket(domain, type, protocol);
	if (this->socket_fd < 0)
	{
		stringstream error;
		error << "Server socket: " << strerror(errno);
		throw domain_error(error.str());
	}
	this->server_addr.sin_family = domain;
	this->created = true;
}

ServerSocket::~ServerSocket() noexcept {}

void ServerSocket::bind(string address, short port)
{
	int_fast8_t result;
	this->server_addr.sin_port = htons(port);
	this->server_addr.sin_addr.s_addr = inet_addr(address.c_str());
	result = sys_bind(
			this->socket_fd, (sockaddr *)&this->server_addr,
			sizeof(this->server_addr));
	if (result < 0)
	{
		stringstream error;
		error << "Server bind: " << strerror(errno);
		throw domain_error(error.str());
	}
}

void ServerSocket::listen(int backlog)
{
	int_fast8_t result;
	result = sys_listen(this->socket_fd, backlog);
	if (result < 0)
	{
		stringstream error;
		error << "Server listen: " << strerror(errno);
		throw domain_error(error.str());
	}
}

ServerSocket ServerSocket::accept()
{
	int_fast8_t result;
	sockaddr_in client_addr;\
	result = sys_accept(this->socket_fd, (sockaddr *)&client_addr, sizeof(client_addr));
	if (result < 0)
	{
		stringstream error;
		error << "Server accept: " << strerror(errno);
		throw domain_error(error.str());
	}
	else
	{
		ServerSocket client_socket = *this;
		client_socket.socket_fd = result;
		client_socket.server_addr = client_addr;
		client_socket.connect = true;
		return client_socket;
	}
}

void ServerSocket::nonblock()
{
	int_fast8_t result;
	result = fcntl(this->socket_fd, O_NONBLOCK);
	if (result < 0) {
		stringstream error;
		error << "Server nonblock: " << strerror(errno);
		throw domain_error(error.str());
	}
}

int ServerSocket::send(string message)
{
	int_fast8_t result;
	int total = 0;
	int len = message.length();
	while (total < len)
	{
		result = sys_send(this->socket_fd, message.c_str(), len-total, 0);
		if (result < 0)
		{
			stringstream error;
			error << "Server send: " << strerror(errno);
			throw domain_error(error.str());
		}
		total += result;
	}
	return total;
}

string ServerSocket::recv()
{
	stringstream buffer;
	char recv_data[PACK_SIZE];
	int result;
	do {
		memset(&recv_data, 0, PACK_SIZE);
		result = sys_recv(this->socket_fd, recv_data, PACK_SIZE, 0);
		buffer << recv_data;
	} while (result > 0);
	if (result < 0 || buffer.str().length() == 0)
	{
		stringstream error;
		error << "Server recv: " << strerror(errno);
		throw domain_error(error.str());
	}
	else
	{
		return buffer.str();
	}
}

string ServerSocket::address()
{
	if (connect) {
		stringstream address;
		address << inet_ntoa(this->server_addr.sin_addr);
		return address.str();
	}
	else
	{
		const string error ("Server: Not have connection client!");
		throw logic_error(error);
	}
}

int ServerSocket::port()
{
	if (connect)
	{
		return this->server_addr.sin_port;
	}
	else
	{
		const string error ("Server: Not have connection client!");
		throw logic_error(error);
	}
}

void ServerSocket::close()
{
	sys_close(this->socket_fd);
	delete this;
}

ServerSocket::operator int() const
{
	if (this->created)
	{
		return this->socket_fd;
	}
	else
	{
		string error ("Object ServerSocket NOT CREATED!");
		throw logic_error(error);
	}
}

ServerSocket::operator bool() const
{
	if (this->created)
	{
		return true;
	}
	return false;
}

/*
 * Реализация класса клиентского сокета ClientSocket
 */

ClientSocket::ClientSocket() : created (false) {}

ClientSocket::ClientSocket(int domain, __socket_type type, int protocol)
{
	this->socket_fd = socket(domain, type, protocol);
	if (this->socket_fd < 0)
	{
		stringstream error;
		error << "Client socket: " << strerror(errno);
		throw domain_error(error.str());
	}
	this->client_addr.sin_family = domain;
	this->created = true;
}

ClientSocket::~ClientSocket() noexcept {}

void ClientSocket::connect(string address, int port)
{
	int_fast8_t result;
	this->client_addr.sin_port = htons(port);
	this->client_addr.sin_addr.s_addr = inet_addr(address.c_str());
	result = sys_connect(this->socket_fd, (sockaddr *)&client_addr, sizeof(this->client_addr));
	if (result < 0)
	{
		stringstream error;
		error << "Client connect: " << strerror(errno);
		throw domain_error(error.str());
	}
}

void ClientSocket::nonblock()
{
	int_fast8_t result;
	result = fcntl(this->socket_fd, O_NONBLOCK);
	if (result < 0) {
		stringstream error;
		error << "Client nonblock: " << strerror(errno);
		throw domain_error(error.str());
	}
}

int ClientSocket::send(string message)
{
	int_fast8_t result;
	int total = 0;
	int len = message.length();
	while (total < len)
	{
		result = sys_send(this->socket_fd, message.c_str(), len-total, 0);
		if (result < 0)
		{
			stringstream error;
			error << "Client send: " << strerror(errno);
			throw domain_error(error.str());
		}
		total += result;
	}
	return total;
}

string ClientSocket::recv()
{
	stringstream buffer;
	char recv_data[PACK_SIZE];
	int result;
	do {
		memset(&recv_data, 0, PACK_SIZE);
		result = sys_recv(this->socket_fd, recv_data, PACK_SIZE, 0);
		buffer << recv_data;
	} while (result > 0);
	if (result < 0 || buffer.str().length() == 0)
	{
		stringstream error;
		error << "Client recv: " << strerror(errno);
		throw domain_error(error.str());
	}
	else {
		return buffer.str();
	}
}

void ClientSocket::close()
{
	sys_close(this->socket_fd);
	delete this;
}

ClientSocket::operator int() const
{
	if (this->created)
	{
		return this->socket_fd;
	}
	else {
		string error ("Object ClientSocket NOT CREATED!");
		throw logic_error(error);
	}
}

ClientSocket::operator bool() const
{
	if (this->created)
	{
		return true;
	}
	return false;
}

/*
 * Реализация класса сокет Socket, который является наследником
 * серверного и клиентского сокета
 */
//Socket::Socket() {

//}
