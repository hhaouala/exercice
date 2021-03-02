#include <map>
#include <tojson.hpp>

#ifndef __GENERIC_CONFIG_MANAGER__
#define __GENERIC_CONFIG_MANAGER__

namespace config
{  
  class GenericConfigManager
  {
    public:
      GenericConfigManager(){}
      virtual ~GenericConfigManager(){}
      
      virtual int start() = 0;
      virtual int stop() = 0;
      virtual int configure() = 0;
      virtual int restart() = 0;
      virtual int getApis(std::map<std::string, nlohmann::json> &map) = 0;

  };

}
#endif /* __GENERIC_CONFIG_MANAGER__ */