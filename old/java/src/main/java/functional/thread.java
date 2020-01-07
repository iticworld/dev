package functional;

public class thread {
    public static StackTraceElement[] stacktrace(Thread current){ return current.getStackTrace(); }
    public static long id(Thread current){ return current.getId(); }
    public static StackTraceElement get(StackTraceElement[] elements, int depth){ return ((depth>=0 && elements!=null && depth < elements.length) ? elements[depth] : null); }
}
