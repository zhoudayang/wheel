#pragma once

#include <mysql_driver.h>
#include <mysql_connection.h>
#include <boost/noncopyable.hpp>
#include <cppconn/prepared_statement.h>
#include <cppconn/statement.h>
#include <assert.h>


class mysql_instance :boost::noncopyable {
public:
	//return single instance
	static mysql_instance * GetInstance();

	void commit() {
		assert(con_->isValid());
		con_->commit();
	}

	sql::Statement * createStatement() {
		assert(con_->isValid());
		return con_->createStatement();
	}

	sql::PreparedStatement * prepareStatement(const sql::SQLString &sql) {
		assert(con_->isValid());
		return con_->prepareStatement(sql);
	}

	~mysql_instance();

private:

	//error occurred, crash immediately!
	mysql_instance() noexcept;
	boost::scoped_ptr<sql::mysql::MySQL_Driver> driver_;
	boost::scoped_ptr<sql::Connection> con_;
};

