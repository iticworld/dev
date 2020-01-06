package functional;

import com.google.gson.JsonElement;

import java.util.Locale;
import java.util.TimeZone;
import java.util.UUID;
import java.util.regex.Pattern;

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

    public static String concat(String s, String... strings) {
        String o = functional.string.get(s);
        if(strings != null){
            for(String str : strings) {
                o = o.concat(functional.string.get(str));
            }
        }
        return o;
    }
}
