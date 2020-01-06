package novemberizing.rx;

import com.google.gson.annotations.Expose;
import novemberizing.ds.func.Single;
import novemberizing.rx.functions.OnComplete;
import novemberizing.rx.functions.OnError;
import novemberizing.rx.functions.OnNext;
import novemberizing.rx.operators.Completion;
import novemberizing.rx.operators.Composer;
import novemberizing.rx.operators.Condition;
import novemberizing.rx.operators.Sync;
import novemberizing.util.Log;

import java.util.Collection;
import java.util.Iterator;
import java.util.LinkedHashSet;
import java.util.LinkedList;

/**
 *
 * @author novemberizing, me@novemberizing.net
 * @since 2017. 1. 17.
 */
@SuppressWarnings({"WeakerAccess", "unused"})
public class Observable<T> {
    private static final String Tag = "novemberizing.rx.observable";

    protected static class Emit<T> extends Task<T, T> {
        private static final String Tag = novemberizing.rx.Observable.Tag + ".emit";
        protected Observable<T> __observable;

        public Emit(T in, Observable<T> observable) {
            super(in);
            Log.f(Tag, "");
            __observable = observable;
        }

        @Override
        public void execute() {
            Log.f(Tag, "");
            Scheduler current = Scheduler.Self();
            synchronized (__observable.__observers) {
                next(__observable.__set(in));
                Iterator<Observer<T>> it = __observable.__observers.iterator();
                while(it.hasNext()){
                    Observer<T> observer = it.next();
                    if(observer.subscribed()) {
                        Scheduler observeOn = observer.observeOn();
                        if (current == observeOn) {
                            try {
                                observer.onNext(__observable.get());
                            } catch(Exception e){
                                observer.onError(e);
                            }
                        } else {
                            observeOn.dispatch(new Subscriber.Observe<>(__observable.get(), observer));
                        }
                    } else {
                        Log.d(Tag, "observer.subscribed()==false");
                        it.remove();
                    }
                }
            }
            complete();
        }

        @Override
        protected void complete() {
            Log.f(Tag, "");
            if(!__completed){
                __observable.emits.decrease();
            }
            super.complete();
        }
    }

    protected static class Emits<T> extends Task<Collection<T>, T> {
        private static final String Tag = novemberizing.rx.Observable.Tag + ".emits";
        protected Observable<T> __observable;

        public Emits(Collection<T> in, Observable<T> observable) {
            super(in);
            Log.f(Tag, "");
            __observable = observable;
        }

        @Override
        public void execute() {
            Log.f(Tag, "");
            Scheduler current = Scheduler.Self();
            synchronized (__observable.__observers) {
                for(T item : in) {
                    next(__observable.__set(item));
                    Iterator<Observer<T>> it = __observable.__observers.iterator();
                    while(it.hasNext()){
                        Observer<T> observer = it.next();
                        if(observer.subscribed()) {
                            Scheduler observeOn = observer.observeOn();
                            if (current == observeOn) {
                                try {
                                    observer.onNext(__observable.get());
                                } catch (Exception e) {
                                    observer.onError(e);
                                }
                            } else {
                                observeOn.dispatch(new Subscriber.Observe<>(__observable.get(), observer));
                            }
                        } else {
                            Log.d(Tag, "observer.subscribed()==false");
                            it.remove();
                        }
                    }
                }
            }
            complete();
        }

        @Override
        protected void complete() {
            Log.f(Tag, "");
            if(!__completed){
                __observable.emits.decrease(in.size());
            }
            super.complete();
        }
    }

    @SuppressWarnings("ThrowableNotThrown")
    protected static class Error<T> extends Task<T, T> {
        private static final String Tag = novemberizing.rx.Observable.Tag + ".error";
        protected Observable<T> __observable;
        protected Throwable __exception;

        public Error(Throwable e, Observable<T> observable) {
            super(null);
            Log.f(Tag, "");
            __observable = observable;
            __exception = e;
        }


        @Override
        public void execute() {
            Log.f(Tag, "");
            Scheduler current = Scheduler.Self();
            synchronized (__observable.__observers) {
                Iterator<Observer<T>> it = __observable.__observers.iterator();
                while(it.hasNext()){
                    Observer<T> observer = it.next();
                    if(observer.subscribed()) {
                        Scheduler observeOn = observer.observeOn();
                        if (current == observeOn) {
                            observer.onError(__exception);
                        } else {
                            observeOn.dispatch(new Subscriber.Error<>(__exception, observer));
                        }
                    } else {
                        Log.d(Tag, "observer.subscribed()==false");
                        it.remove();
                    }
                }
            }
            __observable.exception(__observable.exception(__exception));
            complete();
        }
    }

