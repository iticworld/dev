package novemberizing.rx.requests;

import novemberizing.rx.Req;
import novemberizing.rx.Scheduler;
import novemberizing.util.Log;

import java.util.ArrayList;
import java.util.Collection;
import java.util.Collections;

/**
 *
 * @author novemberizing, me@novemberizing.net
 * @since 2017. 2. 12.
 */
@SuppressWarnings({"WeakerAccess", "Convert2Lambda", "unused"})
public class Multi extends novemberizing.rx.Req<Object> {
    private static final String Tag = "novemberizing.rx.requests.multi";

    public static Multi Gen(novemberizing.rx.Req.Factory<?> req, novemberizing.rx.Req.Factory<?>... requests) {
        Log.f(Tag, "");
        Multi multi = new Multi();
        return multi.add(req, requests);
    }

    public static Multi Gen(novemberizing.rx.Req.Factory<?>[] requests){
        Log.f(Tag, "");
        Multi multi = new Multi();
        return multi.add(requests);
    }

    public static <T> Multi Gen(Collection<novemberizing.rx.Req.Factory<T>> requests){
        Log.f(Tag, "");
        Multi multi = new Multi();
        return multi.add(requests);
    }

    public static novemberizing.rx.Req.Factory<Object> Req(novemberizing.rx.Req.Factory<?> req, novemberizing.rx.Req.Factory<?>... requests) {
        Log.f(Tag, "");
        return new novemberizing.rx.Req.Factory<Object>(){
            @Override
            public Req<Object> call() {
                Log.f(Tag, "");
                novemberizing.rx.Req<Object> executable = Gen(req,requests);
                executable.execute(Scheduler.Local());
                return executable;
            }
        };
    }

    public static novemberizing.rx.Req.Factory<Object> Req(novemberizing.rx.Req.Factory<?>[] requests) {
        Log.f(Tag, "");
        return new novemberizing.rx.Req.Factory<Object>(){
            @Override
            public Req<Object> call() {
                Log.f(Tag, "");
                novemberizing.rx.Req<Object> executable = Gen(requests);
                executable.execute(Scheduler.Local());
                return executable;
            }
        };
    }

    public static <T> novemberizing.rx.Req.Factory<Object> Req(Collection<novemberizing.rx.Req.Factory<T>> requests) {
        Log.f(Tag, "");
        return new novemberizing.rx.Req.Factory<Object>(){
            @Override
            public Req<Object> call() {
                Log.f(Tag, "");
                novemberizing.rx.Req<Object> executable = Gen(requests);
                executable.execute(Scheduler.Local());
                return executable;
            }
        };
    }

    private ArrayList<novemberizing.rx.Req.Factory<?>> __requests = new ArrayList<>();

    public Multi add(novemberizing.rx.Req.Factory<?> req, novemberizing.rx.Req.Factory<?>... requests){
        Log.f(Tag, "");
        if(req!=null){
            __requests.add(req);
        }
        Collections.addAll(__requests, requests);
        return this;
    }

    public Multi add(novemberizing.rx.Req.Factory<?>[] requests){
        Log.f(Tag, "");
        Collections.addAll(__requests, requests);
        return this;
    }

    public <T> Multi add(Collection<novemberizing.rx.Req.Factory<T>> requests){
        Log.f(Tag, "");
        for(novemberizing.rx.Req.Factory<?> request : requests){
            __requests.add(request);
        }
        return this;
    }

    public Multi() {
        Log.f(Tag, "");
        __req = new novemberizing.ds.On.Exec.Empty<>(new novemberizing.ds.on.Single<novemberizing.rx.Req.Callback<Object>>(){
            @Override
            public void on(Callback<Object> o) {
                Log.f(Tag, "");
                novemberizing.rx.Req.Chain(__requests)
                        .success(new novemberizing.ds.on.Empty(){
                            @Override public void on() {
                                Log.f(Tag, "success");
                                __callback.complete();
                            }
                        })
                        .fail(new novemberizing.ds.on.Single<Throwable>(){
                            @Override public void on(Throwable e) {
                                Log.f(Tag, "fail");
                                __callback.error(e);
                                __callback.complete();
                            }
                        });
            }
        });
    }
}
