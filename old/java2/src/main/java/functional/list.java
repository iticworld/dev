package functional;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collection;
import java.util.List;

public class list extends collection {
    public static <T> T begin(List<T> list){ return list != null && list.size() > 0 ? list.get(0) : null; }
    public static <T> T end(List<T> list){ return list != null && list.size() > 0 ? list.get(list.size() - 1) : null; }
    public static <T> T get(List<T> list, int index){ return list != null && 0 <= index && index < list.size() ? list.get(index) : null; }

    @SafeVarargs
    public static <T> List<T> gen(T o, T... objects){ return functional.list.add(new ArrayList<>(), o, objects); }
    public static <T> List<T> gen(Collection<? extends T> collection){ return collection != null ? new ArrayList<>(collection) : new ArrayList<>(); }
    public static <T> List<T> gen(T[] objects){ return objects != null ? Arrays.asList(objects) : null; }
    public static <T> List<T> gen(T o){ return functional.list.add(new ArrayList<>(), o); }

    @SafeVarargs
    public static <T> List<T> add(List<T> list, T o, T... objects) {
        if(list != null) {
            list.add(o);
            if(objects != null) {
                list.addAll(Arrays.asList(objects));
            }
        } else {
            throw new RuntimeException("");
        }
        return list;
    }
    public static <T> List<T> add(List<T> list, T[] objects){
        if(list != null) {
            list.addAll(Arrays.asList(objects));
        } else {
            throw new RuntimeException("");
        }
        return list;
    }
    public static <T> List<T> add(List<T> list, Collection<? extends T> collection) {
        if(list != null) {
            list.addAll(collection);
        } else {
            throw new RuntimeException("");
        }
        return list;
    }
    public static <T> List<T> add(List<T> list, T o) {
        if(list != null) {
            list.add(o);
        } else {
            throw new RuntimeException("");
        }
        return list;
    }
}
