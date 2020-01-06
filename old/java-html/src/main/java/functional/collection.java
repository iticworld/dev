package functional;

import novemberizing.Listener;

import java.util.Collection;

@SuppressWarnings("unused")
public class collection {
    public static boolean exist(Collection<?> collection){ return collection != null && collection.size() > 0; }

    public static int size(Collection<?> collection){ return collection != null ? collection.size() : 0; }

    public static <T> boolean empty(T[] array){ return array == null || array.length == 0; }
    public static boolean empty(Collection<?> array) { return array == null || array.size() == 0; }

    public static <T> void remove(Collection<T> destination, Collection<T> items){
        if(destination != null && items != null) {
            for(T item : items) {
                destination.remove(item);
            }
        }
    }

    public static <T> void each(Collection<T> collection, Listener<T> function){
        if(collection != null){
            for(T o : collection){
                function.on(o);
            }
        }
    }

    public static <T> T get(T[] elements, int index){ return elements != null && 0 <= index && index < elements.length ? elements[index] : null; }
}
