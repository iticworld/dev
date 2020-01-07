package novemberizing.rx;

import novemberizing.util.Log;

/**
 *
 * @author novemberizing, me@novemberizing.net
 * @since 2017. 1. 17.
 */
@SuppressWarnings("WeakerAccess")
public class Subscribers {
    public static class Just<T> extends Subscriber<T> {
        private String __tag = "just";
        private boolean __stacktrace = false;
        private boolean __subscribe = true;

        public String tag(){ return __tag; }

        public Just(){}

        public Just(String tag){ __tag = tag; }

        public Just(String tag, boolean stacktrace){
            __tag = tag;
            __stacktrace = stacktrace;
        }

        @Override public void onNext(T o) { Log.d(__tag, o); }

        @Override
        public void onError(Throwable e) {
            Log.e(__tag, "error", e.getMessage());
            if(__stacktrace){
                e.printStackTrace();
            }
        }

        @Override public void onComplete() { Log.d(__tag, "complete"); }

        @Override public void subscribe(boolean v){ __subscribe = v; }

        @Override public boolean subscribed(){ return __subscribe; }
    }

    public static <T> Just<T> Just(){ return new Just<>(); }

    public static <T> Just<T> Just(String tag){ return new Just<>(tag); }

    public static <T> Just<T> Just(String tag, boolean stacktrace){
        return new Just<>(tag, stacktrace);
    }
}
