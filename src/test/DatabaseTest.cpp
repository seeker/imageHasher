#include <gtest/gtest.h>
#include "../include/Database.hpp"
#include <boost/filesystem.hpp>
#include <iostream>

class DatabaseTest : public :: testing::Test {
protected:

	Database* db;
	boost::filesystem::path* dbPath;

	boost::filesystem::path tempfile() {
		return boost::filesystem::temp_directory_path() /= boost::filesystem::unique_path();
	}

	DatabaseTest() {
		dbPath = new boost::filesystem::path(tempfile());
		db = new Database(dbPath->c_str());
	}

	~DatabaseTest() {
		db->shutdown();
		delete(db);
	}
};

TEST_F(DatabaseTest, dbCreationCustom) {
	ASSERT_TRUE(boost::filesystem::exists(*dbPath));
}

TEST_F(DatabaseTest, writeRecords) {
	Database::db_data dbd1("foo");
	Database::db_data dbd2("bar");

	dbd1.status = Database::OK;
	dbd2.status = Database::OK;

	db->add(dbd1);
	db->add(dbd2);

	db->shutdown();

	ASSERT_EQ(2, db->getRecordsWritten());
}

TEST_F(DatabaseTest, writeRecordsWithInvalid) {
	Database::db_data dbd1("foo");
	Database::db_data dbd2("bar");
	Database::db_data dbd3("notValid");

	dbd1.status = Database::OK;
	dbd2.status = Database::OK;
	dbd3.status = Database::INVALID;

	db->add(dbd1);
	db->add(dbd2);
	db->add(dbd3);

	db->shutdown();

	ASSERT_EQ(3, db->getRecordsWritten());
}

TEST_F(DatabaseTest, writeDuplicateRecords) {
	Database::db_data dbd1("foo");
	Database::db_data dbd2("foo");

	dbd1.status = Database::OK;
	dbd2.status = Database::OK;

	db->add(dbd1);
	db->add(dbd2);

	db->shutdown();

	ASSERT_EQ(1, db->getRecordsWritten());
}

TEST_F(DatabaseTest, entryExistsNonExistant) {
	Database::db_data dbd1("foo");

	ASSERT_FALSE(db->entryExists(dbd1));
}

TEST_F(DatabaseTest, entryExists) {
	Database::db_data dbd1("foo");
	dbd1.status = Database::OK;
	db->add(dbd1);
	db->flush();
	ASSERT_TRUE(db->entryExists(dbd1));
	db->shutdown();
}

TEST_F(DatabaseTest, getSHAvalid) {
	Database::db_data data;

	data.filePath = fs::path("foobar");
	data.sha256 = "ABCD";
	data.pHash = 1;
	data.status = Database::OK;

	db->add(data);
	db->flush();

	std::string shaHash = db->getSHA(fs::path("foobar"));

	ASSERT_EQ("ABCD", shaHash);
	db->shutdown();
}

TEST_F(DatabaseTest, getSHANotExisting) {
	std::string shaHash = db->getSHA(fs::path("unknown"));

	ASSERT_TRUE(shaHash.empty());
	db->shutdown();
}

TEST_F(DatabaseTest, updateSHA) {
	Database::db_data data;

	data.filePath = fs::path("foobar");
	data.sha256 = "";
	data.pHash = 1;
	data.status = Database::OK;

	db->add(data);
	db->flush();

	std::string shaHash = db->getSHA(fs::path("foobar"));

	ASSERT_TRUE(shaHash.empty());

	db->updateSHA256("foobar", "foo");

	shaHash = db->getSHA(fs::path("foobar"));

	ASSERT_EQ("foo", shaHash);
}

TEST_F(DatabaseTest, getDefaultUserSchemaVersion) {
	int version = db->getUserSchemaVersion();

	ASSERT_EQ(Database::getCurrentSchemaVersion(),version);
}

TEST_F(DatabaseTest, setUserSchemaVersion) {
	int version = db->getUserSchemaVersion();

	// guard
	ASSERT_EQ(Database::getCurrentSchemaVersion(), version);

	db->setUserSchemaVersion(42);
	version = db->getUserSchemaVersion();

	ASSERT_EQ(42, version);
}

TEST_F(DatabaseTest, dbNewerThanCurrent) {
	db->exec("PRAGMA locking_mode = NORMAL;");

	db->setUserSchemaVersion(42);
	int version = db->getUserSchemaVersion();

	ASSERT_EQ(42, version);

	db->shutdown();
	ASSERT_THROW(Database db2(dbPath->c_str()), std::runtime_error);
}


