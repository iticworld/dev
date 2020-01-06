package novemberizing.util;

import com.google.gson.Gson;
import com.google.gson.GsonBuilder;
import com.google.gson.annotations.Expose;
import novemberizing.util.impl.ConsoleLog;

import java.util.Calendar;
import java.util.LinkedList;
import java.util.Locale;

/**
 *
 * @author novemberizing
 * @since 2016/12/23
 */
@SuppressWarnings("unused, WeakerAccess, SameParameterValue")
public class Log {
    private static class List {
        @Expose private LinkedList<Object> objects = new LinkedList<>();

        public List(Object o, Object... objects){
            this.objects.add((o instanceof Throwable) ? new Exception((Throwable) o) : o);
            for(Object object : objects){
                this.objects.add((object instanceof Throwable) ? new Exception((Throwable) object) : object);
            }
        }

        public List(Object[] objects){
            for(Object object : objects){
                this.objects.add((object instanceof Throwable) ? new Exception((Throwable) object) : object);
            }
        }
    }

    public static String toJson(Object o) {
        o = (o instanceof Throwable) ? new Exception((Throwable) o) : o;
        GsonBuilder builder = new GsonBuilder().excludeFieldsWithoutExposeAnnotation();
        builder.disableHtmlEscaping();
        Gson gson = builder.create();
        return gson.toJson(o);
    }

    public static String toJson(Object o, Object... objects) {
        GsonBuilder builder = new GsonBuilder().excludeFieldsWithoutExposeAnnotation();
        builder.disableHtmlEscaping();
        Gson gson = builder.create();
        return gson.toJson(new List(o,objects));
    }

    public static String toJson(Object[] o) {
        GsonBuilder builder = new GsonBuilder().excludeFieldsWithoutExposeAnnotation();
        builder.disableHtmlEscaping();
        Gson gson = builder.create();
        return gson.toJson(new List(o));
    }

    private static class Stack {
        @Expose private String c;
        @Expose private String method;
        @Expose private String file;
        @Expose private int line;
        @Expose private boolean __native;

        public Stack(StackTraceElement e){
            c = e.getClassName();
            method = e.getMethodName();
            file = e.getFileName();
            line = e.getLineNumber();
            __native = e.isNativeMethod();
        }
    }

    private static class Exception {
        private Throwable __exception;
        @Expose private LinkedList<Stack> __stack = new LinkedList<>();
        @Expose private String msg;

        public Exception(Throwable e){
            __exception = e;
            for(StackTraceElement element : __exception.getStackTrace()){
                __stack.add(new Stack(element));
            }
            msg = __exception.getMessage();
        }
    }

    private static Log __o = new Log();

    public static final int ERROR       = 0x00000001 <<  1;
    public static final int WARNING     = 0x00000001 <<  2;
    public static final int CAUTION     = 0x00000001 <<  3;
    public static final int NOTICE      = 0x00000001 <<  4;
    public static final int INFORMATION = 0x00000001 <<  5;
    public static final int FLOW        = 0x00000001 <<  6;
    public static final int VERBOSE     = 0x00000001 <<  7;
    public static final int DEBUG       = 0x00000001 <<  8;
    public static final int TAG         = 0x00000001 <<  29;
    public static final int HEADER      = 0x00000001 <<  30;


