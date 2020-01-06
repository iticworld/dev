package novemberizing.rx.operators;

import novemberizing.rx.Operator;
import novemberizing.rx.Subscriber;
import novemberizing.util.Log;

import java.util.Collection;
import java.util.LinkedList;

/**
 *
 * @author novemberizing, me@novemberizing.net
 * @since 2017. 1. 18.
 */
@SuppressWarnings({"WeakerAccess", "DanglingJavadoc", "unused", "Convert2Lambda"})
public class Block {
    private static final String Tag = "novemberizing.rx.operators.block";

    public static class Op<T, Z> extends Operator<T, Z> {
        private static final String Tag = novemberizing.rx.operators.Block.Tag + ".op";

        protected boolean __ret = false;
        protected Header<T, ?, Z> __header = null;

        public boolean ret(){ return __ret; }

        protected void ret(boolean v){ __ret = v; }

        @Override
        protected void on(Task<T, Z> task, T in) {
            Log.f(Tag, "");
            __header.in(task, in);
        }

        protected Block.Header.On<T, Z> header(Block.Header.On<T, Z> on) {
            Log.f(Tag, "");
            __header = on;
            return on;
        }

        protected <U> Block.Header.Run<T, U, Z> header(Block.Header.Run<T, U, Z> run) {
            Log.f(Tag, "");
            __header = run;
            return run;
        }

        protected <U> Block.Header.Func<T, U, Z> header(Block.Header.Func<T, U, Z> func) {
            Log.f(Tag, "");
            __header = func;
            return func;
        }
    }

    public static <T, Z> Block.Header.On<T, Z> begin() {
        Log.f(Tag, "");
        Block.Op<T, Z> block = new Block.Op<>();
        return block.header(new Block.Header.On<>(block));
    }

    public static <T, U, Z> Block.Header.Run<T, U, Z> begin(novemberizing.ds.func.Empty<U> f) {
        Log.f(Tag, "");
        Block.Op<T, Z> block = new Block.Op<>();
        return block.header(new Block.Header.Run<>(block,f));
    }

    public static <T, U, Z> Block.Header.Func<T, U, Z> begin(novemberizing.ds.func.Single<T, U> f) {
        Log.f(Tag, "");
        Block.Op<T, Z> block = new Block.Op<>();
        return block.header(new Block.Header.Func<>(block,f));
    }

    public static class Next<T, V, Z> extends Subscriber<V> {
        private static final String Tag = novemberizing.rx.operators.Block.Tag + ".next";
        protected Operator.Task<T, Z> __task;
        protected Line<T, V, ?, Z> __next;
        protected final LinkedList<V> __items = new LinkedList<>();
        protected novemberizing.ds.func.Pair<T, V, Boolean> __condition;
        protected novemberizing.ds.func.Pair<T, V, V> __composer;
        protected boolean __subscribe = true;

        public Next(Operator.Task<T, Z> task, Block.Line<T, V, ?, Z> next, novemberizing.ds.func.Pair<T, V, Boolean> condition, novemberizing.ds.func.Pair<T, V, V> composer){
            Log.f(Tag, "");
            __task = task;
            __next = next;
            __condition = condition;
            __composer = composer;
        }

        @Override
        public void onNext(V o) {
            Log.f(Tag, "");
            synchronized (this){
                if(__condition==null || __condition.call(__task.in(), o)) {
                    __items.addLast(__composer!=null ? __composer.call(__task.in(), o) : o);
                }
            }
        }

        @Override
        public void onError(Throwable e) {
            Log.e(Tag, e);
        }

        @Override
        public void onComplete() {
            Log.f(Tag, "");
            if(__next!=null){
                if(__items.size()>0){
                    __next.bulk(__task, __items);
                } else {
                    Log.d(Tag, "return void");
                    __task.complete();
                }
            } else {
                Log.d(Tag, "return void");
                __task.complete();
            }
        }

        @Override public void subscribe(boolean v){ __subscribe = v; }

        @Override public boolean subscribed(){ return __subscribe; }
    }

    public static class Complete<T, Z> extends Subscriber<Z> {
        private static final String Tag = novemberizing.rx.operators.Block.Tag + ".complete";

