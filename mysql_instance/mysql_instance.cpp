#include "mysql_instance.h"
//definiton  for some constants
#include "constants.h"

#include <stdio.h>


mysql_instance * mysql_instance::GetInstance() {
	
	static mysql_instance m_instance;
	return &m_instance;
}

mysql_instance::~mysql_instance()
{
	//close connection
	con_->close();
}

mysql_instance::mysql_instance() noexcept:
	driver_(sql::mysql::get_mysql_driver_instance()),
	//here MYSQL_CONNECTION MYSQL_USER MYSQL_PASSWORD  is the definition of mysql server connection info which define in constants.h 
	con_(driver_->connect(MYSQL_CONNECTION, MYSQL_USER, MYSQL_PASSWORD))
{
	if (!con_.get() || !con_->isValid()) {
		printf("fail to connect to mysql server!");
		abort();
	}
	con_->setSchema(MYSQL_DATABASE);
}
