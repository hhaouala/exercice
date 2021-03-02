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


int main(int argc,char *argv[])
{
  std::map<std::string, nlohmann::json> apiList;

  CoreConfigManager config("/mnt/c/Users/PROBOOK/Documents/PERSO/Candidature/3dOutSCALE/Exercice/exercise/glue/build/config.yml");
  FileWatcher filewatcher("/mnt/c/Users/PROBOOK/Documents/PERSO/Candidature/3dOutSCALE/Exercice/exercise/glue/build/config.yml");
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