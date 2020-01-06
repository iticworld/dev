package functional;

import java.util.Map;

public class map {

    public static <K, V> V get(Map<K, V> map, K k){ return map != null ? map.get(k) : null; }
    public static <K, V> V del(Map<K, V> map, K k){ return map != null ? map.remove(k) : null; }
    public static void clear(Map<?, ?> map){
        if(map != null) {
            map.clear();
        }
    }
    public static boolean empty(Map<?, ?> map){ return map == null || map.size() == 0; }
    public static boolean exist(Map<?, ?> map){ return map != null && map.size() > 0; }
    public static int size(Map<?, ?> map){ return map != null ? map.size() : 0; }
}
