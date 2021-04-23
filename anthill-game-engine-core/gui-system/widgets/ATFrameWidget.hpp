#ifndef at_frame_widget
#define at_frame_widget

#include "ATWidget.hpp"
#include <vector>
#include <array>

namespace at::core::gui::widgets
{
	class FrameWidget : public at_interface::IWidget
	{
	public:
		std::array<uint8_t,4> color;
		std::shared_ptr<at_interface::IWidget> widget;
		FrameWidget(std::array<uint8_t, 4> color);
		FrameWidget(std::shared_ptr<at_interface::IWidget> widget = nullptr, std::array<uint8_t, 4> color = { 255, 255, 255,255 });
		~FrameWidget() override;
		auto draw(std::shared_ptr<IRenderProvider> render_provider, fui32_rect_at real_avalable_rect, fui32_rect_at visible_avalable_rect) -> void override;
		auto get_min_size() ->fui32_area_at override;
		//auto fill(pugi::xml_node& element) -> void override;
		//auto serialize(pugi::xml_node& parent) -> void override;
		//auto get_hash() ->size_t override;
	};
}

#endif // at_frame_widget
