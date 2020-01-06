package hornet.editor.application.protocol.response;

import com.google.gson.annotations.Expose;
import hornet.editor.application.protocol.RemoteDocumentPacketType;
import hornet.editor.application.protocol.request.UpdateDocumentReq;
import novemberizing.Packet;

public class UpdateDocumentRes extends Packet {
    public static UpdateDocumentRes ok(UpdateDocumentReq req, Long version){ return new UpdateDocumentRes(req, "ok", version); }
    public static UpdateDocumentRes fail(UpdateDocumentReq req, Long version){ return new UpdateDocumentRes(req, "fail", version); }

    public static class Data {
        @Expose
        private String result;
        @Expose private Long version;

        public Data(String result, Long version) {
            this.result = result;
            this.version = version;
        }
    }

    @Expose private Data data;

    public UpdateDocumentRes(UpdateDocumentReq req, String result, Long version) {
        this.id = req.id();
        this.model = RemoteDocumentPacketType.RES;
        this.type = RemoteDocumentPacketType.UPDATE;
        this.data = new Data(result, version);
    }
}
