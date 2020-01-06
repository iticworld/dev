package novemberizing.ws.protocol.prosemirror;

import com.google.gson.annotations.Expose;
import novemberizing.html.server.DocumentRemoteLine;

import java.util.List;

public class ProseMirror {
    public static class Previous extends DocumentRemoteLine {}

    public static class Attr {
        @Expose private String id;
        @Expose private String align;
        @Expose private String color;
        @Expose private Integer level;

        public String id(){ return id; }
        public String align(){ return align; }
        public String color(){ return color; }
        public Integer level(){ return level; }
    }

    public static class Content {
        @Expose private String type;
        @Expose private String text;
        @Expose private Attr attrs;

        public String type(){ return type; }
        public String text(){ return text; }
        public Attr attrs(){ return attrs; }
        public String id(){ return attrs != null ? attrs.id() : null; }
        public String align(){ return attrs != null ? attrs.align() : null; }
        public String color(){ return attrs != null ?  attrs.color() : null; }
        public Integer level(){ return attrs != null ? attrs.level() : null; }
    }

    public static class Mark {
        @Expose private String type;
        @Expose private Attr attrs;

        public String type(){ return type; }
        public Attr attr(){ return attrs; }
        public String id(){ return attrs != null ? attrs.id() : null; }
        public String color(){ return attrs != null ? attrs.color() : null; }
        public Integer level(){ return attrs != null ? attrs.level() : null; }
        public String align(){ return attrs != null ? attrs.align() : null; }
    }

    public static class Payload {
        @Expose private Long version;
        @Expose private String clientID;
        @Expose private List<Step> steps;

        public Long version(){ return version; }
        public String username(){ return clientID; }
        public Step step(int index){ return steps != null && 0 <= index && index < steps.size() ? steps.get(index) : null; }
        public List<Step> steps(){ return steps; }
    }

    public static class Slice {
        @Expose private Integer openStart;
        @Expose private Integer openEnd;
        @Expose private List<Content> content;

        public int start(){ return openStart; }
        public int end(){ return openEnd; }
        public List<Content> contents(){ return content; }
        public Content content(int i){ return content != null && 0<=i && i < content.size() ? content.get(i) : null; }
    }

    public static class Step {
        @Expose private String stepType;
        @Expose private Integer from;
        @Expose private Integer to;
        @Expose private String id;
        @Expose private Slice slice;
        @Expose private Previous previous;
        @Expose private Mark mark;

        public String type(){ return stepType; }
        public int from(){ return from - previous.start() - 1; }
        public int to(){ return to - previous.start() - 1; }
        public Slice slice(){ return slice; }
        public String id(){ return id; }
        public Previous previous(){ return previous; }
        public Mark mark(){ return mark; }

        public Content content(int i){ return slice != null ? slice.content(i) : null; }
        public List<Content> contents(){ return slice != null ? slice.contents() : null; }

    }
}
