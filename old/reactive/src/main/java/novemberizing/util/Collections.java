package novemberizing.util;

import java.util.Collection;
import java.util.LinkedList;

/**
 *
 * @author novemberizing, me@novemberizing.net
 * @since 2017. 2. 7.
 */
public class Collections {
    public static <T> Collection<T> List(T item){
        Collection<T> collection = new LinkedList<>();
        collection.add(item);
        return collection;
    }
}
