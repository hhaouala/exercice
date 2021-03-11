#include <GenericConfigManager.hpp>
#include <YAMLtoJsonConfigManager.hpp>
#include <FileWatcher.hpp>
#include <tojson.hpp>

#ifndef __CORE_CONFIG_MANAGER__
#define __CORE_CONFIG_MANAGER__

namespace config
{
  class CoreConfigManager : YAMLtoJsonConfigManager
  {
    public:
      CoreConfigManager(FileWatcher &watcher);
      CoreConfigManager(FileWatcher &watcher, const std::string &config);
      ~CoreConfigManager();

      int start() override;
      int stop() override;
      int configure() override;
      int restart() override;
      int getApis(std::map<std::string, nlohmann::json> &map) override;
      
    private:
      FileWatcher &watcher; /**< reference to the ConfigWatcher used internally to be passed using setConfigWatcher*/
  };
}

#endif /*__CORE_CONFIG_MANAGER__*/