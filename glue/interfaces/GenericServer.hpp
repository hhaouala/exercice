
/** \ingroup server */
/** \addtogroup server
* @{
*/
namespace server
{
  /**
   * This class is meant to abstract the state machine of the server
   * framework/lib (like cpp-http) and its APIs/configuration.
   * 
   * By providing virtual methodes like start, stop, configure, the startup sequence
   * is independent of the framework, and can be implemented.
   * Check Main for the startup sequence
   * 
   * It an templated interface where the ServerType is the typename of
   * the web framework we will be using..
   *
   */
  template <class ServerType>  
  class GenericServer
  {
    public:
      GenericServer(){}
      virtual ~GenericServer(){}

      virtual int start() = 0;
      virtual int stop() = 0;
      virtual int configure() = 0;

      /**
     * @brief This API will be called by notification_callback_generic, and will ensure
     * that each child class is defining it, so the child class's callback function
     * is the one to be called.
     */
      virtual void notification_callback(ServerType *obj, int eventID, void* msgData) = 0;

     /**
     * @brief This API will be passed to the register_callback (as it needs a static function)
     * and it call the notification_cabllback that will be defined in the obj of type ServerType.
     * @param [in,out] obj: pointer to ServerType(template) which is passing its callback function (non thread safe) 
     * @param [in] eventID : event id passed from the config watcher
     * @param [in,out] msgData : pointer to use when trying to pass data
     * @return  0 on sucess
     */
      static void notification_callback_generic(ServerType *obj, int eventID, void* msgData)
      {
        obj->notification_callback(obj, eventID, msgData);
      };
      
  };

}
/** @} end of group server */
