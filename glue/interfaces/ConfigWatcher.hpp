#include <iostream>
#include <vector>
#include <functional>

#ifndef __CONFIG_WATCHER__
#define __CONFIG_WATCHER__

/** \ingroup config */
/** \addtogroup config
* @{
*/
namespace config
{  

  using NotificationCallback = std::function<void(void *obj, int, void*)>;
  using CallbackVector = std::vector<std::vector<std::pair<void*,NotificationCallback>>>;

  /**
   * This class is meant to abstract the state machine of the monitoring
   * framework/lib oF file changes (like inotify) and its APIs/configuration.
   * By providing virtual methodes like start, stop, configure, the startup sequence
   * is independent of the framework, and can be implemented.
   * Check Main for the startup sequence.
   *
   */
  class ConfigWatcher
  {
    public:
      
      ConfigWatcher(){}
      virtual ~ConfigWatcher(){}
      
      virtual int start() {}
      virtual int configure() {}
      virtual int stop() {}
      virtual int restart() {}


     /**
     * @brief This API will pass the funtion pointer to the config watcher which will
     * be called when the event msgType is received in the condig watcher
       @param [in] msgType : the message to be notifuied on
       @param [in] function_pointer : the notification function to be called once the event (msgType) takes place
     * @return  0 on sucess
     */
      virtual int register_callback(int msgType, void* obj, NotificationCallback function_pointer) {}

  };

}
/** @} end of group config */
#endif /*__CONFIG_WATCHER__*/
