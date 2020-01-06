package functional;

import com.google.gson.JsonElement;

import java.util.List;
import java.util.Locale;
import java.util.TimeZone;
import java.util.UUID;
import java.util.regex.Pattern;

@SuppressWarnings({"unused", "WeakerAccess"})
public class string {
    public static boolean empty(String v){ return v == null || v.length() == 0; }
    public static boolean empty(String v, boolean trim){ return trim ? (v == null || empty(v.trim())) : empty(v); }
    public static boolean validate(Pattern expression, String v){ return v != null && expression != null && v.matches(expression.pattern()); }

    public static boolean contain(String x, String... strings){
        if(strings != null) {
            for(String y : strings){
                if(functional.string.equal(x, y)) {
                    return true;
                }
            }
        }
        return false;
    }

    public static String fill(String s, int n) {
        StringBuilder builder = new StringBuilder();
        for(int i = 0; i < n; i++) {
            builder.append(s);
        }
        return builder.toString();
    }

    public static class to {
        public static String upper(String v){ return v != null ? v.toUpperCase() : null; }
    }

    public static boolean equal(String x, String y){ return x == null ? y == null : x.equals(y); }
    public static boolean equal(String x, String y, boolean casing){ return x == null ? y == null : (casing ? x.equals(y) : x.equalsIgnoreCase(y)); }

    public static String replace(String original, String target, String replacement){ return original != null ? original.replace(target, replacement) : ""; }
    public static String replace(String original, String target, String replacement, boolean all) {
        if(original != null) {
            return all ? original.replace(target, replacement) : original.replaceAll(target, replacement);
        }
        return null;
    }

    public static String get(String v){ return v != null ? v : ""; }

    public static String from(Class<?> c, boolean simple){ return c != null ? (simple ? c.getSimpleName() : c.getCanonicalName()) : ""; }

    public static String from(StackTraceElement element) {
        if(element != null) {
            String c = functional.string.replace(element.getClassName(), "$", ".");
            return String.format(Locale.getDefault(), "%s.%s (%s:%d)",
                    c,
                    element.getMethodName(),
                    element.getFileName(),
                    element.getLineNumber());
        }
        return null;
    }

    public static String from(JsonElement element){ return element != null ? element.toString() : null; }
    public static String from(Long v){ return v != null ? v.toString() : null; }
    public static String from(Integer v){ return v != null ? v.toString() : null; }
    public static String from(UUID uuid){ return uuid != null ? uuid.toString() : null; }
    public static String from(TimeZone timezone){ return timezone != null ? timezone.getDisplayName() : null; }

    public static List<String> split(String s, int index) {
        if(s == null || index < 0) {
            System.err.println("s: " + s);
            System.err.println("index: " + index);
            throw new RuntimeException("");
        }
        if(s.length() < index) {
            throw new RuntimeException("");
        }
        return s.length() == index ? functional.list.gen(s, "") : functional.list.gen(s.substring(0, index), s.substring(index));
    }

    public static List<String> split(String s, int from, int to) {
        System.err.println("s: " + s);
        System.err.println("from: " + from);
        System.err.println("to: " + to);
        List<String> first = functional.string.split(s, from);
        if(first.size() == 2) {
            System.out.println(first.get(0));
            System.out.println(first.get(1));
            List<String> second = functional.string.split(first.get(1), to - from);
            System.out.println(second.get(0));
            System.out.println(second.get(1));
            return functional.list.gen(first.get(0), second.get(0), second.get(1));
        }
        throw new RuntimeException("");
    }

    public static String merge(String s, String... strings) {
        StringBuilder builder = new StringBuilder();
        builder.append(s != null ? s : "");
        for(String string : strings) {
            builder.append(string != null ? string : "");
        }
        return builder.toString();
    }

    public static String insert(String s, int index, String v) {
        String begin = s.substring(0, index);
        String end = s.substring(index);
        return begin + v + end;
    }

    public static String replace(String s, int from, int to, String v) {
        String begin = s.substring(0, from);
        String end = s.substring(to);
        return begin + v + end;
    }
}
