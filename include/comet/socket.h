#ifndef SOCKET_H
#define SOCKET_H

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <unistd.h>
#include <string>
#include <cstdint>

#define PACK_SIZE 1300

class ServerSocket
{
	public:
		ServerSocket();
		ServerSocket(int domain, __socket_type type);
		ServerSocket(int domain, __socket_type type, int protocol);
		~ServerSocket() noexcept;
		void bind(std::string address, short post);
		void listen(int backlog);
		ServerSocket accept();
		void nonblock();
		int send(std::string message);
		std::string recv();
		std::string address();
		int port();
		void close();
		operator int() const;
		operator bool() const;
	protected:
		int socket_fd;
		sockaddr_in server_addr;
		bool connect;
		bool created;
};

class ClientSocket
{
	public:
		ClientSocket();
		ClientSocket(int domain, __socket_type type, int protocol);
		~ClientSocket() noexcept;
		void connect(std::string address, int port);
		void nonblock();
		int send(std::string message);
		std::string recv();
		void close();
		operator int() const;
		operator bool() const;
	protected:
		int socket_fd;
		sockaddr_in client_addr;
		bool created;
};

class Socket : public ServerSocket, public ClientSocket
{
	public:
		Socket();
};

typedef ServerSocket s_socket_t;
typedef ClientSocket c_socket_t;

/*
 * Пересмотреть реализацию презгрузки системных функций
 */
int_fast8_t sys_bind(int sockfd, struct sockaddr *addr, int addrlen)
{
	return bind(sockfd, addr, addrlen);
}

int_fast8_t sys_listen(int sockfd, int backlog)
{
	return listen(sockfd, backlog);
}

int_fast8_t sys_accept(int sockfd, void *addr, socklen_t addrlen)
{
	return accept(sockfd, (sockaddr *)addr, &addrlen);
}

int_fast8_t sys_send(int sockfd, const void *msg, int len, int flags)
{
	return send(sockfd, msg, len, flags);
}

int_fast8_t sys_recv(int sockfd, void *buf, int len, int flags)
{
	return recv(sockfd, buf, len, flags);
}

int_fast8_t sys_close(int fildes) {
	return close(fildes);
}

int_fast8_t sys_connect(int sockfd, struct sockaddr *serv_addr, int addrlen)
{
	return connect(sockfd, serv_addr, addrlen);
}

#endif // SOCKET_H
