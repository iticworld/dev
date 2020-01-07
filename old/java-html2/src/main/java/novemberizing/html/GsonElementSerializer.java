package novemberizing.html;

import com.google.gson.*;
import org.jsoup.nodes.Element;

import java.lang.reflect.Type;

public class GsonElementSerializer implements JsonSerializer<Element> {
    @Override
    public JsonElement serialize(Element element, Type type, JsonSerializationContext context) {
        if(element != null){
            JsonObject object = new JsonObject();
            object.add("name", new JsonPrimitive(element.nodeName()));
            object.add("text", new JsonPrimitive(functional.html.to.string(element)));
            return object;
        }
        return JsonNull.INSTANCE;
    }
}
