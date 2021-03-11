#include <HttpLibServer.hpp>
#include <FileWatch.hpp>

using namespace httplib;

namespace server
{
  HttpLibServer::HttpLibServer(config::CoreConfigManager &config) : ip("127.0.0.1"), port(9898), configMnger(config)
  {
    try
    {
      srv = std::make_shared<httplib::Server>();
    }
    catch(const std::bad_alloc& e)
    {
      std::cerr << e.what() << std::endl;
    }
  }

  HttpLibServer::HttpLibServer(const std::string &ip, int port, config::CoreConfigManager &config) : ip(ip), port(port), configMnger(config)
  {
    try
    {
      srv = std::make_shared<httplib::Server>();
    }
    catch(const std::bad_alloc& e)
    {
      std::cerr << e.what() << std::endl;
    }
  }

  HttpLibServer::~HttpLibServer()
  {
    stop();  
  }

  int HttpLibServer::start()
  {
    if (srv == nullptr)
    {
      try
      {
        srv = std::make_shared<httplib::Server>();
      }
      catch(const std::bad_alloc& e)
      {
        std::cerr << e.what() << std::endl;
        return -1;
      }

    }
    auto ret = false;
    if (! srv->is_running()){
      std::cout << "starting server on " << ip << ":" << port<< std::endl;
      ret = srv->listen(ip.c_str(), port);
    }
    return (ret) ? 0 : -1;
  }

  int HttpLibServer::stop()
  {
    if (srv)
    {
      if (srv->is_running()){
        std::cout << "stopping server" << std::endl;
        srv->stop();
      }
      srv.reset();
    }
    return 0;
  }

  int HttpLibServer::restart()
  {
    int ret = 0;
    stop();
    ret |= configure();
    ret |= configMnger.restart();
    std::map<std::string, nlohmann::json> apiList;
    ret |= configMnger.getApis(apiList);
    ret |= configureCustomApis(apiList);
    ret |= start();
    return ret;
  }

  int HttpLibServer::configureCustomApis(std::map<std::string, nlohmann::json> map)
  {
    if (srv == nullptr)
    {
      try
      {
         srv = std::make_shared<httplib::Server>();
      }
      catch(const std::bad_alloc& e)
      {
          std::cerr << e.what() << std::endl;
          return -1;
      }
    }

    for (auto &it : map ) {
    std::cout << "Configuring Api " << it.first << std::endl;
		srv->Get(it.first.c_str(), [](const Request& req, Response& res) {
				//res.set_content("200 OK", "text/plain");
				});
		srv->Post(it.first.c_str(), [](const Request& req, Response& res) {
				//res.set_content("200 OK", "text/plain");
				});
	  }
    return 0;
  }

  int HttpLibServer::configure()
  {
    if (srv == nullptr)
    {
      try
      {
         srv = std::make_shared<httplib::Server>();
      }
      catch(const std::bad_alloc& e)
      {
          std::cerr << e.what() << std::endl;
          return -1;
      }
    }
    return 0;
  }

    void HttpLibServer::notification_callback(HttpLibServer *obj, int eventId, void* msgData)
    {
      filewatch::Event event = static_cast<filewatch::Event>(eventId);
      switch (event)
      {
        case filewatch::Event::modified:
          restart();
          break;
        default:
          std::cout << "Unhandled msgID " << eventId << std::endl;
          break;
      }
      
    }
}
