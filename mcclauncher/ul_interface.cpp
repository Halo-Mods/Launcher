#include "mcclauncher_private_pch.h"

void c_halomods_ul_interface::OnClose(
	ultralight::Window* window)
{
	m_app->Quit();
}

void c_halomods_ul_interface::OnChangeCursor(
	ultralight::View* caller,
	ultralight::Cursor cursor)
{
	m_window->SetCursor(cursor);
}

void c_halomods_ul_interface::OnFinishLoading(
	ultralight::View* caller,
	uint64_t frame_id,
	bool is_main_frame,
	const ul::String& url)
{
	m_window->Show();
}

void c_halomods_ul_interface::OnFailLoading(
	ultralight::View* caller,
	uint64_t frame_id,
	bool is_main_frame,
	const ul::String& url,
	const ul::String& description,
	const ul::String& error_domain,
	int error_code)
{
	c_static_wchar_string<1024> error_explanation;

	error_explanation.print(L"Failed to load page (code %d, domain %s) %s:\n%s",
		error_code,
		error_domain.utf16().data(),
		url.utf16().data(),
		description.utf16().data());
	MessageBoxW(reinterpret_cast<HWND>(m_window->native_handle()), error_explanation.get_string(), L"Ultralight Error", MB_OK | MB_ICONERROR);

	m_app->Quit();
}

void c_halomods_ul_interface::OnDOMReady(
	ultralight::View* caller,
	uint64_t frame_id,
	bool is_main_frame,
	const ul::String& url)
{
	using namespace ultralight;

	RefPtr<JSContext> context = caller->LockJSContext();
	SetJSContext(context.get()->ctx());

	JSObject global = JSGlobalObject();

	global["launch_mcc"] = BindJSCallback(&c_halomods_ul_interface::launch_button_on_click);
}

void c_halomods_ul_interface::launch_button_on_click(const ul::JSObject& object, const ul::JSArgs& args)
{
	launch_parameters.extensions_enabled = args[0];
	m_app->Quit();
}

void c_halomods_ul_interface::run()
{
	m_app->Run();
}

c_halomods_ul_interface::c_halomods_ul_interface()
{
	m_app = ul::App::Create();
	m_window = ul::Window::Create(m_app->main_monitor(), 572, 300, false, ul::kWindowFlags_Titled | ul::kWindowFlags_Hidden);
	m_window->SetTitle("Halo Mods");
	m_window->MoveToCenter();
	m_overlay = ul::Overlay::Create(m_window, m_window->width(), m_window->height(), 0, 0);
	m_overlay->view()->LoadURL("file:///launcher/index.html");
	m_window->set_listener(this);
	m_overlay->view()->set_view_listener(this);
	m_overlay->view()->set_load_listener(this);
}

c_halomods_ul_interface::~c_halomods_ul_interface()
{

}
