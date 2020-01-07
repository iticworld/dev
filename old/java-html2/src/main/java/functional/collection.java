package functional;

import novemberizing.Function;
import novemberizing.Listener;

import java.util.Collection;
import java.util.Map;

public class collection {
    public static boolean exist(Collection<?> collection){ return collection != null && collection.size() > 0; }

    public static <T> boolean empty(T[] array){ return array == null || array.length == 0; }
    public static <T> boolean empty(Collection<? super T> array) { return array == null || array.size() == 0; }

    public static <T> void remove(Collection<T> destination, Collection<T> items){
        if(destination != null && items != null) {
            for(T item : items) {
                destination.remove(item);
            }
        }
    }

    public static <T> void remove(Map<T, ?> destination, Collection<T> items){
        if(destination != null && items != null) {
            for(T item : items){
                destination.remove(item);
            }
        }
    }

    public static <K, V> V get(Map<K, V> map, K k, Function<K, V> function){ return map != null ? (map.computeIfAbsent(k, key -> functional.exception.safe(key, function, null))) : null; }

    public static <K, V> V get(Map<K, V> map, K k){ return map != null ? map.get(k) : null; }

    public static <T> void each(Collection<T> collection, Listener<T> function){
        if(collection != null){
            for(T o : collection){
                function.on(o);
            }
        }
    }

    public static <T> T get(T[] elements, int index){ return elements != null && 0 <= index && index < elements.length ? elements[index] : null; }



}