    protected static class Complete<T> extends Task<T, T> {
        private static final String Tag = novemberizing.rx.Observable.Tag + ".complete";
        protected Observable<T> __observable;

        public Complete(Observable<T> observable) {
            super(null);
            Log.f(Tag, "");
            __observable = observable;
        }

        @Override
        public void execute() {
            Log.f(Tag, "");
            Scheduler current = Scheduler.Self();
            synchronized (__observable.__observers) {
                Iterator<Observer<T>> it = __observable.__observers.iterator();
                while(it.hasNext()){
                    Observer<T> observer = it.next();
                    if(observer.subscribed()) {
                        Scheduler observeOn = observer.observeOn();
                        if (current == observeOn) {
                            observer.onComplete();
                        } else {
                            observeOn.dispatch(new Subscriber.Complete<>(__observable.get(), observer));
                        }
                    } else {
                        Log.f(Tag, "observer.subscribed()==false");
                        it.remove();
                    }
                }
            }
            __observable.done();
            complete();
        }
    }

    public static class Requests<T> extends Counter {
        private static final String Tag = novemberizing.rx.Observable.Tag + ".requests";
        private boolean __once = false;

        public void once(boolean v){ __once = v; }

        public boolean once(){ return __once; }
    }

    private final LinkedHashSet<Observer<T>> __observers = new LinkedHashSet<>();
    @Expose public final Counter emits = new Counter();
    @Expose public final Requests<T> requests = new Requests<>();
    @Expose protected T __current;
    protected Replayer<T> __replayer;
    protected Scheduler __observableOn = Scheduler.New();
    protected boolean __completed = false;

    protected Observable(Replayer<T> replayer){
        Log.f(Tag, "");
        __replayer = replayer;
        __current = __replayer.last();
    }

    public Observable(){
        Log.f(Tag, "");
        __replayer = null;
        __current = null;
    }

    protected Scheduler observableOn(){ return __observableOn; }

    public Observable<T> observableOn(Scheduler scheduler){
        __observableOn = scheduler;
        return this;
    }

    protected T snapshot(T o){ return o; }

    protected T get() { return snapshot(__current); }
    protected T __set(T v) {
        Log.f(Tag, "");
        if(__completed) {
            if(__replayer!=null) {
                __replayer.clear();
            }
            __completed = false;
        }
        __current = snapshot(v);
        if(__replayer!=null) {
            __replayer.add(snapshot(__current));
        }
        return snapshot(__current);
    }

    protected Throwable exception(Throwable e) {
        Log.f(Tag, "");
        if(__replayer!=null){
            __replayer.error(e);
        }
        __completed = true;
        return e;
    }

    protected T done() {
        Log.f(Tag, "");
        if(__replayer!=null){
            __replayer.complete(__current);
        }
        __completed = true;
        unsubscribe();
        return __current;
    }

    private Req<T> __req(Req<T> req){
        Log.f(Tag, "");
        requests.increase();
        req.set(this);
        Scheduler current = Scheduler.Self();
        if (current == __observableOn) {
            req.exec();
        } else {
            __observableOn.dispatch(req);
        }
        return req;
    }

    protected Req<T> req(Req<T> req){
        Log.f(Tag, "");
        if(requests.__once){
           if(requests.get()==0) {
               req = __req(req);
           } else {
               req.set(this);
               requests.increase();
               req.error(new RuntimeException("already requested"));
               req.complete();
           }
        } else {
            req = __req(req);
        }
        return req;
    }

    protected Task<T, T> emit(T o){
        Log.f(Tag, "");
        synchronized (this) {
            __current = snapshot(o);
        }
        emits.increase();
        Emit<T> task = new Emit<>(o, this);
        __observableOn.dispatch(task);

        return task;
    }

    @SafeVarargs
    private final Task<Collection<T>, T> foreach(T o, T... items){
        Log.f(Tag, "");
        LinkedList<T> objects = new LinkedList<>();
        objects.addLast(o);
        for(T item : items){
            objects.addLast(item);
        }
        emits.increase(objects.size());
        Emits<T> task = new Emits<>(objects, this);
        __observableOn.dispatch(task);

        return task;
    }

    private Task<Collection<T>, T> foreach(T[] items){
        Log.f(Tag, "");
        LinkedList<T> objects = new LinkedList<>();
        for(T item : items){
            objects.addLast(item);
        }
        emits.increase(objects.size());
        Emits<T> task = new Emits<>(objects, this);
        __observableOn.dispatch(task);

        return task;
    }

