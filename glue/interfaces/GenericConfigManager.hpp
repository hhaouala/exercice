#include <map>
#include <tojson.hpp>

#ifndef __GENERIC_CONFIG_MANAGER__
#define __GENERIC_CONFIG_MANAGER__

/** \ingroup config */

namespace config
{  
  /**
   * This class is meant to abstract the state machine of a parser
   * framework/lib of the YAML config file, and its APIs/configuration.
   * By providing virtual methodes like start, stop, configure, the startup sequence
   * is independent of the framework, and can be implemented.
   * Check Main for the startup sequence.
   *
   */
  class GenericConfigManager
  {
    public:
      GenericConfigManager(){}
      virtual ~GenericConfigManager(){}
      
      virtual int start() = 0;
      virtual int stop() = 0;
      virtual int configure() = 0;
      virtual int restart() = 0;
      
      
     /**
     * @brief This API will get the list of parsed  APIs (Note that Yaml is being converted to JSON)
     * @param [in,out] std::map containing the API name and a JSON struct of the API properties 
     * @return  0 on sucess
     */
      virtual int getApis(std::map<std::string, nlohmann::json> &map) = 0;

  };

}
#endif /* __GENERIC_CONFIG_MANAGER__ */
