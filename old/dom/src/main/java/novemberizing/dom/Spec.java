package novemberizing.dom;

import com.google.gson.annotations.Expose;
import com.google.gson.annotations.SerializedName;
import org.jsoup.nodes.Element;

public class Spec {
    public static final Spec h1 = new Spec("h1");
    public static final Spec h2 = new Spec("h2");
    public static final Spec h3 = new Spec("h3");
    public static final Spec h4 = new Spec("h4");
    public static final Spec h5 = new Spec("h5");
    public static final Spec h6 = new Spec("h6");
    public static final Spec p = new Spec("p");
    public static final Spec span = new Spec("span");
    public static final Spec pre = new Spec("pre");
    public static final Spec code = new Spec("code");
    public static final Spec blockquote = new Spec("blockquote");

    @SerializedName("name") @Expose protected String __name;
    @SerializedName("leaf") @Expose protected boolean __leaf;

    public String name(){ return __name; }

    public boolean match(Element element) {
        return functional.string.equal(element.nodeName(), __name);
    }

    public Spec(String name){
        this.__name = name;
        this.__leaf = false;
    }
}
