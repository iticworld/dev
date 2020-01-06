package hornet.editor.application.protocol.response;

import com.google.gson.annotations.Expose;
import hornet.editor.application.protocol.RemoteDocumentPacketType;
import hornet.editor.application.protocol.request.ChangePosReq;
import hornet.editor.html.server.RemoteCoworker;
import novemberizing.Packet;

import java.util.List;

public class ChangePosRes extends Packet {
    @Expose private List<RemoteCoworker> users;

    public ChangePosRes(ChangePosReq req, List<RemoteCoworker> users) {
        this.type = RemoteDocumentPacketType.CHANGEPOS;
        this.id = req.id();
        this.model = RemoteDocumentPacketType.RES;
        this.users = users;
    }
}
