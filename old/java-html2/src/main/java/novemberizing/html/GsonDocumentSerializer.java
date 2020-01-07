package novemberizing.html;

import com.google.gson.*;
import org.jsoup.nodes.Document;

import java.lang.reflect.Type;

public class GsonDocumentSerializer implements JsonSerializer<Document> {
    @Override
    public JsonElement serialize(Document document, Type type, JsonSerializationContext context) {
        JsonObject object = new JsonObject();
        object.add("name", new JsonPrimitive(document.nodeName()));
        object.add("text", new JsonPrimitive(document.outerHtml()));
        return object;
    }
}
