#include <iostream>
#include <vector>

#ifndef __CONFIG_WATCHER__
#define __CONFIG_WATCHER__

namespace config
{  

  typedef void (*function_ptr_generic)(void* obj, int eventId, void* data);
  using CallbackVector = std::vector<std::vector<std::pair<void*,function_ptr_generic>>*>;

  class ConfigWatcher
  {
    public:
      ConfigWatcher(){}
      virtual ~ConfigWatcher(){}
      
      virtual int start() = 0;
      virtual int configure() = 0;
      virtual int stop() = 0;
      virtual int restart() = 0;

      virtual int register_callback(int msgType, void* obj, function_ptr_generic function_pointer) = 0;

  };

}

#endif /*__CONFIG_WATCHER__*/