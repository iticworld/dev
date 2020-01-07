package novemberizing.html.model.attr;

import com.google.gson.annotations.Expose;
import novemberizing.html.model.Attr;

import java.util.HashMap;
import java.util.Map;

/**
 * {@link Style#name} default attribute name
 * {@link Style#styles} styles map
 *
 * @todo implement constructor: construct with multiple styles.
 *
 * @author novemberizing <novemberizing@gmail.com>
 * @since 0.0.1
 */
public class Style extends Attr {
    public static final String name = "style";

    @Expose private Map<String, String> styles;

    /**
     * set style's attribute value
     * example code: {@code "color: #FFFFFF; font-size: 12pt;"}
     *
     * @param v {@link String} attribute's value
     */
    @Override
    public void value(String v) {
        if(!functional.string.empty(v)) {
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
                        throw new RuntimeException("invalid parameter exception");
                    }
                }
                value = v;
            } else {
                throw new RuntimeException("invalid parameter exception");
            }
        } else {
            clear();
        }
    }

    /**
     * generate attribute value using styles map
     */
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

    /**
     * retrieve style value related key.
     *
     * @param k {@link String} key
     * @return {@link String} return a found style's value
     */
    public String get(String k) { return functional.map.get(styles, k); }

    /**
     * put style
     *
     * @param k {@link String} key
     * @param v {@link String} value
     */
    public void put(String k, String v) {
        if(styles == null){
            styles = new HashMap<>();
        }
        styles.put(k, v);
        gen();
    }

    /**
     * clear styles
     */
    public void clear(){
        if(styles != null) {
            styles.clear();
        }
        gen();
    }

    /**
     * delete style related a key.
     *
     * @param k {@link String} key
     */
    public void del(String k) {
        if(styles != null) {
            styles.remove(k);
            gen();
        }
    }

    /**
     * retrieve equality result.
     *
     * @param o {@link Object} object
     * @return {@link boolean} return a result to equal.
     */
    @Override
    public boolean equals(Object o) {
        if(this == o) {
            return true;
        }
        if(o instanceof Style) {
            Style y = (Style) o;
            return functional.string.equal(value, y.value);
        }
        return false;
    }

    /**
     * default constructor
     */
    public Style(){
        super(Style.name);
        styles = null;
    }

    /**
     * constructor to create style with only one style.
     *
     * @param k {@link String} style key
     * @param v {@link String} style value
     */
    public Style(String k, String v) {
        super(Style.name);
        put(k, v);
    }
}
