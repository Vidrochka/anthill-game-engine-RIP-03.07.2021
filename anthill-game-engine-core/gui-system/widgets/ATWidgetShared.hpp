#ifndef at_widget_shared
#define at_widget_shared

#include "ATWidget.hpp"
#include "ATFrameWidget.hpp"
#include "../../../anthill-game-engine-utils/types/ATString.hpp"

#include <memory>
#include <typeinfo>
#include <functional>

using namespace at::type::string;

namespace at::core::gui::widgets::shared
{
	static auto get_node_by_name(u8string_at name) -> std::shared_ptr<at_interface::IWidget> {
		if(name == "w-frame")
			return std::shared_ptr<at_interface::IWidget>(new FrameWidget());
	}
}

#endif // at_widget_shared
