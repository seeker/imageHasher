/*
 * Database.cpp
 *
 *  Created on: 21 Aug 2013
 *      Author: nicholas
 */

#include "../include/Database.hpp"
#include <string>

#include <odb/transaction.hxx>
#include <odb/result.hxx>
#include <odb/schema-catalog.hxx>

const char *dbName = "imageHasher.db";

const char *insertImageQuery = "INSERT INTO `imagerecord` (`path`,`sha_id`,`phash_id`) VALUES (?,?,?);";
const char *insertInvalidQuery = "INSERT INTO `badfilerecord` (`path`) VALUES (?);";
const char *insertFilterQuery = "INSERT OR IGNORE INTO `filterrecord` (`phash_id`, `reason`) VALUES (?,?);";
const char *prunePathQuery = "SELECT `path` FROM `imagerecord` WHERE `path` LIKE ? UNION SELECT `path` FROM `badfilerecord` WHERE `path` LIKE ?;";
const char *prunePathDeleteImage = "DELETE FROM `imagerecord` WHERE `path` = ?;";
const char *prunePathDeleteBadFile = "DELETE FROM `badfilerecord` WHERE `path` = ?;";
const char *checkExistsQuery = "SELECT EXISTS(SELECT 1 FROM `imagerecord` WHERE `path` = ? LIMIT 1) OR EXISTS(SELECT 1 FROM `badfilerecord`  WHERE `path` = ?  LIMIT 1);";
const char *checkSHAQuery = "SELECT EXISTS(SELECT 1 FROM `imagerecord` JOIN `sha_hash` ON `sha_id`= `id` WHERE `path` = ? AND `sha256` != '' LIMIT 1);";
const char *updateSha = "UPDATE `imagerecord` SET `sha_id`=? WHERE `path` = ?;";
const char *getSHAQuery = "SELECT `sha256` FROM `imagerecord` AS ir JOIN `sha_hash` AS h ON ir.sha_id=h.id WHERE `path` = ?;";
const char *getPhashQuery = "SELECT `pHash` FROM `imagerecord` AS ir JOIN `phash_hash` AS h ON ir.sha_id=h.id WHERE `path` = ?;";
const char *getSHAidQuery = "SELECT `id` FROM `sha_hash` WHERE `sha256`= ?;";
const char *getpHashidQuery = "SELECT `id` FROM `phash_hash` WHERE `pHash`= ?;";
const char *insertShaRecordQuery = "INSERT INTO `sha_hash` (`sha256`) VALUES (?);";
const char *insertpHashRecordQuery = "INSERT INTO `phash_hash` (`pHash`) VALUES (?);";

const char *startTransactionQuery = "BEGIN TRANSACTION;";
const char *commitTransactionQuery = "COMMIT TRANSACTION;";

using namespace odb;

Database::Database(const char* dbPath) {
	dbName = dbPath;
	init();
}

Database::Database() {
	init();
}

Database::~Database() {
	shutdown();
}

int Database::flush() {
	int drainCount = 0;

	LOG4CPLUS_INFO(logger, "Flushing lists...");

	drainCount = drain();
	drainCount += drain();

	return drainCount;
}

void Database::shutdown() {
	if (running) {
		LOG4CPLUS_INFO(logger, "Shutting down...");
		running = false;
		LOG4CPLUS_INFO(logger, "Waiting for db worker to finish...");
		workerThread->interrupt();
		workerThread->join();
		LOG4CPLUS_INFO(logger, "Closing database...");
	}
}

void Database::exec(const char* command) {
	orm_db->execute(command);
}

void Database::init() {
	boost::mutex::scoped_lock lock(dbMutex);
	this->currentList = &dataA;
	this->recordsWritten = 0;
	this->running = true;
	logger = log4cplus::Logger::getInstance(LOG4CPLUS_TEXT("Database"));

	setupDatabase();
	prepareStatements();

	workerThread = new boost::thread(&Database::doWork, this);
}

