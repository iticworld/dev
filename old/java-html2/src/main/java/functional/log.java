package functional;

import novemberizing.log.Type;
import novemberizing.log.Method;

import java.util.Calendar;
import java.util.LinkedHashSet;
import java.util.Locale;

/**
 *
 * @author      novemberizing
 * @since       0.0.1
 */
public class log {
    public static class type {
        public static class to {
            public static String string(int v, boolean shorten){
                switch(v){
                    case Type.ERROR:        return shorten ? "e" : "error";
                    case Type.WARNING:      return shorten ? "w" : "warning";
                    case Type.CAUTION:      return shorten ? "c" : "caution";
                    case Type.NOTICE:       return shorten ? "n" : "notice";
                    case Type.INFORMATION:  return shorten ? "i" : "information";
                    case Type.DEBUG:        return shorten ? "d" : "debug";
                    case Type.VERBOSE:      return shorten ? "v" : "verbose";
                    case Type.FLOW:         return shorten ? "f" : "flow";
                    default:                return shorten ? "?" : "unknown";
                }
            }
        }

        public static void enable(int v){ __types |= v; }
        public static void disable(int v){ __types &= (~v); }
    }

    private static String __tag = "novemberizing";
    private static int __types = Type.ALL;
    private static boolean __shorten = false;
    private static boolean __console = false;
    private static boolean __stacktrace = false;
    private static boolean __date = false;
    private static boolean __function = false;
    private static int __depth = 8;
    private static LinkedHashSet<Method> __methods = new LinkedHashSet<>();

    private static void write(int classification, String type, String tag, String message, Throwable exception, StackTraceElement[] elements) {
        Calendar current = Calendar.getInstance();
        StringBuilder builder = new StringBuilder();
        if(__date) {
            builder.append(String.format(Locale.getDefault(), "%04d/%02d%02d %02d:%02d:%02d.%03d ",
                    current.get(Calendar.YEAR),
                    current.get(Calendar.MONTH),
                    current.get(Calendar.DATE),
                    current.get(Calendar.HOUR_OF_DAY),
                    current.get(Calendar.MINUTE),
                    current.get(Calendar.SECOND),
                    current.get(Calendar.MILLISECOND)));
        }
        builder.append(message);
        if(__function) {
            StackTraceElement element = functional.collection.get(elements, __depth);
            if(element != null) {
                builder.append(String.format(Locale.getDefault(), " %s.%s(%s:%d) ",
                        functional.string.replace(element.getClassName(), "$", "."),
                        element.getMethodName(),
                        element.getFileName(),
                        element.getLineNumber()));
            }
        }
        if(exception != null){
            builder.append(" exception (");
            builder.append(functional.string.from(exception.getClass(), false));
            if(!functional.string.empty(exception.getMessage())) {
                builder.append("/");
                builder.append(exception.getMessage());
            }
            builder.append(")");
        }
        if(__stacktrace && !functional.collection.empty(elements)) {
            builder.append("\n");
            for(StackTraceElement element : elements) {
                builder.append("    ");
                builder.append(functional.string.from(element));
                builder.append("\n");
            }
        }
        String out = builder.toString();
        if(__console){
            System.out.println(out);
        }
        if(__methods.size() > 0) {
            for(Method method : __methods) {
                method.out(classification, type, current, functional.thread.id(Thread.currentThread()), tag, out, exception);
            }
        }
    }

    private static void write(int classification, String tag, String message, Throwable exception, StackTraceElement[] elements) {
        if((__types & classification) != 0 && (__methods.size() > 0 || __console)) {
            write(classification, functional.log.type.to.string(classification, __shorten), tag, message, exception, elements);
        }
    }

    public static void tag(String v){ __tag = v; }
    public static void shorten(boolean v){ __shorten = v; }
    public static void types(int v){ __types = v; }
    public static void stacktrace(boolean v){ __stacktrace = v; }
    public static void date(boolean v){ __date = v; }
    public static void function(boolean v){ __function = v; }
    public static void depth(int v){ __depth = v; }
    public static void console(boolean v){ __console = v; }

    public static void add(Method method){
        if(method != null){
            __methods.add(method);
        }
    }

    public static void del(Method method){ __methods.remove(method); }

    public static void e(Throwable e){ e(__tag, e!=null ? e.getMessage() : "", e); }
    public static void e(String message){ e(__tag, message, null); }
    public static void e(String message, Throwable exception){ e(__tag, message, exception); }
    public static void e(String tag, String message){ e(tag, message, null); }
    public static void e(String tag, String message, Throwable exception){ write(Type.ERROR, tag, message, exception, exception!=null ? exception.getStackTrace() : thread.stacktrace(Thread.currentThread())); }
    public static void e(Object object){ e(__tag, functional.json.from(object), null); }
    public static void e(Object object, Throwable exception){ e(__tag, functional.json.from(object), exception); }
    public static void e(String tag, Object object){ e(tag, functional.json.from(object), null); }
    public static void e(String tag, Object object, Throwable exception){ e(tag, functional.json.from(object), exception); }

    public static void w(Throwable e){ w(__tag, e!=null ? e.getMessage() : "", e); }
    public static void w(String message){ w(__tag, message, null); }
    public static void w(String message, Throwable exception){ w(__tag, message, exception); }
    public static void w(String tag, String message){ w(tag, message, null); }
    public static void w(String tag, String message, Throwable exception){ write(Type.WARNING, tag, message, exception, exception!=null ? exception.getStackTrace() : thread.stacktrace(Thread.currentThread())); }
    public static void w(Object object){ w(__tag, functional.json.from(object), null); }
    public static void w(Object object, Throwable exception){ w(__tag, functional.json.from(object), exception); }
    public static void w(String tag, Object object){ w(tag, functional.json.from(object), null); }
    public static void w(String tag, Object object, Throwable exception){ w(tag, functional.json.from(object), exception); }

