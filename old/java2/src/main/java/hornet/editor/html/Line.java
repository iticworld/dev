package hornet.editor.html;

import com.google.gson.annotations.Expose;

public class Line {
    @Expose private String id;
    @Expose private Integer start;
    @Expose private Integer len;

    public String id(){ return id; }
    public Integer start(){ return start; }
    public Integer len(){ return len; }
    public Integer end(){ return start + len; }
}
