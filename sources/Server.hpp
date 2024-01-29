#ifndef SERVER_HPP
#define SERVER_HPP

#include "Channel.hpp"
#include "Client.hpp"
#include "Parser.hpp"
#include <fcntl.h>
#include <iostream>
#include <map>
#include <netdb.h>
#include <netinet/in.h>
#include <stdexcept>
#include <string.h>
#include <sys/poll.h>
#include <sys/socket.h>
#include <unistd.h>
// #include "Base2.hpp"
#include "Command.hpp"
#include "Utils.hpp"
#include "Socket.hpp"

class Client;
class Channel;

class Server {
      private:
	const std::string port;
	const std::string pass;
	Socket sock;
	// File descriptors events on which we want to be notified about.
	std::vector<pollfd> fds;
	std::map<int, Client *> clients;
	std::vector<Channel *> channels;

      public:
	Server(const std::string &port, const std::string &pass);
	~Server();
	int initializeSocket();
	void start();
	void disconnectClient(int fd);
	void connect_client();
	void handle_client_message(int fd);
	struct message get_client_message(int fd);
	void dispatch(Client *c, message m);
	std::string getPassword() const;
	Client *getClient(const std::string &nickname);
	Channel *getChannel(const std::string &name);
	Channel *addChannel(const std::string &name, const std::string &key,
			    Client *client);
	void closeFreeALL(void);
	void updateNicknameInClients(int fd, const std::string& newNickname);
	void updateNicknameInChannels(const std::string& oldNickname, const std::string& newNickname);
	std::vector<Channel *>  getChannels();
};

#endif