package novemberizing.ws.protocol.broadcast;

import com.google.gson.annotations.Expose;
import novemberizing.document.NovemberizingDocumentServerPacketType;
import novemberizing.packet.Packet;
import novemberizing.ws.protocol.prosemirror.ProseMirror;

import java.util.List;

public class BroadcastUpdatePacket extends Packet {
    public static class Data {
        @Expose private String clientID;
        @Expose private Long version;
        @Expose private List<ProseMirror.Step> steps;
        @Expose private String sessid;
        public Data(String client, String session, Long version, List<ProseMirror.Step> steps) {
            this.clientID = client;
            this.sessid = session;
            this.version = version;
            this.steps = steps;
        }
    }

    @Expose private Data data;

    public BroadcastUpdatePacket(String client, String session, Long version, List<ProseMirror.Step> steps){
        this.type = NovemberizingDocumentServerPacketType.UPDATE;
        this.model = NovemberizingDocumentServerPacketType.SHOUT;
        this.data = new Data(client, session, version, steps);
    }


}
