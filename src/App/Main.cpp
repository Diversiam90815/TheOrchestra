
#include <JuceHeader.h>
#include "PluginEditor.h"


class Application : public JUCEApplication
{
public:
	Application() = default;

	const String getApplicationName() override
	{
		return JucePlugin_Name;
	}

	const String getApplicationVersion() override
	{
		return String(JucePlugin_Version);
	}

	void initialise(const String &) override
	{
		mainWindow.reset(new MainWindow(getApplicationName(), *this));
	}

	void shutdown() override
	{
		mainWindow = nullptr;
	}


private:
	class MainWindow : public DocumentWindow
	{
	public:
		MainWindow(const juce::String &name, JUCEApplication &app)
			: DocumentWindow(name, Desktop::getInstance().getDefaultLookAndFeel().findColour(ResizableWindow::backgroundColourId), DocumentWindow::allButtons), app(app)
		{
			// Create an instance of your AudioProcessor
			processor.reset(new OrchestraProcessor());

			// Create an instance of your editor directly
			editor.reset(new OrchestraEditor(*processor));

			setUsingNativeTitleBar(true);
			setContentOwned(editor.get(), true);

			setResizable(false, false);
						
			centreWithSize(getWidth(), getHeight());

			setVisible(true);
		}

		void closeButtonPressed() override
		{
			editor.reset();
			processor.reset();
			app.systemRequestedQuit();
		}

	private:
		JUCEApplication					   &app;
		std::unique_ptr<OrchestraEditor>	editor;
		std::unique_ptr<OrchestraProcessor> processor;
	};

	std::unique_ptr<MainWindow> mainWindow;
};

START_JUCE_APPLICATION(Application)