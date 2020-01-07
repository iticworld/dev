package functional;

import novemberizing.Listener;
import novemberizing.Packet;

import javax.websocket.RemoteEndpoint;
import javax.websocket.Session;
import java.util.List;
import java.util.Map;

public class ws {

    public static class path {


        public static String get(Session session, String key) {
            return session != null ? functional.map.get(session.getPathParameters(), key) : null;
        }
    }

    public static class request {
        public static String get(Session session, String key) {
            if(session != null){
                Map<String, List<String>> map = session.getRequestParameterMap();
                return functional.list.get(map.get(key), 0);
            }
            return null;
        }
    }

    public static class packet {
        public static String type(Packet packet){ return packet != null ? packet.type() : ""; }
    }

    public static <T> void async(Session session, T o, Listener.triple<Session, T, Throwable> callback) {
        if(session != null) {
            RemoteEndpoint.Async async = session.getAsyncRemote();
            async.sendText(functional.json.to(o), result -> callback.on(session, o, result.getException()));
        } else {
            callback.on(null, o, new NullPointerException("session is null"));
        }
    }
}
