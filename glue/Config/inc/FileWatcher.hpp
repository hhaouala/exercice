#include <ConfigWatcher.hpp>
#include <FileWatch.hpp>

#ifndef __FILE_WATCHER__
#define __FILE_WATCHER__

namespace config
{  

  class FileWatcher : ConfigWatcher
  {
    public:
      FileWatcher(const std::string &fileWatched);
      ~FileWatcher();
      
      int start() override;
      int configure() override;
      int stop() override;
      int restart() override;
      
      int register_callback(int msgType, void* obj, NotificationCallback function_pointer) override;

    private:

      std::mutex v_mtx; /**< mutex to protect the access to the vector of the callbacks registred on the config watcher */
      CallbackVector callbacks_for_event = CallbackVector (8); /**< vector of the callbacks registred on the config watcher */
      
      std::string fileWatched; /**< the full path to the config file of the server */
      filewatch::FileWatch<std::string> *filewatcher; /**< pointer to the filewatch::FileWatch lib to monitor the config file */
  };
}

#endif /*__FILE_WATCHER__*/
