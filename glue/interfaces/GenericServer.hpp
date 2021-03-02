
namespace server
{
  template <class ServerType>  
  class GenericServer
  {
    public:
      GenericServer(){}
      virtual ~GenericServer(){}

      virtual int start() = 0;
      virtual int stop() = 0;
      virtual int configure() = 0;

      virtual void notification_callback(ServerType *obj, int eventID, void* msgData) = 0;

      static void notification_callback_generic(ServerType *obj, int eventID, void* msgData)
      {
        obj->notification_callback(obj, eventID, msgData);
      };
      
  };

}
