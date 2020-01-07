package functional;

import novemberizing.tuple.Pair;

import java.util.HashMap;
import java.util.Map;

public class map {

    @SafeVarargs
    public static <K, V> Map<K, V> create(Pair<K, V> o, Pair<K, V>... objects) {
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

    public static <K, V> boolean empty(Map<K, V> map){ return map == null || map.size() == 0; }
}
