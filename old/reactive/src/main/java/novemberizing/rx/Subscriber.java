package novemberizing.rx;

import novemberizing.util.Log;

import java.util.Collection;
import java.util.HashSet;
import java.util.LinkedList;

/**
 *
 * @author novemberizing, me@novemberizing.net
 * @since 2017. 1. 17.
 */
@SuppressWarnings({"WeakerAccess", "unused"})
public abstract class Subscriber<T> implements Observer<T> {
    private static final String Tag = "novemberizing.rx.subscriber";

    protected static class Observe<T> extends Task<T, T> {
        private static final String Tag = novemberizing.rx.Subscriber.Tag + ".observe";
        protected Observer<T> __observer;

        public Observe(T in, Observer<T> observer) {
            super(in);
            Log.f(Tag, "");
            __observer = observer;
        }

        @Override
        public void execute() {
            Log.f(Tag, "");
            try {
                __observer.onNext(in);
            } catch(Exception e){
                __observer.onError(e);
            }
            complete();
        }
    }

    protected static class Observes<T> extends Task<Collection<T>, Collection<T>> {
        private static final String Tag = novemberizing.rx.Subscriber.Tag + ".observes";
        protected Observer<T> __observer;

        public Observes(Collection<T> in, Observer<T> observer) {
            super(new LinkedList<>(in));
            Log.f(Tag, "");
            __observer = observer;
        }

        @Override
        public void execute() {
            Log.f(Tag, "");
            for(T o : in) {
                try {
                    __observer.onNext(o);
                } catch (Exception e) {
                    __observer.onError(e);
                }
            }
            complete();
        }
    }

    protected static class Error<T> extends Task<T, Throwable> {
        private static final String Tag = novemberizing.rx.Subscriber.Tag + ".error";
        protected Observer<T> __observer;
        protected Throwable __exception;

        public Error(Throwable e, Observer<T> observer) {
            super(null);
            Log.f(Tag, "");
            __observer = observer;
            __exception = e;
        }

        @Override
        public void execute() {
            Log.f(Tag, "");
            try {
                __observer.onError(__exception);
            } catch(Exception e){
                __observer.onError(e);
            }
            complete();
        }
    }

    protected static class Complete<T> extends Task<T, T> {
        private static final String Tag = novemberizing.rx.Subscriber.Tag + ".complete";
        protected Observer<T> __observer;

        public Complete(T in, Observer<T> observer) {
            super(in);
            Log.f(Tag, "");
            __observer = observer;
        }

        @Override
        public void execute() {
            Log.f(Tag, "");
            try {
                __observer.onComplete();
            } catch(Exception e){
                __observer.onError(e);
                Log.d(Tag, this, e);
            }
            complete();
        }
    }

    private final HashSet<Observable<T>> __observables = new HashSet<>();
    private Scheduler __observeOn = Scheduler.New();

    public Scheduler observeOn() { return __observeOn; }

    public Observer<T> observeOn(Scheduler scheduler){
        __observeOn = scheduler;
        return this;
    }

    public void onSubscribe(Observable<T> observable) {
        Log.f(Tag, "");
        if(observable!=null) {
            synchronized (__observables){
                if(!__observables.add(observable)){
                    Log.d(Tag, this, observable, "!__observables.add(observable)");
                }
            }
        } else {
            Log.d(Tag, this, null, "observable==null");
        }
    }

    public void onUnsubscribe(Observable<T> observable) {
        Log.f(Tag, "");
        if(observable!=null) {
            synchronized (__observables){
                if(!__observables.remove(observable)){
                    Log.d(Tag, this, observable, "!__observables.remove(observable)");
                }
            }
        } else {
            Log.d(Tag, this, null, "observable==null");
        }
    }
}
