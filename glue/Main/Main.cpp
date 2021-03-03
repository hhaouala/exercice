#include <HttpLibServer.hpp>
#include <FileWatcher.hpp>
#include <FileWatch.hpp>

using namespace config;
using namespace server;

volatile std::atomic<bool> quit(false);    // signal flag

void got_signal(int)
{
    quit.store(true);
}
void set_signal_handler(){
    struct sigaction sa;
    memset( &sa, 0, sizeof(sa) );
    sa.sa_handler = got_signal;
    sigfillset(&sa.sa_mask);
    sigaction(SIGINT,&sa,NULL);
}

inline bool check_file (const std::string& name) {
    return ( access( name.c_str(), F_OK ) != -1 );
}

int main(int argc,char *argv[])
{
  std::map<std::string, nlohmann::json> apiList;
  char configFile[200] = {0};
  int c=0;

  while ((c = getopt (argc, argv, "i:h:")) != -1)
  {
    switch (c)
    {
      case 'i':
        std::memcpy (configFile, argv[2], sizeof(configFile));
        if (!check_file(configFile))
        {
          std::cerr << std::endl << "use -i to specify the FULL PATH of the yaml file" << std::endl;
          return -1;
        }
        continue;

      case '?':
      case 'h':
      default :
        std::cerr << std::endl << "use -i to specify the full path of the yaml file" << std::endl;
        return -1;

      case -1:
        return -1;
    }

    break;
  }

  CoreConfigManager config(configFile);
  FileWatcher filewatcher(configFile);
  HttpLibServer server;

  filewatcher.register_callback((int)filewatch::Event::modified, (void*)&server, (function_ptr_generic) server.notification_callback_generic);
  config.setConfigWatcher((ConfigWatcher*)&filewatcher);
  config.configure();
  config.getApis(apiList);

  for (auto &it : apiList ) {
    std::cout << "main: got api " << it.first << std::endl;
  }
  
  server.setConfigManager(&config);
  server.configure();
  server.configureCustomApis(apiList);
  
  config.start();
  server.start();

  while (true)
  {
    sleep(1);
    if( quit.load() ) break;
  }

  return 0;
}
