#pragma once
#include<string>
struct MeetingInfo {
public:
	std::string attendee_id;
	std::string external_user_id;
	std::string join_token;
	std::string audio_host_url;
	std::string signaling_url;
	std::string meeting_id;
	std::string external_meeting_id;
};

//https://pulud6u8je.execute-api.us-east-1.amazonaws.com/Prod/create?m=123
/*
{"Attendee":{"ExternalUserId":"Originator","AttendeeId":"192c2b76-a471-f07b-fa53-22e700aeb8bd","JoinToken":"MTkyYzJiNzYtYTQ3MS1mMDdiLWZhNTMtMjJlNzAwYWViOGJkOjY2ZjIxZmVlLTY2NWQtNDhmMC05NzBlLTNkMjg2MjdhNDkyMA"},"Meeting":{"MeetingId":"c3226b73-7846-4763-80a4-3704c34c0706","ExternalMeetingId":"123","MediaPlacement":{"AudioHostUrl":"0ca47b7f67dd143bfbe4526891290b25.k.m1.ue1.app.chime.aws:3478","AudioFallbackUrl":"wss://haxrp.m1.ue1.app.chime.aws:443/calls/c3226b73-7846-4763-80a4-3704c34c0706","ScreenDataUrl":"wss://bitpw.m1.ue1.app.chime.aws:443/v2/screen/c3226b73-7846-4763-80a4-3704c34c0706","ScreenSharingUrl":"wss://bitpw.m1.ue1.app.chime.aws:443/v2/screen/c3226b73-7846-4763-80a4-3704c34c0706","ScreenViewingUrl":"wss://bitpw.m1.ue1.app.chime.aws:443/ws/connect?passcode=null&viewer_uuid=null&X-BitHub-Call-Id=c3226b73-7846-4763-80a4-3704c34c0706","SignalingUrl":"wss://signal.m1.ue1.app.chime.aws/control/c3226b73-7846-4763-80a4-3704c34c0706","TurnControlUrl":"https://ccp.cp.ue1.app.chime.aws/v2/turn_sessions","EventIngestionUrl":"https://data.svc.ue1.ingest.chime.aws/v1/client-events"},"MediaRegion":"us-east-1"}}*/

MeetingInfo CreateMeeting() {
	MeetingInfo details{
		"192c2b76-a471-f07b-fa53-22e700aeb8bd",
		"Originator",
		"MTkyYzJiNzYtYTQ3MS1mMDdiLWZhNTMtMjJlNzAwYWViOGJkOjY2ZjIxZmVlLTY2NWQtNDhmMC05NzBlLTNkMjg2MjdhNDkyMA",
		"0ca47b7f67dd143bfbe4526891290b25.k.m1.ue1.app.chime.aws:3478",
		"wss://signal.m1.ue1.app.chime.aws/control/c3226b73-7846-4763-80a4-3704c34c0706",
		"c3226b73-7846-4763-80a4-3704c34c0706",
		"123"
	};
	return details;
}