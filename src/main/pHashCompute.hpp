/* The MIT License (MIT)
 * Copyright (c) 2014 Nicholas Wright
 * http://opensource.org/licenses/MIT
 */

/**
 * @file pHashCompute.hpp
 *
 * @date 18 Mar 2015
 * @author Nicholas Wright
 * @brief an undocumented file
 * 
 * Some more details about this file.
 */
#ifndef SRC_MAIN_PHASHCOMPUTE_HPP_
#define SRC_MAIN_PHASHCOMPUTE_HPP_

#include "zmq.hpp"

#include <boost/thread.hpp>
#include <boost/thread/thread.hpp>
#include <log4cplus/logger.h>
#include <log4cplus/loggingmacros.h>

namespace imageHasher {

class pHashCompute {
public:
	pHashCompute(std::string server_ip, int remote_push_port, int remote_pull_port, int workers);
	virtual ~pHashCompute();

private:
	static const std::string server_socket;
	static const std::string worker_pull_socket;
	static const std::string worker_push_socket;
	static const std::string worker_ready_socket;

	log4cplus::Logger logger;

	zmq::context_t *context;
	zmq::socket_t *worker_pull, *worker_push;
	zmq::socket_t *client_pull, *client_push;
	zmq::socket_t *worker_ready;

	boost::thread_group worker_group;

	std::string pull_addr;
	std::string push_addr;

	void setup_sockets(std::string ip, int remote_push_port, int remote_pull_port);
	void create_threads(int num_of_threads);
	void process_requests(int worker_no);
	void route_tasks();
	void route_results();
	std::string create_address(std::string ip, int port);
	void thread_ready_wait(int num_of_threads);
};

} /* namespace imageHasher */

#endif /* SRC_MAIN_PHASHCOMPUTE_HPP_ */
