#include <iostream>
#include <vector>

#ifndef __CONFIG_WATCHER__
#define __CONFIG_WATCHER__

/** \ingroup focus_manager */
/** \addtogroup FocusManager
* @{
*/
/**
 * This class is designed to define the FocusManager.
 */
namespace config
{  

  typedef void (*function_ptr_generic)(void* obj, int eventId, void* data);
  using CallbackVector = std::vector<std::vector<std::pair<void*,function_ptr_generic>>*>;

   //!  A test class. 
  /*!
    A more elaborate class description.
  */
   
  class ConfigWatcher
  {
    public:
      
      /// Brief description.
      /** Detailed description. */
      ConfigWatcher(){}
      
      /// Brief description.
      /** Detailed description. */
      virtual ~ConfigWatcher(){}
      
      virtual int start() = 0;
      /*! \brief Brief description.
       *         Brief description continued.
       *
       *  Detailed description starts here.
       */
      virtual int configure() = 0;
      virtual int stop() = 0;
      virtual int restart() = 0;


      //! Brief description, which is
    //! really a detailed description since it spans multiple lines.
    /*! Another detailed description!
     */
      virtual int register_callback(int msgType, void* obj, function_ptr_generic function_pointer) = 0;

  };

}
/** @} end of group FocusManager */
#endif /*__CONFIG_WATCHER__*/
