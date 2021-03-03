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

      int start() override;
      int stop() override;
      int configure() override;
      int restart() override;
      int getApis(std::map<std::string, nlohmann::json> &map) override;
      
      void setConfigWatcher(ConfigWatcher* config_watcher);
      ConfigWatcher* getConfigWatcher();

    private:
      GenericConfigManager *real_engine; /**< pointer to the config parser engine used : toJson + yaml-cpp */
      ConfigWatcher *watcher; /**< pointer to the ConfigWatcher used internally to be passed using setConfigWatcher*/
  };

}
