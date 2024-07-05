#include "controls.h"
#include <json.hpp>
#include <fstream>

int controls::bind(const std::string& control_name, const int key)
{
   if ( control_mapping.find(control_name) != control_mapping.end() )
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

int controls::load_controls(const std::string& file_path)
{
   std::ifstream file{file_path};

   if ( !file.is_open() )
   {
      return INVALID_PATH;
   }

   // Parse without exceptions
   nlohmann::json controls_data = nlohmann::json::parse(file, nullptr, false);

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
         if ( !controls_data.contains("mapping") && !controls_data["mapping"].is_array() )
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

   std::ofstream output_file{file_path, std::ios::out | std::ios::trunc};

   if ( !output_file.is_open() )
   {
      return INVALID_PATH;
   }

   output_file << controls_data.dump(3) << std::endl;
   return SUCCESS;
}
