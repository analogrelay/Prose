#pragma once

namespace Prose {
	typedef std::function<void(Microsoft::WRL::ComPtr<IDWriteTextLayout>, DWRITE_TEXT_RANGE)> format_action_t;
	typedef std::function<format_action_t(Microsoft::WRL::ComPtr<ID2D1RenderTarget>)> dd_format_action_t;

	typedef struct format_operation_t {
		format_action_t action;
		UINT32 start_position;
		UINT32 length;
	} format_operation_t;

	typedef struct dd_format_operation_t {
		dd_format_action_t action;
		UINT32 start_position;
		UINT32 length;
	} dd_format_operation_t;
}