#include <GenericConfigManager.hpp>
#include <tojson.hpp>

#ifndef __YAML_TO_JSON_CONFIG_MANAGER__
#define __YAML_TO_JSON_CONFIG_MANAGER__

namespace config
{
  /**
   * This class implements GenericConfigManager with a template.
   * The idea of the template is to make the DATA_HOLDER adaptable
   * to the container on which we'd like to get the APIs list
   * parsed with the config manager. 
   *
   */  
  //template<typename DATA_HOLDER>  
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
      int getApis(std::map<std::string, nlohmann::json> &map);


    private:

      std::string configFile;
      std::map<std::string, nlohmann::json> apiMap;
      nlohmann::json globalConfig;
  };

  //template class YAMLtoJsonConfigManager<std::map<std::string, nlohmann::json>>;
  //template class YAMLtoJsonConfigManager<std::vector<std::string>>;
  
}
#endif /*__YAML_TO_JSON_CONFIG_MANAGER__*/