
#include <JuceHeader.h>
#include "PluginEditor.h"

#include <Logging.h>


class MainWindow : public DocumentWindow
{
public:
	MainWindow(const juce::String &name, JUCEApplication &app)
		: DocumentWindow(name, Desktop::getInstance().getDefaultLookAndFeel().findColour(ResizableWindow::backgroundColourId), DocumentWindow::allButtons), app(app)
	{
		mDeviceManager.initialise(0, 2, nullptr, true);

		auto availableMIDIDevices = juce::MidiInput::getAvailableDevices();

		for (auto &device : availableMIDIDevices)
		{
			LOG_INFO("Enabling MIDI Device : {}", device.name.toStdString().c_str());
			mDeviceManager.setMidiInputDeviceEnabled(device.identifier, true);
		}
		mDeviceManager.addMidiInputCallback({}, &mPlayer);
		
		processor.reset(new OrchestraProcessor());

		editor.reset(new OrchestraEditor(*processor));

		mPlayer.setProcessor(processor.get());
		mDeviceManager.addAudioCallback(&mPlayer);

		setUsingNativeTitleBar(true);
		setContentOwned(editor.get(), true);
		setResizable(false, false);
		centreWithSize(getWidth(), getHeight());
		setVisible(true);

		LOG_INFO("Mainwindow setup finished!");
	}

	void closeButtonPressed() override
	{
		mDeviceManager.removeAudioCallback(&mPlayer);
		mPlayer.setProcessor(nullptr);

		editor.reset();
		processor.reset();
		app.systemRequestedQuit();
	}

private:
	JUCEApplication					   &app;
	std::unique_ptr<OrchestraEditor>	editor;
	std::unique_ptr<OrchestraProcessor> processor;

	AudioProcessorPlayer				mPlayer;
	AudioDeviceManager					mDeviceManager;
};



class Application : public JUCEApplication
{
public:
	Application() = default;

	const String getApplicationName() override { return JucePlugin_Name; }

	const String getApplicationVersion() override { return String(JucePlugin_VersionString); }

	void		 initialise(const String &) override
	{
		mLog = std::make_unique<Logging>();
		mLog->initLogging();
		logProjectInfo();
		mainWindow.reset(new MainWindow(getApplicationName(), *this));
	}

	void shutdown() override { mainWindow = nullptr; }

	void logProjectInfo()
	{
		LOG_INFO("Project running is:");
		LOG_INFO("\tName\t=\t{}", JucePlugin_Name);
		LOG_INFO("\tVersion\t=\t{}", JucePlugin_VersionString);
	}

private:
	std::unique_ptr<MainWindow> mainWindow;

	std::unique_ptr<Logging>	mLog;
};

START_JUCE_APPLICATION(Application)