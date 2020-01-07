package novemberizing.ds;

import novemberizing.util.Log;

/**
 *
 * @author novemberiizng, me@novemberizing.net
 * @since 2017. 1. 20.
 */
public interface On {
    class Exec {
        private static final String Tag = "novemberizing.ds.on.exec";
        public static class Empty<CALLBACK> implements novemberizing.ds.Exec<CALLBACK> {
            private static final String Tag = novemberizing.ds.On.Exec.Tag + ".empty";
            private novemberizing.ds.on.Single<CALLBACK> __on;

            @Override
            public  void exec(CALLBACK callback){
                Log.f(Tag, "");
                __on.on(callback);
            }

            public Empty(novemberizing.ds.on.Single<CALLBACK> on){
                Log.f(Tag, "");
                __on = on;
            }
        }

        public static class Single<A, CALLBACK> implements novemberizing.ds.Exec<CALLBACK> {
            private static final String Tag = novemberizing.ds.On.Exec.Tag + ".single";
            private novemberizing.ds.tuple.Single<A> __tuple;
            private novemberizing.ds.on.Pair<A, CALLBACK> __on;

            @Override
            public void exec(CALLBACK callback) {
                Log.f(Tag, "");
                __on.on(__tuple.first, callback);
            }

            public Single(novemberizing.ds.tuple.Single<A> tuple, novemberizing.ds.on.Pair<A, CALLBACK> on) {
                Log.f(Tag, "");
                __tuple = tuple;
                __on = on;
            }
        }

        public static class Pair<A, B, CALLBACK> implements novemberizing.ds.Exec<CALLBACK> {
            private static final String Tag = novemberizing.ds.On.Exec.Tag + ".pair";
            private novemberizing.ds.tuple.Pair<A, B> __tuple;
            private novemberizing.ds.on.Triple<A, B, CALLBACK> __on;

            @Override
            public void exec(CALLBACK callback) {
                Log.f(Tag, "");
                __on.on(__tuple.first, __tuple.second, callback);
            }

            public Pair(novemberizing.ds.tuple.Pair<A, B> tuple, novemberizing.ds.on.Triple<A, B, CALLBACK> on){
                Log.f(Tag, "");
                __tuple = tuple;
                __on = on;
            }
        }

        public static class Triple<A, B, C, CALLBACK> implements novemberizing.ds.Exec<CALLBACK> {
            private static final String Tag = novemberizing.ds.On.Exec.Tag + ".triple";
            private novemberizing.ds.tuple.Triple<A, B, C> __tuple;
            private novemberizing.ds.on.Quadruple<A, B, C, CALLBACK> __on;

            @Override
            public void exec(CALLBACK callback) {
                Log.f(Tag, "");
                __on.on(__tuple.first, __tuple.second, __tuple.third, callback);
            }

            public Triple(novemberizing.ds.tuple.Triple<A, B, C> tuple, novemberizing.ds.on.Quadruple<A, B, C, CALLBACK> on) {
                Log.f(Tag, "");
                __tuple = tuple;
                __on = on;
            }
        }

        public static class Quadruple<A, B, C, D, CALLBACK> implements novemberizing.ds.Exec<CALLBACK> {
            private static final String Tag = novemberizing.ds.On.Exec.Tag + ".quadruple";
            private novemberizing.ds.tuple.Quadruple<A, B, C, D> __tuple;
            private novemberizing.ds.on.Quintuple<A, B, C, D, CALLBACK> __on;

            @Override
            public void exec(CALLBACK callback) {
                Log.f(Tag, "");
                __on.on(__tuple.first, __tuple.second, __tuple.third, __tuple.fourth, callback);
            }

            public Quadruple(novemberizing.ds.tuple.Quadruple<A, B, C, D> tuple, novemberizing.ds.on.Quintuple<A, B, C, D, CALLBACK> on) {
                Log.f(Tag, "");
                __tuple = tuple;
                __on = on;
            }
        }

        public static class Quintuple<A, B, C, D, E, CALLBACK> implements novemberizing.ds.Exec<CALLBACK>  {
            private static final String Tag = novemberizing.ds.On.Exec.Tag + ".quintuple";
            private novemberizing.ds.tuple.Quintuple<A, B, C, D, E> __tuple;
            private novemberizing.ds.on.Sextuple<A, B, C, D, E, CALLBACK> __on;

            @Override
            public void exec(CALLBACK callback) {
                Log.f(Tag, "");
                __on.on(__tuple.first, __tuple.second, __tuple.third, __tuple.fourth, __tuple.fifth, callback);
            }

            public Quintuple(novemberizing.ds.tuple.Quintuple<A, B, C, D, E> tuple, novemberizing.ds.on.Sextuple<A, B, C, D, E, CALLBACK> on) {
                Log.f(Tag, "");
                __tuple = tuple;
                __on = on;
            }
        }
    }
}
