package novemberizing.ws.protocol.response;

import com.google.gson.annotations.Expose;
import novemberizing.document.NovemberizingDocumentServerPacketType;
import novemberizing.html.server.DocumentRemoteCoworker;
import novemberizing.html.server.DocumentRemoteRoot;
import novemberizing.packet.Packet;
import novemberizing.ws.protocol.request.DocumentServerInitReq;

import java.util.List;

public class DocumentServerInitRes extends Packet {
    @Expose private DocumentRemoteRoot document;
    @Expose private List<DocumentRemoteCoworker> users;

    public DocumentServerInitRes(DocumentServerInitReq req, DocumentRemoteRoot document) {
        this.type = NovemberizingDocumentServerPacketType.INIT;
        this.id = req.id();
        this.model = "res";
        this.document = document;
        this.users = document.users();
    }
}
