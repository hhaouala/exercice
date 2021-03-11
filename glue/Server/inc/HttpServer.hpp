#include <GenericServer.hpp>
#include <CoreConfigManager.hpp>

#ifndef __HTTP_SERVER__
#define __HTTP_SERVER__

namespace server
{
  template <class DerivedServer>
  class HttpServer : public GenericServer {
    
    public:
      HttpServer(config::CoreConfigManager &config) {}
      HttpServer(const std::string  &ip, int port, config::CoreConfigManager &configMnger){}
      ~HttpServer(){}

      virtual int start() {}
      virtual int stop()  {}
      virtual int restart()  {}
      virtual int configure() {}

      /**
     * @brief This notification callback to be called by notification_callback_generic
     */
      virtual void notification_callback(int eventId, void* msgData){
        DerivedServer::notification_callback();
      }

  };

#endif /*__HTTP_SERVER__*/