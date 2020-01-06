package hornet.editor.application.protocol.broadcast;

import com.google.gson.annotations.Expose;
import hornet.editor.application.protocol.RemoteDocumentPacketType;
import hornet.editor.application.protocol.prosemirror.ProseMirror;
import novemberizing.Packet;

import java.util.List;

public class BroadcastDocumentUpdate extends Packet {
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

    public BroadcastDocumentUpdate(String client, String session, Long version, List<ProseMirror.Step> steps){
        this.type = RemoteDocumentPacketType.UPDATE;
        this.model = RemoteDocumentPacketType.SHOUT;
        this.data = new Data(client, session, version, steps);
    }


}