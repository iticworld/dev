package novemberizing.html.server;

import java.util.HashMap;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

public class DocumentServer {
    private DocumentRemoteObject __document;
    private Lock __o = new ReentrantLock();
    private HashMap<String, DocumentSession> __coworkers = new HashMap<>();
    private HashMap<String, DocumentRemoteObject> __documents = new HashMap<>();


    public DocumentServer() {

    }
}
