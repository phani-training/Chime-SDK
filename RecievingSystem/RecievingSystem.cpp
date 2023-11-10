#include <memory>
#include <iostream>
#include "utils\logger\logger.h"
#include "utils\logger\console_logger.h"
#include "session\meeting_session_credentials.h"
#include "session\meeting_session_urls.h"
#include "session\meeting_session_configuration.h"
#include "session\meeting_session.h"
#include "audiovideo/audio_video_observer.h"
#include "../build/RecievingDataMessageObserver.h"
#include "../build/RestApi.h"
#include"../build/json.hpp"
#include"../build/Messages.h"
#include "../build/MessageHandler.h"


int main()
{
	std::unique_ptr<chime::Logger> logger = std::make_unique<chime::ConsoleLogger>(chime::LogLevel::kDebug);
	Uri request{ L"https://pulud6u8je.execute-api.us-east-1.amazonaws.com/Prod/join?m=123&e=abhi" };
	MeetingDetails details = GetMeetingDetails(request);
	std::string attendee_id = details.attendee_id;
	std::string external_user_id = details.external_user_id;
	std::string join_token = details.join_token;
	std::cout << attendee_id << std::endl;
	chime::MeetingSessionCredentials credentials{ attendee_id,
											 external_user_id,
											 join_token };


	std::string audio_host_url = details.audio_host_url;
	std::string signaling_url = details.signaling_url;

	chime::MeetingSessionURLs urls{ audio_host_url,
							   signaling_url };

	std::string meeting_id = details.meeting_id;
	std::string external_meeting_id = details.external_meeting_id;

	chime::MeetingSessionConfiguration configuration{ meeting_id,
												 external_meeting_id,
												 std::move(credentials),
												 std::move(urls) };


	std::shared_ptr<chime::MeetingSessionDependencies> session_dependencies =
		std::make_shared<chime::MeetingSessionDependencies>();
	session_dependencies->logger = std::move(logger);


	std::unique_ptr<chime::MeetingSession> meeting_session =
		chime::MeetingSession::Create(std::move(configuration), session_dependencies);
	
	//auto data_message_observer = std::make_unique<RecievingDataMessageObserver>();

	//meeting_session->audio_video->AddAudioVideoObserver(data_message_observer.get());
	meeting_session->audio_video->Start();
	std::cout << "This meeting is now attended by " + external_user_id + " for the meeting Id " + external_meeting_id << std::endl;
	Sleep(2000);
	//system("cls");
	while (true) { 
		chime::DataMessageToSend data_message_to_send;
		for (int i = 1; i < 10; i++)
		{
			MouseActionMessage mouseMsg{};
			mouseMsg.button = 0;
			mouseMsg.xPos = 200 + (i * 10);
			mouseMsg.yPos = 300 + (i * 10);

			json jsonData = ConvertToJsonMouse(MessageType::MouseMove,  mouseMsg.xPos, mouseMsg.yPos, mouseMsg.button);
			data_message_to_send.data = jsonData.dump(); // data to send
			data_message_to_send.topic = "chat"; // topic to send
			data_message_to_send.lifetime_ms = 300000; // max five minutes
			meeting_session->audio_video->SendDataMessage(data_message_to_send);
			Sleep(1000);
		}

		//InputEvent msg{ WM_USER + 5, 0, 0, 0 };
		//json jsonData = ConvertToJson(msg);
		//data_message_to_send.data = jsonData.dump();
		//meeting_session->audio_video->SendDataMessage(data_message_to_send);
		//return 0;

	}
}
