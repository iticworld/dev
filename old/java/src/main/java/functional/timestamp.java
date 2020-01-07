package functional;

public class timestamp {
    public static long get(){ return System.currentTimeMillis(); }
    public static long current(){ return System.currentTimeMillis(); }
    public static long after(long millisecond){ return System.currentTimeMillis() + millisecond; }
    public static long before(long millisecond){ return System.currentTimeMillis() - millisecond; }
}
