package hornet.editor.application.protocol.request;

import com.google.gson.annotations.Expose;
import novemberizing.Packet;

import java.util.List;

public class ChangePosReq extends Packet {
    @Expose List<String> pos;

    public List<String> pos(){ return pos; }
}
