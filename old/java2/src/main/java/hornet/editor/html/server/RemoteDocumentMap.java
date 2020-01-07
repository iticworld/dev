package hornet.editor.html.server;

import novemberizing.Function;
import novemberizing.Sync;

import java.util.HashMap;

public class RemoteDocumentMap extends Sync {
    private static RemoteDocumentMap __singleton = null;

    public static RemoteDocumentMap get(){
        synchronized (RemoteDocumentMap.class) {
            if(__singleton == null) {
                __singleton = new RemoteDocumentMap();
            }
        }
        return __singleton;
    }

    private HashMap<String, RemoteDocument> __map = new HashMap<>();

    public <T> RemoteDocument load(String key, Function<T, RemoteDocument> factory, T in){
        lock();
        RemoteDocument document = __map.get(key);
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

    private RemoteDocumentMap() {

    }
}
