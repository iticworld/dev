package novemberizing.ds;

import novemberizing.util.Log;

/**
 *
 * @author novemberiizng, me@novemberizing.net
 * @since 2017. 1. 20.
 */
public interface Func {
    class Exec {
        private static final String Tag = "novemberizing.ds.func.exec";
        public static class Empty<Z, CALLBACK extends novemberizing.ds.on.Single<Z>> implements novemberizing.ds.Exec<CALLBACK> {
            private static final String Tag = novemberizing.ds.Func.Exec.Tag + ".empty";
            private novemberizing.ds.func.Empty<Z> __func;

            @Override
            public void exec(CALLBACK callback){
                Log.f(Tag, "");
                callback.on(__func.call());
            }

            public Empty(novemberizing.ds.func.Empty<Z> func){
                Log.f(Tag, "");
                __func = func;
            }
        }
        /**
         *
         * @author novemberiizng, me@novemberizing.net
         * @since 2017. 1. 20.
         */
        public static class Single<A, Z, CALLBACK extends novemberizing.ds.on.Single<Z>> implements novemberizing.ds.Exec<CALLBACK> {
            private static final String Tag = novemberizing.ds.Func.Exec.Tag + ".single";
            private novemberizing.ds.tuple.Single<A> __tuple;
            private novemberizing.ds.func.Single<A, Z> __func;

            @Override
            public void exec(CALLBACK callback){
                Log.f(Tag, "");
                callback.on(__func.call(__tuple.first));
            }

            public Single(novemberizing.ds.tuple.Single<A> tuple, novemberizing.ds.func.Single<A, Z> func){
                Log.f(Tag, "");
                __tuple = tuple;
                __func = func;
            }
        }

        public static class Pair<A, B, Z, CALLBACK extends novemberizing.ds.on.Single<Z>> implements novemberizing.ds.Exec<CALLBACK> {
            private static final String Tag = novemberizing.ds.Func.Exec.Tag + ".pair";
            private novemberizing.ds.tuple.Pair<A, B> __tuple;
            private novemberizing.ds.func.Pair<A, B, Z> __func;

            @Override
            public void exec(CALLBACK callback){
                Log.f(Tag, "");
                callback.on(__func.call(__tuple.first, __tuple.second));
            }

            public Pair(novemberizing.ds.tuple.Pair<A, B> tuple, novemberizing.ds.func.Pair<A, B, Z> func){
                Log.f(Tag, "");
                __tuple = tuple;
                __func = func;
            }
        }

        public static class Triple<A, B, C, Z, CALLBACK extends novemberizing.ds.on.Single<Z>> implements novemberizing.ds.Exec<CALLBACK> {
            private static final String Tag = novemberizing.ds.Func.Exec.Tag + ".triple";
            private novemberizing.ds.tuple.Triple<A, B, C> __tuple;
            private novemberizing.ds.func.Triple<A, B, C, Z> __func;

            @Override
            public void exec(CALLBACK callback){
                Log.f(Tag, "");
                callback.on(__func.call(__tuple.first, __tuple.second, __tuple.third));
            }

            public Triple(novemberizing.ds.tuple.Triple<A, B, C> tuple, novemberizing.ds.func.Triple<A, B, C, Z> func){
                Log.f(Tag, "");
                __tuple = tuple;
                __func = func;
            }
        }

        public static class Quadruple<A, B, C, D, Z, CALLBACK extends novemberizing.ds.on.Single<Z>> implements novemberizing.ds.Exec<CALLBACK> {
            private static final String Tag = novemberizing.ds.Func.Exec.Tag + ".quadruple";
            private novemberizing.ds.tuple.Quadruple<A, B, C, D> __tuple;
            private novemberizing.ds.func.Quadruple<A, B, C, D, Z> __func;

            @Override
            public void exec(CALLBACK callback){
                Log.f(Tag, "");
                callback.on(__func.call(__tuple.first, __tuple.second, __tuple.third, __tuple.fourth));
            }

            public Quadruple(novemberizing.ds.tuple.Quadruple<A, B, C, D> tuple, novemberizing.ds.func.Quadruple<A, B, C, D, Z> func){
                Log.f(Tag, "");
                __tuple = tuple;
                __func = func;
            }
        }

        public static class Quintuple<A, B, C, D, E, Z, CALLBACK extends novemberizing.ds.on.Single<Z>> implements novemberizing.ds.Exec<CALLBACK> {
            private static final String Tag = novemberizing.ds.Func.Exec.Tag + ".quintuple";
            private novemberizing.ds.tuple.Quintuple<A, B, C, D, E> __tuple;
            private novemberizing.ds.func.Quintuple<A, B, C, D, E, Z> __func;

            @Override
            public void exec(CALLBACK callback){
                Log.f(Tag, "");
                callback.on(__func.call(__tuple.first, __tuple.second, __tuple.third, __tuple.fourth, __tuple.fifth));
            }

            public Quintuple(novemberizing.ds.tuple.Quintuple<A, B, C, D, E> tuple, novemberizing.ds.func.Quintuple<A, B, C, D, E, Z> func){
                Log.f(Tag, "");
                __tuple = tuple;
                __func = func;
            }
        }
    }
}
