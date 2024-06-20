#include "controls.h"

int controls::bind(const std::string& control_name, const int key)
{
   if ( control_mapping.find(control_name) == control_mapping.end() )
   {
      return DUPLICATE_ELEMENT;
   }

   control_mapping.insert({control_name, key});
   return SUCCESS;
}

int controls::unbind(const std::string& control_name)
{
   auto map = control_mapping.find(control_name);
   if ( map == control_mapping.end() )
   {
      return ELEMENT_NOT_FOUND;
   }

   control_mapping.erase(map);
   return SUCCESS;
}

const int controls::get_key(const std::string& control_name)
{
   auto map = control_mapping.find(control_name);
   if ( map == control_mapping.end() )
   {
      return ascii_io::undefined;
   }

   return map->second;
}
