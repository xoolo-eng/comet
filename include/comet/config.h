#ifndef CONFIG_H
#define CONFIG_H
#include <map>
#include <string>


class Config
{
	public:
		static Config& Instance()
		{
			static Config s;
			return s;
		}
		void parse(std::string file_name, std::string default_config);
		void parse(std::string file_name);
		std::string get(std::string key);
		void set(std::string key, std::string value);
		void add(std::string key, std::string value);
		bool is_key(std::string key);
	protected:
		std::pair<std::string, std::string> get_pair(std::string &str, char delimiter);
		std::map<std::string, std::string> options;
		std::string config_file;
	private:
		Config(){}
		~Config(){}
		Config(Config const&) = delete;
		Config &operator = (Config const&) = delete;
};


#endif // CONFIG_H
