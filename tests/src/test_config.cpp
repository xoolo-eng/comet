#include <iostream>
#include <comet/config.h>
#include <string>
#include <stdexcept>
#include <fstream>
#include <cstdio>
#include <cassert>

using namespace std;

string FILE_NAME = "../files/config.cfg";

string DEFAULT_CONFIG_ERR =
		"name=DEFAULT_CONFIG_ERR\n"
		"listen_address = 192.168.0.88\n"
		"error string\n"
		"not value=\n";

string CONFIG_FILE_ERR =
		"name=CONFIG_FILE_ERR\n"
		"listen_address = 192.168.0.99\n"
		"error string file\n"
		"not value file=\n";

string DEFAULT_CONFIG =
		"name=DEFAULT_CONFIG\n"
		"listen_address= 192.168.0.88\n"
		"error_string file=error1\n"
		"TEST = DEFAULT\n"
		"not_value_file=line\n";

string CONFIG_FILE =
		"name = CONFIG_FILE\n"
		"#line=error\n"
		"listen_address = 192.168.0.99\n"
		"\n"
		"error_string_file=error2\n"
		"not_value_file=line\n";

void create_file(string config_data)
{
	ofstream file_config_out;
	file_config_out.open(FILE_NAME);
	file_config_out << config_data;
	file_config_out.close();
}

void subtest_1_1(Config &config)
{
	cout << "subtest_1_1 - start\n";
	create_file(CONFIG_FILE_ERR);
	/*
	 * Не корректные данные в файле конфигурации и в настройках по умолчанию.
	 */
	try
	{
		config.parse(FILE_NAME, DEFAULT_CONFIG_ERR);
		cout << "Not error in config file!\n";
		cout << "Not error in default config!\n";
		cout << "config.parse(file_path, DEFAULT_CONFIG_ERR) - OK!\n\n";
	}
	catch(invalid_argument &err)
	{
		cout << "Error in config file!\n";
		cout << "Error in default config!\n";
		cout << err.what() << "\n";
		cout << "config.parse(file_path, DEFAULT_CONFIG_ERR) - OK!\n\n";
	}
	remove(FILE_NAME.c_str());
}

void subtest_1_2(Config &config)
{
	cout << "subtest_1_2 statr\n";
	create_file(CONFIG_FILE_ERR);
	/*
	 * Не корректные данные в файле конфигурации (без настроек по умолчанию).
	 */
	try
	{
		config.parse(FILE_NAME);
		cout << "Not error in config file!\n";
		cout << "config.parse(file_path); - ERR!\n\n";
	}
	catch(invalid_argument &err)
	{
		cout << "Error in config file!\n";
		cout << err.what() << "\n";
		cout << "config.parse(file_path); - OK!\n\n";
	}
	remove(FILE_NAME.c_str());
}

void subtest_1_3(Config &config)
{
	cout << "subtest_1_3 - start\n";
	create_file(CONFIG_FILE);
	/*
	 * Корректные данные в файле конфигурации и настройках по умолчанию.
	 */
	try
	{
		config.parse(FILE_NAME, DEFAULT_CONFIG);
		cout << "Not error in config file!\n";
		cout << "Not error in default config!\n";
		cout << "config.parse(file_path, DEFAULT_CONFIG) - OK!\n\n";
	}
	catch(invalid_argument &err)
	{
		cout << "Error in config file!\n";
		cout << "Error in default config!\n";
		cout << err.what() << "\n";
		cout << "config.parse(file_path, DEFAULT_CONFIG) - ERR!\n\n";
	}
	remove(FILE_NAME.c_str());
}

void subtest_1_4(Config &config)
{
	cout << "subtest_1_4 - start\n";
	create_file(CONFIG_FILE);
	/*
	 * Коректные данные в файле конфигурации (без настроек по умолчанию).
	 */
	try
	{
		config.parse(FILE_NAME);
		cout << "Not error in config file!\n";
		cout << "config.parse(file_path); - OK!\n\n";
	}
	catch(invalid_argument &err) {
		cout << "Error in config file!\n";
		cout << err.what() << "\n";
		cout << "config.parse(file_path); - ERR!\n\n";
	}
	remove(FILE_NAME.c_str());
}

int test_1(Config &config)
{
	/*
	 * Тестирование метода parse()
	 */
	cout << "test_1 - start\n\n";
	subtest_1_1(config);
	subtest_1_2(config);
	subtest_1_3(config);
	subtest_1_4(config);
	cout << "test_1() - OK!\n\n";
	return 0;
}

int test_2(Config &config)
{
	/*
	 * Тестирование метода get()
	 */
	create_file(CONFIG_FILE);
	config.parse(FILE_NAME);
	assert(config.get("name") == "CONFIG_FILE");
	assert(config.get("listen_address") == "192.168.0.99");
	if (config.is_key("line"))
	{
		assert(config.get("line") == "error");
	}
	cout << "config.parse(FILE_NAME) - OK!\n";
	config.parse(FILE_NAME, DEFAULT_CONFIG);
	assert(config.get("name") == "CONFIG_FILE");
	assert(config.get("listen_address") == "192.168.0.99");
	assert(config.get("TEST") == "DEFAULT");
	cout << "config.parse(FILE_NAME, DEFAULT_CONFIG) - OK!\n";
	remove(FILE_NAME.c_str());
	cout << "test_2() - OK!\n\n";
	return 0;
}

int test_3(Config &config)
{
	/*
	 * Тестирование метода set().
	 */
	create_file(CONFIG_FILE);
	config.parse(FILE_NAME, DEFAULT_CONFIG);
	string test_value = "new_value";
	assert(config.get("name") == "CONFIG_FILE");
	config.set("name", test_value);
	assert(config.get("name") == test_value);
	cout << "test_3() - OK!\n\n";
	remove(FILE_NAME.c_str());
	return 0;
}

int test_4(Config &config)
{
	create_file(CONFIG_FILE);
	config.parse(FILE_NAME, DEFAULT_CONFIG);
	string new_key = "key_100";
	string new_value = "Value_100";
	config.add(new_key, new_value);
	assert(config.get(new_key) == new_value);
	cout << "test_4() - OK!\n\n";
	remove(FILE_NAME.c_str());
	return 0;
}

int main()
{
	Config& config = Config::Instance();
	test_1(config);
	test_2(config);
	test_3(config);
	test_4(config);
	return 0;
}