    private Task<Collection<T>, T> bulk(Collection<T> items){
        Log.f(Tag, "");
        emits.increase(items.size());
        Emits<T> task = new Emits<>(items, this);
        __observableOn.dispatch(task);

        return task;
    }

    protected Task<T, T> error(Throwable e){
        Log.f(Tag, "");
        Error<T> task = new Error<>(e, this);
        __observableOn.dispatch(task);
        return task;
    }

    protected Task<T, T> complete(){
        Log.f(Tag, "");
        Complete<T> task = new Complete<>(this);
        __observableOn.dispatch(task);
        return task;
    }

    protected void onStart(){
        Log.f(Tag, "");
    }

    protected void onStop(){
        Log.f(Tag, "");
    }

    public Observable<T> subscribe(OnNext<T> onNext) {
        Log.f(Tag, "");
        return subscribe(new Subscribers.Just<T>(){
            @Override
            public void onNext(T o){
                Log.f(Tag, "");
                if(onNext!=null){
                    onNext.on(o);
                }
            }
        });
    }

    public Observable<T> subscribe(OnNext<T> onNext, OnError onError) {
        Log.f(Tag, "");
        return subscribe(new Subscribers.Just<T>(){
            @Override
            public void onNext(T o){
                Log.f(Tag, "");
                if(onNext!=null){
                    onNext.on(o);
                }
            }
            @Override
            public void onError(Throwable e){
                Log.f(Tag, "");
                if(onError!=null){
                    onError.on(e);
                }
            }
        });
    }

    public Observable<T> subscribe(OnNext<T> onNext, OnComplete onComplete) {
        Log.f(Tag, "");
        return subscribe(new Subscribers.Just<T>(){
            @Override
            public void onNext(T o) {
                Log.f(Tag, "");
                if(onNext!=null) {
                    onNext.on(o);
                }
            }
            @Override
            public void onComplete() {
                Log.f(Tag, "");
                if(onComplete!=null) {
                    onComplete.on();
                }
            }
        });
    }

    public Observable<T> subscribe(OnNext<T> onNext, OnError onError, OnComplete onComplete) {
        Log.f(Tag, "");
        return subscribe(new Subscribers.Just<T>(){
            @Override
            public void onNext(T o){
                Log.f(Tag, "");
                if(onNext!=null) {
                    onNext.on(o);
                }
            }
            @Override
            public void onError(Throwable e) {
                Log.f(Tag, "");
                if(onError!=null) {
                    onError.on(e);
                }
            }

            @Override
            public void onComplete() {
                Log.f(Tag, "");
                if(onComplete!=null) {
                    onComplete.on();
                }
            }
        });
    }

    public Observable<T> subscribe(Observer<T> observer){
        Log.f(Tag, "");
        if(observer!=null){
            synchronized (__observers){
                if(__observers.add(observer)){
                    onSubscribe(observer,this);
                    if(__replayer!=null){
                        __replayer.replay(observer);
                    }
                    if(__observers.size()==1){
                        onStart();
                    }
                } else {
                    Log.d(Tag, this, observer, "__observers.add(observer)==false");
                }
            }
        } else {
            Log.d(Tag, this, "observer==null");
        }
        return this;
    }

    public <Z> Operator<T, Z> subscribe(Single<T, Z> f){
        Log.f(Tag, "");
        return subscribe(Operator.Op(f));
    }

    public <Z> Operator<T, Z> subscribe(novemberizing.ds.on.Pair<Operator.Task<T, Z>,T> f){
        Log.f(Tag, "");
        return subscribe(Operator.Op(f));
    }

    public <Z> Operator<T, Z> subscribe(Operator<T, Z> operator){
        Log.f(Tag, "");
        if(operator!=null){
            synchronized (__observers){
                if(__observers.add(operator)){
                    onSubscribe(operator,this);
                    if(__replayer!=null){
                        __replayer.replay(operator);
                    }
                    if(__observers.size()==0){
                        onStop();
                    }
                } else {
                    Log.d(Tag, this, operator, "__observers.add(observer)==false");
                }
            }
        } else {
            Log.d(Tag, this, "observer==null");
        }
        return operator;
    }

    public Observable<T> unsubscribe(Observer<T> observer){
        Log.f(Tag, "");
        if(observer!=null){
            synchronized (__observers){
                if(__observers.remove(observer)){
                    onUnsubscribe(observer,this);
                } else {
                    Log.d(Tag, this, observer, "__observers.remove(observer)==false");
                }
            }
        } else {
            Log.d(Tag, this, "observer==null");
        }
        return this;
    }

