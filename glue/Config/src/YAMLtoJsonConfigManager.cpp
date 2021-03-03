#include <iostream>
#include <exception>
#include <YAMLtoJsonConfigManager.hpp>

using namespace tojson;

namespace config
{
  template<typename DATA_HOLDER>  
  YAMLtoJsonConfigManager<DATA_HOLDER>::YAMLtoJsonConfigManager(std::string configFile) 
    : configFile(configFile),
      globalConfig("")
  {

  }

  template<typename DATA_HOLDER>
  YAMLtoJsonConfigManager<DATA_HOLDER>::~YAMLtoJsonConfigManager()
  {
    stop();
  }

  /**
   * @brief This API will be called by YAMLtoJsonConfigManager::configure() when the
   * DATA_HOLDER type is std::map<std::string, nlohmann::json>.
   */
  int store_paths(nlohmann::json paths, std::map<std::string, nlohmann::json> &map){
    for (auto &el : paths.items())
    {
      //std::cout << "key: " << el.key() << ", value:" << el.value() << std::endl;
      const std::string key = el.key();
      const nlohmann::json val = el.value();
      map[key] = val;
    }

    return 0;
  }


  /**
   * @brief This API will be called by YAMLtoJsonConfigManager::configure() when the
   * DATA_HOLDER type is std::vector<std::string>.
   */
  int store_paths(nlohmann::json paths, std::vector<std::string> &vect){
    for (auto &el : paths.items())
    {
      //std::cout << "key: " << el.key() << ", value:" << el.value() << std::endl;
      const std::string key = el.key();
      const nlohmann::json val = el.value();
      vect.push_back(key);
    }

    return 0;
  }
  
  template<typename DATA_HOLDER>
  int YAMLtoJsonConfigManager<DATA_HOLDER>::start()
  {
    
  }
  
  template<typename DATA_HOLDER>
  int YAMLtoJsonConfigManager<DATA_HOLDER>::stop()
  {
    return 0;
  }
  
  template<typename DATA_HOLDER>
  int YAMLtoJsonConfigManager<DATA_HOLDER>::restart()
  {
    int ret = 0;
    ret |= stop();
    ret |= configure();
    ret |= start();
    return ret;
  }

  template<typename DATA_HOLDER>
  int YAMLtoJsonConfigManager<DATA_HOLDER>::configure()
  {
    apiMap.clear();
    try {
      globalConfig = loadyaml(configFile);

      store_paths(globalConfig["paths"], apiMap);
      
      return 0;
    }
    catch(std::exception& e)
    {
      std::cout << "Caught " << e.what() << std::endl;
      return -1;
    }
    return 0;
  }

  template<typename DATA_HOLDER>
  int YAMLtoJsonConfigManager<DATA_HOLDER>::getApis(DATA_HOLDER &map)
  {
    map = apiMap;
  }


}
