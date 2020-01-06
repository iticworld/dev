package novemberizing.html.server;

import novemberizing.Function;
import novemberizing.Sync;

import java.util.HashMap;

public class DocumentRemoteRootMap extends Sync {
    private static DocumentRemoteRootMap __singleton = null;

    public static DocumentRemoteRootMap get(){
        synchronized (DocumentRemoteRoot.class) {
            if(__singleton == null) {
                __singleton = new DocumentRemoteRootMap();
            }
        }
        return __singleton;
    }

    private HashMap<String, DocumentRemoteRoot> __map = new HashMap<>();

    public <T> DocumentRemoteRoot load(String key, Function<T, DocumentRemoteRoot> factory, T in){
        lock();
        DocumentRemoteRoot document = __map.get(key);
        if(document == null) {
            try {
                document = factory.call(in);
                __map.put(key, document);
            } catch(Throwable e) {
                e.printStackTrace();
            }
        }
        unlock();
        return document;
    }

    private DocumentRemoteRootMap() {

    }
}
