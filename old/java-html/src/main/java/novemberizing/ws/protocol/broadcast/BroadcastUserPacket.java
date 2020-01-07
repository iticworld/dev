package novemberizing.ws.protocol.broadcast;

import com.google.gson.annotations.Expose;
import novemberizing.html.server.DocumentRemoteCoworker;
import novemberizing.packet.Packet;

import java.util.List;

public class BroadcastUserPacket extends Packet {
    @Expose private List<DocumentRemoteCoworker> data;

    public BroadcastUserPacket(List<DocumentRemoteCoworker> coworkers) {
        this.type = "user";
        this.model = "shout";
        this.data = coworkers;
    }
}
