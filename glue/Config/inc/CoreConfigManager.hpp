#include <GenericConfigManager.hpp>
#include <ConfigWatcher.hpp>

#include <tojson.hpp>


namespace config
{
  class CoreConfigManager : GenericConfigManager
  {
    public:
      CoreConfigManager();
      CoreConfigManager(std::string config);
      ~CoreConfigManager();

      int start();
      int stop();
      int configure();
      int restart();
      int getApis(std::map<std::string, nlohmann::json> &map);
      void setConfigWatcher(ConfigWatcher* config_watcher);
      ConfigWatcher* getConfigWatcher();

    private:
      GenericConfigManager *real_engine;
      ConfigWatcher *watcher;
  };

}
