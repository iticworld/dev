package functional;

import novemberizing.packet.Packet;

import javax.websocket.RemoteEndpoint;
import javax.websocket.SendHandler;
import javax.websocket.Session;
import java.util.List;
import java.util.Map;

public class ws {
    public static class path {
        public static String get(Session session, String key){
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

    public static <T> void async(Session session, T o, SendHandler handler) {
        RemoteEndpoint.Async async = session.getAsyncRemote();
        async.sendText(functional.json.from(o), handler);
    }
}
