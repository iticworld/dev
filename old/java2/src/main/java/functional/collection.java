package functional;

import java.util.Collection;

public class collection {
    public static boolean exist(Object[] array){ return array != null && array.length > 0; }
    public static boolean exist(Collection<?> collection){ return collection != null && collection.size() > 0; }
    public static boolean empty(Object[] array){ return array == null || array.length == 0; }
    public static boolean empty(Collection<?> collection){ return collection == null || collection.size() == 0; }
    public static int size(Object[] array){ return array != null ? array.length : 0; }
    public static int size(Collection<?> collection){ return collection != null ? collection.size() : 0; }
}
