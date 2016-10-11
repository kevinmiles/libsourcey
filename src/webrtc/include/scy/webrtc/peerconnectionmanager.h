//
// LibSourcey
// Copyright (C) 2005, Sourcey <http://sourcey.com>
//
// LibSourcey is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.
//
// LibSourcey is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program. If not, see <http://www.gnu.org/licenses/>.
//

#ifndef SCY_PeerConnectionManager_H
#define SCY_PeerConnectionManager_H


#include "scy/webrtc/webrtc.h"
#include "scy/webrtc/peerconnection.h"
#include "scy/collection.h"
#include "scy/json/json.h"

#include "webrtc/api/peerconnectioninterface.h"

#include <iostream>
#include <string>


namespace scy {


class PeerConnection;


class PeerConnectionManager: public PointerCollection<std::string, PeerConnection>
{
public:
    PeerConnectionManager();
    virtual ~PeerConnectionManager();

    virtual void sendSDP(PeerConnection* conn, const std::string& type, const std::string& sdp);
    virtual void sendCandidate(PeerConnection* conn, const std::string& mid, int mlineindex, const std::string& sdp);

    virtual void recvSDP(const std::string& peerid, const json::Value& data);
    virtual void recvCandidate(const std::string& peerid, const json::Value& data);

    virtual void onAddRemoteStream(PeerConnection* conn, webrtc::MediaStreamInterface* stream);
    virtual void onRemoveRemoteStream(PeerConnection* conn, webrtc::MediaStreamInterface* stream);

    virtual void onStable(PeerConnection* conn);
    virtual void onClosed(PeerConnection* conn);
    virtual void onFailure(PeerConnection* conn, const std::string& error);

    rtc::scoped_refptr<webrtc::PeerConnectionFactoryInterface> factory() const;

protected:
    rtc::scoped_refptr<webrtc::PeerConnectionFactoryInterface> _factory;
};


} // namespace scy


#endif
