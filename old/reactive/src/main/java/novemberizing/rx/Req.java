package novemberizing.rx;

import novemberizing.ds.*;
import novemberizing.ds.func.Single;
import novemberizing.rx.operators.Composer;
import novemberizing.rx.operators.Condition;
import novemberizing.rx.operators.Sync;
import novemberizing.util.Log;

import java.util.List;

import static novemberizing.ds.Constant.Infinite;

/**
 *
 * @author novemberizing, me@novemberizing.net
 * @since 2017. 1. 20.
 */
@SuppressWarnings({"WeakerAccess", "unused", "Convert2Lambda"})
public class Req<Z> implements Executable {
    private static final String Tag = "novemberizing.rx.req";

    public interface Factory<Z> extends novemberizing.ds.func.Empty<novemberizing.rx.Req<Z>> {}

    public static class Chain {
        private static final String Tag = novemberizing.rx.Req.Tag + ".chain";

        private novemberizing.rx.Req.Factory<?> __current = null;
        private novemberizing.ds.on.Empty onSuccess = null;
        private novemberizing.ds.on.Single<Throwable> onFail = null;
        private novemberizing.rx.Observable<?> __requested = null;

        private boolean __completed = false;
        private Throwable __exception = null;

        public Chain success(novemberizing.ds.on.Empty onSuccess) {
            Log.d(Tag, "");
            this.onSuccess = onSuccess;
            if (__completed && __exception != null) {
                this.onSuccess.on();
            }
            return this;
        }

        public Chain fail(novemberizing.ds.on.Single<Throwable> onFail) {
            Log.d(Tag, "");
            this.onFail = onFail;
            if (__exception != null) {
                this.onFail.on(__exception);
            }
            return this;
        }

        public Chain exec(novemberizing.rx.Req.Factory<?> request, novemberizing.rx.Req.Factory<?>... requests) {
            Log.d(Tag, "");
            __internal(request, 0, requests);
            return this;
        }

        public Chain exec(novemberizing.rx.Req.Factory<?>[] requests) {
            Log.d(Tag, "");
            __internal(requests[0], 1, requests);
            return this;
        }

        public Chain exec(List<novemberizing.rx.Req.Factory<?>> requests){
            Log.d(Tag, "");
            __internal(requests, 0);
            return this;
        }

        private void __internal(List<novemberizing.rx.Req.Factory<?>> requests, int n){
            Log.d(Tag, requests, n);
            if(n>=0 && n<requests.size()){
                novemberizing.rx.Req.Factory<?> factory = requests.get(n);
                __requested = factory!=null ? factory.call().success(()->__internal(requests, n+1)).fail(e->{
                    __exception = e;
                    if (onFail != null) {
                        onFail.on(__exception);
                    }
                }) : null;
            } else {
                __completed = true;
                if (onSuccess != null) {
                    onSuccess.on();
                }
            }
        }

        private void __internal(novemberizing.rx.Req.Factory<?> current, int n, novemberizing.rx.Req.Factory<?>[] next){
            Log.d(Tag, current, n , next);
            __requested = current.call().success(()-> {
                    if (n < next.length) {
                        __internal(next[n],n+1,next);
                    } else {
                        __completed = true;
                        if (onSuccess != null) {
                            onSuccess.on();
                        }
                    }
                }).fail(e->{
                    __exception = e;
                    if (onFail != null) {
                        onFail.on(__exception);
                    }
            });
        }

        public Chain(){
            Log.d(Tag, "");
        }
    }

    public static Chain Chain(novemberizing.rx.Req.Factory<?> request, novemberizing.rx.Req.Factory<?>... requests) {
        Log.f(Tag, "");
        return new Chain().exec(request, requests);
    }

    public static Chain Chain(novemberizing.rx.Req.Factory<?>[] requests) {
        return new Chain().exec(requests);
    }

    public static Chain Chain(List<novemberizing.rx.Req.Factory<?>> requests) {
        Log.f(Tag, "");
        return new Chain().exec(requests);
    }

    public static class Callback<Z> implements novemberizing.ds.on.Single<Z> {
        private static final String Tag = novemberizing.rx.Req.Tag + ".callback";

        private Req<Z> __req;

        public void next(Z o, boolean completed){
            Log.f(Tag, "");
            __req.next(o);
            if(completed){
                complete();
            }
        }
        public void error(Throwable e, boolean completed){
            Log.f(Tag, "");
            __req.error(e);
            if(completed){
                complete();
            }
        }
        public void next(Z o){
            Log.f(Tag, "");
            __req.next(o);
        }

