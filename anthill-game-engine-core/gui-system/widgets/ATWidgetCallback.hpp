#ifndef at_widget_callback
#define at_widget_callback

#include "ATWidget.hpp"
//#include "ATFrameWidget.hpp"
#include "../../../anthill-game-engine-utils/types/ATString.hpp"

#include <memory>
#include <typeinfo>
#include <functional>

using namespace at::type::string;

namespace at::core::gui::widgets::callback
{
	enum class EVENT_TYPE {
		MOUSE_HOVERED = 0,
		MOUSE_ENTER,
		MOUSE_EXIT,
		LEFT_MOUSE_BUTTON_DOWN,
		RIGHT_MOUSE_BUTTON_DOWN,
	};

	struct Event {

	};

	struct Sender {
		at_interface::IWidget const* widget;
	};


	/*struct CallbackSetInfo
	{
	private:
		std::function<bool(Event ev, Sender sender)> const* _callback_ptr;
	public:
		std::type_info widget_type_info;
		at_interface::IWidget* widget;
		u8string_at callback_path;

		auto set_callback(std::function<bool(Event ev, Sender sender)> callback) -> void {
			(*_callback_ptr) = callback;
		}
	};*/
}

#endif // at_widget_callback
