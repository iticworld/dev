package novemberizing.html.server;

import novemberizing.Sync;

import java.util.HashMap;
import java.util.List;

public class DocumentRemoteLineMap extends Sync {
    private HashMap<String, DocumentRemoteCoworker> __map = new HashMap<>();

    public List<String> own(DocumentRemoteCoworker coworker, List<String> prev, List<String> next) {
        System.err.println("implement this");
        return next;
    }
}
