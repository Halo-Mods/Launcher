#pragma once

struct s_game_launch_parameters
{
	bool cancelled;
	bool extensions_enabled;
};

class c_halomods_ul_interface :
	public ul::WindowListener,
	public ul::ViewListener,
	public ul::LoadListener
{
private:
	ul::RefPtr<ul::App> m_app;
	ul::RefPtr<ul::Window> m_window;
	ul::RefPtr<ul::Overlay> m_overlay;
public:
	virtual void OnClose(
		ul::Window* window) override;

	virtual void OnChangeCursor(
		ul::View* caller,
		ul::Cursor cursor) override;

	void OnFinishLoading(
		ul::View* caller,
		uint64_t frame_id,
		bool is_main_frame,
		const ul::String& url);
	void OnFailLoading(
		ul::View* caller,
		uint64_t frame_id,
		bool is_main_frame,
		const ul::String& url,
		const ul::String& description,
		const ul::String& error_domain,
		int error_code) override;

	void OnDOMReady(
		ul::View* caller,
		uint64_t frame_id,
		bool is_main_frame,
		const ul::String& url) override;

	s_game_launch_parameters launch_parameters;

	void launch_button_on_click(const ul::JSObject&, const ul::JSArgs&);

	void run();

	c_halomods_ul_interface();
	virtual ~c_halomods_ul_interface();
};
