package hornet.editor.html.attr;

import com.google.gson.annotations.Expose;
import hornet.editor.html.Attr;

import java.util.HashMap;
import java.util.Map;

public class Style extends Attr {
    @Expose private HashMap<String, String> styles;

    private void gen() {
        if(functional.map.exist(styles)) {
            StringBuilder builder = new StringBuilder();
            for(Map.Entry<String, String> entry : styles.entrySet()) {
                builder.append(entry.getKey());
                builder.append(": ");
                builder.append(entry.getValue());
                builder.append("; ");
            }
            if(builder.length() > 0) {
                builder.deleteCharAt(builder.length() - 1);
            }
            value = builder.toString();
        } else {
            value = "";
        }
    }

    @Override
    public void value(String v) {
        if(functional.string.exist(v)) {
            if(styles != null) {
                styles.clear();
            } else {
                styles = new HashMap<>();
            }
            String[] array = v.split(";");
            if(array.length > 0) {
                for(String s : array) {
                    String[] pair = s.split(":", 2);
                    if(pair.length == 2) {
                        styles.put(pair[0].trim(), pair[1].trim());
                    } else {
                        throw new RuntimeException("");
                    }
                }
            }
            value = v;
        } else {
            clear();
        }
    }

    public String get(String k){ return functional.map.get(styles, k); }

    public void put(String k, String v){
        if(styles == null) {
            styles = new HashMap<>();
        }
        styles.put(k, v);
        gen();
    }

    public void clear() {
        if(styles != null) {
            styles.clear();
        }
        gen();
    }

    public void del(String k){
        if(styles != null) {
            styles.remove(k);
            gen();
        }
    }

    @Override
    public boolean equals(Object o){
        if(this == o) {
            return true;
        }
        if(o instanceof Style) {
            Style y = (Style) o;
            return functional.string.equal(value, y.value);
        }
        return false;
    }

    public Style() {
        super("style", "");
        styles = null;
    }

    public Style(String k, String v) {
        super("style", "");
        put(k, v);
    }
}
