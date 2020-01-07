package hornet.editor.html.server;

import com.google.gson.annotations.Expose;

import javax.websocket.SendHandler;
import java.util.ArrayList;
import java.util.List;

public abstract class RemoteCoworker {
    @Expose protected String id;
    @Expose protected List<String> owns = new ArrayList<>();

    public abstract <T> void send(T o, SendHandler result);

    public String id(){ return id; }

    public List<String> pos(){ return owns; }
    public void pos(List<String> o) {
        if(o == null) {
            o = new ArrayList<>();
        }
        owns = o;
    }

    public RemoteCoworker(String id) {
        this.id = id;
    }
}
