#include <iostream>
#include <exception>
#include <CoreConfigManager.hpp>
#include <FileWatcher.hpp>
#include <YAMLtoJsonConfigManager.hpp>

using namespace tojson;

namespace config
{
  CoreConfigManager::CoreConfigManager()
  {
    real_engine = (GenericConfigManager *) new YAMLtoJsonConfigManager<std::map<std::string, nlohmann::json>>();
  }
  
  CoreConfigManager::CoreConfigManager(std::string config)
  {
    real_engine = (GenericConfigManager *) new YAMLtoJsonConfigManager<std::map<std::string, nlohmann::json>>(config);
  }

  CoreConfigManager::~CoreConfigManager()
  {
    real_engine->stop();
    delete real_engine;
  }

  int CoreConfigManager::start()
  {
    int ret = 0;
    if(watcher)
    {
      ret |= watcher->start();
    }
     ret |= real_engine->start();
     return ret;
  }
  
  int CoreConfigManager::stop()
  {
    int ret = 0;
    if(watcher)
    {
      ret |= watcher->stop();
    }
     ret |= real_engine->stop();
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
    if(watcher)
    {
      ret |= watcher->configure();
    }
     ret |= real_engine->configure();
     return ret;
  }

  void CoreConfigManager::setConfigWatcher(ConfigWatcher* config_watcher)
  {
    watcher = config_watcher;
  }
  
  ConfigWatcher* CoreConfigManager::getConfigWatcher()
  {
    return watcher;
  }

  int CoreConfigManager::getApis(std::map<std::string, nlohmann::json> &map)
  {
    return real_engine->getApis(map); 
  }

}