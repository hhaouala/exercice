#include <GenericConfigManager.hpp>
#include <tojson.hpp>

namespace config
{
  
  template<typename DATA_HOLDER>  
  class YAMLtoJsonConfigManager : GenericConfigManager
  {
    public:
      YAMLtoJsonConfigManager() : configFile(""), globalConfig("") {};
      YAMLtoJsonConfigManager(std::string configFile);
      ~YAMLtoJsonConfigManager();
      
      int start();
      int stop();
      int configure();
      int restart();
      int getApis(DATA_HOLDER &map);


    private:

      std::string configFile;
      DATA_HOLDER apiMap;
      nlohmann::json globalConfig;
  };

  template class YAMLtoJsonConfigManager<std::map<std::string, nlohmann::json>>;
  template class YAMLtoJsonConfigManager<std::vector<std::string>>;
  
}