    public Observable<T> unsubscribe(){
        Log.f(Tag, "");
        synchronized (__observers) {
            Iterator<Observer<T>> it = __observers.iterator();
            while(__observers.size()>0 && it.hasNext()){
                Observer<T> observer = it.next();
                unsubscribe(observer);
                it = __observers.iterator();
            }
        }
        return this;
    }

    public <S> Operator<S, T> previous(Operator<S, T> op){
        Log.f(Tag, "");
        return (Operator<S, T>) op.subscribe(new Subscriber<T>() {
            private boolean __subscribe = true;
            @Override
            public void onNext(T o) {
                Log.f(Tag, "");
                emit(o);
            }

            @Override
            public void onError(Throwable e) {
                Log.f(Tag, "");
                error(e);
            }

            @Override
            public void onComplete() {
                Log.f(Tag, "");
                complete();
            }

            @Override public void subscribe(boolean v){ __subscribe = v; }
            @Override public boolean subscribed(){ return __subscribe; }
        });
    }

    public <S> Operator<S, T> previous(Single<S, T> f){
        Log.f(Tag, "");
        return previous(Operator.Op(f));
    }

    public <S> Operator<S, T> previous(novemberizing.ds.on.Pair<Operator.Task<S, T>, S> f){
        Log.f(Tag, "");
        return previous(Operator.Op(f));
    }

    public <Z> Operator<T, Z> next(Single<T, Z> f){
        Log.f(Tag, "");
        return subscribe(f);
    }
    public <Z> Operator<T, Z> next(Operator<T, Z> op){
        Log.f(Tag, "");
        return subscribe(op);
    }
    public <Z> Operator<T, Z> next(novemberizing.ds.on.Pair<Operator.Task<T, Z>,T> f){
        Log.f(Tag, "");
        return subscribe(f);
    }

    public Observable<T> once(novemberizing.ds.on.Single<T> f){
        Log.f(Tag, "");
        return subscribe(new Subscribers.Just<T>() {
            @Override
            public void onNext(T o) {
                Log.f(Tag, "");
                f.on(o);
                subscribe(false);
            }
        });
    }

    public Observable<T> on(novemberizing.ds.on.Single<T> f){
        Log.f(Tag, "");
        return subscribe(new Subscribers.Just<T>() {
            @Override
            public void onNext(T o) {
                Log.f(Tag, "");
                f.on(o);
            }
        });
    }

    public Observable<T> exception(novemberizing.ds.on.Single<Throwable> f){
        Log.f(Tag, "");
        return subscribe(new Subscribers.Just<T>() {
            @Override
            public void onError(Throwable e) {
                Log.f(Tag, "");
                f.on(e);
            }
        });
    }

    public Observable<T> fail(novemberizing.ds.on.Single<Throwable> f) {
        Log.f(Tag, "");
        return subscribe(new Subscribers.Just<T>() {
            @Override public void onError(Throwable e) {
                Log.f(Tag, "");
                f.on(e);
                subscribe(false);
            }
        });
    }

    public Observable<T> success(novemberizing.ds.on.Empty f) {
        Log.f(Tag, "");
        return subscribe(new Subscribers.Just<T>(){
            private Throwable exception = null;
            @Override public void onNext(T o) {
                Log.f(Tag, "");
            }
            @Override public void onError(Throwable e){
                Log.f(Tag, "");
                exception = e;
            }
            @Override public void onComplete() {
                Log.f(Tag, "");
                if (exception == null) {
                    f.on();
                    subscribe(false);
                }
            }
        });
    }

    public Observable<T> success(novemberizing.ds.on.Single<T> f) {
        Log.f(Tag, "");
        return subscribe(new Subscribers.Just<T>(){
            private T item = null;
            private Throwable exception = null;
            @Override
            public void onNext(T o) {
                Log.f(Tag, "");
                item = o;
            }
            @Override
            public void onError(Throwable e) {
                Log.f(Tag, "");
                exception = e;
            }
            @Override
            public void onComplete() {
                Log.f(Tag, "");
                if (exception == null) {
                    f.on(item);
                    subscribe(false);
                }
            }
        });
    }

    public Observable<T> completion(novemberizing.ds.on.Empty f) {
        Log.f(Tag, "");
        return subscribe(new Subscribers.Just<T>() {
            @Override
            public void onComplete() {
                Log.f(Tag, "");
                f.on();
            }
        });
    }

