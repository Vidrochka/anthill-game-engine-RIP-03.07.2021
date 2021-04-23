#ifndef at_image_widget
#define at_image_widget

#include "ATWidget.hpp"
#include "ATWidgetAttributes.hpp"
#include "../draw-types/ATImage.hpp"
#include <vector>
#include <array>

using namespace at::core::gui::type::image;

namespace at::core::gui::widgets
{
	class ImageWidget : public at_interface::IWidget
	{
	public:
		std::shared_ptr<Image> image;
		attributes::ALIGNMENT alignment = attributes::ALIGNMENT::TOP_LEFT;

		uint_least32_t width, height;
		ImageWidget(std::shared_ptr<Image> image, uint_least32_t width, uint_least32_t height);
		~ImageWidget() override;
		auto draw(std::shared_ptr<IRenderProvider> render_provider, fui32_rect_at real_avalable_rect, fui32_rect_at visible_avalable_rect) -> void override;
		auto get_min_size()->fui32_area_at override;
	};
}

#endif // at_image_widget