        protected Operator.Task<T, Z> __task;
        protected boolean __subscribe = true;

        public Complete(Operator.Task<T, Z> task) {
            Log.f(Tag, "");
            __task = task;
        }

        @Override
        public void onNext(Z o) {
            Log.f(Tag, "");
            __task.next(o);
        }

        @Override
        public void onError(Throwable e) {
            Log.f(Tag, "");
            __task.error(e);
        }

        @Override
        public void onComplete() {
            Log.f(Tag, "");
            __task.complete();
        }

        @Override public void subscribe(boolean v){ __subscribe = v; }

        @Override public boolean subscribed(){ return __subscribe; }
    }


    public static class Line<T, U, V, Z> {
        private static final String Tag = novemberizing.rx.operators.Block.Tag + ".line";

        protected Operator<U, V> __operator;
        protected Block.Op<T, Z> __parent;
        protected Line<T, V, ?, Z> __next;
        protected novemberizing.ds.func.Pair<T, V, V> __composer;
        protected novemberizing.ds.func.Pair<T, V, Boolean> __condition;

        public Line(Block.Op<T, Z> parent, Operator<U, V> operator){
            Log.f(Tag, "");
            __parent = parent;
            __operator = operator;
            __next = null;
            __composer = null;
            __condition = null;
        }

        public Line<T, U, V, Z> composer(novemberizing.ds.func.Pair<T, V, V> composer){
            Log.f(Tag, "");
            __composer = composer;
            return this;
        }

        public Line<T, U, V, Z> condition(novemberizing.ds.func.Pair<T, V, Boolean> condition){
            Log.f(Tag, "");
            __condition = condition;
            return this;
        }

        public <W> Line<T, V, W, Z> next(Operator<V, W> op){
            Log.f(Tag, "");
            Line<T, V, W, Z> next = new Line<>(__parent, op);
            __next = next;
            return next;
        }

        public <W> Line<T, V, W, Z> next(novemberizing.ds.func.Single<V,W> f){
            Log.f(Tag, "");
            return next(Operator.Op(f));
        }

        public Block.Op<T, Z>  ret(){
            Log.f(Tag, "");
            if(__parent.ret()){
                Log.e(Tag, new RuntimeException("__parent.ret()"));
                return __parent;
            }
            __parent.ret(true);
            return __parent;
        }

        public Block.Op<T, Z>  ret(novemberizing.ds.func.Empty<Z> f){
            Log.f(Tag, "");
            return ret(new novemberizing.ds.func.Single<V, Z>(){
                @Override
                public Z call(V o) {
                    Log.f(Tag, "");
                    return f.call();
                }
            });
        }

        public Block.Op<T, Z>  ret(novemberizing.ds.func.Single<V,Z> f){
            Log.f(Tag, "");
            return ret(Operator.Op(f));
        }

        public Block.Op<T, Z>  ret(Operator<V,Z> op){
            Log.f(Tag, "");
            if(__parent.ret()){
                Log.e(Tag, new RuntimeException("__parent.ret()"));
                return __parent;
            }
            __parent.ret(true);
            __next = new Footer<>(__parent, op);
            return __parent;
        }

        protected void exec(Operator.Task<T, Z> task, U o){
            Log.f(Tag, "");
            __operator.exec(o).subscribe(new Next<>(task, __next, __condition, __composer));
        }
        protected void bulk(Operator.Task<T, Z> task, Collection<U> items){
            Log.f(Tag, "");
            __operator.bulk(items).subscribe(new Next<>(task, __next, __condition, __composer));
        }
    }

    public static class Footer<T, V, Z> extends Block.Line<T, V, Z, Z> {
        private static final String Tag = novemberizing.rx.operators.Block.Tag + ".footer";

        public Footer(Op<T, Z> parent, Operator<V, Z> operator) {
            super(parent, operator);
            Log.f(Tag, "");
        }