void Database::setupDatabase() {
	orm_db = new sqlite::database(dbName,SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE);

	LOG4CPLUS_INFO(logger, "Setting up database " << dbName);

	transaction t(orm_db->begin());

	odb:schema_catalog::create_schema(*orm_db, "", false);
/*
 	 // TODO get this to work with odb
	exec(const_cast<char *>("PRAGMA page_size = 4096;"));
	exec(const_cast<char *>("PRAGMA cache_size=10000;"));
	exec(const_cast<char *>("PRAGMA locking_mode=EXCLUSIVE;"));
	exec(const_cast<char *>("PRAGMA synchronous=NORMAL;"));
	exec(const_cast<char *>("PRAGMA temp_store = MEMORY;"));
	exec(const_cast<char *>("PRAGMA journal_mode=MEMORY;"));
	*/

	t.commit();
}


void Database::updateSHA256(std::string path, std::string sha){
	int shaId = getSHAid(sha);

	LOG4CPLUS_DEBUG(logger,"Found ID "<< shaId << " for sha " << sha);

	if((shaId == -1) || (shaId == 0)) {
		LOG4CPLUS_ERROR(logger,"No pHash available, unable to update SHA");
		return;
	}else{
		int64_t pHash = getPhash(path);
		shaId = addHashEntry(sha,pHash);
	}

	//TODO implement update sha
}

void Database::add(db_data data) {
	boost::mutex::scoped_lock lock(flipMutex);
	currentList->push_back(data);
}

void Database::flipLists() {
	boost::mutex::scoped_lock lock(flipMutex);

	if(currentList == &dataA) {
		currentList = &dataB;
	}else{
		currentList = &dataA;
	}
}

int Database::drain() {
	boost::mutex::scoped_lock lock(dbMutex);
	std::list<db_data>* workList;
	int drainCount = 0;

	workList = currentList;
	flipLists();

	startTransaction();

	for(std::list<db_data>::iterator ite = workList->begin(); ite != workList->end(); ++ite) {
		addToBatch(*ite);
		recordsWritten++;
		drainCount++;
	}

	commitTransaction();

	workList->clear();
	return drainCount;
}

bool Database::entryExists(fs::path filePath) {
boost::mutex::scoped_lock lock(dbMutex);
	const char* path = filePath.c_str();
	int pathSize = filePath.string().size();

	LOG4CPLUS_DEBUG(logger, "Looking for file " << path);

	//TODO implement entry exists

	return false;
}

bool Database::entryExists(db_data data) {
	return entryExists(data.filePath);
}

bool Database::hasSHA(fs::path filepath) {
	boost::mutex::scoped_lock lock(dbMutex);

	LOG4CPLUS_DEBUG(logger, "Looking if " << filepath << " has SHA");

	//TODO implement has sha

	return false;
}

std::list<fs::path> Database::getFilesWithPath(fs::path directoryPath) {
	std::list<fs::path> filePaths;
	std::string query(directoryPath.string());
	query += "%";
	const char* path = query.c_str();
	int pathSize = query.size();
	int response = -1;

	LOG4CPLUS_INFO(logger, "Looking for files with path " << directoryPath);

	boost::mutex::scoped_lock lock(dbMutex);

	//TODO implement get file with path

	LOG4CPLUS_INFO(logger, "Found  " << filePaths.size() << " records for path " << directoryPath);
	return filePaths;
}

void Database::startTransaction() {
	//TODO implement start transaction
}

void Database::commitTransaction() {
	//TODO implement commit transaction
}

void Database::prunePath(std::list<fs::path> filePaths) {
	boost::mutex::scoped_lock lock(dbMutex);

	bool allOk = true;

	startTransaction();

	for(std::list<fs::path>::iterator ite = filePaths.begin(); ite != filePaths.end(); ++ite){
		const char* path = ite->c_str();
		int pathSize = ite->string().size();
		int response = 0;

		//TODO implement prunePath
	}

	commitTransaction();

	if (!allOk) {
		LOG4CPLUS_WARN(logger, "Failed to delete some file paths");
	}
}

void Database::addToBatch(db_data data) {
	int response = 0;
	int hashId = -1;

	switch (data.status) {
	case OK:
		hashId = getSHAid(data.sha256);

		if(hashId == -1) {
			hashId = addHashEntry(data.sha256, data.pHash);
		}

		if(hashId == -1) {
			LOG4CPLUS_WARN(logger, "Failed to add " << data.filePath << " / " << data.pHash);
			recordsWritten--;
			return;
		}

		//TODO add new record

		if (response != SQLITE_DONE) {
			LOG4CPLUS_WARN(logger, "Failed to add " << data.filePath << " / " << data.pHash);
			recordsWritten--;
		}

		break;

	case SHA:
		updateSHA256(data.filePath.string(), data.sha256);
		break;

	case INVALID:
		//TODO add invalid record

		if (response != SQLITE_DONE) {
			LOG4CPLUS_WARN(logger, "Failed to add " << data.filePath);
			recordsWritten--;
		}

		break;

	case FILTER:
		//TODO add filter record

		if (response != SQLITE_DONE) {
			LOG4CPLUS_WARN(logger, "Failed to add filter for " << data.pHash << " " << data.reason);
		}

		break;

	default:
		LOG4CPLUS_ERROR(logger, "Unhandled state encountered");
		throw "Unhandled state encountered";
		break;
	}
}

