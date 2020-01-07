package novemberizing.html.model;

import com.google.gson.annotations.Expose;

import java.util.List;

public class Mark {
    @Expose private String tag;
    @Expose private List<Attr> attrs;

    public String tag(){ return tag; }
    public List<Attr> attrs(){ return attrs; }
}

