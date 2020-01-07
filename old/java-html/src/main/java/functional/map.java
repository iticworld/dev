package functional;

import novemberizing.tuple.Pair;

import java.util.HashMap;
import java.util.Map;

@SuppressWarnings("unused")
public class map {
    @SafeVarargs
    public static <K, V> Map<K, V> gen(Pair<K, V> o, Pair<K, V>... objects) {
        Map<K, V> map = null;
        if(o != null){
            map = new HashMap<>();
            map.put(o.first(), o.second());
        }
        if(objects != null) {
            map = map != null ? map : new HashMap<>();
            for(Pair<K, V> object : objects) {
                map.put(object.first(), object.second());
            }
        }
        return map;
    }

    public static <K, V> V get(Map<K, V> map, K k) { return map != null ? map.get(k) : null; }

    public static boolean empty(Map<?, ?> map){ return map == null || map.size() == 0; }
    public static int size(Map<?, ?> map){ return map != null ? map.size() : 0; }
    public static boolean exist(Map<?, ?> map){ return map != null && map.size() > 0; }

    public static void clear(Map<?, ?> map){
        if(map != null) {
            map.clear();
        }
    }

    public static <K, V> V del(Map<K, V> map, K k) {
        if(map != null){
            return map.remove(k);
        }
        return null;
    }
}
