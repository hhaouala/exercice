#include <FileWatcher.hpp>

using namespace filewatch;

namespace config
{  

  FileWatcher::FileWatcher(const std::string &file) : fileWatched(file)
  {

  }

  FileWatcher::~FileWatcher()
  {
    stop();
  }

  int FileWatcher::start()
  {

  }

  int FileWatcher::configure()
  {

    filewatcher = new filewatch::FileWatch<std::string>(fileWatched, 
      [this](const std::string& file, const filewatch::Event event_type) {
        switch (event_type)
        {
          case filewatch::Event::modified:
            std::cout << "The file was modified. This can be a change in the time stamp or attributes." << '\n';
            this->v_mtx.lock();
            //for (const std::pair<void*,function_ptr_generic> x : this->callbacks_for_event[(int)event_type])
            auto x = this->callbacks_for_event[(int)event_type];
            for (auto x : this->callbacks_for_event[(int)event_type])
              x.second(x.first, (int)event_type, nullptr);
            this->v_mtx.unlock(); 
            break;
        };
        
      }
    );
  }

  int FileWatcher::stop()
  {
      return 0;
  }

  int FileWatcher::restart()
  {
      int ret = 0;
      ret |= stop();
      ret |= configure();
      ret |= start();
      return ret;
  }

  int FileWatcher::register_callback(int msgType, void *server, NotificationCallback function_pointer)
  {
    if ((Event)msgType < Event::added ||
      (Event)msgType > Event::renamed_old)
    return -1;

    std::unique_lock<std::mutex> lk(v_mtx);       
    std::cout << "== registering callback for msgType" << msgType << std::endl ;
    callbacks_for_event[msgType].push_back(std::make_pair(server, function_pointer));
    return 0;
  }
}
