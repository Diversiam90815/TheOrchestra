
#include <JuceHeader.h>
#include "PluginEditor.h"

#include <Logging.h>
#include "buildinfo.h"

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

		mDeviceManager.addMidiInputCallback({}, editor->mPianoRollView.get());

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
		LOG_INFO("=======================================");
		LOG_INFO("============ SYSTEM INFO ==============");

		LOG_INFO("Project Name:\t\t {}", BuildInfo::Name);
		LOG_INFO("Project Version:\t\t {}", BuildInfo::Version);

		LOG_INFO("Build Time:\t\t {}", BuildInfo::Timestamp);
		LOG_INFO("Branch:\t\t\t {}", BuildInfo::Branch);
		LOG_INFO("Commit SHA:\t\t {}", BuildInfo::CommitSHA);
		LOG_INFO("Commit SHA Short:\t {}", BuildInfo::CommitSHAShort);

		LOG_INFO("Generator:\t\t {}", BuildInfo::Generator);
		LOG_INFO("CPP Version:\t\t {}", BuildInfo::CxxStandard);

		LOG_INFO("System Name:\t\t {}", BuildInfo::SystemName);
		LOG_INFO("System Version:\t\t {}", BuildInfo::SystemVersion);
		LOG_INFO("System CPU:\t\t {}", BuildInfo::SystemCPU);

		LOG_INFO("Compiler:\t\t {}", BuildInfo::CompilerID);
		LOG_INFO("Compiler Version:\t {}", BuildInfo::CompilerVersion);

		LOG_INFO("================= END =================");
		LOG_INFO("=======================================");
	}

private:
	std::unique_ptr<MainWindow> mainWindow;

	std::unique_ptr<Logging>	mLog;
};

START_JUCE_APPLICATION(Application)