    public static <T> T e(String tag, T o){
        if((__o.__types & ERROR)==ERROR) {
            __o.___write(ERROR, tag, toJson(o));
        }
        return o;
    }
    public static <T> T w(String tag, T o) {
        if ((__o.__types & WARNING) == WARNING) {
            __o.___write(WARNING, tag, toJson(o));
        }
        return o;
    }
    public static <T> T c(String tag, T o) {
        if ((__o.__types & CAUTION) == CAUTION) {
            __o.___write(CAUTION, tag, toJson(o));
        }
        return o;
    }
    public static <T> T n(String tag, T o){
        if((__o.__types & NOTICE)==NOTICE) {
            __o.___write(NOTICE, tag, toJson(o));
        }
        return o;
    }
    public static <T> T i(String tag, T o) {
        if ((__o.__types & INFORMATION) == INFORMATION) {
            __o.___write(INFORMATION, tag, toJson(o));
        }
        return o;
    }
    public static <T> T d(String tag, T o) {
        if ((__o.__types & DEBUG) == DEBUG) {
            __o.___write(DEBUG, tag, toJson(o));
        }
        return o;
    }
    public static <T> T f(String tag, T o){
        if ((__o.__types & FLOW) == FLOW) {
            __o.___write(FLOW,tag,toJson(o));
        }
        return o;
    }
    public static <T> T v(String tag, T o){
        if ((__o.__types & VERBOSE) == VERBOSE) {
            __o.___write(VERBOSE, tag, toJson(o));
        }
        return o;
    }

    public static Object e(String tag, Object o, Object... objects) {
        if ((__o.__types & ERROR) == ERROR) {
            __o.___write(ERROR, tag, toJson(o, objects));
        }
        return o;
    }
    public static Object w(String tag, Object o, Object... objects) {
        if ((__o.__types & WARNING) == WARNING) {
            __o.___write(WARNING, tag, toJson(o, objects));
        }
        return o;
    }
    public static Object c(String tag, Object o, Object... objects){
        if ((__o.__types & CAUTION) == CAUTION) {
            __o.___write(CAUTION, tag, toJson(o, objects));
        }
        return o;
    }
    public static Object n(String tag, Object o, Object... objects){
        if ((__o.__types & NOTICE) == NOTICE) {
            __o.___write(NOTICE, tag, toJson(o, objects));
        }
        return o;
    }
    public static Object i(String tag, Object o, Object... objects){
        if ((__o.__types & INFORMATION) == INFORMATION) {
            __o.___write(INFORMATION, tag, toJson(o, objects));
        }
        return o;
    }
    public static Object d(String tag, Object o, Object... objects){
        if ((__o.__types & DEBUG) == DEBUG) {
            __o.___write(DEBUG, tag, toJson(o, objects));
        }
        return o;
    }
    public static Object f(String tag, Object o, Object... objects){
        if ((__o.__types & FLOW) == FLOW) {
            __o.___write(FLOW, tag, toJson(o, objects));
        }
        return o;
    }
    public static Object v(String tag, Object o, Object... objects){
        if ((__o.__types & VERBOSE) == VERBOSE) {
            __o.___write(VERBOSE, tag, toJson(o, objects));
        }
        return o;
    }
    public static Object e(String tag, Object[] objects){
        if ((__o.__types & ERROR) == ERROR) {
            __o.___write(ERROR, tag, toJson(objects));
        }
        return objects[0];
    }
    public static Object w(String tag, Object[] objects){
        if ((__o.__types & WARNING) == WARNING) {
            __o.___write(WARNING, tag, toJson(objects));
        }
        return objects[0];
    }
    public static Object c(String tag, Object[] objects){
        if ((__o.__types & CAUTION) == CAUTION) {
            __o.___write(CAUTION, tag, toJson(objects));
        }
        return objects[0];
    }
    public static Object n(String tag, Object[] objects){
        if ((__o.__types & CAUTION) == CAUTION) {
            __o.___write(NOTICE, tag, toJson(objects));
        }
        return objects[0];
    }

    public static Object i(String tag, Object[] objects){
        if ((__o.__types & INFORMATION) == INFORMATION) {
            __o.___write(INFORMATION, tag, toJson(objects));
        }
        return objects[0];
    }
    public static Object d(String tag, Object[] objects){
        if ((__o.__types & DEBUG) == DEBUG) {
            __o.___write(DEBUG, tag, toJson(objects));
        }
        return objects[0];
    }
    public static Object f(String tag, Object[] objects){
        if ((__o.__types & FLOW) == FLOW) {
            __o.___write(FLOW, tag, toJson(objects));
        }
        return objects[0];
    }
    public static Object v(String tag, Object[] objects){
        if ((__o.__types & VERBOSE) == VERBOSE) {
            __o.___write(VERBOSE, tag, toJson(objects));
        }
        return objects[0];
    }

