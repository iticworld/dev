package novemberizing.html.model;

import com.google.gson.annotations.Expose;

import java.util.HashMap;
import java.util.Locale;
import java.util.Map;

public class Style extends Attr {
    @Expose private Map<String, String> styles;

    public void put(String key, String value) {
        if(styles == null){
            styles = new HashMap<>();
        }
        styles.put(key, value);
    }

    public String str() {
        if(!functional.map.empty(styles)) {
            StringBuilder builder = new StringBuilder();
            for(Map.Entry<String, String> entry : styles.entrySet()) {
                builder.append(String.format(Locale.getDefault(), "%s: %s;", entry.getKey(), entry.getKey()));
            }
            this.value = builder.toString();
        }
        return super.str();
    }

    public Style(){
        super("style");
    }
}