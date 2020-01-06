package novemberizing.rx;

/**
 *
 * @author novemberizing, me@novemberizing.net
 * @since 2017. 1. 17.
 */
public interface Observer<T> {
    Scheduler observeOn();
    void onNext(T o);
    void onError(Throwable e);
    void onComplete();
    void subscribe(boolean v);
    boolean subscribed();
}