    public Observable<T> on(novemberizing.ds.on.Single<T> f, boolean once) {
        Log.f(Tag, "");
        return subscribe(new Subscribers.Just<T>() {
            @Override
            public void onNext(T o) {
                Log.f(Tag, "");
                f.on(o);
                if(once){ subscribe(false); }
            }
        });
    }

    public Observable<T> exception(novemberizing.ds.on.Single<Throwable> f, boolean once){
        Log.f(Tag, "");
        return subscribe(new Subscribers.Just<T>() {
            @Override
            public void onError(Throwable e) {
                Log.f(Tag, "");
                f.on(e);
                if(once){ subscribe(false); }
            }
        });
    }

    public <Z> Sync<T, Z> sync(Single<T, Z> f){
        Log.f(Tag, "");
        return (Sync<T, Z>) subscribe(Operator.Sync(f));
    }

    public <Z> Sync<T, Z> sync(novemberizing.ds.on.Pair<Operator.Task<T, Z>,T> f){
        Log.f(Tag, "");
        return (Sync<T, Z>) subscribe(Operator.Sync(f));
    }

    public <U, Z> Composer<T, U, Z> compose(Observable<U> secondary, novemberizing.ds.func.Pair<T, U, Z> f){
        Log.f(Tag, "");
        return (Composer<T, U, Z>) subscribe(Operator.Composer(secondary,f));
    }

    public <U, Z> Condition<T, U, Z> condition(Observable<U> observable, novemberizing.ds.func.Pair<T, U, Boolean> condition , novemberizing.ds.func.Pair<T, U, Z> f){
        Log.f(Tag, "");
        return (Condition<T, U, Z>) subscribe(Operator.Condition(observable,condition,f));
    }

    public <Z> Operator<T, Z> condition(Single<T, Boolean> condition, Single<T, Z> f){
        Log.f(Tag, "");
        return subscribe(Operator.Condition(condition, f));
    }

    public <U, Z> Completion<T, U, Z> completion(Observable<U> observable, novemberizing.ds.func.Pair<T, U, Boolean> condition , novemberizing.ds.func.Pair<T, U, Z> f){
        Log.f(Tag, "");
        return (Completion<T, U, Z>) subscribe(Operator.Completion(observable,condition,f));
    }

    public <U, Z> Completion<T, U, Z> completion(Observable<U> observable, novemberizing.ds.func.Pair<T, U, Z> f){
        Log.f(Tag, "");
        return (Completion<T, U, Z>) subscribe(Operator.Completion(observable, null,f));
    }

    public Observable<T> replay(int limit){
        Log.f(Tag, "");
        if(limit==0){
            __replayer = null;
        } else if(__replayer==null){
            __replayer = new Replayer<>(limit);
        } else {
            __replayer.limit(limit);
        }
        return this;
    }

    public static <T> Task<T, T> Emit(Observable<T> observable, T o){
        Log.f(Tag, "");
        return observable.emit(o);
    }

    @SafeVarargs
    public static <T> Task<Collection<T>, T> Foreach(Observable<T> observable, T o, T... items){
        Log.f(Tag, "");
        return observable.foreach(o, items);
    }

    public static <T> Task<Collection<T>, T> Foreach(Observable<T> observable, T[] items){
        Log.f(Tag, "");
        return observable.foreach(items);
    }

    public static <T> Task<Collection<T>,T> Bulk(Observable<T> observable, Collection<T> list){
        Log.f(Tag, "");
        return observable.bulk(list);
    }


    public static <T> Task<T, T> Complete(Observable<T> observable) {
        Log.f(Tag, "");
        return observable.complete();
    }

    public static <T> Task<T, T> Error(Observable<T> observable, Throwable e){
        Log.f(Tag, "");
        return observable.error(e);
    }

    protected static <T> void onSubscribe(Observer<T> observer, Observable<T> observable){
        Log.f(Tag, "");
        if(observer instanceof Operator){
            Operator<T, ?> operator = (Operator<T, ?>) observer;
            operator.onSubscribe(observable);
        } else if(observer!=null){
            Subscriber<T> subscriber = (Subscriber<T>) observer;
            subscriber.onSubscribe(observable);
        }
    }

    protected static <T> void onUnsubscribe(Observer<T> observer, Observable<T> observable) {
        Log.f(Tag, "");
        if(observer instanceof Operator){
            Operator<T, ?> operator = (Operator<T, ?>) observer;
            operator.onUnsubscribe(observable);
        } else if(observer!=null){
            Subscriber<T> subscriber = (Subscriber<T>) observer;
            subscriber.onUnsubscribe(observable);
        }
    }
}
