#include <iostream>
#include <exception>
#include <CoreConfigManager.hpp>

using namespace tojson;

namespace config
{
  CoreConfigManager::CoreConfigManager(FileWatcher &config_watcher) : watcher(config_watcher)
  {
  }
  
  CoreConfigManager::CoreConfigManager(FileWatcher &config_watcher, const std::string   &config) : YAMLtoJsonConfigManager(config), watcher(config_watcher)
  {
  }

  CoreConfigManager::~CoreConfigManager()
  {
    stop();
  }

  int CoreConfigManager::start()
  {
    int ret = 0;
    ret |= watcher.start();
    ret |= YAMLtoJsonConfigManager::start();
    return ret;
  }
  
  int CoreConfigManager::stop()
  {
    int ret = 0;
    ret |= watcher.stop();
    ret |= YAMLtoJsonConfigManager::stop();
    return ret;
  }
  
  int CoreConfigManager::restart()
  {
    int ret = 0;
    ret |= stop();
    ret |= configure();
    ret |= start();
    return ret;
  }

  int CoreConfigManager::configure()
  {

    int ret = 0;
    ret |= watcher.configure();
    ret |= YAMLtoJsonConfigManager::configure();
     return ret;
  }
  
  int CoreConfigManager::getApis(std::map<std::string, nlohmann::json> &map)
  {
    return YAMLtoJsonConfigManager::getApis(map); 
  }
}
