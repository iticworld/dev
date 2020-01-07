package novemberizing.ws.protocol.request;

import com.google.gson.annotations.Expose;
import novemberizing.packet.Packet;
import novemberizing.ws.protocol.prosemirror.ProseMirror;

public class DocumentUpdateReq extends Packet {
    @Expose private ProseMirror.Payload payload;

    public ProseMirror.Payload payload(){ return payload; }
    public Long version(){ return payload != null ? payload.version() : null; }
    // {"payload":{"version":0,"steps":[{"stepType":"replace","from":369,"to":369,"slice":{"content":[{"type":"text","text":" "}]},"id":"8bdb7d21-8fa1-477d-ad57-8823d7454da3","previous":{"start":340,"id":"870405e2-aa56-402f-96f7-26c21d1a9259","len":116}}],"clientID":"9653"},"id":3}
}
