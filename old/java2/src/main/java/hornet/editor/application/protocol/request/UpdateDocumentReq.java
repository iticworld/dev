package hornet.editor.application.protocol.request;

import com.google.gson.annotations.Expose;
import hornet.editor.application.protocol.prosemirror.ProseMirror;
import novemberizing.Packet;

public class UpdateDocumentReq extends Packet {
    @Expose private ProseMirror.Payload payload;

    public ProseMirror.Payload payload(){ return payload; }
    public Long version(){ return payload != null ? payload.version() : null; }
}
