#include "ATPreloadWindowInitializeSettings.hpp"
#include "../../../third_party_libs/json/single_include/nlohmann/json.hpp"
using json = nlohmann::json;

namespace at::core::window_system::preload_window_initialize_settings
{
    void to_json(json &j, const PreloadWindowInitializeSettings &win_init_sett)
    {
        j = json{
            {"height", win_init_sett.height},
            {"width", win_init_sett.width},
            {"x_pos", win_init_sett.x_pos},
            {"y_pos", win_init_sett.y_pos},
            {"lable", win_init_sett.lable},
            {"draw_init_mode", win_init_sett.draw_init_mode},
            {"borderless", win_init_sett.borderless},
            {"resizable", win_init_sett.resizable},
            {"grabbed", win_init_sett.grabbed},
            {"highdpi", win_init_sett.highdpi},
            {"backgroud_color", win_init_sett.backgroud_color.to_vector()},
            {"picture_path", win_init_sett.picture_path},
        };
    }

    void from_json(const json &j, PreloadWindowInitializeSettings &win_init_sett)
    {
        if (j.contains("height"))
            j.at("height").get_to(win_init_sett.height);

        if (j.contains("width"))
            j.at("width").get_to(win_init_sett.width);

        if (j.contains("x_pos"))
            j.at("x_pos").get_to(win_init_sett.x_pos);

        if (j.contains("y_pos"))
            j.at("y_pos").get_to(win_init_sett.y_pos);

        if (j.contains("lable"))
            j.at("lable").get_to(win_init_sett.lable);

        if (j.contains("draw_init_mode"))
            j.at("draw_init_mode").get_to(win_init_sett.draw_init_mode);

        if (j.contains("borderless"))
            j.at("borderless").get_to(win_init_sett.borderless);

        if (j.contains("resizable"))
            j.at("resizable").get_to(win_init_sett.resizable);

        if (j.contains("grabbed"))
            j.at("grabbed").get_to(win_init_sett.grabbed);

        if (j.contains("highdpi"))
            j.at("highdpi").get_to(win_init_sett.highdpi);

        if (j.contains("backgroud_color"))
            win_init_sett.backgroud_color = RGBA_at<uint8_t>::from_vector(j["backgroud_color"].get<std::vector<uint8_t>>());

         if (j.contains("picture_path"))
            j.at("picture_path").get_to(win_init_sett.picture_path);
    }
}