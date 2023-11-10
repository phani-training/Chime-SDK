#pragma once

#include <signaling/signaling_client_observer.h>
using namespace chime;

class MySignalingObserver : public SignalingClientObserver/*, public webrtc::CreateSessionDescriptionObserver, public webrtc::PeerConnectionObserver, public webrtc::SetSessionDescriptionObserver*/ {
public:
    // Inherited via SignalingClientObserver
	void OnRemoteDescriptionReceived(const std::string& sdp_answer) override;
	void OnSignalingClientStarted(const SignalingClientStartInfo& start_info) override;
	void OnSignalingClientStopped(const SignalingClientStatus& status) override;

    virtual void OnSignalingStarted(const SignalingClientStartInfo& join_info) {
        // Connection has been established.
        // if no peer connection, setup new peer connection here.
        auto credentials = join_info.credentials;        
    };

    // SetSessionDescriptionObserver
    virtual void OnSuccess() {
        // if turn candidate has been gathered
        SendUpdate();
    }

    virtual void OnDataMessageReceived(const std::vector<DataMessageReceived>& messages)
    {
        auto firstMsg = messages.front();
        std::string strInfo = "Received Message from " + firstMsg.attendee.external_user_id + ":";
        for (const auto& message : messages) {
            std::cout << message.data << std::endl;
        }
    }

    void SendUpdate() {
        // Assuming that AddLocalVideo/AddLocalAudio/UpdateLocalVideo/UpdateLocalAudio/UpdateRemoteVideoSubscriptions has been called appropriately. 
        //signaling_client_v2_->SetLocalDescription(sdp_offer);
        //if (!signaling_client_v2_->SendUpdates()) {
        //    // Unable to send...
        //    return;
        //}
    }
};

void MySignalingObserver::OnRemoteDescriptionReceived(const std::string& sdp_answer)
{
    //// peer connection set remote description using sdp
        //std::unique_ptr<webrtc::SessionDescriptionInterface> session_description = webrtc::CreateSessionDescription(webrtc::SdpType::kAnswer, sdp, &error);
        //if (!session_description) return;
        //// Setup codecs based description
        //peer_connection_->SetRemoteDescription(
        //    new rtc::RefCountedObject<MySignalingObserver>(false, this), session_description.release());
}

void MySignalingObserver::OnSignalingClientStarted(const SignalingClientStartInfo& start_info)
{

}

void MySignalingObserver::OnSignalingClientStopped(const SignalingClientStatus& status)
{
}