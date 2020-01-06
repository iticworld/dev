package hornet.editor.html.server;

import novemberizing.Sync;

import java.util.HashMap;
import java.util.List;

public class RemoteLineMap extends Sync {
    private HashMap<String, RemoteCoworker> __map = new HashMap<>();

    public List<String> own(RemoteCoworker coworker, List<String> prev, List<String> next) {
        System.err.println("implement this");
        return next;
    }
}