        public void error(Throwable e){
            Log.f(Tag, "");
            __req.error(e);
        }
        public void complete(){
            Log.f(Tag, "");
            __req.complete();
        }
        public Callback(Req<Z> req){
            Log.f(Tag, "");
            __req = req;
        }

        @Override
        public void on(Z o) {
            Log.f(Tag, "");
            __req.next(o);
        }
    }

    protected Observable<Z> __completionPort;
    protected Replayer<Z> __replayer;
    protected Z __out;
    protected Observable<Z> __observable;
    protected final Req.Callback<Z> __callback = new Callback<>(this);
    protected novemberizing.ds.Exec<Callback<Z>> __req;
    protected boolean __completed;
    protected Executor __executor;
    protected boolean __executed;

    public Req(){
        Log.f(Tag, "");
        __req = null;
        __observable = null;
        __completionPort = null;
        __replayer = new Replayer<>(Infinite);
        __completed = false;

        __executor = null;
        __executed = false;
    }

    public Req(novemberizing.ds.on.Single<Req.Callback<Z>> on) {
        Log.f(Tag, "");
        __req = new On.Exec.Empty<>(on);
        __observable = null;
        __completionPort = null;
        __replayer = new Replayer<>(Infinite);
        __completed = false;

        __executor = null;
        __executed = false;
    }

    public <A> Req(A first, novemberizing.ds.on.Pair<A, Req.Callback<Z>> on) {
        Log.f(Tag, "");
        __req = new On.Exec.Single<>(new novemberizing.ds.tuple.Single<>(first), on);
        __observable = null;
        __completionPort = null;
        __replayer = new Replayer<>(Infinite);
        __completed = false;

        __executor = null;
        __executed = false;
    }

    public <A, B> Req(A first, B second, novemberizing.ds.on.Triple<A, B, Req.Callback<Z>> on) {
        Log.f(Tag, "");
        __req = new On.Exec.Pair<>(new novemberizing.ds.tuple.Pair<>(first, second), on);
        __observable = null;
        __completionPort = null;
        __replayer = new Replayer<>(Infinite);
        __completed = false;

        __executor = null;
        __executed = false;
    }

    public <A, B, C> Req(A first, B second, C third ,novemberizing.ds.on.Quadruple<A, B, C, Req.Callback<Z>> on) {
        Log.f(Tag, "");
        __req = new On.Exec.Triple<>(new novemberizing.ds.tuple.Triple<>(first, second, third), on);
        __observable = null;
        __completionPort = null;
        __replayer = new Replayer<>(Infinite);
        __completed = false;

        __executor = null;
        __executed = false;
    }

    public <A, B, C, D> Req(A first, B second, C third, D fourth, novemberizing.ds.on.Quintuple<A, B, C, D, Req.Callback<Z>> on) {
        Log.f(Tag, "");
        __req = new On.Exec.Quadruple<>(new novemberizing.ds.tuple.Quadruple<>(first, second, third, fourth), on);
        __observable = null;
        __completionPort = null;
        __replayer = new Replayer<>(Infinite);
        __completed = false;

        __executor = null;
        __executed = false;
    }

    public <A, B, C, D, E> Req(A first, B second, C third, D fourth, E fifth, novemberizing.ds.on.Sextuple<A, B, C, D, E, Req.Callback<Z>> on) {
        Log.f(Tag, "");
        __req = new On.Exec.Quintuple<>(new novemberizing.ds.tuple.Quintuple<>(first, second, third, fourth, fifth), on);
        __observable = null;
        __completionPort = null;
        __replayer = new Replayer<>(Infinite);
        __completed = false;

        __executor = null;
        __executed = false;
    }

    public Req(novemberizing.ds.func.Empty<Z> func){
        Log.f(Tag, "");
        __req = new Func.Exec.Empty<>(func);
        __observable = null;
        __completionPort = null;
        __replayer = new Replayer<>(Infinite);
        __completed = false;

        __executor = null;
        __executed = false;
    }

    public <A> Req(A first, novemberizing.ds.func.Single<A, Z> func) {
        Log.f(Tag, "");
        __req = new Func.Exec.Single<>(new novemberizing.ds.tuple.Single<>(first), func);
        __observable = null;
        __completionPort = null;
        __replayer = new Replayer<>(Infinite);
        __completed = false;

        __executor = null;
        __executed = false;
    }

