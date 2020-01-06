package functional;

import com.google.gson.Gson;
import com.google.gson.GsonBuilder;
import novemberizing.Listener;

public class json {
    private static json __singleton = null;

    public static void init() {
        synchronized (json.class) {
            if(__singleton == null) {
                __singleton = new json();
            }
        }
    }

    public static void init(Listener<GsonBuilder> listener) {
        synchronized (json.class) {
            if(__singleton == null) {
                __singleton = new json(listener);
            }
        }
    }

    public static <T> String to(T o){ return __singleton.gson.toJson(o); }

    public static <T> T from(String s, Class<T> c){ return __singleton.gson.fromJson(s, c); }

    private final Gson gson;

    private json(){
        GsonBuilder builder = new GsonBuilder();
        builder.disableHtmlEscaping();
        builder.excludeFieldsWithoutExposeAnnotation();
        gson = builder.create();
    }

    private json(Listener<GsonBuilder> func){
        GsonBuilder builder = new GsonBuilder();
        builder.disableHtmlEscaping();
        builder.excludeFieldsWithoutExposeAnnotation();
        if(func != null) {
            func.on(builder);
        }
        gson = builder.create();
    }
}
