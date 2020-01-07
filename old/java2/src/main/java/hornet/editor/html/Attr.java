package hornet.editor.html;

import com.google.gson.annotations.Expose;

public class Attr {
    @Expose protected String name;
    @Expose protected String value;

    public String name(){ return name; }
    public String value(){ return value; }

    public void name(String v){ name = v; }
    public void value(String v){ value = v; }

    public Attr(){
        this.name = null;
        this.value = null;
    }

    public Attr(String name, String value) {
        this.name = name;
        this.value = value;
    }
}
