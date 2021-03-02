#include <HttpLibServer.hpp>
#include <FileWatch.hpp>

using namespace httplib;

namespace server
{

  HttpLibServer::HttpLibServer() : ip("127.0.0.1"), port(9898)
  {
    if (!svr)
      svr = new Server();
  }

  HttpLibServer::HttpLibServer(std::string ip, int port) : ip(ip), port(port)
  {
      if (!svr)
      svr = new Server();
  }

  HttpLibServer::~HttpLibServer()
  {
    stop();  
  }

  int HttpLibServer::start()
  {
    if (!svr)
      svr = new Server();

    auto ret = false;
    if (! svr->is_running()){
      std::cout << "starting server on " << ip << ":" << port<< std::endl;
      ret = svr->listen(ip.c_str(), port);
    }
    return (ret) ? 0 : -1;
  }

  int HttpLibServer::stop()
  {
    if (svr)
    {
      if (svr->is_running()){
        std::cout << "stopping server" << std::endl;
        svr->stop();
      }
      delete svr;
    }
    return 0;
  }

  int HttpLibServer::restart()
  {
    int ret = 0;
    stop();
    ret |= configure();
    if (configMnger){
      ret |= configMnger->restart();
      std::map<std::string, nlohmann::json> apiList;
      ret |= configMnger->getApis(apiList);
      ret |= configureCustomApis(apiList);
    }
    ret |= start();
    return ret;
  }

  int HttpLibServer::configureCustomApis(std::map<std::string, nlohmann::json> map)
  {
    if (!svr)
      svr = new Server();

    for (auto &it : map ) {
    std::cout << "Configuring Api " << it.first << std::endl;
		svr->Get(it.first.c_str(), [](const Request& req, Response& res) {
				res.set_content("Hello World!", "text/plain");
				});
	  }
    return 0;
  }

  int HttpLibServer::configure()
  {
    if (svr)
      svr = new Server();

    svr->Get("/hi", [](const Request& req, Response& res) {
				res.set_content("Hello World!", "text/plain");
				});

    svr->Get(R"(/numbers/(\d+))", [&](const Request& req, Response& res) {
    auto numbers = req.matches[1];
    res.set_content(numbers, "text/plain");
    });

    svr->Get("/body-header-param", [](const Request& req, Response& res) {
            if (req.has_header("Content-Length")) {
            auto val = req.get_header_value("Content-Length");
            }
            if (req.has_param("key")) {
            auto val = req.get_param_value("key");
            }
            res.set_content(req.body, "text/plain");
            });

    svr->Get("/stop", [&](const Request& req, Response& res) {
            svr->stop();
            });

    return 0;
  }

    void HttpLibServer::setConfigManager(config::CoreConfigManager *_config)
    {
        configMnger = _config;
    }

    config::CoreConfigManager HttpLibServer::getConfigManager()
    {
        return *configMnger;
    }

    void HttpLibServer::notification_callback(HttpLibServer *obj, int eventId, void* msgData)
    {
      HttpLibServer* cls = (HttpLibServer*) obj;
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