    public <A, B> Req(A first, B second, novemberizing.ds.func.Pair<A, B, Z> func){
        Log.f(Tag, "");
        __req = new Func.Exec.Pair<>(new novemberizing.ds.tuple.Pair<>(first, second), func);
        __observable = null;
        __completionPort = null;
        __replayer = new Replayer<>(Infinite);
        __completed = false;

        __executor = null;
        __executed = false;
    }

    public <A, B, C> Req(A first, B second, C third ,novemberizing.ds.func.Triple<A, B, C, Z> func) {
        Log.f(Tag, "");
        __req = new Func.Exec.Triple<>(new novemberizing.ds.tuple.Triple<>(first, second, third), func);
        __observable = null;
        __completionPort = null;
        __replayer = new Replayer<>(Infinite);
        __completed = false;

        __executor = null;
        __executed = false;
    }

    public <A, B, C, D> Req(A first, B second, C third, D fourth ,novemberizing.ds.func.Quadruple<A, B, C, D, Z> func) {
        Log.f(Tag, "");
        __req = new Func.Exec.Quadruple<>(new novemberizing.ds.tuple.Quadruple<>(first, second, third, fourth), func);
        __observable = null;
        __completionPort = null;
        __replayer = new Replayer<>(Infinite);
        __completed = false;

        __executor = null;
        __executed = false;
    }

    public <A, B, C, D, E> Req(A first, B second, C third, D fourth, E fifth ,novemberizing.ds.func.Quintuple<A, B, C, D, E, Z> func){
        Log.f(Tag, "");
        __req = new Func.Exec.Quintuple<>(new novemberizing.ds.tuple.Quintuple<>(first, second, third, fourth,fifth), func);
        __observable = null;
        __completionPort = null;
        __replayer = new Replayer<>(Infinite);
        __completed = false;

        __executor = null;
        __executed = false;
    }

    synchronized protected boolean executed(){ return __executed; }

    @Override
    public void execute(Executor executor) {
        Log.f(Tag, "");
        synchronized (this){
            if(__executed){
                Log.d(Tag, "__executed==true");
                return;
            }
            __executed = true;
        }
        if(__executor!=null){
            Log.d(Tag, this, "__executor!=null");
        }
        __executor = executor;
        exec();
    }

    @Override
    public boolean completed() { return __completed; }


    protected void set(Observable<Z> observable) {
        __observable = observable;
    }

    protected void exec() {
        Log.f(Tag, "");
        try {
            __req.exec(__callback);
        } catch(Exception e){
            error(e);
            complete();
        }
    }

    protected void error(Throwable e) {
        Log.f(Tag, "");
        if(!__completed) {
            if(__observable!=null) {
                __observable.error(e);
            }
            if (__completionPort != null) {
                __completionPort.error(e);
            } else {
                __replayer.error(e);
            }
        }
    }

    protected void next(Z o) {
        Log.f(Tag, "");
        if(!__completed) {
            __out = o;
            if(__observable!=null) {
                __observable.emit(o);
            }
            if (__completionPort != null) {
                __completionPort.emit(o);
            } else {
                __replayer.add(o);
            }
        }
    }

    protected void complete() {
        Log.f(Tag, "");
        if(!__completed) {
            Executor executor = __executor;

            __completed = true;
            __executor = null;

            if(__observable!=null) {
                __observable.requests.decrease();
            }

            if (__completionPort != null) {
                __completionPort.complete();
            } else {
                __replayer.complete(__out);
            }

            if (executor != null) {
                executor.completed(this);
            } else {
                Log.d(Tag, "executor is null");
            }
        } else {
            Log.d(Tag, "completed");
        }
    }


    public Observable<Z> subscribe(Observer<Z> observer) {
        Log.f(Tag, "");
        if(__completionPort==null){
            __completionPort = new Observable<>(__replayer);
        }
        return __completionPort.subscribe(observer);
    }

    public Observable<Z> unsubscribe(Observer<Z> observer){
        Log.f(Tag, "");
        return __completionPort!=null ? __completionPort.unsubscribe(observer) : null;
    }
    public Observable<Z> unsubscribe(){
        Log.f(Tag, "");
        return __completionPort!=null ? __completionPort.unsubscribe() : null;
    }

    public Observable<Z> once(novemberizing.ds.on.Single<Z> f) {
        Log.f(Tag, "");
        return subscribe(new Subscribers.Just<Z>() {
            @Override
            public void onNext(Z o) {
                Log.f(Tag, "");
                f.on(o);
                subscribe(false);
            }
        });
    }

    public Observable<Z> on(novemberizing.ds.on.Single<Z> f) {
        Log.f(Tag, "");
        return subscribe(new Subscribers.Just<Z>() {
            @Override
            public void onNext(Z o) {
                Log.f(Tag, "");
                f.on(o);
            }
        });
    }

