package hornet.editor.application.protocol.broadcast;

import com.google.gson.annotations.Expose;
import hornet.editor.html.server.RemoteCoworker;
import novemberizing.Packet;

import java.util.List;

public class BroadcastCoworkerList extends Packet {
    @Expose private List<RemoteCoworker> data;

    public BroadcastCoworkerList(List<RemoteCoworker> coworkers) {
        this.type = "user";
        this.model = "shout";
        this.data = coworkers;
    }
}
