/* The MIT License (MIT)
 * Copyright (c) 2014 Nicholas Wright
 * http://opensource.org/licenses/MIT
 */

/*
 * HashWorker.h
 *
 *  Created on: 20 Aug 2013
 *      Author: nicholas
 */

#ifndef HASHWORKER_H_
#define HASHWORKER_H_

#include <boost/filesystem.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/thread.hpp>
#include <boost/thread/thread.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/sources/severity_logger.hpp>

#include <memory>

#include "Database.hpp"

using boost::filesystem::path;

class HashWorker {
public:
	HashWorker(std::shared_ptr<std::list<path>> image_paths, int number_of_workers);
	HashWorker(std::list<path>* ,int)__attribute__((deprecated));
	void start();
	void clear();

private:
	int numOfWorkers;
	std::shared_ptr<std::list<path>> imagePaths;
	boost::mutex workQueueMutex;
	boost::mutex stats_mutex;
	boost::log::sources::severity_logger<boost::log::trivial::severity_level> logger;
	Database db;
	bool running;
	int totalNumOfFiles;
	unsigned int skipped_files;

	typedef std::list<path> pathList;

	void doWork(int);
	path getWork();
};

#endif /* HASHWORKER_H_ */
