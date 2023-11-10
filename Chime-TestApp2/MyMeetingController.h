#pragma once
#include "controllers/meeting_controller_configuration.h"
#include "controllers/meeting_controller_dependencies.h"
#include <signaling/default_signaling_client.h>
using namespace chime;

class MyMeetingController
{
public:
	static std::unique_ptr<MyMeetingController> Create(MeetingControllerConfiguration configuration,
		std::unique_ptr<SignalingClient> signaling_client,
		SessionDescriptionObserver* session_description_observer);
	MyMeetingController(MeetingControllerConfiguration configuration, MeetingControllerDependencies dependencies);
	~MyMeetingController();

	void Start();
	void Stop();

	void StartLocalVideo();
	void SendDataMessage(const std::string& msg);

private:

};


std::unique_ptr<MyMeetingController> MyMeetingController::Create(MeetingControllerConfiguration configuration,
	std::unique_ptr<SignalingClient> signaling_client,
	SessionDescriptionObserver* session_description_observer) {

	MeetingControllerDependencies dependencies{};
	dependencies.signaling_client = std::move(signaling_client);
	//dependencies.session_description_observer = session_description_observer;

	//dependencies.signaling_thread = rtc::Thread::Create();
	//dependencies.signaling_thread->SetName("signaling_sdk_demo_thread", nullptr);
	dependencies.signaling_thread->Start();

	dependencies.log_sink = std::make_unique<LogSink>();
	SetSignalingLogLevel(configuration.log_level);
	rtc::LogMessage::AddLogToStream(dependencies.log_sink.get(), rtc::LS_VERBOSE);

	webrtc::FileAudioDeviceFactory::SetFilenamesToUse(configuration.input_audio_filename.c_str(),
		configuration.output_audio_filename.c_str());

	// To stay in the meeting, Chime's audio server requires a consistent stream of audio packets at all times.
	//   For more ways to send dummy audio see webrtc::TestAudioDeviceModule (omitted for brevity).
	dependencies.peer_connection_factory = webrtc::CreatePeerConnectionFactory(
		nullptr /* network_thread */, nullptr /* worker_thread */, dependencies.signaling_thread.get(),
		nullptr /* default adm */, webrtc::CreateBuiltinAudioEncoderFactory(), webrtc::CreateBuiltinAudioDecoderFactory(),
		webrtc::CreateBuiltinVideoEncoderFactory(), webrtc::CreateBuiltinVideoDecoderFactory(), nullptr /* audio_mixer */,
		nullptr /* audio_processing */);

	return std::make_unique<MyMeetingController>(configuration, std::move(dependencies));
}
