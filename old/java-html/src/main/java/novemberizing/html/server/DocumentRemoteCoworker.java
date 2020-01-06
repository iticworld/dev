package novemberizing.html.server;

import com.google.gson.annotations.Expose;
import novemberizing.Sync;

import javax.websocket.SendHandler;
import java.util.ArrayList;
import java.util.List;

public abstract class DocumentRemoteCoworker extends Sync {
    @Expose protected String id;
    @Expose protected List<String> owns = new ArrayList<>();

    public String id(){ return id; }

    public List<String> pos(){ return owns; }
    public void pos(List<String> o) {
        if(o == null) {
            o = new ArrayList<>();
        }
        owns = o;
    }

    public DocumentRemoteCoworker(String id) {
        this.id = id;
    }

    public abstract <T> void send(T o, SendHandler result);
}
