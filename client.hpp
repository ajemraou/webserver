/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajemraou <ajemraou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 14:51:32 by ajemraou          #+#    #+#             */
/*   Updated: 2023/06/22 09:48:52 by ajemraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef CLIENT_HPP
#define CLIENT_HPP

#include "parsing.hpp"
#include "request.hpp"
#include "response.hpp"

struct data_header {
	/* add this iterators for a map loaction */
	std::map<std::string, std::map<std::string, std::string> >::const_iterator	it;
	std::map<std::string, std::string>::const_iterator							iter;

	/* They are necessary when processing requests */
	std::string		Content_type;
	std::string		Host;
	std::string		transfer_encoding;
	std::string		method;
	std::string		uri;
	std::string		http_version;
	std::string		boundary;
	std::string		new_uri;
	std::string		query;
	std::string		redirect_path;
	std::string		methods;
	std::string		Cookies;
	std::string		requested_resource;
	std::string		cgi_path;
	std::string		cgi_script;
	std::string		path_info;
	std::string		TempPath;
	std::string		client_index;
	int				Content_Length;
	int				res_status;

	/* Boolean variables */
	bool			is_redirect;
	bool			_is_cgi;
	bool			read_p;
	bool			write_p;
	bool			exec_p;
	bool			is_dir;
	bool			_uploaded;
	bool			_error;
	data_header();
};

class Client
{
	Socket				*Base;
	User_data			*user_data;
	char				buffer[BUFFER_SIZE];
	struct				kevent	client_event[2];
	struct				sockaddr client;
	socklen_t			len;
	int					fd;
	int					nbytes;
	std::string			request_buffer;
	data_header			*header_data;
	request				*client_request;
	response			*client_response;

public:

	Client( const data_serv*,  Socket*, int );
	~Client( );

	int		client_connection( int );
	void	attach_client_socket( int );
	int		read_from_socket();
	void	send_the_response();

	static int is_file_or_directory(const char *str, data_header *);

	bool 	eof();
	void	close_fd();
	void	client_index( int index );
	void	SetTemporaryPath( std::string );
};

#endif /* CLIENT_HPP */
