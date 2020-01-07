package functional;

import com.google.gson.*;
import novemberizing.Listener;

@SuppressWarnings("unused")
public class json {
    private static json __singleton = null;
    private static JsonParser __parser = null;

    public static void init(){
        synchronized (json.class) {
            if(__singleton == null) {
                __singleton = new json();
            }
            if(__parser == null){
                __parser = new JsonParser();
            }
        }
    }

    public static void init(Listener<GsonBuilder> listener){
        synchronized (json.class) {
            if(__singleton == null) {
                __singleton = new json(listener);
            }
            if(__parser == null){
                __parser = new JsonParser();
            }
        }
    }

    public static json get(){
        init();
        return __singleton;
    }

    public static JsonElement get(JsonObject object, String s, String... strings){
        if(object != null){
            if (object.has(s)) {
                JsonElement element = object.get(s);
                if(strings != null){
                    for(String str : strings){
                        if(element != null && element.isJsonObject()){
                            object = element.getAsJsonObject();
                            if(!object.has(str)){
                                return JsonNull.INSTANCE;
                            }
                            element = object.get(str);
                        }
                    }
                }
                return element;
            }
        }
        return JsonNull.INSTANCE;
    }

    public static JsonObject object(String o){
        JsonElement element = __parser.parse(o);
        return element != null && element.isJsonObject() ? element.getAsJsonObject() : null;
    }
    public static JsonObject object(JsonElement element){
        return element != null && element.isJsonObject() ? element.getAsJsonObject() : null;
    }
    public static JsonObject object(JsonObject object, String key){
        if(object != null){
            JsonElement element = object.get(key);
            if(element!= null){
                if(element.isJsonObject()) {
                    return element.getAsJsonObject();
                } else {
                    functional.log.e("element is not json primitive");
                }
            } else {
                functional.log.e("element == null: " + key);
            }
        }
        return null;
    }

    public static JsonObject object(JsonObject object, String key, String... keys) {
        if(object != null){
            JsonElement element = object.get(key);
            if(element != null){
                if(element.isJsonObject()){
                    return element.getAsJsonObject();
                }
                return null;
            }
            for(String v : keys){
                element = object.get(v);
                if(element != null){
                    if(element.isJsonObject()){
                        return element.getAsJsonObject();
                    }
                    return null;
                }
            }
        }
        return null;
    }

    public static String string(JsonElement element){
        return element != null && element.isJsonPrimitive() ? element.getAsString() : null;
    }
    public static String string(JsonObject object, String key){
        if(object != null){
            JsonElement element = object.get(key);
            if(element!= null){
                if(element.isJsonPrimitive()) {
                    return element.getAsString();
                } else {
                    functional.log.e("element is not json primitive");
                }
            }
        }
        return null;
    }

    public static String string(JsonObject object, String key, String... keys) {
        if(object != null){
            JsonElement element = object.get(key);
            if(element != null){
                if(element.isJsonPrimitive()){
                    return element.getAsString();
                }
                return null;
            }
            for(String v : keys){
                element = object.get(v);
                if(element != null){
                    if(element.isJsonPrimitive()){
                        return element.getAsString();
                    }
                    return null;
                }
            }
        }
        return null;
    }

    public static Boolean bool(JsonObject object, String key){
        if(object != null){
            JsonElement element = object.get(key);
            if(element!= null){
                if(element.isJsonPrimitive()) {
                    JsonPrimitive primitive = element.getAsJsonPrimitive();
                    if(primitive.isBoolean()){
                        return primitive.getAsBoolean();
                    } else {
                        functional.log.e("primitive is not boolean");
                    }
                } else {
                    functional.log.e("element is not json primitive");
                }
            } else {
                functional.log.e("element == null");
            }
        }
        return null;
    }

    public static Boolean bool(JsonObject object, String key, String... keys) {
        if(object != null){
            JsonElement element = object.get(key);
            if(element != null){
                if(element.isJsonPrimitive()){
                    JsonPrimitive primitive = element.getAsJsonPrimitive();
                    if(primitive.isBoolean()){
                        return primitive.getAsBoolean();
                    } else {
                        functional.log.e("primitive is not boolean");
                    }
                }
                return null;
            }
            for(String v : keys){
                element = object.get(v);
                if(element != null){
                    JsonPrimitive primitive = element.getAsJsonPrimitive();
                    if(primitive.isBoolean()){
                        return primitive.getAsBoolean();
                    } else {
                        functional.log.e("primitive is not boolean");
                    }
                    return null;
                }
            }
        }
        return null;
    }

