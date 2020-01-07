package novemberizing.html.server.json;

import com.google.gson.*;
import novemberizing.html.server.DocumentRemoteRoot;

import java.lang.reflect.Type;

public class GsonDocumentRemoteRootSerializer implements JsonSerializer<DocumentRemoteRoot> {
    @Override
    public JsonElement serialize(DocumentRemoteRoot document, Type type, JsonSerializationContext context) {
        if(document != null) {
            JsonObject object = new JsonObject();
            object.add("id", new JsonPrimitive(document.id()));
            object.add("content", new JsonPrimitive(document.out()));
            object.add("version", new JsonPrimitive(document.version()));
            return object;
        }
        return JsonNull.INSTANCE;
    }
}
