package novemberizing.html.server;

import java.util.HashMap;

public class DocumentRemoteObjectMap extends novemberizing.Lock {
    private HashMap<String, DocumentRemoteObject> __map = new HashMap<>();

    public Long insert(String document, String id, int index, String text) {
        Long version = null;
        try {
            lock();
            DocumentRemoteObject object = __map.get(id);
            version = object.insert(id, index, text);
        } catch(Throwable e) {
            e.printStackTrace();
        } finally {
            unlock();
        }
        return version;
    }
}