void Database::prepareStatements() {
	LOG4CPLUS_INFO(logger, "Creating prepared statements...");

	createPreparedStatement(insertImageQuery, addOkStmt);
	createPreparedStatement(insertInvalidQuery, addInvalidStmt);
	createPreparedStatement(insertFilterQuery,addFilterStmt);
	createPreparedStatement(checkExistsQuery, checkExistsStmt);
	createPreparedStatement(checkSHAQuery,checkSHAStmt);
	createPreparedStatement(getSHAQuery, getSHAqueryStmt);
	createPreparedStatement(getPhashQuery,getPhashQueryStmt);

	createPreparedStatement(startTransactionQuery, startTrStmt);
	createPreparedStatement(commitTransactionQuery, commitTrStmt);

	createPreparedStatement(prunePathQuery, pruneQueryStmt);
	createPreparedStatement(prunePathDeleteImage, pruneDeleteImageStmt);
	createPreparedStatement(prunePathDeleteBadFile, pruneDeleteBadFileStmt);

	createPreparedStatement(updateSha, updateShaStmt);
	createPreparedStatement(getSHAidQuery,getSHAidQueryStmt);

	createPreparedStatement(insertShaRecordQuery,insertShaRecordQueryStmt);
	createPreparedStatement(insertpHashRecordQuery,insertpHashRecordQueryStmt);
}

void Database::createPreparedStatement(const char *&query, sqlite3_stmt *&stmt) {
	//TODO implement create prepared statements
}

void Database::doWork() {
	while(running) {
		try{
			boost::this_thread::sleep_for(boost::chrono::seconds(3));
		}catch(boost::thread_interrupted&) {
			LOG4CPLUS_INFO(logger,"DB thread interrupted");
		}

		if(currentList->size() > 1000) {
			int drainCount = drain();
			LOG4CPLUS_INFO(logger, drainCount << " records processed, Total: " << recordsWritten);
		}
	}

	// make sure both lists are committed
	int drainCount = flush();
	LOG4CPLUS_INFO(logger, drainCount << " records processed, Total: " << recordsWritten);
}

unsigned int Database::getRecordsWritten() {
	return recordsWritten;
}

std::string Database::getSHA(fs::path filepath) {
	std::string sha = "";
	LOG4CPLUS_DEBUG(logger, "Getting SHA for path " << filepath);

	//TODO implement getSHA

	return sha;
}

int64_t Database::getPhash(fs::path filepath) {
	int pHash = -1;
	LOG4CPLUS_DEBUG(logger, "Getting pHash for path " << filepath);

	//TODO implement get phash

	return pHash;
}

int userVersionCallback(void* dbVersion,int numOfresults,char** valuesAsString,char** columnNames) {
	int version = -1;

	if(numOfresults == 1) {
		version = atoi(valuesAsString[0]);
		*((int*)dbVersion) = version;
	}

	return 0;
}

int emptySHAcheckCallback(void* emptyShaRows,int numOfresults,char** valuesAsString,char** columnNames) {
	int rows = -1;

	if(numOfresults == 1) {
		rows = atoi(valuesAsString[0]);
		*((int*)emptyShaRows) = rows;
	}

	return 0;
}

int Database::getEmptyShaRows() {
	int emptyShaRows = -1;

	//TODO implement get empty sha rows

	return emptyShaRows;
}

int Database::getSHAid(std::string sha) {
	int row_id = -1;

	//TODO implement get sha id

	return row_id;
}

int Database::getpHashId(long pHash) {
	int row_id = -1;

	//TODO implement get pHashId

	return row_id;
}

int Database::addHashEntry(std::string sha, u_int64_t pHash) {
	int rowId = -1;

	//TODO implement add hash entry

	return rowId;
}
