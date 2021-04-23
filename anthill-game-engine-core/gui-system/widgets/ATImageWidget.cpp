#include "ATImageWidget.hpp"
#include <cstdint>

namespace at::core::gui::widgets
{
	ImageWidget::ImageWidget(std::shared_ptr<Image> image, uint_least32_t width, uint_least32_t height) : image(image), width(width), height(height) {
	}

	ImageWidget::~ImageWidget() {
	}

	auto ImageWidget::draw(std::shared_ptr<IRenderProvider> render_provider, fui32_rect_at real_avalable_rect, fui32_rect_at visible_avalable_rect) -> void {
		double_t w_scale_factor = static_cast<double_t>(image->get_width()) / real_avalable_rect.width;
		double_t h_scale_factor = static_cast<double_t>(image->get_height()) / real_avalable_rect.height;

		uint_fast32_t scaled_w;
		uint_fast32_t scaled_h;
		if (w_scale_factor > 1 || h_scale_factor > 1)
		{
			if (w_scale_factor < h_scale_factor)
			{
				scaled_w = image->get_width() / h_scale_factor;
				scaled_h = image->get_height() / h_scale_factor;
			}
			else
			{
				scaled_w = image->get_width() / w_scale_factor;
				scaled_h = image->get_height() / w_scale_factor;
			}
		}
		else
		{
			scaled_w = image->get_width();
			scaled_h = image->get_height();
		}

		uint_fast32_t image_x = real_avalable_rect.x;
		uint_fast32_t image_y = real_avalable_rect.y;

		/*тут правим позицию в зависимости от выравнивания*/

		if (visible_avalable_rect.is_include({ image_x, image_y, scaled_w, scaled_h }))
			render_provider->draw_image({ image_x, image_y, scaled_w, scaled_h } {0, 0, 1, 1});

		uint_fast32_t image_visible_w = (real_avalable_rect.x + real_avalable_rect.width - visible_avalable_rect.width);
		uint_fast32_t image_visible_h = (real_avalable_rect.y + real_avalable_rect.height - visible_avalable_rect.height)
		render_provider->draw_image(image, fui32_rect_at(visible_avalable_rect.x, visible_avalable_rect.y, (visible_avalable_rect >), );
	}

	auto ImageWidget::get_min_size() -> fui32_area_at {
		return { image->get_width(), image->get_height() };
	}
}