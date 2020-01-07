package hornet.editor.application.protocol.response;

import com.google.gson.annotations.Expose;
import hornet.editor.application.protocol.RemoteDocumentPacketType;
import hornet.editor.application.protocol.request.DocumentGetReq;
import hornet.editor.html.server.RemoteCoworker;
import hornet.editor.html.server.RemoteDocument;
import novemberizing.Packet;

import java.util.List;

public class DocumentGetRes extends Packet {
    @Expose private RemoteDocument document;
    @Expose private List<RemoteCoworker> users;

    public DocumentGetRes(DocumentGetReq req, RemoteDocument document) {
        this.type = RemoteDocumentPacketType.GET;
        this.id = req.id();
        this.model = RemoteDocumentPacketType.RES;
        this.document = document;
        this.users = document.users();
    }
}
