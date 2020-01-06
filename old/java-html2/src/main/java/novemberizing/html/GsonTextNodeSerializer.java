package novemberizing.html;

import com.google.gson.*;
import org.jsoup.nodes.TextNode;

import java.lang.reflect.Type;

public class GsonTextNodeSerializer implements JsonSerializer<TextNode> {
    @Override
    public JsonElement serialize(TextNode node, Type type, JsonSerializationContext context) {
        if(node != null) {
            return new JsonPrimitive(functional.html.to.string(node));
        }
        return JsonNull.INSTANCE;
    }
}
