//#include <HttpServer.hpp>
#include <GenericServer.hpp>
#include <CoreConfigManager.hpp>

#include <httplib.h>
#include <tojson.hpp>

#ifndef __HTTP_LIB_SERVER__
#define __HTTP_LIB_SERVER__

namespace server
{

  class HttpLibServer : public GenericServer<HttpLibServer> {
    
    public:
      HttpLibServer(config::CoreConfigManager &config);
      HttpLibServer(const std::string  &ip, int port, config::CoreConfigManager &configMnger);
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

    private:
      std::shared_ptr<httplib::Server> srv = nullptr;
      std::string ip;
      int port;
      config::CoreConfigManager &configMnger;
  };
}
#endif /*__HTTP_LIB_SERVER__*/