    public static void c(Throwable e){ c(__tag, e!=null ? e.getMessage() : "", e); }
    public static void c(String message){ c(__tag, message, null); }
    public static void c(String message, Throwable exception){ c(__tag, message, exception); }
    public static void c(String tag, String message){ c(tag, message, null); }
    public static void c(String tag, String message, Throwable exception){ write(Type.CAUTION, tag, message, exception, exception!=null ? exception.getStackTrace() : thread.stacktrace(Thread.currentThread())); }
    public static void c(Object object){ c(__tag, functional.json.from(object), null); }
    public static void c(Object object, Throwable exception){ c(__tag, functional.json.from(object), exception); }
    public static void c(String tag, Object object){ c(tag, functional.json.from(object), null); }
    public static void c(String tag, Object object, Throwable exception){ c(tag, functional.json.from(object), exception); }

    public static void n(Throwable e){ n(__tag, e!=null ? e.getMessage() : "", e); }
    public static void n(String message){ n(__tag, message, null); }
    public static void n(String message, Throwable exception){ n(__tag, message, exception); }
    public static void n(String tag, String message){ n(tag, message, null); }
    public static void n(String tag, String message, Throwable exception){ write(Type.NOTICE, tag, message, exception, exception!=null ? exception.getStackTrace() : thread.stacktrace(Thread.currentThread())); }
    public static void n(Object object){ n(__tag, functional.json.from(object), null); }
    public static void n(Object object, Throwable exception){ n(__tag, functional.json.from(object), exception); }
    public static void n(String tag, Object object){ n(tag, functional.json.from(object), null); }
    public static void n(String tag, Object object, Throwable exception){ n(tag, functional.json.from(object), exception); }

    public static void i(Throwable e){ i(__tag, e!=null ? e.getMessage() : "", e); }
    public static void i(String message){ i(__tag, message, null); }
    public static void i(String message, Throwable exception){ i(__tag, message, exception); }
    public static void i(String tag, String message){ i(tag, message, null); }
    public static void i(String tag, String message, Throwable exception){ write(Type.INFORMATION, tag, message, exception, exception!=null ? exception.getStackTrace() : thread.stacktrace(Thread.currentThread())); }
    public static void i(Object object){ i(__tag, functional.json.from(object), null); }
    public static void i(Object object, Throwable exception){ i(__tag, functional.json.from(object), exception); }
    public static void i(String tag, Object object){ i(tag, functional.json.from(object), null); }
    public static void i(String tag, Object object, Throwable exception){ i(tag, functional.json.from(object), exception); }

    public static void d(Throwable e){ d(__tag, e!=null ? e.getMessage() : "", e); }
    public static void d(String message){ d(__tag, message, null); }
    public static void d(String message, Throwable exception){ d(__tag, message, exception); }
    public static void d(String tag, String message){ d(tag, message, null); }
    public static void d(String tag, String message, Throwable exception){ write(Type.DEBUG, tag, message, exception, exception!=null ? exception.getStackTrace() : thread.stacktrace(Thread.currentThread())); }
    public static void d(Object object){ d(__tag, functional.json.from(object), null); }
    public static void d(Object object, Throwable exception){ d(__tag, functional.json.from(object), exception); }
    public static void d(String tag, Object object){ d(tag, functional.json.from(object), null); }
    public static void d(String tag, Object object, Throwable exception){ d(tag, functional.json.from(object), exception); }

    public static void v(Throwable e){ v(__tag, e!=null ? e.getMessage() : "", e); }
    public static void v(String message){ v(__tag, message, null); }
    public static void v(String message, Throwable exception){ v(__tag, message, exception); }
    public static void v(String tag, String message){ v(tag, message, null); }
    public static void v(String tag, String message, Throwable exception){ write(Type.VERBOSE, tag, message, exception, exception!=null ? exception.getStackTrace() : thread.stacktrace(Thread.currentThread())); }
    public static void v(Object object){ v(__tag, functional.json.from(object), null); }
    public static void v(Object object, Throwable exception){ v(__tag, functional.json.from(object), exception); }
    public static void v(String tag, Object object){ v(tag, functional.json.from(object), null); }
    public static void v(String tag, Object object, Throwable exception){ v(tag, functional.json.from(object), exception); }

    public static void f(Throwable e){ f(__tag, e!=null ? e.getMessage() : "", e); }
    public static void f(String message){ f(__tag, message, null); }
    public static void f(String message, Throwable exception){ f(__tag, message, exception); }
    public static void f(String tag, String message){ f(tag, message, null); }
    public static void f(String tag, String message, Throwable exception){ write(Type.FLOW, tag, message, exception, exception!=null ? exception.getStackTrace() : thread.stacktrace(Thread.currentThread())); }
    public static void f(Object object){ f(__tag, functional.json.from(object), null); }
    public static void f(Object object, Throwable exception){ f(__tag, functional.json.from(object), exception); }
    public static void f(String tag, Object object){ f(tag, functional.json.from(object), null); }
    public static void f(String tag, Object object, Throwable exception){ f(tag, functional.json.from(object), exception); }
}