    public static String e(String tag, String o){ __o.___write(ERROR,tag, o); return o; }
    public static String w(String tag, String o){ __o.___write(WARNING,tag, o); return o; }
    public static String c(String tag, String o){ __o.___write(CAUTION,tag, o); return o; }
    public static String n(String tag, String o){ __o.___write(NOTICE,tag, o); return o; }
    public static String i(String tag, String o){ __o.___write(INFORMATION,tag, o); return o; }
    public static String d(String tag, String o){ __o.___write(DEBUG,tag, o); return o; }
    public static String f(String tag, String o){ __o.___write(FLOW,tag, o); return o; }
    public static String v(String tag, String o){ __o.___write(VERBOSE,tag, o); return o; }

    private static String ___str(int type){
        switch(type){
            case ERROR:         return "ERROR";
            case WARNING:       return "WARNING";
            case CAUTION:       return "CAUTION";
            case NOTICE:        return "NOTICE";
            case INFORMATION:   return "INFORMATION";
            case FLOW:          return "FLOW";
            case DEBUG:         return "DEBUG";
            case VERBOSE:       return "VERBOSE";
            default:            return "UNKNOWN";
        }
    }

    public static void add(Logger o){ if(o!=null && !__o.__loggers.contains(o)){ __o.__loggers.add(o); } }
    public static void depth(int depth){ __o.__depth = depth; }
    public static void enable(int types){ __o.__types |= types; }
    public static void disable(int types){ __o.__types &= (~types); }

    private int __types = (ERROR | WARNING | CAUTION | NOTICE | INFORMATION | FLOW | VERBOSE | DEBUG | HEADER | TAG);
    private int __depth = 4;
    private LinkedList<Logger> __loggers = new LinkedList<>();
    private ConsoleLog __console = null;

    private static String ___str(StackTraceElement e){
        return String.format(Locale.getDefault(),"%s:%d:%s:%s",
                e.getFileName(),
                e.getLineNumber(),
                e.getClassName(),
                e.getMethodName());
    }

    private void ___write(int type, String tag, String message){
        if((__types & type)==type)
        {
            if((__types & TAG)!=TAG) {
                tag = "";
            }
            if((__types & HEADER)==HEADER) {
                StackTraceElement[] elements = Thread.currentThread().getStackTrace();
                Calendar calendar = Calendar.getInstance();

                String str = String.format(Locale.getDefault(),
                        "[%04d/%02d/%02d %02d:%02d:%02d.%03d] %s %s:%d:%s %s %s",
                        calendar.get(Calendar.YEAR),
                        calendar.get(Calendar.MONTH),
                        calendar.get(Calendar.DAY_OF_MONTH),
                        calendar.get(Calendar.HOUR_OF_DAY),
                        calendar.get(Calendar.MINUTE),
                        calendar.get(Calendar.SECOND),
                        calendar.get(Calendar.MILLISECOND),
                        ___str(type),
                        ___str(elements[__depth]),
                        Thread.currentThread().getId(),
                        Thread.currentThread().getName(),
                        tag,
                        message);
                if(__loggers.size()>0) {
                    for (Logger o : __loggers) {
                        o.write(type, tag, str);
                    }
                } else {
                    if(__console==null){ __console = new ConsoleLog(); }
                    __console.write(type, tag, str);
                }
            } else {
                String str;
                if(tag!=null && tag.length()>0){
                    str = tag + " " + message;
                } else {
                    str = message;
                }
                if(__loggers.size()>0) {
                    for (Logger o : __loggers) {
                        o.write(type, tag, str);
                    }
                } else {
                    if(__console==null){ __console = new ConsoleLog(); }
                    __console.write(type, tag, str);
                }
            }
        }
    }

    public Log(){}
}
