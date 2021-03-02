#include <ConfigWatcher.hpp>
#include <FileWatch.hpp>

namespace config
{  

  // #define CALLBACK_ARGS const std::string& file, const filewatch::Event event_type, void *obj
  // #define CALLBACK_ARGS_TYPE void(CALLBACK_ARGS)
  //typedef std::function<unsigned int(const std::string& , const filewatch::Event, void *)> CALLBACK_SIGNATURE;
  
  class FileWatcher : ConfigWatcher
  {
    public:
      FileWatcher(std::string fileWatched);
      ~FileWatcher();
      
      int start();
      int configure();
      int stop();
      int restart();
      
      int register_callback(int msgType, void* obj, function_ptr_generic function_pointer);

    private:

      std::mutex v_mtx;
      CallbackVector callbacks_for_event = CallbackVector (8);
      
      std::string fileWatched;
      filewatch::FileWatch<std::string> *filewatcher;
  };

}
