#ifndef at_widgets_tree_builder
#define at_widgets_tree_builder

#include "ATWidget.hpp"

#include "ATWidgetShared.hpp"

#include "../../../anthill-game-engine-utils/types/ATString.hpp"
#include "../../../third-party-libs/pugixml/src/pugixml.hpp"
#include "ATWidgetExceptions.hpp"

#include <memory>
#include <sstream>
#include <functional>

using namespace at::type::string;

namespace at::core::gui::widgets
{
	static auto build_node_tree(u8string_at xml_node_tree, std::function<>) -> std::shared_ptr<at_interface::IWidget> widget {
		pugi::xml_document doc{};
		pugi::xml_parse_result doc_res = pugi::xml_document::load_string(xml_node_tree.c_str());

		if (!doc_res)
			throw exceptions::widget_deserialization_exception("Layout parsing error. Offset: ["u8at + int_to_u8_at((int)doc_res.offset) + "]"u8at);
		
		auto node = shared::get_node_by_name(doc.root().first_child().name());
		node.fill(doc.root().first_child());

		return node;
	}

	static auto serialize_node_tree(std::shared_ptr<at_interface::IWidget> widget) -> u8string_at {
		pugi::xml_document doc{};
		widget->serialize(doc.root());

		std::stringstream buff{};
		doc.save(buff);

		return u8string_at(buff.rdbuf());
	}
}

#endif // at_widgets_tree_builder
