#include "launcher-private-pch.h"

static const char* resource_ids[] =
{
	"UI_BG",
	"UI_BUTTON",
	"UI_CHECKBOX",
	"UI_ICON_MODDED",
	"UI_ICON_EAC",
	"UI_LOGO",
	"UI_CLOSE",
	"UI_MINIMIZE",
	"UI_FONT"
};

void load_resource(e_resource_id id, void*& data, size_t& size)
{
	assert(id < k_number_of_resource_ids && id >= 0);
	HRSRC resource_info = FindResourceA(nullptr, resource_ids[id], "CUSTOMDATA");
	assert(resource_info);

	data = LoadResource(nullptr, resource_info);
	size = SizeofResource(nullptr, resource_info);
	assert(data && size);
}
