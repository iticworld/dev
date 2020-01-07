package novemberizing.ws.protocol.response;

import com.google.gson.annotations.Expose;
import novemberizing.document.NovemberizingDocumentServerPacketType;
import novemberizing.html.server.DocumentRemoteCoworker;
import novemberizing.packet.Packet;
import novemberizing.ws.protocol.request.ChangePosReq;

import java.util.List;

public class ChangePosRes extends Packet {
    @Expose private List<DocumentRemoteCoworker> users;

    public ChangePosRes(ChangePosReq req, List<DocumentRemoteCoworker> users) {
        this.type = NovemberizingDocumentServerPacketType.CHANGEPOS;
        this.id = req.id();
        this.model = "res";
        this.users = users;
    }
}