    public Observable<Z> exception(novemberizing.ds.on.Single<Throwable> f) {
        Log.f(Tag, "");
        return subscribe(new Subscribers.Just<Z>() {
            @Override
            public void onError(Throwable e) {
                Log.f(Tag, "");
                f.on(e);
            }
        });
    }

    public Observable<Z> fail(novemberizing.ds.on.Single<Throwable> f){
        Log.f(Tag, "");
        return subscribe(new Subscribers.Just<Z>() {
            @Override public void onError(Throwable e) {
                Log.f(Tag, "");
                f.on(e);
                subscribe(false);
            }
        });
    }

    public Observable<Z> success(novemberizing.ds.on.Single<Z> f){
        Log.f(Tag, "");
        return subscribe(new Subscribers.Just<Z>(){
            private Z item = null;
            private Throwable exception = null;
            @Override
            public void onNext(Z o) {
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

    public Observable<Z> success(novemberizing.ds.on.Empty f) {
        Log.f(Tag, "");
        return subscribe(new Subscribers.Just<Z>() {
            private Throwable exception = null;

            @Override
            public void onNext(Z o) {
                Log.f(Tag, "");
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
                    f.on();
                    subscribe(false);
                }
            }
        });
    }

    public Observable<Z> completion(novemberizing.ds.on.Empty f) {
        Log.f(Tag, "");
        return subscribe(new Subscribers.Just<Z>() {
            @Override
            public void onComplete() {
                Log.f(Tag, "");
                f.on();
            }
        });
    }

    public Observable<Z> on(novemberizing.ds.on.Single<Z> f, boolean once) {
        Log.f(Tag, "");
        return subscribe(new Subscribers.Just<Z>() {
            @Override
            public void onNext(Z o) {
                Log.f(Tag, "");
                f.on(o);
                if(once){ subscribe(false); }
            }
        });
    }

    public Observable<Z> exception(novemberizing.ds.on.Single<Throwable> f, boolean once) {
        Log.f(Tag, "");
        return subscribe(new Subscribers.Just<Z>() {
            @Override
            public void onError(Throwable e) {
                Log.f(Tag, "");
                f.on(e);
                if(once){ subscribe(false); }
            }
        });
    }


    public <U> Sync<Z, U> sync(Single<Z, U> f){
        Log.f(Tag, "");
        if(__completionPort==null){
            __completionPort = new Observable<>(__replayer);
        }
        return (Sync<Z, U>) __completionPort.subscribe(Operator.Sync(f));
    }

    public <U> Sync<Z, U> sync(novemberizing.ds.on.Pair<Operator.Task<Z, U>, Z> f) {
        Log.f(Tag, "");
        if(__completionPort==null){
            __completionPort = new Observable<>(__replayer);
        }
        return (Sync<Z, U>) __completionPort.subscribe(Operator.Sync(f));
    }

    public <U, V> Composer<Z, U, V> compose(Observable<U> secondary, novemberizing.ds.func.Pair<Z, U, V> f) {
        Log.f(Tag, "");
        if(__completionPort==null){
            __completionPort = new Observable<>(__replayer);
        }
        return (Composer<Z, U, V>) __completionPort.subscribe(Operator.Composer(secondary,f));
    }

    public <U, V> Condition<Z, U, V> condition(Observable<U> observable, novemberizing.ds.func.Pair<Z, U, Boolean> condition , novemberizing.ds.func.Pair<Z, U, V> f) {
        Log.f(Tag, "");
        if(__completionPort==null){
            __completionPort = new Observable<>(__replayer);
        }
        return (Condition<Z, U, V>) __completionPort.subscribe(Operator.Condition(observable,condition,f));
    }

    public <U> Operator<Z, U> condition(Single<Z, Boolean> condition, Single<Z, U> f) {
        Log.f(Tag, "");
        if(__completionPort==null){
            __completionPort = new Observable<>(__replayer);
        }
        return __completionPort.subscribe(Operator.Condition(condition, f));
    }

    public Observable<Z> replay(int limit) {
        Log.f(Tag, "");
        if(__completionPort==null){
            __completionPort = new Observable<>(__replayer);
        }
        if(limit==0){
            __completionPort.__replayer = null;
        } else if(__replayer==null){
            __completionPort.__replayer = new Replayer<>(limit);
        } else {
            __completionPort.__replayer.limit(limit);
        }
        return __completionPort;
    }
}
