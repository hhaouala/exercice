#include <iostream>
#include <vector>

#ifndef __CONFIG_WATCHER__
#define __CONFIG_WATCHER__

/** \ingroup config */
/** \addtogroup config
* @{
*/
namespace config
{  

  typedef void (*function_ptr_generic)(void* obj, int eventId, void* data);
  using CallbackVector = std::vector<std::vector<std::pair<void*,function_ptr_generic>>*>;

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
      
      virtual int start() = 0;
      virtual int configure() = 0;
      virtual int stop() = 0;
      virtual int restart() = 0;


     /**
     * @brief This API will pass the funtion pointer to the config watcher which will
     * be called when the event msgType is received in the condig watcher
       @param [in] msgType : the message to be notifuied on
       @param [in,out] obj : pointer on the object needing the notification (not thread safe)
       @param [in] function_pointer : the notification function to be called once the event (msgType) takes place
     * @return  0 on sucess
     */
      virtual int register_callback(int msgType, void* obj, function_ptr_generic function_pointer) = 0;

  };

}
/** @} end of group config */
#endif /*__CONFIG_WATCHER__*/
