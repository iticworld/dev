package hornet.editor.html.server.json;

import com.google.gson.*;
import hornet.editor.html.server.RemoteDocument;

import java.lang.reflect.Type;

public class RemoteDocumentJsonSerializer implements JsonSerializer<RemoteDocument> {
    @Override
    public JsonElement serialize(RemoteDocument document, Type type, JsonSerializationContext context) {
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