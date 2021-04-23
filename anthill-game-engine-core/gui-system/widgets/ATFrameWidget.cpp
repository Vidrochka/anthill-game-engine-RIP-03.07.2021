#include "ATFrameWidget.hpp"
#include "ATWidgetExceptions.hpp"
#include "ATWidgetShared.hpp"
#include <regex>

namespace at::core::gui::widgets
{
	FrameWidget::FrameWidget(std::array<uint8_t, 4> color) : widget(nullptr), color(color) {
	}

	FrameWidget::FrameWidget(std::shared_ptr<at_interface::IWidget> widget, std::array<uint8_t, 4> color) : widget(widget), color(color){
	}

	FrameWidget::~FrameWidget() {
	}

	auto FrameWidget::draw(std::shared_ptr<IRenderProvider> render_provider, fui32_rect_at real_avalable_rect, fui32_rect_at visible_avalable_rect) -> void {
	}

	auto FrameWidget::get_min_size() -> fui32_area_at {
	}

	/*auto FrameWidget::fill(pugi::xml_node& element) -> void {
		const std::regex r("(\\d+),(\\d+),(\\d+))"u8at);

		for (auto& attr : element.attributes()) {
			if (attr.name() == "color") {
				
				
				u8string_at val = u8string_at(attr.value());
				std::sregex_iterator iter(val.begin(), val.end(), r);
				std::sregex_iterator end;

				while (iter != end) {
					for (unsigned i = 0; i < iter->size(); i++) {
						color[i] = std::stoul((*iter)[i]);
					}
					++iter;
				}
			}
		}

		pugi::xml_node child_node = element.first_child();

		widget = shared::get_node_by_name(child_node.name());
		widget->fill(child_node);
	}*/

	/*auto FrameWidget::serialize(pugi::xml_node& parent) -> void {
		pugi::xml_node node = parent.append_child("w-frame");
		pugi::xml_attribute color_attr = node.append_attribute("color");

		u8string_at color_attr_data = U8StringBuilder{ "{0},{1},{2},{3}" }.fmt(0, color[0]).fmt(1, color[1]).fmt(2, color[2]).fmt(3, color[3]);
		color_attr.set_value(color_attr_data.c_str());

		if (widget != nullptr)
			widget->serialize(node);
	}*/

	//MAKE_HASH(FrameWidget);
}