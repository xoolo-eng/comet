#include <comet/config.h>
#include <stdexcept>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <cstring>
#include <cstdint>


using namespace std;


/*
 * Удаление начальных и конечных пробелов, и символа переноса из строки
 */
string clear_string(string &str)
{
	size_t len_string;
	while (str[0] == ' ')
	{
		str.erase(0, 1);
	}
	len_string = str.length();
	if (str[len_string-1] == '\n')
	{
		str.erase(len_string-1, 1);
		--len_string;
	}
	while (str[len_string -1] == ' ')
	{
		str.erase(len_string-1, 1);
		--len_string;
	}
	return str;
}

/*
 * Деление полученной строки (key = value) по делителю (по умолчанию "=").
 * После разделения происходит удаление "незначащих" символов:
 *	перенос строки
 *	начальные пробелы
 *	конечные пробелы
 * Возвращается пара значений в виде строк разделенных по первому
 * встреченному делителю.
 * При ошибке в форматировании строки
 * бросается исключение: invalid_argument()
 */
pair<string, string> Config::get_pair(string &str, char delimiter='=')
{
	pair<string, string> key_value;
	uint_fast8_t size_str;
	if (str.length() < 255)
	{
		size_str = str.length();
	}
	else
	{
		size_str = 255;
	}
	uint_fast8_t pos_delimiter = str.find(delimiter);
	if ((pos_delimiter == 255) || pos_delimiter == 0)
	{
		string error = "get_pair: Error in enter Parametr!";
		throw invalid_argument(error);
	}
	string buffer_first (str.substr(0, pos_delimiter));
	string buffer_second (str.substr(pos_delimiter + 1, size_str));
	key_value.first = clear_string(buffer_first);
	key_value.second = clear_string(buffer_second);
	return key_value;
}

/*
 * Парсинг полученых данных. Принимает путь к файлу и конфигурцию
 * по умолчанию. Данные делятся по символу переноса или
 * окончания строки.
 */
void Config::parse(string file_name, string default_config)
{
	string line;
	ifstream file;
	file.open(file_name);
	this->options.clear();
	while (getline(file, line))
	{
		if ((line[0] != '#') && (line.length() > 0))
		{
			this->options.insert(this->get_pair(line));
		}
	}
	file.close();
	stringstream stream_default_conf (default_config);
	while (getline(stream_default_conf, line))
	{
		this->options.insert(this->get_pair(line));
	}
}

/*
 * Парсинг полученых данных. Принимает путь к файлу. Данные делятся по символу
 *  переноса или окончания строки.
 */
void Config::parse(string file_name)
{
	string line;
	ifstream file;
	file.open(file_name);
	while (getline(file, line))
	{
		if ((line[0] != '#') && (line.length() > 0))
		{
			this->options.insert(this->get_pair(line));
		}
	}
	file.close();
}

/*
 * Получение значения ключа по его названию. При отсутствии ключа
 * бросается исключение out_of_range(). Для проверки наличия ключа
 * использовать this.is_key(name).
 */
string Config::get(string key)
{
	return this->options.at(key);
}

/*
 * Замена значения ключа. Принимает название ключа и его новое значение
 **/
void Config::set(string key, string value)
{
	auto option = this->options.find(key);
	option->second = value;
}

/*
 * Добавление нового ключа
 */
void Config::add(string key, string value)
{
	pair<string, string> buffer;
	buffer.first = clear_string(key);
	buffer.second = clear_string(value);
	this->options.insert(buffer);
}

/*
 * Проверка наличия ключа.
 */
bool Config::is_key(string key)
{
	try
	{
		static_cast<void>(this->options.at(key));
	}
	catch(out_of_range)
	{
		return false;
	}
	return true;
}
