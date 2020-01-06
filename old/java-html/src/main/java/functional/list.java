package functional;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collection;
import java.util.List;

@SuppressWarnings({"WeakerAccess", "unused"})
public class list extends functional.collection {
    public static <T> T begin(List<T> list){ return list != null && list.size() > 0 ? list.get(0) : null; }
    public static <T> T end(List<T> list){ return list != null && list.size() > 0 ? list.get(list.size() - 1) : null; }

    public static <T> List<T> gen(Collection<T> collection){ return collection != null ? new ArrayList<>(collection) : null; }

    @SafeVarargs
    public static <T> List<T> gen(T o, T... objects) {
        return add(new ArrayList<>(), o, objects);
    }

    public static <T> T get(List<T> list, int index) {
        return (index >= 0 && list != null && index < list.size()) ? list.get(index) : null;
    }

    public static <T> List<T> add(List<T> list, T o) {
        if(list != null) {
            list.add(o);
        }
        return list;
    }

    @SafeVarargs
    public static <T> List<T> add(List<T> list, T o, T... objects) {
        if(list != null) {
            list.add(o);
            if(objects != null) {
                list.addAll(Arrays.asList(objects));
            }
        }
        return list;
    }
}
