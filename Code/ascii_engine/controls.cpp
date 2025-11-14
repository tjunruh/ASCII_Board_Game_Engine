#include "../ascii_engine_dll_files/pch.h"
#include "controls.h"
#include "../../external_libraries/json.hpp"
#include "../file_manager/file_manager.h"
#include <algorithm>

int controls::bind(const std::string& control_name, const int key)
{
   if ( control_mapping.find(control_name) != control_mapping.end() )
   {
      return DUPLICATE_ELEMENT;
   }

   control_mapping.insert({control_name, key});
   return SUCCESS;
}

void controls::force_bind(const std::string& control_name, const int key)
{
    auto map = control_mapping.find(control_name);
    if (map != control_mapping.end())
    {
        control_mapping.erase(map);
    }

    control_mapping.insert({ control_name, key });
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

int controls::get_key(const std::string& control_name)
{
   auto map = control_mapping.find(control_name);
   if ( map == control_mapping.end() )
   {
      return ascii_io::undefined;
   }

   return map->second;
}

int controls::load_controls(const std::string& file_path)
{
   std::string content = "";
   int status = file_manager::read_file(file_path, content);

   if (status != 0)
   {
      return INVALID_PATH;
   }

   // Parse without exceptions
   nlohmann::json controls_data = nlohmann::json::parse(content, nullptr, false);

   if ( controls_data.is_discarded() )
   {
      return INVALID_PATH;
   }

   if ( !controls_data.contains("version") && !controls_data["version"].is_number_integer() )
   {
      return INVALID_PATH;
   }

   int_fast32_t version_number = controls_data["version"].template get<int_fast32_t>();

   // Get rid of old controsl if present
   control_mapping.clear();

   switch ( version_number )
   {
      case 0:
      {
         if ( !controls_data.contains("mapping") && !controls_data["mapping"].is_array() && !controls_data.contains("select_keys"))
         {
            return INVALID_PATH;
         }

         nlohmann::json controls = controls_data["mapping"];
         for ( auto itr = controls.begin(); itr != controls.end(); ++itr )
         {
            if ( !(*itr).is_object() )
            {
               // Discard invalid data
               continue;
            }

            if ( !(*itr).contains("name") || !(*itr).contains("key") )
            {
               //discard invalid data
               continue;
            }
            
            nlohmann::json& json_name = (*itr)["name"];
            nlohmann::json& json_key  = (*itr)["key"];

            if ( !json_name.is_string() )
            {
               continue;
            }

            if ( !json_key.is_number_integer() )
            {
               continue;
            }
  
            std::string  name = json_name.template get<std::string>();
            int key = json_key.template get<int>();
            control_mapping.insert({name, key});
         }

         nlohmann::json select_keys = controls_data["select_keys"];
         _select_keys = select_keys.template get<std::vector<int>>();

         return SUCCESS;
      }

      default:
         return INVALID_PATH;
   }
}

int controls::save_controls(const std::string& file_path)
{
   nlohmann::json controls_data;

   controls_data["version"] = 0;

   nlohmann::json controls;
   for ( auto itr = control_mapping.begin(); itr != control_mapping.end(); ++itr )
   {
      nlohmann::json control;
      control["name"] = itr->first;
      control["key"]  = itr->second;
      controls.push_back(control);
   }

   controls_data["mapping"] = controls;
   controls_data["select_keys"] = _select_keys;

   int status = file_manager::write_file(file_path, controls_data.dump(3));

   if (status != 0)
   {
      return INVALID_PATH;
   }

   return SUCCESS;
}

void controls::set_select_keys(const std::vector<int>& select_keys)
{
    _select_keys = select_keys;
}

std::vector<int> controls::get_select_keys()
{
    return _select_keys;
}

bool controls::key_in_select_keys(const int key)
{
    bool in_select_keys = false;
    if (std::count(_select_keys.begin(), _select_keys.end(), key) != 0)
    {
        in_select_keys = true;
    }

    return in_select_keys;
}