#include <GenericServer.hpp>
#include <CoreConfigManager.hpp>
#include <httplib.h>
#include <tojson.hpp>

namespace server
{

  // class HttpLibServerCallback {
  //   virtual void notification_callback(HttpLibServer *obj, int eventId, void* msgData);
  // };
  
  // class HttpLibServer : public GenericServer<HttpLibServerCallback>, HttpLibServerCallback {
  class HttpLibServer : public GenericServer<HttpLibServer> {
    
    public:
      HttpLibServer();
      HttpLibServer(std::string ip, int port);
      ~HttpLibServer();

      int start();
      int stop();
      int restart();
      int configure();

      int configureCustomApis(std::map<std::string, nlohmann::json> map);
      void notification_callback(HttpLibServer *obj, int eventId, void* msgData);

      void setConfigManager(config::CoreConfigManager *config);
      config::CoreConfigManager getConfigManager();

    private:
      httplib::Server *svr;
      std::string ip;
      int port;
      config::CoreConfigManager *configMnger;
  };

  typedef void (*function_ptr)(HttpLibServer* obj, int eventId, void* data);

}
