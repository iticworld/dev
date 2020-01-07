package functional;

import java.util.Collection;
import java.util.List;
import java.util.Objects;
import java.util.UUID;

@SuppressWarnings("Duplicates")
public class string {
    public static boolean empty(String v){ return v == null || v.length() == 0; }
    public static boolean exist(String v){ return v != null && v.length() > 0; }

    public static boolean contain(String x, String o, String... strings) {
        if(functional.string.equal(x, o)) {
            return true;
        }
        if(strings != null) {
            for(String y : strings) {
                if(functional.string.equal(x, y)) {
                    return true;
                }
            }
        }
        return false;
    }

    public static boolean contain(String x, Collection<String> strings) {
        if(strings != null) {
            for(String y : strings) {
                if(functional.string.equal(x, y)) {
                    return true;
                }
            }
        }
        return false;
    }

    public static boolean contain(String x, String[] strings) {
        if(strings != null) {
            for(String y : strings) {
                if(functional.string.equal(x, y)) {
                    return true;
                }
            }
        }
        return false;
    }

    public static boolean equal(String x, String y) { return Objects.equals(x, y); }

    public static String v(UUID uuid){ return uuid != null ? uuid.toString() : null; }
    public static String v(String s){ return s != null ? s : ""; }

    public static List<String> split(String s, int index) {
        if(s != null && 0 <= index && index <= s.length()) {
            if(index == 0) {
                return functional.list.gen(null, s);
            } else if(index == s.length()) {
                return functional.list.gen(s, (String) null);
            } else {
                return functional.list.gen(s.substring(0, index), s.substring(index));
            }
        } else {
            System.out.println(s);
            System.out.println(index);
            throw new RuntimeException("");
        }
    }

    public static List<String> split(String s, int from, int to) {
        List<String> first = functional.string.split(s, from);
        if(first.size() == 2) {
            List<String> second = functional.string.split(first.get(1), to - from);
            return functional.list.gen(first.get(0), second.get(0), second.get(1));
        } else {
            throw new RuntimeException("");
        }
    }

    public static String merge(String s, String... strings) {
        StringBuilder builder = new StringBuilder();
        builder.append(s != null ? s : "");
        if(strings != null) {
            for(String string : strings) {
                builder.append(string != null ? string : "");
            }
        }
        return builder.toString();
    }

    public static String merge(String[] strings) {
        StringBuilder builder = new StringBuilder();
        if(strings != null) {
            for(String string : strings) {
                builder.append(string != null ? string : "");
            }
        }
        return builder.toString();
    }

    public static String merge(Collection<String> strings) {
        StringBuilder builder = new StringBuilder();
        if(strings != null) {
            for(String string : strings) {
                builder.append(string != null ? string : "");
            }
        }
        return builder.toString();
    }

    public static String insert(String s, int index, String v) {
        List<String> strings = functional.string.split(s, index);
        return functional.string.v(strings.get(0)) + functional.string.v(v) + functional.string.v(strings.get(1));
    }

    public static String replace(String s, int from, int to, String v) {
        List<String> strings = functional.string.split(s, from, to);
        return functional.string.v(strings.get(0)) + functional.string.v(v) + functional.string.v(strings.get(2));
    }
}
