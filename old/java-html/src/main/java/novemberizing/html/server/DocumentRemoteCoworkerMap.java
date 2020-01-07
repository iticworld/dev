package novemberizing.html.server;

import novemberizing.Sync;

import javax.websocket.SendHandler;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;

public class DocumentRemoteCoworkerMap extends Sync {
    private HashMap<String, DocumentRemoteCoworker> __map = new HashMap<>();

    public List<DocumentRemoteCoworker> list(){
        lock();
        ArrayList<DocumentRemoteCoworker> o = new ArrayList<>(__map.values());
        unlock();
        return o;
    }

    public List<DocumentRemoteCoworker> join(DocumentRemoteCoworker coworker) {
        lock();
        // TODO: CHECK CONTAIN KEY
        __map.put(coworker.id(), coworker);
        ArrayList<DocumentRemoteCoworker> o = new ArrayList<>(__map.values());
        unlock();
        return o;
    }

    public List<DocumentRemoteCoworker> leave(DocumentRemoteCoworker coworker) {
        ArrayList<DocumentRemoteCoworker> o = null;
        lock();
        if(__map.remove(coworker.id(), coworker)) {
            o = new ArrayList<>(__map.values());
        }
        unlock();
        return o;
    }

    public <T> void broadcast(T o, SendHandler handler) {
        List<DocumentRemoteCoworker> coworkers = list();
        for(DocumentRemoteCoworker coworker : coworkers) {
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
