package hornet.editor.html.server;

import novemberizing.Sync;

import javax.websocket.SendHandler;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;

public class RemoteCoworkerMap extends Sync {
    private HashMap<String, RemoteCoworker> __map = new HashMap<>();

    public List<RemoteCoworker> list(){
        lock();
        ArrayList<RemoteCoworker> o = new ArrayList<>(__map.values());
        unlock();
        return o;
    }

    public List<RemoteCoworker> join(RemoteCoworker coworker) {
        lock();
        // TODO: CHECK CONTAIN KEY
        __map.put(coworker.id(), coworker);
        ArrayList<RemoteCoworker> o = new ArrayList<>(__map.values());
        unlock();
        return o;
    }

    public List<RemoteCoworker> leave(RemoteCoworker coworker) {
        ArrayList<RemoteCoworker> o = null;
        lock();
        if(__map.remove(coworker.id(), coworker)) {
            o = new ArrayList<>(__map.values());
        }
        unlock();
        return o;
    }

    public <T> void broadcast(T o, SendHandler handler) {
        List<RemoteCoworker> coworkers = list();
        for(RemoteCoworker coworker : coworkers) {
            if(coworker != null) {
                try {
                    coworker.send(o, handler);
                } catch(IllegalStateException e) {
                    leave(coworker);
                }
            }
        }
    }
}
