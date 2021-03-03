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

     /**
     * @brief This API will pass parsed API from config manager to the server
     * @param [in,out] std::map containing the API name and a JSON struct of the API properties 
     * @return  0 on sucess
     */
      int configureCustomApis(std::map<std::string, nlohmann::json> map);
      
      /**
     * @brief This notification callback to be called by notification_callback_generic
     */
      void notification_callback(HttpLibServer *obj, int eventId, void* msgData);

      void setConfigManager(config::CoreConfigManager *config);
      config::CoreConfigManager getConfigManager();

    private:
      httplib::Server *svr;
      std::string ip;
      int port;
      config::CoreConfigManager *configMnger; /**< pointer to the config manager used internally to be passed using setConfigManager*/
  };

  typedef void (*function_ptr)(HttpLibServer* obj, int eventId, void* data);

}