    public static JsonArray array(JsonObject object, String key){
        if(object != null){
            JsonElement element = object.get(key);
            if(element!= null){
                if(element.isJsonArray()) {
                    return element.getAsJsonArray();
                } else {
                    functional.log.e("element is not json primitive");
                }
            } else {
                functional.log.e("element == null");
            }
        }
        return null;
    }

    public static JsonArray array(JsonObject object, String key, String... keys) {
        if(object != null){
            JsonElement element = object.get(key);
            if(element != null){
                if(element.isJsonArray()) {
                    return element.getAsJsonArray();
                } else {
                    functional.log.e("element is not json primitive");
                }
                return null;
            }
            for(String v : keys){
                element = object.get(v);
                if(element != null){
                    if(element.isJsonArray()) {
                        return element.getAsJsonArray();
                    } else {
                        functional.log.e("element is not json primitive");
                    }
                    return null;
                }
            }
        }
        return null;
    }

    public static Integer integer(JsonElement element){
        if(element != null && element.isJsonPrimitive()){
            JsonPrimitive primitive = element.getAsJsonPrimitive();
            return primitive.isNumber() ? primitive.getAsInt() : null;
        }
        return null;
    }

    public static Integer integer(JsonObject object, String key){
        if(object != null){
            JsonElement element = object.get(key);
            if(element!= null){
                if(element.isJsonPrimitive()) {
                    JsonPrimitive primitive = element.getAsJsonPrimitive();
                    if(primitive.isNumber()){
                        return primitive.getAsInt();
                    }
                } else {
                    functional.log.e("element is not json primitive: " + key);
                }
            } else {
                functional.log.e("element == null");
            }
        }
        return null;
    }

    public static Integer integer(JsonObject object, String key, String... keys) {
        if(object != null){
            JsonElement element = object.get(key);
            if(element != null){
                if(element.isJsonPrimitive()){
                    return element.getAsInt();
                }
                return null;
            }
            for(String v : keys){
                element = object.get(v);
                if(element != null){
                    if(element.isJsonPrimitive()){
                        return element.getAsInt();
                    }
                    return null;
                }
            }
        }
        return null;
    }

    public static boolean exist(JsonObject object, String key){ return object != null && object.has(key); }

    public static boolean exist(JsonObject object, boolean all, String s, String... strings){
        if(object != null) {
            if(all) {
                if(!object.has(s)){
                    return false;
                }
                if(strings != null){
                    for(String str : strings){
                        if(!object.has(str)){
                            return false;
                        }
                    }
                }
                return true;
            } else {
                if(object.has(s)){
                    return true;
                }
                if(strings != null){
                    for(String str : strings){
                        if(object.has(str)){
                            return true;
                        }
                    }
                }
                return false;
            }
        }
        return false;
    }

    public static JsonElement create(String v){ return v != null ? new JsonPrimitive(v) : JsonNull.INSTANCE; }
    public static JsonElement create(Boolean v){ return v != null ? new JsonPrimitive(v) : JsonNull.INSTANCE; }
    public static JsonElement create(Integer v){ return v != null ? new JsonPrimitive(v) : JsonNull.INSTANCE; }

    public static <T> String from(T o){ return __singleton.gson.toJson(o); }
    public static <T> T to(String json, Class<T> c){
        return __singleton.gson.fromJson(json, c);
    }
    public static <T> T to(byte[] bytes, Class<T> c){ return functional.json.to(new String(bytes), c); }
    public static String value(String v){ return v!=null ? "\"" + v.replace("\\", "\\\\").replace("\'", "\\\'").replace("\"", "\\\"").replace("\r\n", "\\n").replace("\n", "\\n") + "\"" : "null"; }

    private final Gson gson;

    private Gson __create(){
        // JsonUtils.
        GsonBuilder builder = new GsonBuilder();
        builder.disableHtmlEscaping();
        builder.excludeFieldsWithoutExposeAnnotation();
        // builder.setPrettyPrinting();
        return builder.create();
    }

    private Gson __create(Listener<GsonBuilder> function){
        GsonBuilder builder = new GsonBuilder();
        builder.disableHtmlEscaping();
        builder.excludeFieldsWithoutExposeAnnotation();
        // builder.setPrettyPrinting();
        if(function!=null){
            function.on(builder);
        }
        return builder.create();
    }

    private json(){ gson = __create(); }

    private json(Listener<GsonBuilder> function){ gson = __create(function); }
}