        protected void exec(Operator.Task<T, Z> task, V o){
            Log.f(Tag, "");
            __operator.exec(o).subscribe(new Block.Complete<>(task));
        }
        protected void bulk(Operator.Task<T, Z> task, Collection<V> items){
            Log.f(Tag, "");
            __operator.bulk(items).subscribe(new Block.Complete<>(task));
        }

    }

    protected static abstract class Header<T, U, Z> {
        private static final String Tag = novemberizing.rx.operators.Block.Tag + ".header";

        protected Block.Op<T, Z> __parent;
        protected Line<T, U, ?, Z> __next;
        protected novemberizing.ds.func.Pair<T, U, U> __composer;
        protected novemberizing.ds.func.Pair<T, U, Boolean> __condition;

        public Header(Op<T, Z> parent) {
            Log.f(Tag, "");
            __parent = parent;
        }

        protected abstract void in(Operator.Task<T, Z> task, T in);

        public Header<T, U, Z> composer(novemberizing.ds.func.Pair<T, U, U> composer) {
            Log.f(Tag, "");
            __composer = composer;
            return this;
        }

        public Header<T, U, Z> condition(novemberizing.ds.func.Pair<T, U, Boolean> condition) {
            Log.f(Tag, "");
            __condition = condition;
            return this;
        }

        public <V> Line<T, U, V, Z> next(Operator<U, V> op) {
            Log.f(Tag, "");
            Line<T, U, V, Z> next = new Line<>(__parent, op);
            __next = next;
            return next;
        }

        public <V> Line<T, U, V, Z> next(novemberizing.ds.func.Single<U, V> f){
            Log.f(Tag, "");
            return next(Operator.Op(f));
        }

        public Block.Op<T, Z>  ret(){
            Log.f(Tag, "");
            if(__parent.ret()){
                Log.e(Tag, new RuntimeException("__parent.ret()"));
                return __parent;
            }
            __parent.ret(true);
            return __parent;
        }

        public Block.Op<T, Z>  ret(novemberizing.ds.func.Empty<Z> f) {
            Log.f(Tag, "");
            return ret(new novemberizing.ds.func.Single<U, Z>(){
                @Override
                public Z call(U o) {
                    Log.f(Tag, "");
                    return f.call();
                }
            });
        }

        public Block.Op<T, Z>  ret(novemberizing.ds.func.Single<U ,Z> f){
            Log.f(Tag, "");
            return ret(Operator.Op(f));
        }

        public Block.Op<T, Z>  ret(Operator<U ,Z> op){
            Log.f(Tag, "");
            if(__parent.ret()){
                Log.e(Tag, new RuntimeException("__parent.ret()"));
                return __parent;
            }
            __parent.ret(true);
            __next = new Footer<>(__parent, op);
            return __parent;
        }

        public static class Func<T, U, Z> extends Header<T, U, Z> {
            private static final String Tag = novemberizing.rx.operators.Block.Tag + ".func";

            private novemberizing.ds.func.Single<T, U> __func;

            public Func(Op<T, Z> parent, novemberizing.ds.func.Single<T, U> f) {
                super(parent);
                Log.f(Tag, "");
                __func = f;
            }

            @Override
            protected void in(Operator.Task<T, Z> task, T in) {
                Log.f(Tag, "");
                __next.exec(task, __func.call(in));
            }
        }

        public static class Run<T, U, Z> extends Header<T, U, Z> {
            private static final String Tag = novemberizing.rx.operators.Block.Tag + ".run";

            private novemberizing.ds.func.Empty<U> __func;

            public Run(Op<T, Z> parent, novemberizing.ds.func.Empty<U> f) {
                super(parent);
                Log.f(Tag, "");
                __func = f;
            }

            @Override
            protected void in(Operator.Task<T, Z> task, T in) {
                Log.f(Tag, "");
                __next.exec(task, __func.call());
            }
        }

        public static class On<T, Z> extends Header<T, T, Z> {
            private static final String Tag = novemberizing.rx.operators.Block.Tag + ".on";
            public On(Op<T, Z> parent) {
                super(parent);
                Log.f(Tag, "");
            }

            @Override
            protected void in(Operator.Task<T, Z> task, T in) {
                Log.f(Tag, "");
                __next.exec(task, in);
            }
        }
    }
}
