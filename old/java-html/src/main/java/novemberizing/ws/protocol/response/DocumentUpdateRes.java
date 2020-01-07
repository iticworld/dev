package novemberizing.ws.protocol.response;

import com.google.gson.annotations.Expose;
import novemberizing.document.NovemberizingDocumentServerPacketType;
import novemberizing.packet.Packet;
import novemberizing.ws.protocol.request.DocumentUpdateReq;

public class DocumentUpdateRes extends Packet {

    public static DocumentUpdateRes ok(DocumentUpdateReq req, Long version){ return new DocumentUpdateRes(req, "ok", version); }
    public static DocumentUpdateRes fail(DocumentUpdateReq req, Long version){ return new DocumentUpdateRes(req, "fail", version); }

    public static class Data {
        @Expose private String result;
        @Expose private Long version;

        public Data(String result, Long version) {
            this.result = result;
            this.version = version;
        }
    }

    @Expose private Data data;

    public DocumentUpdateRes(DocumentUpdateReq req, String result, Long version) {
        this.id = req.id();
        this.model = NovemberizingDocumentServerPacketType.RES;
        this.type = NovemberizingDocumentServerPacketType.UPDATE;
        this.data = new Data(result, version);
    }
}
