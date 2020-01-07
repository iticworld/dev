package novemberizing.ws.protocol.request;

import com.google.gson.annotations.Expose;
import novemberizing.packet.Packet;

import java.util.List;

public class ChangePosReq extends Packet {
    @Expose List<String> pos;

    public List<String> pos(){ return pos; }
    // {"type":"changepos","model":"req","pos":["34678b39-853b-431d-96c9-ee457c14f21a"],"id":2}
}
