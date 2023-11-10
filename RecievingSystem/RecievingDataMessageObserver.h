#pragma once
#include"../build/framework.h"
#include "../lib/include/audiovideo/audio_video_observer.h"
#include "utils/logger/logger.h"
#include "utils/logger/console_logger.h"
#include<string>
#include "../build/json.hpp"
#include "../build/Messages.h"
using json = nlohmann::json;

using namespace chime;



struct KeyboardMessage
{
	int key;
};

std::ofstream logFile;

void LogMessage(const std::string& message) {
	logFile << message << std::endl;
}

class RecievingDataMessageObserver : public chime::AudioVideoObserver {
private:
	HWND m_hWnd;
public:
	chime::ConsoleLogger logger;
	virtual void OnDataMessagesReceived(const std::vector<DataMessageReceived>& messages) {
		auto firstMsg = messages.front();
		//MessageBox(NULL, "Message recieved", "Messages", MB_OK);
		std::string strInfo = "Received Message from " + firstMsg.attendee.external_user_id + ":";
		logger.Info(strInfo);
		for (const auto& message : messages) {
			auto data = json::parse(message.data);
			LogMessage(message.data);
			if (data["eventId"] == WM_LBUTTONDOWN) {
				logger.Info("Mouse Left Button is down");
				LogMessage("Mouse Left Button is down");
				PostMessage(m_hWnd, WM_MOUSEMOVE, 0, MAKELPARAM(140, 260));
			}
			else if (data["eventId"] == WM_MOUSEMOVE) {

				logger.Info("Mouse Is moved");
			}
			else {
				std::string strContent = message.data;
				logger.Info(strContent);
			}
		}
	}

	virtual void OnAttendeeJoined(const Attendee& attendee)
	{
		std::string details = "This meeting is now joined by " + attendee.external_user_id;
		logger.Info(details);
	}
};