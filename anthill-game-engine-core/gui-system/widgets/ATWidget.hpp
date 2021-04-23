#ifndef at_widget
#define at_widget

#include "../../../anthill-game-engine-utils/types/ATString.hpp"
#include "../render-system/ATRenderProvider.hpp"

#include "../draw-types/ATRect.hpp"
#include "../draw-types/ATArea.hpp"
//#include "../../../third-party-libs/pugixml/src/pugixml.hpp"

#include <memory>
#include <map>
#include <exception>
#include <typeinfo>

//#define MAKE_HASH(widget_class_name) auto widget_class_name::get_hash() -> size_t { return typeid(this).hash_code(); }

using namespace at::type::string;
using namespace at::core::gui::type::rect;
using namespace at::core::gui::type::area;
using namespace at::core::gui::render::at_interface;

namespace at::core::gui::widgets 
{
	namespace at_interface
	{
		class IWidget
		{
		public:
			virtual ~IWidget() {}
			virtual auto draw(std::shared_ptr<IRenderProvider> render_provider, fui32_rect_at real_avalable_rect, fui32_rect_at visible_avalable_rect) -> void = 0;
			virtual auto get_min_size() ->fui32_area_at = 0;
			//virtual auto fill(pugi::xml_node& node) -> void = 0;
			//virtual auto serialize(pugi::xml_node& parent) -> void = 0;
			virtual auto get_hash() ->size_t;

			template<class T>
			auto is() -> bool {
				return (typeid(T).hash_code() == get_hash());
			}

			template<class T>
			auto cast() -> T& {
				if (typeid(T).hash_code() != get_hash())
					std::runtime_error("unavalable widget cast");

				return (*static_cast<T*>(this));
			}
		};

		auto IWidget::get_hash() -> size_t {
			return typeid(*this).hash_code();
		}
	}
}

#endif // at_widget
