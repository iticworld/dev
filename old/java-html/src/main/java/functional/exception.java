package functional;

import novemberizing.Function;

@SuppressWarnings("unused")
public class exception {
    public static void on(Exception e) {}
    public static <IN, OUT> OUT safe(IN in, Function<IN, OUT> function, OUT v) {
        try {
            return function != null ? function.call(in) : v;
        } catch(Throwable e) {
            // check throwable
        }
        return v;
    }
}
